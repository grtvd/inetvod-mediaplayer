/* RecreateSettingsControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RecreateSettingsControlH
#define RecreateSettingsControlH

namespace asi
{

/******************************************************************************/

class RecreateSettingsControl : public ContainerControl
{
protected:
	static const ControlID fDescriptionID;
	static const ControlID fSerialNoLabelID;
	static const ControlID fSerialNoID;
	static const ControlID fPINLabelID;
	static const ControlID fPINID;
	static const ControlID fRememberPINLabelID;
	static const ControlID fRememberPINID;
public:
	static const ControlID ContinueID;

protected:
	RecreateSettingsControl(const ControlID& controlID, const ScreenID& screenID);
	virtual ~RecreateSettingsControl() {}

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

#endif	//RecreateSettingsControlH
/******************************************************************************/
/******************************************************************************/
