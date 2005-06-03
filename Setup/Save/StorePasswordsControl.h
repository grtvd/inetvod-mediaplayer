/* StorePasswordsControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef StorePasswordsControlH
#define StorePasswordsControlH

namespace asi
{

/******************************************************************************/

class StorePasswordsControl : public ContainerControl
{
protected:
	static const ControlID fDescriptionID;
public:
	static const ControlID NotStoredID;
	static const ControlID StoreLocallyID;
	static const ControlID StoreServerID;

protected:
	StorePasswordsControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~StorePasswordsControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
};

/******************************************************************************/

};	//namespace asi

#endif	//StorePasswordsControlH
/******************************************************************************/
/******************************************************************************/
