/* PreferencesScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef PreferencesScreenH
#define PreferencesScreenH

namespace asi
{

/******************************************************************************/

class PreferencesScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fAccessAdultTextID;
	static const ControlID fAccessAdultValueID;
	static const ControlID fAccessAdultButtonID;

protected:
	PreferencesScreen();
	virtual ~PreferencesScreen() {}

public:
	static ScreenPtr newInstance() { return Screen::newInstance(new PreferencesScreen()); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//PreferencesScreenH
/******************************************************************************/
/******************************************************************************/
