/* AskSignedUpControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef AskSignedUpControlH
#define AskSignedUpControlH

namespace asi
{

/******************************************************************************/

class AskSignedUpControl : public ContainerControl
{
public:
	static const ControlID AlreadyRegisteredID;
	static const ControlID NotRegisteredID;
protected:
	static const ControlID fWelecomeTextID;
	static const ControlID fRegisteredTextID;

protected:
	AskSignedUpControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~AskSignedUpControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
};

/******************************************************************************/

};	//namespace asi

#endif	//AskSignedUpControlH
/******************************************************************************/
/******************************************************************************/
