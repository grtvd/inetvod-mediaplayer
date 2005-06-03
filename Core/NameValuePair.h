/* NameValuePair.h */

/******************************************************************************/
/******************************************************************************/
#ifndef NameValuePairH
#define NameValuePairH

namespace asi
{

/******************************************************************************/

class NameValuePair;	//forward reference
typedef RefCountPtr<NameValuePair> NameValuePairPtr;

class NameValuePair : public RefCountObject
{
protected:
	CStr64 fName;
	CStrVar fValue;

protected:
	NameValuePair(const char* name = NULL, const char* value = NULL)
		{ fName.copy(name); fValue.copy(value); }
	virtual ~NameValuePair() {}

private:
	NameValuePair(const NameValuePair&);						// don't allow copy constructor
	const NameValuePair& operator=(const NameValuePair&);		// or operator=

public:
	// Construction Methods
	static NameValuePairPtr newInstance(const char* name = NULL, const char* value = NULL)
		{ return NameValuePairPtr(new NameValuePair(name, value)); }

	// Data Get/Set Methods
	void setName(const char* name) { fName.copy(name); }
	const char* getName() const { return fName.c_str(); }

	void setValue(const char* value) { fValue.copy(value); }
	const char* getValue() const { return fValue.c_str(); }

	friend class RefCountPtr<NameValuePair>;
};

/******************************************************************************/

class NameValuePairVector : public std::vector<NameValuePairPtr>
{
public:
	void copy(const NameValuePairVector& nameValuePairVector)
		{ clear(); insert(end(),nameValuePairVector.begin(),nameValuePairVector.end()); }

	int findPosByName(const char* name) const;

protected:
	struct findNameCompare
	{
	protected:
		CStr64 fName;

	public:
		findNameCompare(const char* name) { fName.copy(name); }
		bool operator() (const NameValuePairPtr& lhs) const
			{ return(fName == lhs->getName()); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//NameValuePairH
/******************************************************************************/
/******************************************************************************/
