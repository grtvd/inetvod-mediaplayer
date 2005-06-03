/* SearchScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SearchScreenH
#define SearchScreenH

#include "SearchData.h"

namespace asi
{

/******************************************************************************/

class SearchScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fDescriptionID;
	static const ControlID fShowNameLabelID;
	static const ControlID fShowNameID;
	static const ControlID fSearchID;
	static const ControlID fRefineTextID;
	static const ControlID fProviderLabelID;
	static const ControlID fProviderID;
	static const ControlID fCategoryLabelID;
	static const ControlID fCategoryID;
	static const ControlID fRatingLabelID;
	static const ControlID fRatingID;

	SearchDataPtr fSearchDataPtr;

protected:
	SearchScreen();
	virtual ~SearchScreen() {}

public:
	static ScreenPtr newInstance() { return Screen::newInstance(new SearchScreen()); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//SearchScreenH
/******************************************************************************/
/******************************************************************************/
