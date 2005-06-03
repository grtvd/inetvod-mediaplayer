/* MessageScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef MessageScreenH
#define MessageScreenH

namespace asi
{

/******************************************************************************/

// Message Return
enum MessageReturn
{
	mr_OK,
	mr_Cancel,
	mr_Yes,
	mr_No
};

// Message Prompt
enum MessagePrompt
{
	mp_OK,
	mp_OKCancel,
	mp_YesNo,
	mp_YesNoCancel
};

/******************************************************************************/

class MessageScreen : public Screen
{
protected:
	static const ScreenID ID;
protected:
	static const ControlID fTextID;
	static const ControlID fYesID;		// or OK
	static const ControlID fNoID;
	static const ControlID fCancelID;

	MessagePrompt fMessagePrompt;
	CStrVar fText;
	MessageReturn fMessageReturn;

protected:
	MessageScreen(MessagePrompt messagePrompt, const char* text);
	virtual ~MessageScreen() {}

public:
	static MessageReturn newInstance(MessagePrompt messagePrompt, const char* text);

	MessageReturn getMessageReturn() const { return fMessageReturn; }

protected:
	virtual void createControls();
	virtual void onButton(const ControlID& controlID);

	friend class RefCountPtr<MessageScreen>;
};

class MessageScreenPtr : public RefCountPtr<MessageScreen>
{
public:
	MessageScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<MessageScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<MessageScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

}; //namespace asi

#endif	//MessageScreenH
/******************************************************************************/
/******************************************************************************/
