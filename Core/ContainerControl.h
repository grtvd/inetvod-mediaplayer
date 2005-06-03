/* ContainerControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ContainerControlH
#define ContainerControlH

namespace asi
{

/******************************************************************************/

class ContainerControl : public Control
{
protected:
	ControlVector fControlVector;
	CStr64 fTitle;	// optional Title

protected:
	ContainerControl(const ControlID& controlID,const ScreenID& screenID)
		: Control(controlID,screenID) {}
	virtual ~ContainerControl() {}

private:
	ContainerControl(const ContainerControl&);						// don't allow copy constructor
	const ContainerControl& operator=(const ContainerControl&);		// or operator=

public:
	static ControlPtr newInstance(const ControlID& controlID,const ScreenID& screenID,
		const Rect& rect);

	void newControl(ControlPtr controlPtr);
	ControlPtr findControl(const ControlID& controlID);
	ControlPtr getControl(const ControlID& controlID);
	void deleteControl(const ControlID& controlID);

	virtual void createControls() {}
	virtual bool loadData(ObjectPtr objectPtr) { return true; }
	virtual bool unloadData(ObjectPtr objectPtr) { return true; }

	const char* getTitle() const;

	virtual bool canFocus() const;
	virtual void setFocus(bool set);

	virtual void draw(bool showFocus);
	virtual bool key(int key);
	virtual bool mouseClick(bool leftbutton, bool buttonDown, int x, int y);
	virtual void mouseMove(bool buttonDown, int x, int y);

	friend class RefCountPtr<ContainerControl>;
	friend class Screen;
};

class ContainerControlPtr : public RefCountPtr<ContainerControl>
{
public:
	ContainerControlPtr(ControlPtr controlPtr = ControlPtr()) : 
		RefCountPtr<ContainerControl>(controlPtr.isNull() ? NULL :
		&dynamic_cast<ContainerControl&>(*controlPtr)) {}

	operator ControlPtr() { return(ControlPtr(fT)); }
	static bool isA(ControlPtr controlPtr)
		{ return (dynamic_cast<ContainerControl*>(&(*controlPtr)) != NULL); }
};

/******************************************************************************/

}; //namespace asi

#endif	//ContainerControlH
/******************************************************************************/
/******************************************************************************/
