/* AskPINScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef AskPINScreenH
#define AskPINScreenH

namespace asi
{

/******************************************************************************/

class AskPINScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fTextID;
	static const ControlID fPINLabelID;
	static const ControlID fPINID;

	CStr32 fUserPassword;

protected:
	AskPINScreen();
	virtual ~AskPINScreen() {}

public:
	static ScreenPtr newInstance();

	const char* getUserPassword() const { return fUserPassword.c_str(); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);

	friend class RefCountPtr<AskPINScreen>;
};

class AskPINScreenPtr : public RefCountPtr<AskPINScreen>
{
public:
	AskPINScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<AskPINScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<AskPINScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//AskPINScreenH
/******************************************************************************/
/******************************************************************************/
