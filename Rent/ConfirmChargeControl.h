/* ConfirmChargeControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ConfirmChargeControlH
#define ConfirmChargeControlH

namespace asi
{

/******************************************************************************/

class ConfirmChargeControl : public ContainerControl
{
public:
	static const ControlID ChargeAccountID;
	static const ControlID DontChargeAccountID;
protected:
	static const ControlID fChargeTextID;

protected:
	ConfirmChargeControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~ConfirmChargeControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
	virtual bool loadData(ObjectPtr objectPtr);
};

/******************************************************************************/

};	//namespace asi

#endif	//ConfirmChargeControlH
/******************************************************************************/
/******************************************************************************/
