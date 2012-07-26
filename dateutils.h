/*
Authors : Guru Kathiresan - gururamnath@yahoo.com , 
          FreePascal Team - http://www.freepascal.org

License :

Short Verion : wxVCL is distributed under Modified LGPL 
(the same license used by FCL, LCL). In short, 
this license allows you to use wxVCL in your application either 
statically or dynamically linked (and keep your source code as 
closed source) but you cannot sell wxVCL alone as a seperate 
product or claim owner ship for it and when you make a change to 
the wxVCL library (not your application code), you have to give 
the changes (of the wxVCL library code) back to the community.

Long Version : The source code of wxVCL is distributed under the 
Library GNU General Public License with the following modification:

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent modules,
and to copy and distribute the resulting executable under terms of your choice,
provided that you also meet, for each linked independent module, the terms
and conditions of the license of that module. An independent module is a module
which is not derived from or based on this library. If you modify this
library, you may extend this exception to your version of the library, but you are
not obligated to do so. If you do not wish to do so, delete this exception
statement from your version.
*/

#pragma once
#ifndef DateUtilsH
#define DateUtilsH

#include <wx/wx.h>
#include <wx/datetime.h>
#include "sysconst.h"
#include "sysutils.h"

const int DaysPerWeek = 7;
const int WeeksPerFortnight = 2;
const int MonthsPerYear = 12;
const int YearsPerDecade = 10;
const int YearsPerCentury = 100;
const int YearsPerMillennium = 1000;

const int DayMonday = 1;
const int DayTuesday = 2;
const int DayWednesday = 3;
const int DayThursday = 4;
const int DayFriday = 5;
const int DaySaturday = 6;
const int DaySunday = 7;

const double OneHour = 1 * 1.0 / HoursPerDay;
const double OneMinute = 1 * 1.0 / MinsPerDay;
const double OneSecond = 1 * 1.0 / SecsPerDay;
const double OneMillisecond = 1 * 1.0 / MSecsPerDay;

const int DaysInLeapYear = 366;
const int DaysInNoneLeapYear = 365;

const double ApproxDaysPerMonth = 30.4375;
const double ApproxDaysPerYear = 365.25;
const unsigned int RecodeLeaveFieldAsIS = UINT_MAX;
const unsigned int LFAI = RecodeLeaveFieldAsIS;

enum TValueRelationship
{
  LessThanValue = -1,
  EqualsValue = 0,
  GreaterThanValue = 1
};

bool InMonthRange ( int AValue )
{
  return ( AValue > 0 && AValue < 12 );
}

bool InWeekOfMonthRange ( int AValue )
{
  return ( AValue > 0 && AValue < 6 );
}

bool InDayOfWeekRange ( int AValue )
{
  return ( AValue > 0 && AValue < 7 );
}

/* ---------------------------------------------------------------------
  Forward Declaration
---------------------------------------------------------------------*/
/* ---------------------------------------------------------------------
  Simple trimming functions.
---------------------------------------------------------------------*/
wxDateTime DateOf ( const wxDateTime & AValue );
wxDateTime TimeOf ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Identification functions.
---------------------------------------------------------------------*/
bool IsInLeapYear ( const wxDateTime & AValue );
bool IsPM ( const wxDateTime & AValue );
bool IsValidDate ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay );
bool IsValidTime ( const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond );
bool IsValidDateTime ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond );
bool IsValidDateDay ( const unsigned short & AYear, const unsigned short & ADayOfYear );
bool IsValidDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear, const unsigned short & ADayOfWeek );
bool IsValidDateMonthWeek ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek );
/* ---------------------------------------------------------------------
  Enumeration functions.
---------------------------------------------------------------------*/
unsigned short WeeksInYear ( const wxDateTime & AValue );
unsigned short WeeksInAYear ( const unsigned short & AYear );
unsigned short DaysInYear ( const wxDateTime & AValue );
unsigned short DaysInAYear ( const unsigned short & AYear );
unsigned short DaysInMonth ( const wxDateTime & AValue );
unsigned short DaysInAMonth ( const unsigned short & AYear, const unsigned short & AMonth );
/* ---------------------------------------------------------------------
  Variations on current date/time.
---------------------------------------------------------------------*/
wxDateTime Today();
wxDateTime Yesterday();
wxDateTime Tomorrow();
bool IsToday ( const wxDateTime & AValue );
bool IsSameDay ( const wxDateTime & AValue, const wxDateTime & ABasis );
unsigned short PreviousDayOfWeek ( unsigned short DayOfWeek );
/* ---------------------------------------------------------------------
  Extraction functions.
---------------------------------------------------------------------*/
unsigned short YearOf ( const wxDateTime & AValue );
unsigned short MonthOf ( const wxDateTime & AValue );
unsigned short WeekOf ( const wxDateTime & AValue );
unsigned short DayOf ( const wxDateTime & AValue );
unsigned short HourOf ( const wxDateTime & AValue );
unsigned short MinuteOf ( const wxDateTime & AValue );
unsigned short SecondOf ( const wxDateTime & AValue );
unsigned short MilliSecondOf ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Start/End of year functions.
---------------------------------------------------------------------*/
wxDateTime StartOfTheYear ( const wxDateTime & AValue );
wxDateTime EndOfTheYear ( const wxDateTime & AValue );
wxDateTime StartOfAYear ( const unsigned short & AYear );
wxDateTime EndOfAYear ( const unsigned short & AYear );
/* ---------------------------------------------------------------------
  Start/End of month functions.
---------------------------------------------------------------------*/
wxDateTime StartOfTheMonth ( const wxDateTime & AValue );
wxDateTime EndOfTheMonth ( const wxDateTime & AValue );
wxDateTime StartOfAMonth ( const unsigned short & AYear, const unsigned short & AMonth );
wxDateTime EndOfAMonth ( const unsigned short & AYear, const unsigned short & AMonth );
/* ---------------------------------------------------------------------
  Start/End of week functions.
---------------------------------------------------------------------*/
wxDateTime StartOfTheWeek ( const wxDateTime & AValue );
wxDateTime EndOfTheWeek ( const wxDateTime & AValue );
wxDateTime StartOfAWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   const unsigned short & ADayOfWeek );
wxDateTime StartOfAWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear ); // ADayOFWeek 1
wxDateTime EndOfAWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   const unsigned short & ADayOfWeek );
wxDateTime EndOfAWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear ); // const ADayOfWeek: Word = 7
/* ---------------------------------------------------------------------
  Start/End of day functions.
---------------------------------------------------------------------*/
wxDateTime StartOfTheDay ( const wxDateTime & AValue );
wxDateTime EndOfTheDay ( const wxDateTime & AValue );
wxDateTime StartOfADay ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay ) /*overload*/;
wxDateTime StartOfADay ( const unsigned short & AYear, const unsigned short & ADayOfYear ) /*overload*/;
wxDateTime EndOfADay ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay ) /*overload*/;
wxDateTime EndOfADay ( const unsigned short & AYear, const unsigned short & ADayOfYear ) /*overload*/;
/* ---------------------------------------------------------------------
  Part of year functions.
---------------------------------------------------------------------*/
unsigned short MonthOfTheYear ( const wxDateTime & AValue );
unsigned short WeekOfTheYear ( const wxDateTime & AValue ) /*overload*/;
unsigned short WeekOfTheYear ( const wxDateTime & AValue,   unsigned short & AYear ) /*overload*/;
unsigned short DayOfTheYear ( const wxDateTime & AValue );
unsigned short HourOfTheYear ( const wxDateTime & AValue );
unsigned long MinuteOfTheYear ( const wxDateTime & AValue );
unsigned long SecondOfTheYear ( const wxDateTime & AValue );
long MilliSecondOfTheYear ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Part of month functions.
---------------------------------------------------------------------*/
unsigned short WeekOfTheMonth ( const wxDateTime & AValue ) /*overload*/;
unsigned short WeekOfTheMonth ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AMonth ) /*overload*/;
unsigned short DayOfTheMonth ( const wxDateTime & AValue );
unsigned short HourOfTheMonth ( const wxDateTime & AValue );
unsigned short MinuteOfTheMonth ( const wxDateTime & AValue );
unsigned long SecondOfTheMonth ( const wxDateTime & AValue );
unsigned long MilliSecondOfTheMonth ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Part of week functions.
---------------------------------------------------------------------*/
unsigned short DayOfTheWeek ( const wxDateTime & AValue );
unsigned short HourOfTheWeek ( const wxDateTime & AValue );
unsigned short MinuteOfTheWeek ( const wxDateTime & AValue );
unsigned long SecondOfTheWeek ( const wxDateTime & AValue );
unsigned long MilliSecondOfTheWeek ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Part of day functions.
---------------------------------------------------------------------*/
unsigned short HourOfTheDay ( const wxDateTime & AValue );
unsigned short MinuteOfTheDay ( const wxDateTime & AValue );
unsigned long SecondOfTheDay ( const wxDateTime & AValue );
unsigned long MilliSecondOfTheDay ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Part of hour functions.
---------------------------------------------------------------------*/
unsigned short MinuteOfTheHour ( const wxDateTime & AValue );
unsigned short SecondOfTheHour ( const wxDateTime & AValue );
unsigned long MilliSecondOfTheHour ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Part of minute functions.
---------------------------------------------------------------------*/
unsigned short SecondOfTheMinute ( const wxDateTime & AValue );
unsigned long MilliSecondOfTheMinute ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Part of second functions.
---------------------------------------------------------------------*/
unsigned short MilliSecondOfTheSecond ( const wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Range checking functions.
---------------------------------------------------------------------*/
bool WithinPastYears ( const wxDateTime & ANow, const wxDateTime & AThen,   int const& AYears );
bool WithinPastMonths ( const wxDateTime & ANow, const wxDateTime & AThen,   int const& AMonths );
bool WithinPastWeeks ( const wxDateTime & ANow, const wxDateTime & AThen,   int const& AWeeks );
bool WithinPastDays ( const wxDateTime & ANow, const wxDateTime & AThen,   int const& ADays );
bool WithinPastHours ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & AHours );
bool WithinPastMinutes ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & AMinutes );
bool WithinPastSeconds ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & ASeconds );
bool WithinPastMilliSeconds ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & AMilliSeconds );
/* ---------------------------------------------------------------------
  Period functions.
---------------------------------------------------------------------*/
int YearsBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
int MonthsBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
int WeeksBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
int DaysBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
long HoursBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
long MinutesBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
long SecondsBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
long MilliSecondsBetween ( const wxDateTime & ANow, const wxDateTime & AThen );
/* ---------------------------------------------------------------------
  Timespan in xxx functions.
---------------------------------------------------------------------*/
/* YearSpan and MonthSpan are approximate values */
double YearSpan ( const wxDateTime & ANow, const wxDateTime & AThen );
double MonthSpan ( const wxDateTime & ANow, const wxDateTime & AThen );
double WeekSpan ( const wxDateTime & ANow, const wxDateTime & AThen );
double DaySpan ( const wxDateTime & ANow, const wxDateTime & AThen );
double HourSpan ( const wxDateTime & ANow, const wxDateTime & AThen );
double MinuteSpan ( const wxDateTime & ANow, const wxDateTime & AThen );
double SecondSpan ( const wxDateTime & ANow, const wxDateTime & AThen );
double MilliSecondSpan ( const wxDateTime & ANow, const wxDateTime & AThen );
/* ---------------------------------------------------------------------
  Increment/decrement functions.
---------------------------------------------------------------------*/
wxDateTime IncYear ( const wxDateTime & AValue,   int const& ANumberOfYears );
wxDateTime IncYear ( const wxDateTime & AValue ); // ; const ANumberOfYears: Integer = 1)
// Function IncMonth is in SysUtils
wxDateTime IncWeek ( const wxDateTime & AValue,   int const& ANumberOfWeeks );
wxDateTime IncWeek ( const wxDateTime & AValue ); // ; const ANumberOfWeeks: Integer = 1)
wxDateTime IncDay ( const wxDateTime & AValue,   int const& ANumberOfDays );
wxDateTime IncDay ( const wxDateTime & AValue ); //; const ANumberOfDays: Integer = 1)
wxDateTime IncHour ( const wxDateTime & AValue,   const long & ANumberOfHours );
wxDateTime IncHour ( const wxDateTime & AValue ); //; const ANumberOfHours: Int64 = 1
wxDateTime IncMinute ( const wxDateTime & AValue,   const long & ANumberOfMinutes );
wxDateTime IncMinute ( const wxDateTime & AValue ); // ; const ANumberOfMinutes: Int64 = 1
wxDateTime IncSecond ( const wxDateTime & AValue,   const long & ANumberOfSeconds );
wxDateTime IncSecond ( const wxDateTime & AValue ); // ; const ANumberOfSeconds: Int64 = 1
wxDateTime IncMilliSecond ( const wxDateTime & AValue,   const long & ANumberOfMilliSeconds );
wxDateTime IncMilliSecond ( const wxDateTime & AValue ); // ; const ANumberOfMilliSeconds: Int64 = 1
/* ---------------------------------------------------------------------
  Encode/Decode of complete timestamp
---------------------------------------------------------------------*/
wxDateTime EncodeDateTime ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond );
void DecodeDateTime ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AMonth, unsigned short & ADay, unsigned short & AHour, unsigned short & AMinute, unsigned short & ASecond, unsigned short & AMilliSecond );
bool TryEncodeDateTime ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond,   wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Encode/decode date, specifying week of year and day of week
---------------------------------------------------------------------*/
wxDateTime EncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   const unsigned short & ADayOfWeek );
wxDateTime EncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear ); //; const ADayOfWeek: Word = 1
void DecodeDateWeek ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AWeekOfYear, unsigned short & ADayOfWeek );
bool TryEncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   wxDateTime & AValue,   const unsigned short & ADayOfWeek );
bool TryEncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   wxDateTime & AValue ); //; const ADayOfWeek: Word = 1
/* ---------------------------------------------------------------------
  Encode/decode date, specifying day of year
---------------------------------------------------------------------*/
wxDateTime EncodeDateDay ( const unsigned short & AYear, const unsigned short & ADayOfYear );
void DecodeDateDay ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & ADayOfYear );
bool TryEncodeDateDay ( const unsigned short & AYear, const unsigned short & ADayOfYear,   wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Encode/decode date, specifying week of month
---------------------------------------------------------------------*/
wxDateTime EncodeDateMonthWeek ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek );
void DecodeDateMonthWeek ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AMonth, unsigned short & AWeekOfMonth, unsigned short & ADayOfWeek );
bool TryEncodeDateMonthWeek ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek,   wxDateTime & AValue );
/* ---------------------------------------------------------------------
  Replace given element with supplied value.
---------------------------------------------------------------------*/
wxDateTime RecodeYear ( const wxDateTime & AValue,   const unsigned short & AYear );
wxDateTime RecodeMonth ( const wxDateTime & AValue,   const unsigned short & AMonth );
wxDateTime RecodeDay ( const wxDateTime & AValue,   const unsigned short & ADay );
wxDateTime RecodeHour ( const wxDateTime & AValue,   const unsigned short & AHour );
wxDateTime RecodeMinute ( const wxDateTime & AValue,   const unsigned short & AMinute );
wxDateTime RecodeSecond ( const wxDateTime & AValue,   const unsigned short & ASecond );
wxDateTime RecodeMilliSecond ( const wxDateTime & AValue,   const unsigned short & AMilliSecond );
wxDateTime RecodeDate ( const wxDateTime & AValue,   const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay );
wxDateTime RecodeTime ( const wxDateTime & AValue,   const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond );
wxDateTime RecodeDateTime ( const wxDateTime & AValue,   const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond );
bool TryRecodeDateTime ( const wxDateTime & AValue,   const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond,   wxDateTime & AResult );
/* ---------------------------------------------------------------------
  Comparision of date/time
---------------------------------------------------------------------*/
TValueRelationship CompareDateTime ( const wxDateTime & A, const wxDateTime & B );
TValueRelationship CompareDate ( const wxDateTime & A, const wxDateTime & B );
TValueRelationship CompareTime ( const wxDateTime & A, const wxDateTime & B );
bool SameDateTime ( const wxDateTime & A, const wxDateTime & B );
bool SameDate ( const wxDateTime & A, const wxDateTime & B );
bool SameTime ( const wxDateTime & A, const wxDateTime & B );
/* For a given date these Functions tell you the which day of the week of the
  month (or year).  If its a Thursday, they will tell you if its the first,
  second, etc Thursday of the month (or year).  Remember, even though its
  the first Thursday of the year it doesn't mean its the first week of the
  year.  See ISO 8601 above for more information. */
unsigned short NthDayOfWeek ( const wxDateTime & AValue );
void DecodeDayOfWeekInMonth ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AMonth, unsigned short & ANthDayOfWeek, unsigned short & ADayOfWeek );
wxDateTime EncodeDayOfWeekInMonth ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ANthDayOfWeek, const unsigned short & ADayOfWeek );
bool TryEncodeDayOfWeekInMonth ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ANthDayOfWeek, const unsigned short & ADayOfWeek,   wxDateTime & AValue );
/* ---------------------------------------------------------------------
    Exception throwing routines
  ---------------------------------------------------------------------*/
void InvalidDateTimeError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond,   const wxDateTime & ABaseDate );
void InvalidDateTimeError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond ); // const ABaseDate: wxDateTime = 0
void InvalidDateWeekError ( const unsigned short & AYear, const unsigned short & AWeekOfYear, const unsigned short & ADayOfWeek );
void InvalidDateDayError ( const unsigned short & AYear, const unsigned short & ADayOfYear );
void InvalidDateMonthWeekError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek );
void InvalidDayOfWeekInMonthError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ANthDayOfWeek, const unsigned short & ADayOfWeek );
/* ---------------------------------------------------------------------
  Julian and Modified Julian Date conversion support
---------------------------------------------------------------------*/
double DateTimeToJulianDate ( const wxDateTime & AValue );
wxDateTime JulianDateToDateTime ( const double & AValue );
bool TryJulianDateToDateTime ( const double & AValue,   wxDateTime & ADateTime );
double DateTimeToModifiedJulianDate ( const wxDateTime & AValue );
wxDateTime ModifiedJulianDateToDateTime ( const double & AValue );
bool TryModifiedJulianDateToDateTime ( const double & AValue,   wxDateTime & ADateTime );
/* ---------------------------------------------------------------------
  Unix timestamp support.
---------------------------------------------------------------------*/
long DateTimeToUnix ( const wxDateTime & AValue );
wxDateTime UnixToDateTime ( const long & AValue );
long UnixTimeStampToMac ( const long & AValue );
/* ---------------------------------------------------------------------
  Mac timestamp support.
---------------------------------------------------------------------*/
long DateTimeToMac ( const wxDateTime & AValue );
wxDateTime MacToDateTime ( const long & AValue );
long MacTimeStampToUnix ( const long & AValue );

#endif//DateUtilsH
