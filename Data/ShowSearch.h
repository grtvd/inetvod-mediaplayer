/* ShowSearch.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ShowSearchH
#define ShowSearchH

#include "DataID.h"
#include "Object.h"
#include "ShowCost.h"
#include "ShowProvider.h"

namespace asi
{

/******************************************************************************/

class ShowSearch : public Streamable
{
protected:
	ShowID fShowID;
	CStr128 fName;
	CStr64 fEpisodeName;
	TInt16 fReleasedYear;
	ShowProviderVector fShowProviderVector;

protected:
	ShowSearch() {}
	virtual ~ShowSearch() {}

private:
	ShowSearch(const ShowSearch&);						// don't allow copy constructor
	const ShowSearch& operator=(const ShowSearch&);		// or operator=

public:
	// Construction Methods
	static ObjectPtr newInstance();

	virtual const char* className() const { return "ShowSearch"; }

	virtual void clear() { Object::clear(); fShowID.clear(); fName.clear(); }	//TODO:

	// Data Get Methods
	const ShowID& getShowID() const { return(fShowID); }
	const char* getName() const { return fName.c_str(); }
	const char* getEpisodeName() const { return fEpisodeName.c_str(); }
	TInt16 getReleasedYear() const { return fReleasedYear; }

	void getShowProviderVector(ShowProviderVector& showProviderVector) const
		{ showProviderVector.copy(fShowProviderVector); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<ShowSearch>;
};

class ShowSearchPtr : public RefCountPtr<ShowSearch>
{
public:
	ShowSearchPtr(ObjectPtr objectPtr = ObjectPtr()) : 
		RefCountPtr<ShowSearch>(objectPtr.isNull() ? NULL :
		&dynamic_cast<ShowSearch&>(*objectPtr)) {}

	operator ObjectPtr() { return(ObjectPtr(fT)); }
};

/******************************************************************************/

class ShowSearchVector : public std::vector<ShowSearchPtr>
{
public:
	void copy(const ShowSearchVector& showSearchVector)
		{ clear(); insert(end(), showSearchVector.begin(), showSearchVector.end()); }

	ShowSearchPtr findByID(const ShowID& showID) const;
	ShowSearchPtr getByID(const ShowID& showID) const;
	void removeByID(const ShowID& showID);

	void readFromFiler(DataFilerPtr filerPtr);
	void writeToFiler(DataFilerPtr filerPtr) const;

protected:
	struct findIDCompare
	{
	protected:
		ShowID fShowID;

	public:
		findIDCompare(const ShowID& showID) { fShowID = showID; }
		bool operator() (const ShowSearchPtr& lhs) const
			{ return(lhs->getShowID() == fShowID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//ShowSearchH
/******************************************************************************/
/******************************************************************************/
