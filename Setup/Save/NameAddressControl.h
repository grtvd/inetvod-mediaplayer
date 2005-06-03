/* NameAddressControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef NameAddressControlH
#define NameAddressControlH

namespace asi
{

/******************************************************************************/

class NameAddressControl : public ContainerControl
{
protected:
	static const ControlID fDescriptionID;
	static const ControlID fDescription2ID;
	static const ControlID fNameLabelID;
	static const ControlID fFirstNameID;
	static const ControlID fLastNameID;
	static const ControlID fAddressLabelID;
	static const ControlID fAddrStreet1ID;
	static const ControlID fAddrStreet2ID;
	static const ControlID fCityLabelID;
	static const ControlID fCityID;
	static const ControlID fStateLabelID;
	static const ControlID fStateID;
	static const ControlID fPostalCodeLabelID;
	static const ControlID fPostalCodeID;
	static const ControlID fPhoneLabelID;
	static const ControlID fPhoneID;
public:
	static const ControlID ContinueID;

protected:
	NameAddressControl(const ControlID& controlID, const ScreenID& screenID);
	virtual ~NameAddressControl() {}

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

#endif	//NameAddressControlH
/******************************************************************************/
/******************************************************************************/
