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

#include "dateutils.h"
#include <wx/wx.h>
#include <wx/datetime.h>
#include "sysconst.h"
#include "sysutils.h"

int DaysPerYear ( bool LeapYear )
{
  if ( LeapYear )
    return 365;
  else
    return 366;
}

wxDateTime Frac ( const wxDateTime& AValue )
{
  wxDateTime Result( AValue.GetHour(), AValue.GetMinute(), AValue.GetSecond(), AValue.GetMillisecond() );
  return Result;
}

wxDateTime DateOf ( const wxDateTime& AValue )
{
  return Trunc ( AValue );
}

wxDateTime TimeOf ( const wxDateTime & AValue )
{
  return Frac ( AValue );
}

bool IsInLeapYear ( const wxDateTime & AValue )
{
  return wxDateTime::IsLeapYear ( AValue.GetYear() );
}

bool IsPM ( const wxDateTime & AValue )
{
  return AValue.GetHour() >= 12;
}

bool IsValidDate ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay )
{
  wxDateTime datetm ( AYear, AMonth, ADay );
  return datetm.IsValid();
}


bool IsValidTime ( const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, unsigned short const& AMilliSecond )
{
  wxDateTime datetm = wxDateTime::Now();
  datetm.Set(AHour, AMinute, ASecond, AMilliSecond);
  return datetm.IsValid();
}

bool IsValidDateTime ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, unsigned short const& AHour, unsigned short const& AMinute, unsigned short const& ASecond, const unsigned short & AMilliSecond )
{
  return IsValidDate ( AYear, AMonth, ADay ) && IsValidTime ( AHour, AMinute, ASecond, AMilliSecond );
}

bool IsValidDateDay ( const unsigned short & AYear, const unsigned short & ADayOfYear )
{
  return  ( AYear != 0 ) && ( ADayOfYear != 0 ) && ( AYear < 10000 ) &&
           ( ADayOfYear <= DaysPerYear ( wxDateTime::IsLeapYear ( AYear ) ) );;
}

bool IsValidDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear, const unsigned short & ADayOfWeek )
{
  return  ( AYear != 0 ) && ( AYear < 10000 ) && ( InDayOfWeekRange ( ADayOfWeek ) ) && ( AWeekOfYear != 0 ) && ( AWeekOfYear <= WeeksInAYear ( AYear ) );

}

bool IsValidDateMonthWeek ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek )
{
  return ( AYear != 0 ) && ( AYear < 10000 )
           && ( InMonthRange ( AMonth )  )
           && ( InWeekOfMonthRange ( AWeekOfMonth ) )
           && ( InDayOfWeekRange ( ADayOfWeek ) );
}

unsigned short WeeksInYear ( const wxDateTime& AValue )
{
  return WeeksInAYear ( AValue.GetYear() );;
}

unsigned short WeeksInAYear ( const unsigned short& AYear )
{
  unsigned short Result = 52;
  unsigned short DOW = DayOfTheWeek ( StartOfAYear ( AYear ) );
  if (  ( DOW == 4 ) || ( ( DOW == 3 ) && wxDateTime::IsLeapYear ( AYear ) ) )
    ++Result;
  return Result;
}

unsigned short DaysInYear ( const wxDateTime& AValue )
{
  return DaysPerYear ( wxDateTime::IsLeapYear ( AValue.GetYear() ) );
}

unsigned short DaysInAYear ( const unsigned short& AYear )
{
  return DaysPerYear ( wxDateTime::IsLeapYear ( AYear ) );
}

unsigned short DaysInMonth ( const wxDateTime & AValue )
{
  return MonthDays[ wxDateTime::IsLeapYear ( AValue.GetYear() ) ][AValue.GetMonth() ];
}

unsigned short DaysInAMonth ( const unsigned short& AYear, const unsigned short& AMonth )
{
  return MonthDays[ wxDateTime::IsLeapYear ( AYear ) ][AMonth ];;
}

wxDateTime Today( void )
{
  return wxDateTime::Today();
}

wxDateTime Yesterday( void )
{
  return wxDateTime::Today().Subtract ( wxDateSpan::Day() );
}

wxDateTime Tomorrow()
{
  return  wxDateTime::Today().Add ( wxDateSpan::Day() );
}

bool IsToday (const wxDateTime& AValue )
{
  return wxDateTime::Today().IsSameDate ( AValue );
}

bool IsSameDay ( const wxDateTime& AValue, const wxDateTime& ABasis )
{
  return Trunc ( AValue ).IsSameDate ( Trunc ( ABasis ) );
}

static unsigned short const DOWMap[ 7 ] = { 7 , 1 , 2 , 3 , 4 , 5 , 6 };

unsigned short PreviousDayOfWeek ( const unsigned short DayOfWeek )
{
  if (  ! ( InDayOfWeekRange ( DayOfWeek ) ) )
    throw EConvertError::CreateFmt ( wxString::Format ( SErrInvalidDayOfWeek, DayOfWeek ) );
  return DOWMap[ DayOfWeek ];
}

unsigned short YearOf ( const wxDateTime& AValue )
{
  return AValue.GetYear();
}

unsigned short MonthOf ( const wxDateTime& AValue )
{
  return AValue.GetMonth();
}

unsigned short WeekOf ( const wxDateTime& AValue )
{
  unsigned short Result = WeekOfTheYear ( AValue );
  return Result;
}

unsigned short DayOf ( const wxDateTime& AValue )
{
  return AValue.GetDay();
}

unsigned short HourOf ( const wxDateTime& AValue )
{
  return AValue.GetHour();
}

unsigned short MinuteOf ( const wxDateTime& AValue )
{
  return AValue.GetMinute();
}

unsigned short SecondOf ( const wxDateTime& AValue )
{
  return AValue.GetSecond();
}

unsigned short MilliSecondOf (const wxDateTime& AValue )
{
  return AValue.GetMillisecond();;
}

wxDateTime StartOfTheYear (const wxDateTime& AValue )
{
  wxDateTime Result = AValue;
  return Result.SetMonth ( ( wxDateTime::Month ) 0 ).SetDay ( 1 );
}

wxDateTime EndOfTheYear (const wxDateTime& AValue )
{
  return wxDateTime ( AValue.GetYear(), ( wxDateTime::Month ) 11, 30, 23, 59, 59, 999 );
}

wxDateTime StartOfAYear (const unsigned short & AYear )
{
  return wxDateTime ( AYear, 0, 0 );
}

wxDateTime EndOfAYear (const unsigned short & AYear )
{
  return wxDateTime ( AYear, ( wxDateTime::Month ) 12, 31, 23, 59, 59, 999 ) ;
}

wxDateTime StartOfTheMonth ( const wxDateTime & AValue )
{
  wxDateTime Result = AValue;
  Result.SetDay ( 0 );
  return Result;
}

wxDateTime EndOfTheMonth (const wxDateTime & AValue )
{
  wxDateTime Result ( MonthDays[ IsInLeapYear ( AValue ) ][ AValue.GetMonth() ], ( wxDateTime::Month ) AValue.GetMonth(), AValue.GetYear(), ( wxDateTime::wxDateTime_t ) 23, ( wxDateTime::wxDateTime_t ) 59, ( wxDateTime::wxDateTime_t ) 59, ( wxDateTime::wxDateTime_t ) 999 );
  return Result;
}

wxDateTime StartOfAMonth (const unsigned short & AYear,const unsigned short & AMonth )
{
  return wxDateTime ( AYear, AMonth, 0 );
}

wxDateTime EndOfAMonth (const unsigned short & AYear,const unsigned short & AMonth )
{
  return EncodeDateTime ( AYear, AMonth, MonthDays[ IsInLeapYear ( AYear ) ][ AMonth ], 23, 59, 59, 999 );
}

wxDateTime StartOfTheWeek (const wxDateTime & AValue )
{
  return Trunc ( AValue - wxDateSpan ( 0, DayOfTheWeek ( AValue ) + 1 ) );
}

wxDateTime EndOfTheWeek (const wxDateTime & AValue )
{
  return EndOfTheDay ( AValue - wxDateSpan ( 0, DayOfTheWeek ( AValue ) + 7 ) );
}

wxDateTime StartOfAWeek (const unsigned short & AYear,const unsigned short & AWeekOfYear,const   unsigned short & ADayOfWeek )
{
  return EncodeDateWeek ( AYear, AWeekOfYear, ADayOfWeek );
}

wxDateTime StartOfAWeek (const unsigned short & AYear,const unsigned short & AWeekOfYear )
{
  return StartOfAWeek ( AYear, AWeekOfYear, 1 );
}

wxDateTime EndOfAWeek (const unsigned short & AYear,const unsigned short & AWeekOfYear,const   unsigned short & ADayOfWeek )
{
  return EndOfTheDay ( EncodeDateWeek ( AYear , AWeekOfYear , ADayOfWeek ) );
}

wxDateTime EndOfAWeek (const unsigned short & AYear,const unsigned short & AWeekOfYear )
{
  return EndOfAWeek ( AYear, AWeekOfYear, 7 );
}

wxDateTime StartOfTheDay (const wxDateTime & AValue )
{
  return Trunc ( AValue );
}


wxDateTime EndOfTheDay (const wxDateTime & AValue )
{
  wxDateTime Result = AValue;
  Result.Set ( 23, 59, 59, 999 );
  return Result;
}


wxDateTime StartOfADay (const unsigned short & AYear,const unsigned short & AMonth,const unsigned short & ADay )
{
  wxDateTime Result ( AYear, AMonth, ADay );
  return Result;
}


wxDateTime StartOfADay (const unsigned short& AYear,const unsigned short & ADayOfYear )
{
  wxDateTime Result ( AYear, 1, 1 ) ;
  Result = Result.Add ( wxDateSpan ( 0, 0, 0, ADayOfYear - 1 ) );
  return Result;
}


wxDateTime EndOfADay ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay )
{
  return EndOfTheDay ( EncodeDate ( AYear, AMonth, ADay ) );
}


wxDateTime EndOfADay ( const unsigned short & AYear, const unsigned short & ADayOfYear )
{
  return StartOfADay ( AYear, ADayOfYear ).Set ( 23, 59, 59, 999 );
}

unsigned short MonthOfTheYear ( const wxDateTime & AValue )
{
  unsigned short Result ,  Y, D;
  DecodeDate ( AValue, Y, Result, D );
  return Result;
}

unsigned short WeekOfTheYear ( const wxDateTime & AValue )
{
  unsigned short Result, Y, DOW;
  DecodeDateWeek ( AValue, Y, Result, DOW );
  return Result;
}

unsigned short WeekOfTheYear ( const wxDateTime & AValue,   unsigned short & AYear )
{
  unsigned short Result , DOW;
  DecodeDateWeek ( AValue, AYear, Result, DOW );
  return Result;
}

unsigned short DayOfTheYear ( const wxDateTime & AValue )
{
  wxTimeSpan tsp = AValue.Subtract ( StartOfTheYear ( AValue ) );
  return tsp.GetDays();
}

unsigned short HourOfTheYear ( const wxDateTime & AValue )
{
  unsigned short Result , H, M, S, MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = H + ( ( DayOfTheYear ( AValue ) - 1 ) * 24 );
  return Result;
}

unsigned long MinuteOfTheYear ( const wxDateTime & AValue )
{
  unsigned long Result ;
  unsigned short  H , M , S, MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = M + ( H + ( ( DayOfTheYear ( AValue ) - 1 ) * 24 ) ) * 60;
  return Result;
}


unsigned long SecondOfTheYear ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short H , M , S, MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( M + ( H + ( ( DayOfTheYear ( AValue ) - 1 ) * 24 ) ) * 60 ) * 60 + S;
  return Result;
}

long MilliSecondOfTheYear ( const wxDateTime & AValue )
{
  long Result;
  unsigned short H , M , S, MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( ( M + ( H + ( ( DayOfTheYear ( AValue ) - 1 ) * 24 ) ) * 60 ) * 60 + S ) * 1000 + MS;
  return Result;
}


unsigned short WeekOfTheMonth ( const wxDateTime & AValue )
{
  unsigned short Result, Y , M , DOW;
  DecodeDateMonthWeek ( AValue, Y, M, Result, DOW );
  return Result;
}

unsigned short WeekOfTheMonth ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AMonth )
{
  unsigned short Result , DOW;
  DecodeDateMonthWeek ( AValue, AYear, AMonth, Result, DOW );
  return Result;
}

unsigned short DayOfTheMonth ( const wxDateTime & AValue )
{
  unsigned short Result , Y , M;
  DecodeDate ( AValue, Y, M, Result );
  return Result;
}

unsigned short HourOfTheMonth ( const wxDateTime & AValue )
{
  unsigned short Result , Y , M , D , H , N , S , MS;
  DecodeDateTime ( AValue, Y, M, D, H, N, S, MS );
  Result = ( D - 1 ) * 24 + H;
  return Result;
}


unsigned short MinuteOfTheMonth ( const wxDateTime & AValue )
{
  unsigned short Result , Y , M , D , H , N , S , MS;
  DecodeDateTime ( AValue, Y, M, D, H, N, S, MS );
  Result = ( ( D - 1 ) * 24 + H ) * 60 + N;
  return Result;
}


unsigned long SecondOfTheMonth ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short Y , M , D , H , N , S , MS;
  DecodeDateTime ( AValue, Y, M, D, H, N, S, MS );
  Result = ( ( ( D - 1 ) * 24 + H ) * 60 + N ) * 60 + S;
  return Result;
}


unsigned long MilliSecondOfTheMonth ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short Y , M , D , H , N , S , MS;
  DecodeDateTime ( AValue, Y, M, D, H, N, S, MS );
  Result = ( ( ( ( D - 1 ) * 24 + H ) * 60 + N ) * 60 + S ) * 1000 + MS;
  return Result;
}

unsigned short DayOfTheWeek ( const wxDateTime & AValue )
{
  unsigned short Result;
  Result = DOWMap[ DayOfWeek ( AValue ) ];
  return Result;
}

unsigned short HourOfTheWeek ( const wxDateTime & AValue )
{
  unsigned short Result , H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( DayOfTheWeek ( AValue ) - 1 ) * 24 + H;
  return Result;
}

unsigned short MinuteOfTheWeek ( const wxDateTime & AValue )
{
  unsigned short Result , H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( ( DayOfTheWeek ( AValue ) - 1 ) * 24 + H ) * 60 + M;
  return Result;
}

unsigned long SecondOfTheWeek ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( ( ( DayOfTheWeek ( AValue ) - 1 ) * 24 + H ) * 60 + M ) * 60 + S;
  return Result;
}

unsigned long MilliSecondOfTheWeek ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( ( ( ( DayOfTheWeek ( AValue ) - 1 ) * 24 + H ) * 60 + M ) * 60 + S ) * 1000 + MS;
  return Result;
}

unsigned short HourOfTheDay ( const wxDateTime & AValue )
{
  unsigned short Result , M , S , MS;
  DecodeTime ( AValue, Result, M, S, MS );
  return Result;
}

unsigned short MinuteOfTheDay ( const wxDateTime & AValue )
{
  unsigned short Result , H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( H * 60 ) + M;
  return Result;
}

unsigned long SecondOfTheDay ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( ( H * 60 ) + M ) * 60 + S;
  return Result;
}

unsigned long MilliSecondOfTheDay ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( ( ( H * 60 ) + M ) * 60 + S ) * 1000 + MS;
  return Result;
}

unsigned short MinuteOfTheHour ( const wxDateTime & AValue )
{
  unsigned short Result , H , S , MS;
  DecodeTime ( AValue, H, Result, S, MS );
  return Result;
}

unsigned short SecondOfTheHour ( const wxDateTime & AValue )
{
  unsigned short Result , H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = M * 60 + S;
  return Result;
}

unsigned long MilliSecondOfTheHour ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = ( M * 60 + S ) * 1000 + MS;
  return Result;
}

unsigned short SecondOfTheMinute ( const wxDateTime & AValue )
{
  unsigned short Result;
  unsigned short H , M , MS;
  DecodeTime ( AValue, H, M, Result, MS );
  return Result;
}

unsigned long MilliSecondOfTheMinute ( const wxDateTime & AValue )
{
  unsigned long Result;
  unsigned short H , M , S , MS;
  DecodeTime ( AValue, H, M, S, MS );
  Result = S * 1000 + MS;
  return Result;
}

unsigned short MilliSecondOfTheSecond ( const wxDateTime & AValue )
{
  unsigned short Result;
  unsigned short H , M , S ;
  DecodeTime ( AValue, H, M, S, Result );
  return Result;
}

bool WithinPastYears ( const wxDateTime & ANow, const wxDateTime & AThen,   const int & AYears )
{
  return YearsBetween ( ANow, AThen ) <= AYears;
}

bool WithinPastMonths ( const wxDateTime & ANow, const wxDateTime & AThen,   const int & AMonths )
{
  return MonthsBetween ( ANow, AThen ) <= AMonths;
}

bool WithinPastWeeks ( const wxDateTime & ANow, const wxDateTime & AThen,   const int & AWeeks )
{
  return WeeksBetween ( ANow, AThen ) <= AWeeks;
}

bool WithinPastDays ( const wxDateTime & ANow, const wxDateTime & AThen,   const int & ADays )
{
  return DaysBetween ( ANow, AThen ) <= ADays;
}

bool WithinPastHours ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & AHours )
{
  return HoursBetween ( ANow, AThen ) <= AHours;
}

bool WithinPastMinutes ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & AMinutes )
{
  return MinutesBetween ( ANow, AThen ) <= AMinutes;
}

bool WithinPastSeconds ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & ASeconds )
{
  return SecondsBetween ( ANow, AThen ) <= ASeconds;
}

bool WithinPastMilliSeconds ( const wxDateTime & ANow, const wxDateTime & AThen,   const long & AMilliSeconds )
{
  return MilliSecondsBetween ( ANow, AThen ) <= AMilliSeconds;
}

int YearsBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return ( AThen.GetYear() - ANow.GetYear() );
}

int MonthsBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  //Fixme: Important
  THROW_NOT_IMPLEMENTED_ERROR;
  /*
    wxTimeSpan tsp = AThen.Subtract(ANow);
    wxDateSpan Result =  wxDateSpan(0,0,0,0);
      Result = tsp + Result;
    return Result.GetMonths();
  */
}

int WeeksBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  wxTimeSpan tsp = AThen.Subtract ( ANow );
  return tsp.GetWeeks();
}

int DaysBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  wxTimeSpan tsp = AThen.Subtract ( ANow );
  return tsp.GetDays();
}
long HoursBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  long Result = ( DaysBetween ( ANow, AThen ) * HoursPerDay );
  //Fixme: Check if we need to give the exact hours
  //Result = Result - ANow.GetHour() + AThen.GetHour();
  return Result;
}

long MinutesBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  long Result = ( DaysBetween ( ANow, AThen ) * MinsPerDay );
  //Fixme: Check if we need to give the exact hours
  //Result = Result - ANow.GetHour() + AThen.GetHour();
  return Result;
}

long SecondsBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  long Result = ( DaysBetween ( ANow, AThen ) * SecsPerDay );
  //Fixme: Check if we need to give the exact hours
  //Result = Result - ANow.GetHour() + AThen.GetHour();
  return Result;
}

long MilliSecondsBetween ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  long Result = ( DaysBetween ( ANow, AThen ) * MSecsPerDay );
  //Fixme: Check if we need to give the exact hours
  //Result = Result - ANow.GetHour() + AThen.GetHour();
  return Result;
}

double YearSpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return ( DaysBetween ( ANow, AThen ) * 1.0 ) / ApproxDaysPerYear;
}


double MonthSpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return ( DaysBetween ( ANow, AThen ) * 1.0 ) / ApproxDaysPerMonth;
}


double WeekSpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return ( DaysBetween ( ANow, AThen ) * 1.0 ) / 7;
}


double DaySpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return ( DaysBetween ( ANow, AThen ) * 1.0 );
}


double HourSpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return ( DaysBetween ( ANow, AThen ) * HoursPerDay );
}


double MinuteSpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return  ( DaysBetween ( ANow, AThen ) * MinsPerDay );
}


double SecondSpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return  ( DaysBetween ( ANow, AThen ) * SecsPerDay );
}


double MilliSecondSpan ( const wxDateTime & ANow, const wxDateTime & AThen )
{
  return  ( DaysBetween ( ANow, AThen ) * MSecsPerDay );
}

wxDateTime IncYear ( const wxDateTime & AValue,   const int & ANumberOfYears )

{
  wxDateTime Result;
  unsigned short Y, M , D , H , N , S , MS;
  DecodeDateTime ( AValue, Y, M, D, H, N, S, MS );
  Y = Y + ANumberOfYears;
  if (  ( M == 2 ) && ( D == 29 ) && ( !IsLeapYear ( Y ) ) )
    D = 28;
  Result = EncodeDateTime ( Y, M, D, H, N, S, MS );
  return Result;
}


wxDateTime IncYear ( const wxDateTime & AValue )
{
  return  IncYear ( AValue, 1 );
}


wxDateTime IncWeek ( const wxDateTime & AValue,   const int & ANumberOfWeeks )
{
  return  AValue.Add ( wxDateSpan ( 0, 0, ANumberOfWeeks, 0 ) ) ;
}


wxDateTime IncWeek ( const wxDateTime & AValue )
{
  return  IncWeek ( AValue, 1 );
}


wxDateTime IncDay ( const wxDateTime & AValue,   const int & ANumberOfDays )
{
  return  AValue.Add ( wxDateSpan ( 0, 0, 0, ANumberOfDays ) ) ;
}


wxDateTime IncDay ( const wxDateTime & AValue )
{
  return  IncDay ( AValue, 1 );
}


wxDateTime IncHour ( const wxDateTime & AValue,   const long & ANumberOfHours )
{
  return AValue.Add ( wxTimeSpan ( ANumberOfHours, 0, 0, 0 ) ) ;
}


wxDateTime IncHour ( const wxDateTime & AValue )
{
  return IncHour ( AValue, 1 );
}


wxDateTime IncMinute ( const wxDateTime & AValue,   const long & ANumberOfMinutes )
{
  return AValue.Add ( wxTimeSpan ( 0, ANumberOfMinutes, 0, 0 ) ) ;
}


wxDateTime IncMinute ( const wxDateTime & AValue )
{
  return IncMinute ( AValue, 1 );
}


wxDateTime IncSecond ( const wxDateTime & AValue,   const long & ANumberOfSeconds )
{
  return AValue.Add ( wxTimeSpan ( 0, 0, ANumberOfSeconds, 0 ) ) ;
}


wxDateTime IncSecond ( const wxDateTime & AValue )
{
  return IncSecond ( AValue, 1 );
}


wxDateTime IncMilliSecond ( const wxDateTime & AValue,   const long & ANumberOfMilliSeconds )
{
  return AValue.Add ( wxTimeSpan ( 0, 0, 0, ANumberOfMilliSeconds ) ) ;
}


wxDateTime IncMilliSecond ( const wxDateTime & AValue ) 
{
  return IncMilliSecond ( AValue, 1 );
}

wxDateTime EncodeDateTime ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond )
{
  wxDateTime Result;
  if (  !TryEncodeDateTime ( AYear , AMonth , ADay , AHour , AMinute , ASecond , AMilliSecond, Result ) )
    InvalidDateTimeError ( AYear , AMonth , ADay , AHour , AMinute , ASecond , AMilliSecond );
  return Result;
}


void DecodeDateTime ( const wxDateTime & AValue, unsigned short & AYear, unsigned short & AMonth, unsigned short & ADay, unsigned short & AHour, unsigned short & AMinute, unsigned short & ASecond, unsigned short & AMilliSecond )
{
  DecodeDate ( AValue, AYear, AMonth, ADay );
  DecodeTime ( AValue, AHour, AMinute, ASecond, AMilliSecond );
}


bool TryEncodeDateTime ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond,   wxDateTime & AValue )
{
  wxDateTime dt ( ( wxDateTime::wxDateTime_t ) ADay, ( wxDateTime::Month ) AMonth, AYear, AHour, AMinute, ASecond, AMilliSecond );
  if ( dt.IsValid() == false )
    return false;
   AValue = dt;
  return true;
}

wxDateTime EncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   const unsigned short & ADayOfWeek )
{
  wxDateTime Result;
  if (  !TryEncodeDateWeek ( AYear, AWeekOfYear, Result, ADayOfWeek ) )
    InvalidDateWeekError ( AYear, AWeekOfYear, ADayOfWeek );
  return Result;
}


wxDateTime EncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear ) 
{
  return EncodeDateWeek ( AYear, AWeekOfYear, 1 );
}


void DecodeDateWeek ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AWeekOfYear, unsigned short & ADayOfWeek )
{
  AYear = AValue.GetYear();
  AWeekOfYear = WeekOfTheYear ( AValue );
  ADayOfWeek = DayOfWeek ( AValue );
}

bool TryEncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   wxDateTime & AValue,   const unsigned short & ADayOfWeek )
{
  unsigned short DOW;
  int Rest;
  wxDateTime dt;
  bool Result = IsValidDateWeek ( AYear, AWeekOfYear, ADayOfWeek );
  if (  Result )
  {
    AValue = EncodeDate ( AYear, 1, 1 ).Add ( wxDateSpan ( 0, 0, 0, ( 7 * ( AWeekOfYear - 1 ) ) ) );
    DOW = DayOfTheWeek ( AValue );
    Rest = ADayOfWeek - DOW;
    if (  ( DOW > 4 ) )
      Rest += 7;
    AValue = AValue.Add ( wxDateSpan ( 0, 0, 0, Rest ) );
  }
  return Result;
}

bool TryEncodeDateWeek ( const unsigned short & AYear, const unsigned short & AWeekOfYear,   wxDateTime & AValue ) 
{
  return TryEncodeDateWeek ( AYear, AWeekOfYear, AValue, 1 );
}

wxDateTime EncodeDateDay ( const unsigned short & AYear, const unsigned short & ADayOfYear )
{
  wxDateTime Result;
  if (  !TryEncodeDateDay ( AYear, ADayOfYear, Result ) )
    InvalidDateDayError ( AYear, ADayOfYear );
  return Result;
}

void DecodeDateDay ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & ADayOfYear )
{
  unsigned short M , D;
  DecodeDate ( AValue, AYear, M, D );
  wxTimeSpan tsp = AValue - EncodeDate ( AYear, 1, 1 );
  ADayOfYear = tsp.GetDays() + 1;
}

bool TryEncodeDateDay ( const unsigned short & AYear, const unsigned short & ADayOfYear,   wxDateTime & AValue )
{
  bool Result = ( ADayOfYear != 0 ) && ( ADayOfYear <= DaysPerYear ( IsLeapYear ( AYear ) ) );
  if (  Result )
    AValue = EncodeDate ( AYear, 1, 1 ) + wxDateSpan ( 0, 0, 0, ADayOfYear - 1 );
  return Result;
}

wxDateTime EncodeDateMonthWeek ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek )
{
  wxDateTime Result;
  if (  !TryEncodeDateMonthWeek ( AYear, AMonth, AWeekOfMonth, ADayOfWeek, Result ) )
    InvalidDateMonthWeekError ( AYear, AMonth, AWeekOfMonth, ADayOfWeek );
  return Result;
}

void DecodeDateMonthWeek ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AMonth, unsigned short & AWeekOfMonth, unsigned short & ADayOfWeek )
{
  AYear = AValue.GetYear();
  AMonth = AValue.GetMonth();
  AWeekOfMonth = WeekOfTheMonth ( AValue );
  ADayOfWeek = DayOfTheWeek ( AValue );
}

bool TryEncodeDateMonthWeek ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek,   wxDateTime & AValue )
{
  unsigned short S;
  int DOM;
  bool Result = IsValidDateMonthWeek ( AYear, AMonth, AWeekOfMonth, ADayOfWeek );
  if (  Result )
  {
    AValue = EncodeDate ( AYear, AMonth, 1 );
    DOM = ( AWeekOfMonth - 1 ) * 7 + ADayOfWeek - 1;
    /* Correct for first week in last month.*/
    S = DayOfTheWeek ( AValue );
    DOM -= S - 1;
    if ( (  S == DayFriday ) ||  (  S == DaySaturday ) || (  S ==  DaySunday )  )
      DOM += 7;
    AValue = AValue.Add ( wxDateSpan ( 0, 0, 0, DOM ) );
  }
  return Result;
}

wxDateTime RecodeYear ( const wxDateTime & AValue,   const unsigned short & AYear )
{
  return wxDateTime ( AValue ).SetYear ( AYear );
}

wxDateTime RecodeMonth ( const wxDateTime & AValue,   const unsigned short & AMonth )
{
  return wxDateTime ( AValue ).SetMonth ( ( wxDateTime::Month ) AMonth );
}

wxDateTime RecodeDay ( const wxDateTime & AValue,   const unsigned short & ADay )
{
  return wxDateTime ( AValue ).SetDay ( ADay );
}

wxDateTime RecodeHour ( const wxDateTime & AValue,   const unsigned short & AHour )
{
  return wxDateTime ( AValue ).SetHour ( AHour );
}

wxDateTime RecodeMinute ( const wxDateTime & AValue,   const unsigned short & AMinute )
{
  return wxDateTime ( AValue ).SetMinute ( AMinute );
}

wxDateTime RecodeSecond ( const wxDateTime & AValue,   const unsigned short & ASecond )
{
  return wxDateTime ( AValue ).SetSecond ( ASecond );
}

wxDateTime RecodeMilliSecond ( const wxDateTime & AValue,   const unsigned short & AMilliSecond )
{
  return wxDateTime ( AValue ).SetMillisecond ( AMilliSecond );
}


wxDateTime RecodeDate ( const wxDateTime & AValue,   const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay )
{
  return  wxDateTime ( AValue ).Set ( AYear, AMonth, ADay );
}


wxDateTime RecodeTime ( const wxDateTime & AValue,   const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond )
{
  return  wxDateTime ( AValue ).Set ( AHour, AMinute, ASecond, AMilliSecond );
}

wxDateTime RecodeDateTime ( const wxDateTime & AValue,   const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond )
{
  return  wxDateTime ( AValue ).Set ( ADay, ( wxDateTime::Month ) AMonth, AYear, AHour, AMinute, ASecond, AMilliSecond );
}

bool TryRecodeDateTime ( const wxDateTime & AValue,   const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond,   wxDateTime & AResult )
{
  //Check how this works
  return TryEncodeDateTime ( AYear, AMonth, ADay, AHour, AMinute, ASecond, AMilliSecond, AResult );
}

TValueRelationship CompareDateTime ( const wxDateTime & A, const wxDateTime & B )
{
  TValueRelationship Result;
  if (  SameDateTime ( A, B ) )
    Result = EqualsValue;
  else
    if (  A > B )
      Result = GreaterThanValue;
    else
      Result = LessThanValue;
  return Result;
}


TValueRelationship CompareDate ( const wxDateTime & A, const wxDateTime & B )
{
  TValueRelationship Result;
  if (  SameDate ( A, B ) )
    Result = EqualsValue;
  else
    if (  A < B )
      Result = LessThanValue;
    else
      Result = GreaterThanValue;
  return Result;
}


TValueRelationship CompareTime ( const wxDateTime & A, const wxDateTime & B )

{
  TValueRelationship Result;
  if (  SameTime ( A, B ) )
    Result = EqualsValue;
  else
    if (  Frac ( A ) < Frac ( B ) )
      Result = LessThanValue;
    else
      Result = GreaterThanValue;
  return Result;
}


bool SameDateTime ( const wxDateTime & A, const wxDateTime & B )
{
  return ( A.IsSameTime ( B ) && A.IsSameDate ( B ) );
}

bool SameDate ( const wxDateTime & A, const wxDateTime & B )
{
  return A.IsSameDate ( B );
}

bool SameTime ( const wxDateTime & A, const wxDateTime & B )
{
  return A.IsSameTime ( B );
}

unsigned short InternalNthDayOfWeek ( unsigned short DOM )
{
  unsigned short Result = ( DOM - 1 ) / 7 + 1;
  return Result;
}

unsigned short NthDayOfWeek ( const wxDateTime & AValue )
{
  unsigned short Result = InternalNthDayOfWeek ( DayOfTheMonth ( AValue ) );
  return Result;
}


void DecodeDayOfWeekInMonth ( const wxDateTime & AValue,   unsigned short & AYear, unsigned short & AMonth, unsigned short & ANthDayOfWeek, unsigned short & ADayOfWeek )
{
  unsigned short D = 0;
  DecodeDate ( AValue, AYear, AMonth, D );
  ADayOfWeek = DayOfTheWeek ( AValue );
  ANthDayOfWeek = InternalNthDayOfWeek ( D );
}


wxDateTime EncodeDayOfWeekInMonth ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ANthDayOfWeek, const unsigned short & ADayOfWeek )
{
  wxDateTime Result;
  if (  !TryEncodeDayOfWeekInMonth ( AYear, AMonth, ANthDayOfWeek, ADayOfWeek, Result ) )
    InvalidDayOfWeekInMonthError ( AYear, AMonth, ANthDayOfWeek, ADayOfWeek );
  return Result;
}


bool TryEncodeDayOfWeekInMonth ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ANthDayOfWeek, const unsigned short & ADayOfWeek,   wxDateTime & AValue )
{
  unsigned short SOM , D;
  SOM = DayOfTheWeek ( EncodeDate ( AYear, AMonth, 1 ) );
  D = 1 + ADayOfWeek - SOM + 7 * ( ANthDayOfWeek - 1 );
  if (  SOM > ADayOfWeek )
    D = D + 7; 
  bool Result = TryEncodeDate ( AYear, AMonth, D, AValue );
  return Result;
}

wxString DoField ( unsigned int Arg, unsigned short Def,  wxString Unknown , const wxDateTime &ABaseDate )
{
  wxString Result;
  if (  ( Arg != LFAI ) )
    Result = Format ( wxT("%.*d"),  Length ( Unknown ), Arg  );
  else
    if ( ABaseDate.IsValid() == false )
      Result = Unknown;
    else
      Result = Format ( wxT("%.*d"), Length ( Unknown ), Arg );
  return Result;
}

void InvalidDateTimeError (const wxDateTime & ErrorDate, const wxDateTime & ABaseDate )
{
  unsigned short Y , M , D , H , N , S , MS;
  wxString Msg;
  DecodeDateTime ( ABaseDate, Y, M, D, H, N, S, MS );
  Msg = DoField ( ErrorDate.GetYear(), Y, wxT("????") , ABaseDate );
  Msg = Msg + DateSeparator + DoField ( ErrorDate.GetMonth(), M, wxT("??") , ABaseDate );
  Msg = Msg + DateSeparator + DoField ( ErrorDate.GetDay(), D, wxT("??") , ABaseDate );
  Msg = Msg + wxT(" ") + DoField ( ErrorDate.GetHour(), H, wxT("??") , ABaseDate );
  Msg = Msg + TimeSeparator + DoField ( ErrorDate.GetMinute(), N, wxT("??") , ABaseDate );
  Msg = Msg + TimeSeparator + DoField ( ErrorDate.GetSecond(), S, wxT("??") , ABaseDate );
  Msg = Msg + DecimalSeparator + DoField ( ErrorDate.GetMillisecond(), MS, wxT("???") , ABaseDate );
  throw EConvertError::CreateFmt ( wxString::Format ( SErrInvalidTimeStamp,  Msg.c_str() ) );
}

void InvalidDateTimeError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond,   const wxDateTime & ABaseDate )
{
  unsigned short Y , M , D , H , N , S , MS;
  wxString Msg;
  DecodeDateTime ( ABaseDate, Y, M, D, H, N, S, MS );
  Msg = DoField ( AYear, Y, wxT("????") , ABaseDate );
  Msg = Msg + DateSeparator + DoField ( AMonth, M, wxT("??") , ABaseDate );
  Msg = Msg + DateSeparator + DoField ( ADay, D, wxT("??") , ABaseDate );
  Msg = Msg + wxT(" ") + DoField ( AHour, H, wxT("??") , ABaseDate );
  Msg = Msg + TimeSeparator + DoField ( AMinute, N, wxT("??") , ABaseDate );
  Msg = Msg + TimeSeparator + DoField ( ASecond, S, wxT("??") , ABaseDate );
  Msg = Msg + DecimalSeparator + DoField ( AMilliSecond, MS, wxT("???") , ABaseDate );
  throw EConvertError::CreateFmt ( wxString::Format ( SErrInvalidTimeStamp,  Msg.c_str() ) );
}


void InvalidDateTimeError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ADay, const unsigned short & AHour, const unsigned short & AMinute, const unsigned short & ASecond, const unsigned short & AMilliSecond )
{
  InvalidDateTimeError ( AYear, AMonth, ADay, AHour, AMinute, ASecond, AMilliSecond, wxDefaultDateTime );
}


void InvalidDateWeekError ( const unsigned short & AYear, const unsigned short & AWeekOfYear, const unsigned short & ADayOfWeek )
{
  throw EConvertError::CreateFmt ( wxString::Format ( SErrInvalidDateWeek,  AYear, AWeekOfYear, ADayOfWeek ) );
}


void InvalidDateDayError ( const unsigned short & AYear, const unsigned short & ADayOfYear )
{
  throw EConvertError::CreateFmt ( wxString::Format ( SErrInvalidDayOfYear,  AYear, ADayOfYear ) );
}


void InvalidDateMonthWeekError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & AWeekOfMonth, const unsigned short & ADayOfWeek )
{
  throw EConvertError::CreateFmt ( wxString::Format ( SErrInvalidDateMonthWeek,  AYear, AMonth, AWeekOfMonth, ADayOfWeek ) );
}


void InvalidDayOfWeekInMonthError ( const unsigned short & AYear, const unsigned short & AMonth, const unsigned short & ANthDayOfWeek, const unsigned short & ADayOfWeek )
{
  throw EConvertError::CreateFmt ( wxString::Format ( SErrInvalidDayOfWeekInMonth, AYear, AMonth, ANthDayOfWeek, ADayOfWeek ) );
}


double DateTimeToJulianDate ( const wxDateTime & AValue )
{
  return AValue.GetJulianDayNumber();
}


wxDateTime JulianDateToDateTime ( const double & AValue )
{
  wxDateTime Result;
  if (TryJulianDateToDateTime(AValue,Result) == false)
  {
    throw EConvertError::CreateFmt ( wxString::Format ( wxT("Invalid Julian Date %f"),  AValue ) );
  }
  return Result;
}


bool TryJulianDateToDateTime ( const double & AValue,   wxDateTime & ADateTime )
{
  bool Result = false;
  wxDateTime DTTest;
  DTTest.Set(AValue);
  if (DTTest.IsValid())
  {
    ADateTime = DTTest;
    Result = true;
  }
  return Result;
}

double DateTimeToModifiedJulianDate ( const wxDateTime & AValue )
{
  return AValue.GetModifiedJulianDayNumber();
}


wxDateTime ModifiedJulianDateToDateTime ( const double & AValue )
{
  //Fixme: Important
  THROW_NOT_IMPLEMENTED_ERROR;
}


bool TryModifiedJulianDateToDateTime ( const double & AValue,   wxDateTime & ADateTime )
{
  //Fixme: Important
  THROW_NOT_IMPLEMENTED_ERROR;
}

long DateTimeToUnix ( const wxDateTime & AValue )
{
  wxDateTime Epoch = EncodeDateTime ( 1970 , 1 , 1 , 0 , 0 , 0 , 0 );
  return SecondsBetween ( Epoch , AValue );
}


wxDateTime UnixToDateTime ( const long & AValue )
{
  wxDateTime Epoch = EncodeDateTime ( 1970 , 1 , 1 , 0 , 0 , 0 , 0 );
  return IncSecond ( Epoch , AValue );
}


long UnixTimeStampToMac ( const long & AValue )
{
  static double const Epoch = 24107 * 24 * 3600;
  return AValue + Epoch;
}

long DateTimeToMac ( const wxDateTime & AValue )
{
  wxDateTime Epoch = EncodeDateTime ( 1904 , 1 , 1 , 0 , 0 , 0 , 0 );
  return SecondsBetween ( Epoch , AValue );
}


wxDateTime MacToDateTime ( const long & AValue )
{
  wxDateTime Epoch = EncodeDateTime ( 1904 , 1 , 1 , 0 , 0 , 0 , 0 );
  return IncSecond ( Epoch , AValue );
}


long MacTimeStampToUnix ( const long & AValue )
{
  static double const Epoch = 24107 * 24 * 3600;
  return AValue - Epoch;
}
