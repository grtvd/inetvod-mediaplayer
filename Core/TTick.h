/* TTick.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TTickH
#define TTickH

namespace asi
{

/******************************************************************************/

#if defined(WIN32)

typedef clock_t TTick;
#define TICKS_PER_TENTH		((TTick)(CLOCKS_PER_SEC / 10))

#else

typedef ulong TTick;
#define TICKS_PER_TENTH		((TTick)6)

#endif

#define TICK_MAX			(ULONG_MAX)

/******************************************************************************/

TTick tGetTickCount();
TTick tConvertTenthsToTicks(ulong tenths);
TTick tConvertSecsToTicks(ulong secs);
void tPauseTenths(ulong tenths);
void tPauseSecs(ulong secs);
bool tHaveTenthsPast(TTick prevTicks,ulong tenths);
bool tHaveSecsPast(TTick prevTicks,ulong secs);

/******************************************************************************/

}; //namespace asi

#endif //TTickH
/******************************************************************************/
/******************************************************************************/
