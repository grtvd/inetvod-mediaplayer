/* WelcomeScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef WelcomeScreenH
#define WelcomeScreenH

namespace asi
{

/******************************************************************************/

class WelcomeScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fNowPlayingID;
	static const ControlID fFeaturedID;
	static const ControlID fSearchByCategoryID;
	static const ControlID fSearchByNameID;
	static const ControlID fPreferencesID;
	static const ControlID fHelpLabelID;
	static const ControlID fHelpID;

protected:
	WelcomeScreen();
	virtual ~WelcomeScreen() {}

public:
	static ScreenPtr newInstance() { return Screen::newInstance(new WelcomeScreen()); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);
	virtual void onFocus(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//WelcomeScreenH
/******************************************************************************/
/******************************************************************************/
