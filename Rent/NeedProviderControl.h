/* NeedProviderControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef NeedProviderControlH
#define NeedProviderControlH

namespace asi
{

/******************************************************************************/

class NeedProviderControl : public ContainerControl
{
public:
	static const ControlID CreateMembershipID;
protected:
	static const ControlID fMemberTextID;

protected:
	NeedProviderControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~NeedProviderControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
	virtual bool loadData(ObjectPtr objectPtr);
};

/******************************************************************************/

};	//namespace asi

#endif	//NeedProviderControlH
/******************************************************************************/
/******************************************************************************/
