/* SetupScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SetupScreenH
#define SetupScreenH

#include "SetupData.h"

namespace asi
{

/******************************************************************************/

class SetupScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fStepControlID;

	SetupDataPtr fSetupDataPtr;
	int fCurStep;
	int fTotalSteps;

	bool fSignonNeeded;

protected:
	SetupScreen();
	virtual ~SetupScreen() {}

public:
	static bool newInstance();

	bool getSignonNeeded() const { return fSignonNeeded; }

protected:
	virtual void createControls();
	void openStep(int step);
	bool closeStep(bool doUnload = true);
public:
	virtual bool key(int key);
	virtual void onButton(const ControlID& controlID);
protected:
	bool canPingServer();
	bool loadSettingsFromMemoryCard();
	void saveSettingsToMemoryCard();
	void onRecreateSettingsButton();
	void onSerialNoPinButton();
	void onStorePasswordsButton(const ControlID& controlID);
	void onIncludeAdultButton(const ControlID& controlID);

	friend class RefCountPtr<SetupScreen>;
};

class SetupScreenPtr : public RefCountPtr<SetupScreen>
{
public:
	SetupScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<SetupScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<SetupScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//SetupScreenH
/******************************************************************************/
/******************************************************************************/
