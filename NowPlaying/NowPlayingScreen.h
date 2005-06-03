/* NowPlayingScreen.h */

/******************************************************************************/
/******************************************************************************/
#ifndef NowPlayingScreenH
#define NowPlayingScreenH

#include "RentedShow.h"

namespace asi
{

/******************************************************************************/

class NowPlayingScreen : public Screen
{
public:
	static const ScreenID ID;
protected:
	static const ControlID fShowListID;
	static const ControlID fNoShowsTextID;

	RentedShowSearchVector fRentedShowSearchVector;

protected:
	NowPlayingScreen();
	virtual ~NowPlayingScreen() {}

public:
	static ScreenPtr newInstance();

	void removeRentedShow(const RentedShowID& rentedShowID);

protected:
	bool fetchData();
	virtual void createControls();
	void createNoItemsControl();
public:
	virtual void onButton(const ControlID& controlID);

	friend class RefCountPtr<NowPlayingScreen>;
};

class NowPlayingScreenPtr : public RefCountPtr<NowPlayingScreen>
{
public:
	NowPlayingScreenPtr(ScreenPtr screenPtr = ScreenPtr()) : 
		RefCountPtr<NowPlayingScreen>(screenPtr.isNull() ? NULL :
		&dynamic_cast<NowPlayingScreen&>(*screenPtr)) {}

	operator ScreenPtr() { return(ScreenPtr(fT)); }
};

/******************************************************************************/

};	//namespace asi

#endif	//NowPlayingScreenH
/******************************************************************************/
/******************************************************************************/
