/* SearchResultsScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef SearchResultsScreenH
#define SearchResultsScreenH

#include "ShowSearch.h"

namespace asi
{

/******************************************************************************/

class SearchResultsScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fShowListID;
	static const ControlID fNoShowsTextID;

	ShowSearchVector fShowSearchVector;

protected:
	SearchResultsScreen(const ShowSearchVector& showSearchVector);
	virtual ~SearchResultsScreen() {}

public:
	static ScreenPtr newInstance(const ShowSearchVector& showSearchVector)
		{ return Screen::newInstance(new SearchResultsScreen(showSearchVector)); }

protected:
	virtual void createControls();
public:
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//SearchResultsScreenH
/******************************************************************************/
/******************************************************************************/
