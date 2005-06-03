/* NeedLogonIDControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef NeedLogonIDControlH
#define NeedLogonIDControlH

namespace asi
{

/******************************************************************************/

class NeedLogonIDControl : public ContainerControl
{
public:
	static const ControlID HaveLogonID;
protected:
	static const ControlID fRegisterTextID;
	static const ControlID fProceedTextID;

protected:
	NeedLogonIDControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~NeedLogonIDControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
};

/******************************************************************************/

};	//namespace asi

#endif	//NeedLogonIDControlH
/******************************************************************************/
/******************************************************************************/
