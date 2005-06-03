/* AskHaveProviderControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef AskHaveProviderControlH
#define AskHaveProviderControlH

namespace asi
{

/******************************************************************************/

class AskHaveProviderControl : public ContainerControl
{
public:
	static const ControlID HaveMembershipID;
	static const ControlID NeedMembershipID;
protected:
	static const ControlID fWelecomeTextID;
	static const ControlID fMembershipTextID;

protected:
	AskHaveProviderControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~AskHaveProviderControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
	virtual bool loadData(ObjectPtr objectPtr);
};

/******************************************************************************/

};	//namespace asi

#endif	//AskHaveProviderControlH
/******************************************************************************/
/******************************************************************************/
