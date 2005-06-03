/* RatingSelectScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef RatingSelectScreenH
#define RatingSelectScreenH

#include "SearchData.h"

namespace asi
{

/******************************************************************************/

class RatingSelectScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fDescriptionID;
	static const ControlID fRatingsID;

	SearchDataPtr fSearchDataPtr;

protected:
	RatingSelectScreen(SearchDataPtr& searchDataPtr);
	virtual ~RatingSelectScreen() {}

public:
	static void newInstance(SearchDataPtr& searchDataPtr);

protected:
	virtual void createControls();
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//RatingSelectScreenH
/******************************************************************************/
/******************************************************************************/
