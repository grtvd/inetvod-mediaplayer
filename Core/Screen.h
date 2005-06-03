/* Screen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ScreenH
#define ScreenH

namespace asi
{

/******************************************************************************/

class Screen;	//forward reference
typedef RefCountPtr<Screen> ScreenPtr;

class Screen : public RefCountObject
{
protected:
	ScreenID fScreenID;

	int fContentLeft;
	int fContentTop;
	int fContentWidth;
	int fContentHeight;

	bool fIsFullScreen;
	int fBorderWidth;
	int fTitleHeight;
	int fTitlePadWidth;
	int fShadowWidth;
	int fStatusHeight;

	CStr64 fTitle;
	ContainerControl fContainerControl;

	//bool fDataLoaded;
	//bool fFailedDataLoad;

protected:
	Screen(const ScreenID& screenID);
	virtual ~Screen() {}

private:
	Screen(const Screen&);						// don't allow copy constructor
	const Screen& operator=(const Screen&);		// or operator=

public:
	static ScreenPtr newInstance(Screen* pScreen);
	virtual void createControls() {}

	const ScreenID& getScreenID() const { return(fScreenID); }
	void close() const;

	bool isFullScreen() const { return fIsFullScreen; }
	const char* getTitle() const;

	void newControl(ControlPtr controlPtr)
		{ fContainerControl.newControl(controlPtr); }
	ControlPtr findControl(const ControlID& controlID)
		{ return fContainerControl.findControl(controlID); }
	ControlPtr getControl(const ControlID& controlID)
		{ return fContainerControl.getControl(controlID); }
	void deleteControl(const ControlID& controlID)
		{ fContainerControl.deleteControl(controlID); }

	//virtual bool loadData() { return true; }
	//virtual void needLoadData() { fDataLoaded = false; fFailedDataLoad = false; }
	//virtual bool didLoadDataFail() { return fDataLoaded && fFailedDataLoad; }

	virtual void draw(bool hasFocus);
protected:
	virtual void drawFrame(bool hasFocus);
	virtual void drawStatus();
	virtual void drawContent(bool hasFocus);

public:
	virtual bool key(int key);
	virtual void idle();
	virtual bool mouseClick(bool leftButton, bool buttonDown, int x, int y);
	virtual void mouseMove(bool buttonDown, int x, int y);
	virtual void onButton(const ControlID& controlID);
	virtual void onFocus(const ControlID& controlID) {}

	friend class RefCountPtr<Screen>;
};

/******************************************************************************/

class ScreenVector : public std::vector<ScreenPtr>
{
public:
	ScreenPtr findByID(const ScreenID& screenID) const;
	ScreenPtr getByID(const ScreenID& screenID) const;
	void removeByID(const ScreenID& screenID);

protected:
	struct findIDCompare
	{
	protected:
		ScreenID fScreenID;

	public:
		findIDCompare(const ScreenID& screenID) { fScreenID = screenID; }
		bool operator()(const ScreenPtr& lhs) const
			{ return(lhs->getScreenID() == fScreenID); }
	};
};

/******************************************************************************/

}; //namespace asi

#endif	//ScreenH
/******************************************************************************/
/******************************************************************************/
