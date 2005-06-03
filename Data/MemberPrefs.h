/* MemberPrefs.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MemberPrefsH
#define MemberPrefsH

namespace asi
{

/******************************************************************************/

class MemberPrefs : public Streamable
{
protected:
	IncludeAdult fIncludeAdult;

protected:
	MemberPrefs(DataFilerPtr filerPtr) { readFromFiler(filerPtr); }
	virtual ~MemberPrefs() {}

private:
	MemberPrefs(const MemberPrefs&);						// don't allow copy constructor
	const MemberPrefs& operator=(const MemberPrefs&);		// or operator=

public:
	// Construction Methods
	static StreamablePtr newInstance(DataFilerPtr filerPtr)
		{ return StreamablePtr(new MemberPrefs(filerPtr)); }

	virtual const char* className() const { return "MemberPrefs"; }

	// Data Get/Set Methods
	IncludeAdult getIncludeAdult() const { return fIncludeAdult; }

	virtual void readFromFiler(DataFilerPtr filerPtr);
	virtual void writeToFiler(DataFilerPtr filerPtr) const;

	friend class RefCountPtr<MemberPrefs>;
};

class MemberPrefsPtr : public RefCountPtr<MemberPrefs>
{
public:
	MemberPrefsPtr(StreamablePtr streamablePtr = StreamablePtr()) : 
		RefCountPtr<MemberPrefs>(streamablePtr.isNull() ? NULL :
		&dynamic_cast<MemberPrefs&>(*streamablePtr)) {}

	operator StreamablePtr() const { return(StreamablePtr(fT)); }
};

/******************************************************************************/

class MemberPrefsConstructor : public StreamableConstructor
{
public:
	virtual StreamablePtr newInstance(DataFilerPtr filerPtr) const
		{ return MemberPrefs::newInstance(filerPtr); }
};

/******************************************************************************/

}; //namespace asi

#endif	//MemberPrefsH
/******************************************************************************/
/******************************************************************************/
