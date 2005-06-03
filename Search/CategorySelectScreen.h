/* CategorySelectScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef CategorySelectScreenH
#define CategorySelectScreenH

#include "SearchData.h"

namespace asi
{

/******************************************************************************/

class CategorySelectScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fDescriptionID;
	static const ControlID fCategoriesID;

	SearchDataPtr fSearchDataPtr;

protected:
	CategorySelectScreen(SearchDataPtr& searchDataPtr);
	virtual ~CategorySelectScreen() {}

public:
	static void newInstance(SearchDataPtr& searchDataPtr);

protected:
	virtual void createControls();
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//CategorySelectScreenH
/******************************************************************************/
/******************************************************************************/
