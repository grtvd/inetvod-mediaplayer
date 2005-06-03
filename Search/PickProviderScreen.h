/* PickProviderScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef PickProviderScreenH
#define PickProviderScreenH

namespace asi
{

/******************************************************************************/

class PickProviderScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fAvailTextID;
	static const ControlID fSelectTextID;
	static const ControlID fProviderListID;

	ShowSearchPtr fShowSearchPtr;
	ProviderID fProviderID;

protected:
	PickProviderScreen(ShowSearchPtr showSearchPtr);
	virtual ~PickProviderScreen() {}

public:
	static ScreenPtr newInstance(ShowSearchPtr showSearchPtr);

	ProviderID getProviderID() const { return fProviderID; }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);

	friend class RefCountPtr<PickProviderScreen>;
};

class PickProviderScreenPtr : public RefCountPtr<PickProviderScreen>
{
public:
	PickProviderScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<PickProviderScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<PickProviderScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//PickProviderScreenH
/******************************************************************************/
/******************************************************************************/
