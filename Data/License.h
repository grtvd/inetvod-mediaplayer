/* License.h */

/******************************************************************************/
/******************************************************************************/
#ifndef LicenseH
#define LicenseH

#include "DataID.h"
#include "Object.h"

namespace asi
{

/******************************************************************************/

enum LicenseMethod
{
	lm_URLOnly,
	lm_LicenseServer
};

CStr32 ConvertLicenseMethodToString(LicenseMethod sct);
LicenseMethod ConvertStringToLicenseMethod(const char* sct);

/******************************************************************************/

class License : public Streamable
{
protected:
	LicenseMethod fLicenseMethod;
	CStrVar fShowURL;
	CStrVar fLicenseURL;

protected:
	License(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~License() {}

private:
	License(const License&);						// don't allow copy constructor
	const License& operator=(const License&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new License(filerPtr)); }

	virtual const char* className() const { return "License"; }

	virtual void clear() { Object::clear(); fLicenseMethod = lm_URLOnly; fShowURL.clear(); fLicenseURL.clear(); }

	// Data Get/Set Methods
	LicenseMethod getLicenseMethod() const { return fLicenseMethod; }
	const char* getShowURL() const { return fShowURL.c_str(); }
	const char* getLicenseURL() const { return fLicenseURL.c_str(); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<License>;
};

class LicensePtr : public RefCountPtr<License>
{
public:
	LicensePtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<License>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<License&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class LicenseConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return License::newInstance(filerPtr); }
};

/******************************************************************************/

}; //namespace asi

#endif	//LicenseH
/******************************************************************************/
/******************************************************************************/
