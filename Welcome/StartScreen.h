/* StartScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef StartScreenH
#define StartScreenH

namespace asi
{

/******************************************************************************/

class StartScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fTextID;
	static const ControlID fStartID;

protected:
	StartScreen();
	virtual ~StartScreen() {}

public:
	static ScreenPtr newInstance() { return Screen::newInstance(new StartScreen()); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);
protected:
	bool doSignon();
};

/******************************************************************************/

};	//namespace asi

#endif	//StartScreenH
/******************************************************************************/
/******************************************************************************/
