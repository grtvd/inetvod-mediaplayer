/* IncludeAdultControl.h */

/******************************************************************************/
/******************************************************************************/
#ifndef IncludeAdultControlH
#define IncludeAdultControlH

namespace asi
{

/******************************************************************************/

class IncludeAdultControl : public ContainerControl
{
protected:
	static const ControlID fDescriptionID;
public:
	static const ControlID NeverID;
	static const ControlID PromptPasswordID;
	static const ControlID AlwaysID;

protected:
	IncludeAdultControl(const ControlID& controlID,const ScreenID& screenID)
		: ContainerControl(controlID, screenID) {}
	virtual ~IncludeAdultControl() {}

public:
	static ControlPtr newInstance(const ControlID& controlID, const ScreenID& screenID,
		const Rect& rect);

protected:
	virtual void createControls();
};

/******************************************************************************/

};	//namespace asi

#endif	//IncludeAdultControlH
/******************************************************************************/
/******************************************************************************/
