/* PickRentalControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef PickRentalControlH
#define PickRentalControlH

namespace asi
{

/******************************************************************************/

class PickRentalControl : public ContainerControl
{
protected:
	static const ControlID fAvailTextID;
	static const ControlID fSelectTextID;
public:
	static const ControlID ProviderListID;

protected:
	PickRentalControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~PickRentalControl() {}

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

#endif	//PickRentalControlH
/******************************************************************************/
/******************************************************************************/
