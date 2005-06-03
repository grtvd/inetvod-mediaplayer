/* CategorySearchScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef CategorySearchScreenH
#define CategorySearchScreenH

#include "SearchData.h"

namespace asi
{

/******************************************************************************/

class CategorySearchScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fDescriptionID;
	static const ControlID fCategoriesID;

protected:
	CategorySearchScreen();
	virtual ~CategorySearchScreen() {}

public:
	static void newInstance()
		{ Screen::newInstance(new CategorySearchScreen()); }

protected:
	virtual void createControls();
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//CategorySearchScreenH
/******************************************************************************/
/******************************************************************************/
