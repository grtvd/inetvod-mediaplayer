/* MemCardSaveScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MemCardSaveScreenH
#define MemCardSaveScreenH

namespace asi
{

/******************************************************************************/

class MemCardSaveScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fTextID;
	static const ControlID fMemCard1ControlID;
	static const ControlID fMemCard2ControlID;

	MemoryCardSlot fSelectedMemoryCardSlot;

protected:
	MemCardSaveScreen();
	virtual ~MemCardSaveScreen() {}

public:
	static MemoryCardSlot newInstance();

	MemoryCardSlot getSelectedMemoryCardSlot() const { return fSelectedMemoryCardSlot; }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);

	friend class RefCountPtr<MemCardSaveScreen>;
};

class MemCardSaveScreenPtr : public RefCountPtr<MemCardSaveScreen>
{
public:
	MemCardSaveScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<MemCardSaveScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<MemCardSaveScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//MemCardSaveScreenH
/******************************************************************************/
/******************************************************************************/
