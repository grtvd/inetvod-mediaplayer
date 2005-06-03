/* HaveProviderControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef HaveProviderControlH
#define HaveProviderControlH

namespace asi
{

/******************************************************************************/

class HaveProviderControl : public ContainerControl
{
protected:
	static const ControlID fDescriptionID;
	static const ControlID fUserIDLabelID;
	static const ControlID fUserIDID;
	static const ControlID fPasswordLabelID;
	static const ControlID fPasswordID;
public:
	static const ControlID ContinueID;

protected:
	HaveProviderControl(const ControlID& controlID, const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~HaveProviderControl() {}

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

#endif	//HaveProviderControlH
/******************************************************************************/
/******************************************************************************/
