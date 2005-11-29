/* RentedShowDetailScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RentedShowDetailScreenH
#define RentedShowDetailScreenH

#include "RentedShow.h"

namespace asi
{

/******************************************************************************/

class RentedShowDetailScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fNameID;
	static const ControlID fEpisodeID;
	static const ControlID fReleasedLabelID;
	static const ControlID fReleasedID;
	static const ControlID fDescriptionID;
	static const ControlID fRunningMinsLabelID;
	static const ControlID fRunningMinsID;
	static const ControlID fCategoryLabelID;
	static const ControlID fCategoryID;
	static const ControlID fProviderLabelID;
	static const ControlID fProviderID;
	static const ControlID fRatingLabelID;
	static const ControlID fRatingID;
	static const ControlID fCostLabelID;
	static const ControlID fCostID;
	static const ControlID fRentalPeriodHoursLabelID;
	static const ControlID fRentalPeriodHoursID;
	static const ControlID fRentedOnLabelID;
	static const ControlID fRentedOnID;
	static const ControlID fAvailableUntilLabelID;
	static const ControlID fAvailableUntilID;
	static const ControlID fWatchNowID;
	static const ControlID fDeleteNowID;

	RentedShowPtr fRentedShowPtr;

protected:
	RentedShowDetailScreen(const RentedShowPtr& rentedShowPtr);
	virtual ~RentedShowDetailScreen() {}

public:
	static ScreenPtr newInstance(const RentedShowPtr& rentedShowPtr)
		{ return Screen::newInstance(new RentedShowDetailScreen(rentedShowPtr)); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//RentedShowDetailScreenH
/******************************************************************************/
/******************************************************************************/
