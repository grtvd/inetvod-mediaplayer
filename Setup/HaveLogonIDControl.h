/* HaveLogonIDControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef HaveLogonIDControlH
#define HaveLogonIDControlH

namespace asi
{

/******************************************************************************/

class HaveLogonIDControl : public ContainerControl
{
protected:
	static const ControlID fDescriptionID;
	static const ControlID fLogonIDLabelID;
	static const ControlID fLogonIDID;
	static const ControlID fPINLabelID;
	static const ControlID fPINID;
	static const ControlID fRememberPINLabelID;
	static const ControlID fRememberPINID;
public:
	static const ControlID ContinueID;

protected:
	HaveLogonIDControl(const ControlID& controlID, const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~HaveLogonIDControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
	virtual bool loadData(ObjectPtr objectPtr);
	virtual bool unloadData(ObjectPtr objectPtr);
};

/******************************************************************************/

};	//namespace asi

#endif	//HaveLogonIDControlH
/******************************************************************************/
/******************************************************************************/
