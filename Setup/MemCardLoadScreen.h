/* MemCardLoadScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MemCardLoadScreenH
#define MemCardLoadScreenH

namespace asi
{

/******************************************************************************/

class MemCardLoadScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fTextID;
	static const ControlID fMemCard1ControlID;
	static const ControlID fMemCard2ControlID;

	MemoryCardSlot fSelectedMemoryCardSlot;

protected:
	MemCardLoadScreen();
	virtual ~MemCardLoadScreen() {}

public:
	static MemoryCardSlot newInstance();

	MemoryCardSlot getSelectedMemoryCardSlot() const { return fSelectedMemoryCardSlot; }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);

	friend class RefCountPtr<MemCardLoadScreen>;
};

class MemCardLoadScreenPtr : public RefCountPtr<MemCardLoadScreen>
{
public:
	MemCardLoadScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<MemCardLoadScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<MemCardLoadScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//MemCardLoadScreenH
/******************************************************************************/
/******************************************************************************/
