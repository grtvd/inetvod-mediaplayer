/* ProviderSelectScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ProviderSelectScreenH
#define ProviderSelectScreenH

#include "SearchData.h"

namespace asi
{

/******************************************************************************/

class ProviderSelectScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fDescriptionID;
	static const ControlID fProvidersID;

	SearchDataPtr fSearchDataPtr;

protected:
	ProviderSelectScreen(SearchDataPtr& searchDataPtr);
	virtual ~ProviderSelectScreen() {}

public:
	static void newInstance(SearchDataPtr& searchDataPtr);

protected:
	virtual void createControls();
	virtual void onButton(const ControlID& controlID);
};

/******************************************************************************/

};	//namespace asi

#endif	//ProviderSelectScreenH
/******************************************************************************/
/******************************************************************************/
