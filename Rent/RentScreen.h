/* RentScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentScreenH
#define RentScreenH

#include "RentData.h"

namespace asi
{

/******************************************************************************/

enum RentStep;

class RentScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fStepControlID;

	RentDataPtr fRentDataPtr;
	int fCurStep;
	int fTotalSteps;

	RentedShowID fRentedShowID;

protected:
	RentScreen(const ShowDetailPtr& showDetailPtr);
	virtual ~RentScreen() {}

public:
	static RentedShowID newInstance(const ShowDetailPtr& showDetailPtr);

	RentedShowID getRentedShowID() const { return fRentedShowID; }

protected:
	virtual void createControls();
	void openStep(int step);
	bool closeStep(bool doUnload = true);
public:
	virtual bool key(int key);
	virtual void onButton(const ControlID& controlID);
protected:
	RentStep checkShowAvail();
	void rentShow();
	bool setProvider();
	bool providerEnroll();

	friend class RefCountPtr<RentScreen>;
};

class RentScreenPtr : public RefCountPtr<RentScreen>
{
public:
	RentScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<RentScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<RentScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//RentScreenH
/******************************************************************************/
/******************************************************************************/
