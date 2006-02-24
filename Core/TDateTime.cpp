/* TDateTime.ccpp */

/******************************************************************************/
/******************************************************************************/

#include "StdAfx.h"
#include "Core.h"

namespace asi
{

const char TDateTimeUtil::DateSeparator('/');
const char TDateTimeUtil::TimeSeparator(':');
const int TDateTimeUtil::DaysPerMonth[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
const char* TDateTimeUtil::DaysOfWeekShort[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const char* TDateTimeUtil::DaysOfWeekLong[7] = { "Sunday", "Monday", "Tuesday", "Wedneday", "Thursday", "Friday", "Saturday" };
const char* TDateTimeUtil::AMPMShortIndicator[2] = { "a", "p" };
const char* TDateTimeUtil::AMPMIndicator[2] = { "am", "pm" };

/******************************************************************************/
/******************************************************************************/

bool TDateTimeUtil::isDateChar(char ch, TDateTimeFormat format)
{
	/* For time being, only these can be used for input */
	//TODO: dtf_ISO8601_Date
	if((format != dtf_MM_DD_YY) && (format != dtf_MM_DD_YYYY))
		throw ASIException("TDateTimeUtil::isDateChar", "Unknown format(%d)", (int)format);

	if(!isdigit(ch))
		return(FALSE);

	//TODO: 
	//if(format == dtf_ISO8601_Date)
	//{
	//	if(ch == '-')
	//		return(TRUE);
	//}
	//else
	//{
		if((ch == '/') || (ch == '-'))
			return(TRUE);
	//}

	return(FALSE);
}

/******************************************************************************/

bool TDateTimeUtil::isDateTimeChar(char ch, TDateTimeFormat format)
{
	/* For time being, only these can be used for input */
	//TODO: 
	//if(format != dtf_ISO8601_DateTime)
		throw ASIException("TDateTimeUtil::isDateTimeChar", "Can't parse format(%d)", (int)format);

	//if(isdigit(ch) || (ch == '-') || (ch == ':') || (ch == 'T'))
	//	return(TRUE);

	//return(FALSE);
}

/******************************************************************************/

bool TDateTimeUtil::allDateString(const char* str, TDateTimeFormat format)
{
	int len = STRLEN(str);

	for(int i = 0; i < len; i++)
		if(!isDateChar(str[i], format))
			return FALSE;

	return TRUE;
}

/******************************************************************************/

bool TDateTimeUtil::allDateTimeString(const char* str, TDateTimeFormat format)
{
	int i,len = STRLEN(str);

	for(i = 0; i < len; i++)
		if(!isDateTimeChar(str[i], format))
			return(FALSE);

	return(TRUE);
}

/******************************************************************************/

CStr32 TDateTimeUtil::dateTimeToString(ulong tDate, ulong tTime, TDateTimeFormat format)
{
	CStr32 strDate;
	CStr32 strTime;
	CStr32 strDateTime;
	int month, day, year;
	int hour, minute, second;
	int isPM;

	if(tDate != 0)
	{
		dateToMDY(tDate, month, day, year);

		switch(format)
		{
			//TODO: case dtf_ISO8601_Date:
				//str.copyVarg("%04d-%02d-%02d", year, month, day);
				//break;

			case dtf_YYYY:
				strDate.copyVarg("%04d", year);
				break;

			case dtf_MM_DD_YY:
				strDate.copyVarg("%02d%c%02d%c%02d", month, DateSeparator, day,
					DateSeparator, year % 100);
				break;
				/*
			case DF_MMDDYY:
				sprintf(str,"%02d%02d%02d",month,day,year % 100);
				break;
				*/
			case dtf_M_D_YYYY:
				strDate.copyVarg("%d%c%d%c%04d", month, DateSeparator, day,
					DateSeparator, year);
				break;
			case dtf_MM_DD_YYYY:
				strDate.copyVarg("%02d%c%02d%c%04d", month, DateSeparator, day,
					DateSeparator, year);
				break;
				/*
			case DF_MON_DD_YYYY:
				sprintf(str,"%s %d, %d",monthStr[month - 1],day,year);
				break;
			case DF_MONTH_DD_YYYY:
				sprintf(str,"%s %d, %d",longMonthStr[month - 1],day,year);
				break;
			case DF_MONTH_DD:
				sprintf(str,"%s %d",longMonthStr[month - 1],day);
				break;
			case DF_MM_YY:
				sprintf(str,"%02d%c%02d",month,gDateSeparator,year % 100);
				break;
			case DF_MMYY:
				sprintf(str,"%02d%02d",month,year % 100);
				break;
			case DF_MM_YYYY:
				sprintf(str,"%02d%c%04d",month,gDateSeparator,year);
				break;
			case DF_MON_YYYY:
				sprintf(str,"%s %d",monthStr[month - 1],year);
				break;
			case DF_MONTH_YYYY:
				sprintf(str,"%s %d",longMonthStr[month - 1],year);
				break;
			case DF_MM_DD:
				sprintf(str,"%02d%c%02d",month,gDateSeparator,day);
				break;
				*/
			case dtf_M_YY:
				strDate.copyVarg("%d%c%02d", month, DateSeparator, year % 100);
				break;
			case dtf_M_D:
				strDate.copyVarg("%d%c%d", month, DateSeparator, day, DateSeparator);
				break;
			case dtf_M_D_YYYY_H_MM_AM:
			case dtf_M_D_YYYY_H_MM_SS_AM:
				strDate.copyVarg("%d%c%d%c%d", month, DateSeparator, day, DateSeparator, year);
				break;

			case dtf_M_D_H_MM_AM:
				strDate.copyVarg("%d%c%d", month, DateSeparator, day);
				break;

			//formats with no date output
			case dtf_H_AM:
			case dtf_Ha:
			case dtf_H_MM_AM:
			case dtf_H_MMa:
				break;

			default:
				throw ASIException("TDateTimeUtil::dateToString", "Unsupported date format(%d)", (int)format);
		}
	}

	if(tTime != TIME_UNDEF)
	{
		timeToHMS(tTime, hour, minute, second);
		isPM = (hour >= 12) ? 1 : 0;
		if(hour == 0)
			hour = 12;
		else if(hour > 12)
			hour -= 12;

		switch(format)
		{
			case dtf_M_D_YYYY_H_MM_AM:
				strTime.copyVarg("%d%c%02d %s", hour, TimeSeparator, minute, AMPMIndicator[isPM]);
				break;

			case dtf_M_D_YYYY_H_MM_SS_AM:
				strTime.copyVarg("%d%c%02d%c%02d %s", hour, TimeSeparator, minute, TimeSeparator,
					second, AMPMIndicator[isPM]);
				break;

			case dtf_M_D_H_MM_AM:
				strTime.copyVarg("%d%c%02d %s", hour, TimeSeparator, minute, AMPMIndicator[isPM]);
				break;

			case dtf_H_AM:
				strTime.copyVarg("%d %s", hour, AMPMIndicator[isPM]);
				break;

			case dtf_Ha:
				strTime.copyVarg("%d%s", hour, AMPMShortIndicator[isPM]);
				break;

			case dtf_H_MM_AM:
				strTime.copyVarg("%d%c%02d %s", hour, TimeSeparator, minute, AMPMIndicator[isPM]);
				break;

			case dtf_H_MMa:
				strTime.copyVarg("%d%c%02d%s", hour, TimeSeparator, minute, AMPMShortIndicator[isPM]);
				break;

				//formats with no time output
			case dtf_MM_DD_YY:
			case dtf_MM_DD_YYYY:
			case dtf_M_D:
				break;

			default:
				throw ASIException("TDateTimeUtil::dateToString", "Unsupported time format(%d)", (int)format);
		}
	}

	if(tTime == TIME_UNDEF)
		return strDate;
	if(tDate == 0)
		return strTime;

	switch(format)
	{
		//date only formats
		case dtf_MM_DD_YY:
		case dtf_MM_DD_YYYY:
		case dtf_M_D:
			return strDate;

		//time only formats
		case dtf_H_AM:
		case dtf_Ha:
		case dtf_H_MM_AM:
		case dtf_H_MMa:
			return strTime;

		//date/time formats
		case dtf_M_D_YYYY_H_MM_AM:
		case dtf_M_D_YYYY_H_MM_SS_AM:
		case dtf_M_D_H_MM_AM:
			strDateTime.copy(strDate);
			strDateTime.concat(" ");
			strDateTime.concat(strTime);
			return strDateTime;

		default:
			throw ASIException("TDateTimeUtil::dateToString", "Unsupported time format(%d)", (int)format);
	}
}

/******************************************************************************/
//TODO: 
/*
bool TDateTimeUtil::stringToISO8601Date(const char* str, ulong& tDate)
{
	long month,day,year;
	int i,len = STRLEN(str);
	bool slash1,slash2,bad;

	tDate = 0;

	if(len == 0)
		return(TRUE);

	if(!allDateString(str, dtf_ISO8601_Date))
		return(FALSE);

	bad = slash1 = slash2 = FALSE;
	month = day = year = 0;

	for(i = 0; (i < len) && !bad; i++)
	{
		if(str[i] == '-')
		{
			if(slash1)
				if(slash2)
					bad = TRUE;
				else
					slash2 = TRUE;
			else
				slash1 = TRUE;
		}
		else if((str[i] >= '0') && (str[i] <= '9'))
		{ 
			if(slash1)
				if(slash2)
					day = day * 10 + (long)str[i] - '0';
				else
					month = month * 10 + (long)str[i] - '0';
			else
				year = year * 10 + (long)str[i] - '0';
		}
		else
			bad = TRUE;
	}

	if(!bad)
	{
		if(!slash1 && !slash2)
		{
			if(len == 8)
			{
				day = month % 100L;
				month = ((year / 100L) % 100L);
				year = year / 10000L;
			}
			else
				bad = TRUE;
		}
		else if(!(slash1 && slash2))
			bad = TRUE;

		if(!bad && (month >= 1) && (month <= 12) &&
			(year >= 0) && (year <= 4000) &&
			(day >= 1) && (day <= DaysPerMonth[(int)month - 1]))
		{
			if((month == 2) && (day == 29) && !isLeapYear((int)year))
				return(FALSE);
			else
			{
				tDate = mdyToDate((int)month,(int)day,(int)year);
				return(TRUE);
			}
		}
	}

	return(FALSE);
}
*/
/******************************************************************************/

bool TDateTimeUtil::stringToMM_DD_YYYYDate(const char* str, ulong& tDate)
{
	long month,day,year;
	int i,len = STRLEN(str);
	bool slash1,slash2,bad;

	tDate = 0;

	if(len == 0)
		return(TRUE);

	if(!allDateString(str, dtf_MM_DD_YYYY))
		return(FALSE);

	bad = slash1 = slash2 = FALSE;
	month = day = year = 0;

	for(i = 0; (i < len) && !bad; i++)
	{
		if((str[i] == '/') || (str[i] == '-'))
		{
			if(slash1)
				if(slash2)
					bad = TRUE;
				else
					slash2 = TRUE;
			else
				slash1 = TRUE;
		}
		else if((str[i] >= '0') && (str[i] <= '9'))
		{ 
			if(slash1)
				if(slash2)
					year = year * 10 + (long)str[i] - '0';
				else
					day = day * 10 + (long)str[i] - '0';
			else
				month = month * 10 + (long)str[i] - '0';
		}
		else
			bad = TRUE;
	}

	if(!bad)
	{
		if(!slash1 && !slash2)
		{
			if((month >= 0101L) && (month <= 1231L))
			{
				day = month % 100L;
				year = dateYear(getSystemDate());
				month = month / 100L;
			}
			else if((month >= 010100L) && (month <= 123199L))
			{
				day = ((month / 100L) % 100L);
				year = month % 100L;
				month = month / 10000L;
			}
			else if((month >= 01010000L) && (month <= 12319999L))
			{
				day = ((month / 10000L) % 100L);
				year = month % 10000L;
				month = month / 1000000L;
			}
			else
				bad = TRUE;
		}
		else if(slash1 && !slash2)
			year = dateYear(getSystemDate());
		else if(!(slash1 && slash2))
			bad = TRUE;

		if(!bad && (month >= 1) && (month <= 12) &&
			(year >= 0) && (year <= 4000) &&
			(day >= 1) && (day <= DaysPerMonth[(int)month - 1]))
		{
			if((year >= 0) && (year <= 99))
				year += (year > 50) ? 1900 : 2000;

			if((month == 2) && (day == 29) && !isLeapYear((int)year))
				return(FALSE);
			else
			{
				tDate = mdyToDate((int)month,(int)day,(int)year);
				return(TRUE);
			}
		}
	}

	return(FALSE);
}

/******************************************************************************/

bool TDateTimeUtil::isLeapYear(int year)
{
	int fourhund,hund,four;
	
	fourhund = (year % 400) ? TRUE : FALSE;
	hund = (year % 100) ? TRUE : FALSE;
	four = (year % 4) ? TRUE : FALSE;
	return(!four && (hund == fourhund));
}
/******************************************************************************/

DayOfWeek TDateTimeUtil::dayOfWeek(ulong tDate)
{
	return (DayOfWeek)((tDate + 2L) % 7L);
}

/******************************************************************************/

ulong TDateTimeUtil::mdyToDate(int month, int day, int year)
{
	unsigned long days,yfirst,ylast;

	if((month == 0) && (day == 0) && (year == 0))
		return 0;

	if(month <= 2)
	{
		year--;
		month += 10;
	}
	else
		month -= 2;

	yfirst = (unsigned long)year / 100L;	
	ylast = (unsigned long)year % 100L; 
	days = (yfirst << 4L) + (yfirst << 3L) + (ylast >> 2L) + (yfirst >> 2L) + 
		((unsigned long)year * 365L) + (unsigned long)((30.6 * (double)month) - 
		2.2) + (unsigned long)day;

	return(days);
}

/******************************************************************************/

void TDateTimeUtil::dateToMDY(ulong tDate, int& month, int& day, int& year)
{
	unsigned long tYear,tDays,tMonth,yfirst,ylast,yDays;
	
	if(tDate == 0)
	{
		month = day = year = 0;
		return;
	}

	tYear = (unsigned long)((double)tDate / 365.2435);
	
	yfirst = tYear / 100L;
	ylast = tYear % 100L;
	
	yDays = (tYear * 365L) + (yfirst << 4L) + (yfirst << 3L) + (ylast >> 2L) + 
		(yfirst >> 2L);
	tDays = tDate - yDays;
	
	tMonth = (unsigned long)(ceil(((double)tDays + 2.2) / 30.6)) - 1;
	month = (int)(tMonth + 2);
	
	if(tDays > 334)
		year = (int)(tYear + 1);
	else
		year = (int)tYear;
		
	if(month > 12)
		month -= 12;
		
	if(tMonth == 0)
	{
		if(isLeapYear((int)tYear))
			tDays++;
		
		if(tDays == 0)
		{
			day = 31;
			month = 1;
		}
		else
			day = (int)tDays;
	}
	else
		day = (int)(tDays - (unsigned long)((30.6 * (double)tMonth) - 2.2));
}

/******************************************************************************/

int TDateTimeUtil::dateMonth(ulong tDate)
{
	int month,day,year;

	dateToMDY(tDate, month, day, year);
	return(month);
}

/******************************************************************************/

int TDateTimeUtil::dateDay(ulong tDate)
{
	int month,day,year;

	dateToMDY(tDate, month, day, year);
	return(day);
}

/******************************************************************************/

int TDateTimeUtil::dateYear(ulong tDate)
{
	int month,day,year;

	dateToMDY(tDate, month, day, year);
	return(year);
}

/******************************************************************************/

ulong TDateTimeUtil::hmsToTime(int hour, int minute, int second)
{
	if((hour < 0) || (hour >= 24) || (minute < 0) || (minute >= 60) || (second < 0) || (second >= 60))
		return TIME_UNDEF;

	return(((ulong)hour * 3600UL) + ((ulong)minute * 60UL) + (ulong)second);
}

/******************************************************************************/

void TDateTimeUtil::timeToHMS(ulong tTime, int& hour, int& minute, int& second)
{
	if(tTime == TIME_UNDEF)
	{
		hour = minute = second = 0;
		return;
	}

	hour = (int)(tTime / 3600UL);
	minute = (int)((tTime % 3600UL) / 60UL);
	second = (int)(tTime % 60UL);
}

/******************************************************************************/

ulong TDateTimeUtil::getSystemDate()
{
	time_t secs;
	struct tm *pTm;
	
	secs = time((time_t*)NULL);
	pTm = localtime(&secs);
	
	return(mdyToDate(pTm->tm_mon + 1,pTm->tm_mday,pTm->tm_year + 1900));
}

/******************************************************************************/

ulong TDateTimeUtil::getSystemTime()
{
	time_t secs;
	struct tm *pTm;
	
	secs = time((time_t*)NULL);
	pTm = localtime(&secs);
	
	return(hmsToTime(pTm->tm_hour,pTm->tm_min,pTm->tm_sec));
}

/******************************************************************************/
/******************************************************************************/

const char* TDayOfWeek::c_str(TDateOfWeekFormat format) const
{
	if(format == dwf_Sun)
		return TDateTimeUtil::DaysOfWeekShort[fDayOfWeek];
	if(format == dwf_Sunday)
		return TDateTimeUtil::DaysOfWeekLong[fDayOfWeek];

	throw ASIException("TDayOfWeek::c_str", "Bad TDateOfWeekFormat");
}

/******************************************************************************/
/******************************************************************************/

int TTimeSpan::getDays() const
{
	return (int)fDays;
}

/******************************************************************************/

int TTimeSpan::getHours() const
{
	double days = fDays;
	double temp;
	int hour, minute, second;
	double modifier = 1.0;

	if(days < 0)
	{
		days = abs(days);
		modifier = -1.0;
	}

	ulong tTime = (ulong)((modf(days, &temp) * (double)SECONDS_PER_DAY) + 0.5);
	TDateTimeUtil::timeToHMS(tTime, hour, minute, second);

	return hour * modifier;
}

/******************************************************************************/

int TTimeSpan::getMinutes() const
{
	double days = fDays;
	double temp;
	int hour, minute, second;
	double modifier = 1.0;

	if(days < 0)
	{
		days = abs(days);
		modifier = -1.0;
	}

	ulong tTime = (ulong)((modf(days, &temp) * (double)SECONDS_PER_DAY) + 0.5);
	TDateTimeUtil::timeToHMS(tTime, hour, minute, second);

	return minute * modifier;
}

/******************************************************************************/

int TTimeSpan::getSeconds() const
{
	double days = fDays;
	double temp;
	int hour, minute, second;
	double modifier = 1.0;

	if(days < 0)
	{
		days = abs(days);
		modifier = -1.0;
	}

	ulong tTime = (ulong)((modf(days, &temp) * (double)SECONDS_PER_DAY) + 0.5);
	TDateTimeUtil::timeToHMS(tTime, hour, minute, second);

	return second * modifier;
}

/******************************************************************************/
/******************************************************************************/

TDate::TDate(int month, int day, int year)
{
	fDate = TDateTimeUtil::mdyToDate(month, day, year);
}

/******************************************************************************/

TDate::TDate(const char* str, TDateTimeFormat format)
{
	/* For time being, only these can be used for input */
	//TODO: 
	/*
	if(format != dtf_ISO8601_Date)
	{
		//ERRORDEBUG( ErrorMsg("StringToDate: format not supported for input"); );
		throw ASIException("TDateTime::TDateTime", "can't parse format(%d)", (int)format);
	}

	if(format == dtf_ISO8601_Date)
	{
		if(TDateTimeUtil::stringToISO8601Date(str, fDate))
			return;
	}
	//else if((format == DF_MM_YY) || (format == DF_MM_YYYY))
	//	return(StringToMMYYYYDate(str,tDate));
	*/

	throw ASIException("TDateTime::TDateTime", "can't parse format(%d)", (int)format);
}

/******************************************************************************/

TTimeSpan TDate::compare(const TDate& tDate)
{
	double d1 = (double)fDate;
	double d2 = (double)tDate.fDate;

	return TTimeSpan(d1 - d2);
}

/******************************************************************************/

const char* TDate::c_str(TDateTimeFormat format) const
{
	CStr32 str = TDateTimeUtil::dateTimeToString(fDate, TIME_UNDEF, format);
	int size = str.len() + 1;
	#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
	(const_cast<TDate*>(this))->fFormatted.reset(new char[size]);
	#else
	(const_cast<TDate*>(this))->fFormatted = auto_ptr<char>(new char[size]);
	#endif
	tStrCpy(fFormatted.get(), size, str.c_str());

	return fFormatted.get();
}

/******************************************************************************/

TDate TDate::getSystemDate()
{
	int month;
	int day;
	int year;
	ulong date;

	date = TDateTimeUtil::getSystemDate();
	TDateTimeUtil::dateToMDY(date, month, day, year);

	return TDate(month, day, year);
}

/******************************************************************************/
/******************************************************************************/

TDateTime::TDateTime(int month, int day, int year, int hour, int minute, int second) : TDate(month, day, year)
{
	if(fDate == 0)
		fTime = TIME_UNDEF;
	else
		fTime = TDateTimeUtil::hmsToTime(hour, minute, second);
}

/******************************************************************************/

TDateTime::TDateTime(const char* str, TDateTimeFormat format)
{
	/* For time being, only these can be used for input */
	//TODO: 
	/*
	if(format != dtf_ISO8601_DateTime)
	{
		//ERRORDEBUG( ErrorMsg("StringToDate", "format not supported for input"); );
		throw ASIException("TDateTime::TDateTime", "can't parse format(%d)", (int)format);
	}
	*/
	//if(format == dtf_ISO8601_DateTime)
	//{
	//	if(TDateTimeUtil::stringToMM_DD_YYYYDate(str, fDate))
	//		return;
	//}
	
	throw ASIException("TDateTime::TDateTime", "can't parse format(%d)", (int)format);
}

/******************************************************************************/

TTimeSpan TDateTime::compare(const TDateTime& tDateTime)
{
	double d1 = (double)fDate + (double)fTime / (double)SECONDS_PER_DAY;
	double d2 = (double)tDateTime.fDate + (double)tDateTime.fTime / (double)SECONDS_PER_DAY;

	return TTimeSpan(d1 - d2);
}

/******************************************************************************/

const char* TDateTime::c_str(TDateTimeFormat format) const
{
	CStr32 str = TDateTimeUtil::dateTimeToString(fDate, fTime, format);
	int size = str.len() + 1;
	#if !defined(_MSC_VER) || (_MSC_VER >= 1300)
	(const_cast<TDateTime*>(this))->fFormatted.reset(new char[size]);
	#else
	(const_cast<TDateTime*>(this))->fFormatted = auto_ptr<char>(new char[size]);
	#endif
	tStrCpy(fFormatted.get(), size, str.c_str());

	return fFormatted.get();
}

/******************************************************************************/

TDateTime TDateTime::getSystemDateTime()
{
	int month;
	int day;
	int year;
	int hour;
	int minute;
	int second;
	ulong date;
	ulong time;

	date = TDateTimeUtil::getSystemDate();
	TDateTimeUtil::dateToMDY(date, month, day, year);

	time = TDateTimeUtil::getSystemTime();
	TDateTimeUtil::timeToHMS(time, hour, minute, second);

	return TDateTime(month, day, year, hour, minute, second);
}

/******************************************************************************/

};	//namespace asi

/******************************************************************************/
/******************************************************************************/
