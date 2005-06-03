/* TTick.c */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

clock_t x;

/******************************************************************************/
/******************************************************************************/

TTick tGetTickCount()
{
	#if defined(WIN32)
		return(clock());
	#else
		return(TickCount());
	#endif
}

/******************************************************************************/

TTick tConvertTenthsToTicks(ulong tenths)
{
	return(tenths * TICKS_PER_TENTH);
}

/******************************************************************************/

TTick tConvertSecsToTicks(ulong secs)
{
	return(tConvertTenthsToTicks(secs * 10UL));
}

/******************************************************************************/

void tPauseTenths(ulong tenths)
{
	TTick endTicks;

	endTicks = tGetTickCount() + tConvertTenthsToTicks(tenths);
	while(endTicks > tGetTickCount())
		;
}

/******************************************************************************/

void tPauseSecs(ulong secs)
{
	tPauseTenths(secs * 10UL);
}

/******************************************************************************/

bool tHaveTenthsPast(TTick prevTicks,ulong tenths)
{
	TTick endTicks;

	endTicks = prevTicks + tConvertTenthsToTicks(tenths);
	return(endTicks <= tGetTickCount());
}

/******************************************************************************/

bool tHaveSecsPast(TTick prevTicks,ulong secs)
{
	return(tHaveTenthsPast(prevTicks,secs * 10UL));
}

/******************************************************************************/

}; //namespace asi

/******************************************************************************/
/******************************************************************************/
