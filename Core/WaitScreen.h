/* WaitScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef WaitScreenH
#define WaitScreenH

namespace asi
{

/******************************************************************************/

class WaitScreen : public Screen
{
protected:
	static const ScreenID ID;
protected:
	static const ControlID fTextID;

	CStrVar fText;

protected:
	WaitScreen(const char* text = NULL);
	virtual ~WaitScreen() {}

public:
	static ScreenPtr newInstance(const char* text = NULL)
		{ return Screen::newInstance(new WaitScreen(text)); }

protected:
	virtual void createControls();
public:
	virtual bool key(int key);
};

/******************************************************************************/

}; //namespace asi

#endif	//WaitScreenH
/******************************************************************************/
/******************************************************************************/
