/* Control.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ControlH
#define ControlH

namespace asi
{

/******************************************************************************/

class Screen;	//forward reference
typedef RefCountPtr<Screen> ScreenPtr;

class Control;	//forward reference
typedef RefCountPtr<Control> ControlPtr;

class Control : public RefCountObject
{
protected:
	static const int fFocusedBorderWidth;

	ControlID fControlID;
	ScreenID fScreenID;
//	char fName[64];
	Rect fRect;
private:
	bool fFocused;	//derived classes should use the functions

protected:
	Control(const ControlID& controlID,const ScreenID& screenID)
	{
		fControlID = controlID;
		fScreenID = screenID;
		fFocused = false;
	}
	virtual ~Control() {}

private:
	Control(const Control&);						// don't allow copy constructor
	const Control& operator=(const Control&);		// or operator=

public:
	static ControlPtr newInstance(Control* pControl,const Rect& rect);

	virtual void clear() {}

	const ControlID& getControlID() const { return(fControlID); }
	ScreenPtr getScreen() const;

	const Rect& getRect() const { return fRect; }
	void setRect(const Rect& rect) { fRect = rect; }
	virtual int getStandardHeight() const { return 38; }

	virtual bool canFocus() const { return true; }
	virtual bool hasFocus() const { return fFocused; }
	virtual void setFocus(bool set);

	virtual void draw(bool showFocus) = 0;
	virtual bool key(int /*key*/) { return false; }
	virtual bool mouseClick(bool leftButton, bool buttonDown, int x, int y) { return false; }
	virtual void mouseMove(bool buttonDown, int x, int y) {}

	friend class RefCountPtr<Control>;
};

/******************************************************************************/

class ControlVector : public std::vector<ControlPtr>
{
public:
	ControlPtr findByID(const ControlID& controlID) const;
	ControlPtr getByID(const ControlID& controlID) const;
	void removeByID(const ControlID& controlID);
	int getFocusedPos() const;

protected:
	struct findIDCompare
	{
	protected:
		ControlID fControlID;

	public:
		findIDCompare(const ControlID& controlID) { fControlID = controlID; }
		bool operator() (const ControlPtr& lhs) const
			{ return(lhs->getControlID() == fControlID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//ControlH
/******************************************************************************/
/******************************************************************************/
