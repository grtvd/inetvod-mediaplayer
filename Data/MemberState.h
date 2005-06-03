/* MemberState.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MemberStateH
#define MemberStateH

#include "MemberPrefs.h"
#include "MemberProvider.h"

namespace asi
{

/******************************************************************************/

class MemberState : public Streamable
{
protected:
	MemberPrefsPtr fMemberPrefsPtr;
	MemberProviderVector fMemberProviderVector;

protected:
	MemberState(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~MemberState() {}

private:
	MemberState(const MemberState&);						// don't allow copy constructor
	const MemberState& operator=(const MemberState&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new MemberState(filerPtr)); }

	virtual const char* className() const { return "MemberState"; }

	// Data Get/Set Methods
	MemberPrefsPtr getMemberPrefs() const { return fMemberPrefsPtr; }
	void getMemberProviderVector(MemberProviderVector& memberProviderVector) const
		{ memberProviderVector.copy(fMemberProviderVector); }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<MemberState>;
};

class MemberStatePtr : public RefCountPtr<MemberState>
{
public:
	MemberStatePtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<MemberState>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<MemberState&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class MemberStateConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return MemberState::newInstance(filerPtr); }
};

/******************************************************************************/

}; //namespace asi

#endif	//MemberStateH
/******************************************************************************/
/******************************************************************************/
