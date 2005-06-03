/* SearchDetailScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SearchDetailScreenH
#define SearchDetailScreenH

#include "ShowDetail.h"

namespace asi
{

/******************************************************************************/

class SearchDetailScreen : public Screen
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
	static const ControlID fRentalHoursLabelID;
	static const ControlID fRentalHoursID;
	static const ControlID fRentNowID;

	ShowDetailPtr fShowDetailPtr;

protected:
	SearchDetailScreen(const ShowDetailPtr& showDetailPtr);
	virtual ~SearchDetailScreen() {}

public:
	static ScreenPtr newInstance(const ShowDetailPtr& showDetailPtr)
		{ return Screen::newInstance(new SearchDetailScreen(showDetailPtr)); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//SearchDetailScreenH
/******************************************************************************/
/******************************************************************************/
