/* AskAdultPINScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef AskAdultPINScreenH
#define AskAdultPINScreenH

namespace asi
{

/******************************************************************************/

class AskAdultPINScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fTextID;
	static const ControlID fPINLabelID;
	static const ControlID fPINID;

	CStr32 fAdultPassword;

protected:
	AskAdultPINScreen();
	virtual ~AskAdultPINScreen() {}

public:
	static ScreenPtr newInstance();

	const char* getAdultPassword() const { return fAdultPassword.c_str(); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);

	friend class RefCountPtr<AskAdultPINScreen>;
};

class AskAdultPINScreenPtr : public RefCountPtr<AskAdultPINScreen>
{
public:
	AskAdultPINScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<AskAdultPINScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<AskAdultPINScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//AskAdultPINScreenH
/******************************************************************************/
/******************************************************************************/
