/* TDateTime.h */

/******************************************************************************/
/******************************************************************************/
#ifndef TDateTimeH
#define TDateTimeH

namespace asi
{

/******************************************************************************/

#define DATE_MAX			0xFFFFFFFFUL
#define TIME_MIN			0UL
#define TIME_MAX			86399UL
#define TIME_UNDEF			0xFFFFFFFFUL
#define SECONDS_PER_DAY		86400UL

/******************************************************************************/

enum TDateTimeFormat
{
								// expample of Feb. 3rd, 2004 at 1:05:07 PM
	//TODO: dtf_ISO8601_Date,
	//TODO: dtf_ISO8601_DateTime,
	dtf_MM_DD_YY,				// 02/03/04
	dtf_MM_DD_YYYY,				// 02/03/2004
	dtf_M_D,					// 2/3
	dtf_M_D_YYYY_H_MM_AM,		// 2/3/2004 1:05 PM
	dtf_M_D_YYYY_H_MM_SS_AM,	// 2/3/2004 1:05:07 PM
	dtf_M_D_H_MM_AM,			// 2/3 1:05 PM
	dtf_H_AM,					// 1 PM
	dtf_H_MM_AM,				// 1:05 PM
};

/******************************************************************************/

enum TDateOfWeekFormat
{
	dwf_Sun,
	dwf_Sunday
};

/******************************************************************************/

enum DayOfWeek
{
	dow_Sunday = 0,
	dow_Monday,
	dow_Tuesday,
	dow_Wednesday,
	dow_Thursday,
	dow_Friday,
	dow_Saturday
};

/******************************************************************************/

struct TDateTimeUtil
{
private:
	#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
	TDateTimeUtil() = 0;
	#endif

public:
	static const char DateSeparator;
	static const char TimeSeparator;
	static const int DaysPerMonth[12];
	static const char* DaysOfWeekShort[7];
	static const char* DaysOfWeekLong[7];
	static const char* AMPMIndicator[2];

	// static routines
	static bool isDateChar(char ch, TDateTimeFormat format);
	static bool isDateTimeChar(char ch, TDateTimeFormat format);

	static bool allDateString(const char* str, TDateTimeFormat format);
	static bool allDateTimeString(const char* str, TDateTimeFormat format);

	static CStr32 dateTimeToString(ulong tDate, ulong tTime, TDateTimeFormat format);

	//TODO: static bool stringToISO8601Date(const char* str, ulong& tDate);
	static bool stringToMM_DD_YYYYDate(const char* str, ulong& tDate);

	static bool isLeapYear(int year);
	static DayOfWeek dayOfWeek(ulong tDate);

	static ulong mdyToDate(int month, int day, int year);
	static void dateToMDY(ulong dateTime, int& month, int& day, int& year);

	static int dateMonth(ulong tDate);
	static int dateDay(ulong tDate);
	static int dateYear(ulong tDate);

	static ulong hmsToTime(int hour, int minute, int second);
	static void timeToHMS(ulong tTime, int& hour, int& minute, int& second);

	static int timeHour(ulong tTime);
	static int timeMinute(ulong tTime);
	static int timeSecond(ulong tTime);

	static ulong getSystemDate();
	static ulong getSystemTime();
};

/******************************************************************************/

struct TDayOfWeek
{
protected:
	DayOfWeek fDayOfWeek;

public:
	TDayOfWeek() { fDayOfWeek = dow_Sunday; }
	TDayOfWeek(DayOfWeek dayOfWeek) { fDayOfWeek = dayOfWeek; }

	const char* c_str(TDateOfWeekFormat format) const;
};

/******************************************************************************/

struct TTimeSpan
{
protected:
	double fDays;

public:
	TTimeSpan() { fDays = 0.0; }
	TTimeSpan(double days) { fDays = days; }
	//TTimeSpan(ulong seconds) { fDays = (double)seconds / (double)SECONDS_PER_DAY; }

	int getDays() const;
	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;

	double getTotalDays() const { return fDays; }
	double getTotalHours() const;
	double getTotalMinutes() const;
	double getTotalSeconds() const;
};

/******************************************************************************/

struct TDate
{
protected:
	ulong fDate;
	auto_ptr<char> fFormatted;

public:
	TDate() { fDate = 0; }
	TDate(int month, int day, int year);
	TDate(const TDate& tDate) { fDate = tDate.fDate; }
	TDate(const char* str, TDateTimeFormat format);
	TDate& operator=(const TDate& tDate) { fDate = tDate.fDate; fFormatted.release(); return *this; }
	virtual ~TDate() {}

	void clear() { fDate = 0; fFormatted.release(); }
	bool isUndefined() const { return (fDate == 0); }

	TDayOfWeek getDayOfWeek() const { return TDayOfWeek(TDateTimeUtil::dayOfWeek(fDate)); }
	void getMDY(int& month, int& day, int& year) { TDateTimeUtil::dateToMDY(fDate, month, day, year); }
	int compare(const TDate& tDate);

	virtual const char* c_str(TDateTimeFormat format) const;
};

/******************************************************************************/

struct TDateTime : public TDate
{
protected:
	ulong fTime;

public:
	TDateTime() { fTime = TIME_UNDEF; }
	TDateTime(int month, int day, int year, int hour, int minute, int second);
	TDateTime(const TDateTime& tDate) { fDate = tDate.fDate; fTime = tDate.fTime; }
	TDateTime(const char* str, TDateTimeFormat format);
	TDateTime& operator=(const TDateTime& tDate) { fDate = tDate.fDate; fTime = tDate.fTime; fFormatted.release(); return *this; }
	virtual ~TDateTime() {}

	void clear() { TDate::clear(); fTime = TIME_UNDEF; }
	bool isUndefined() const { return (TDate::isUndefined() && (fTime == TIME_UNDEF)); }

	void getHMS(int& hour, int& minute, int& second) { TDateTimeUtil::timeToHMS(fTime, hour, minute, second); }
	TTimeSpan compare(const TDateTime& tDate);

	virtual const char* c_str(TDateTimeFormat format) const;

	static TDateTime getSystemDateTime();
};

/******************************************************************************/

}; //namespace asi

#endif	//TDateTimeH
/******************************************************************************/
/******************************************************************************/

