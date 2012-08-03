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

#ifndef SysConstH
#define SysConstH

#include <wx/wx.h>

wxString GetRunError(unsigned short Errno);

static wxChar* const SAbortError = wxT("Operation aborted");
static wxChar* const SAbstractError = wxT("Abstract method called");
static wxChar* const SAccessDenied = wxT("Access denied");
static wxChar* const SAccessViolation = wxT("Access violation");
static wxChar* const SArgumentMissing =
  wxT("Missing argument in format \"%s\"");
static wxChar* const SAssertError = wxT("%s (%s, line %d)");
static wxChar* const SAssertionFailed = wxT("Assertion failed");
static wxChar* const SBusError = wxT("Bus error or misaligned data access");
static wxChar* const SCannotCreateEmptyDir =
  wxT("Cannot create empty directory");
static wxChar* const SControlC = wxT("Control-C hit");
static wxChar* const SDiskFull = wxT("Disk Full");
static wxChar* const SDispatchError = wxT("No variant method call dispatch");
static wxChar* const SDivByZero = wxT("Division by zero");
static wxChar* const SEndOfFile = wxT("Read past end of file");
static wxChar* const SErrInvalidDateMonthWeek =
  wxT("Year %d, month %d, Week %d and day %d is not a valid date.");
static wxChar* const SErrInvalidDateWeek =
  wxT("%d %d %d is not a valid dateweek");
static wxChar* const SErrInvalidDayOfWeek =
  wxT("%d is not a valid day of the week");
static wxChar* const SErrInvalidDayOfWeekInMonth =
  wxT("Year %d Month %d NDow %d DOW %d is not a valid date");
static wxChar* const SErrInvalidDayOfYear =
  wxT("Year %d does not have a day number %d");
static wxChar* const SErrInvalidTimeStamp =
  wxT("Invalid date/timestamp : \"%s\"");
static wxChar* const SExceptionErrorMessage = wxT("exception at %p");
static wxChar* const SExceptionStack = wxT("Exception stack error");
static wxChar* const SExecuteProcessFailed = wxT("Failed to execute %s : %d");
static wxChar* const SExternalException = wxT("External exception %x");
static wxChar* const SFileNotAssigned = wxT("File not assigned");
static wxChar* const SFileNotFound = wxT("File not found");
static wxChar* const SFileNotOpen = wxT("File not open");
static wxChar* const SFileNotOpenForInput = wxT("File not open for input");
static wxChar* const SFileNotOpenForOutput = wxT("File not open for output");
static wxChar* const SInValidFileName = wxT("Invalid filename");
static wxChar* const SIntOverflow = wxT("Arithmetic overflow");
static wxChar* const SIntfCastError = wxT("Interface not supported");
static wxChar* const SInvalidArgIndex =
  wxT("Invalid argument index in format \"%s\"");
static wxChar* const SInvalidBoolean = wxT("\"%s\" is not a valid boolean.");
static wxChar* const SInvalidCast = wxT("Invalid type cast");
static wxChar* const SInvalidCurrency = wxT("Invalid currency: \"%s\"");
static wxChar* const SInvalidDateTime =
  wxT("%f is not a valid date/time value.");
static wxChar* const SInvalidDrive = wxT("Invalid drive specified");
static wxChar* const SInvalidFileHandle = wxT("Invalid file handle");
static wxChar* const SInvalidFloat = wxT("\"%s\" is an invalid float");
static wxChar* const SInvalidFormat = wxT("Invalid format specifier : \"%s\"");
static wxChar* const SInvalidGUID = wxT("\"%s\" is not a valid GUID value");
static wxChar* const SInvalidInput = wxT("Invalid input");
static wxChar* const SInvalidInteger = wxT("\"%s\" is an invalid integer");
static wxChar* const SInvalidOp = wxT("Invalid floating point operation");
static wxChar* const SInvalidPointer = wxT("Invalid pointer operation");
static wxChar* const SInvalidVarCast = wxT("Invalid variant type cast");
static wxChar* const SInvalidVarNullOp = wxT("Invalid NULL variant operation");
static wxChar* const SInvalidVarOp = wxT("Invalid variant operation");
static wxChar* const SInvalidVarOpWithHResultWithPrefix =
  wxT("Invalid variant operation (%s%.8x) %s");
static wxChar * const SNoError = wxT("No error.");
static wxChar* const SNoThreadSupport =
  wxT("Threads not supported. Recompile program with thread driver.");
static wxChar* const SOSError = wxT("System error, (OS Code %d): %s");
static wxChar* const SOutOfMemory = wxT("Out of memory");
static wxChar* const SOverflow = wxT("Floating point overflow");
static wxChar* const SPrivilege = wxT("Privileged instruction");
static wxChar* const SRangeError = wxT("Range check error");
static wxChar* const SSafecallException = wxT("Exception in safecall method");
static wxChar* const STooManyOpenFiles = wxT("Too many open files");
static wxChar* const SUnKnownRunTimeError =
  wxT("Unknown Run-Time error : %3.3d");
static wxChar* const SUnderflow = wxT("Floating point underflow");
static wxChar* const SUnkOSError = wxT("An operating system call failed.");
static wxChar* const SUnknown = wxT("Unknown run-time error code: ");
static wxChar* const SUnknownErrorCode = wxT("Unknown error code: %d");
static wxChar* const SVarArrayBounds = wxT("Variant array bounds error");
static wxChar* const SVarArrayCreate = wxT("Variant array cannot be created");
static wxChar* const SVarArrayLocked = wxT("Variant array locked");
static wxChar* const SVarBadType = wxT("Invalid variant type");
static wxChar* const SVarInvalid = wxT("Invalid argument");
static wxChar* const SVarInvalid1 = wxT("Invalid argument: %s");
static wxChar* const SVarNotArray = wxT("Variant doesn\'t contain an array");
static wxChar* const SVarNotImplemented = wxT("Operation not supported");
static wxChar* const SVarOutOfMemory = wxT("Variant operation ran out memory");
static wxChar* const SVarOverflow = wxT("Variant overflow");
static wxChar* const SVarParamNotFound = wxT("Variant Parameter not found");
static wxChar* const SVarTypeAlreadyUsedWithPrefix =
  wxT("Custom variant type (%s%.4x) already used by %s");
static wxChar* const SVarTypeConvertOverflow =
  wxT("Overflow while converting variant of type (%s) into type (%s)");
static wxChar* const SVarTypeCouldNotConvert =
  wxT("Could not convert variant of type (%s) into type (%s)");
static wxChar* const SVarTypeNotUsableWithPrefix =
  wxT("Custom variant type (%s%.4x) is not usable");
static wxChar* const SVarTypeOutOfRangeWithPrefix =
  wxT("Custom variant type (%s%.4x) is out of range");
static wxChar* const SVarTypeRangeCheck1 =
  wxT("Range check error for variant of type (%s)");
static wxChar* const SVarTypeRangeCheck2 =
  wxT("Range check error while converting variant of type (%s) into type (%s)");
static wxChar* const SVarTypeTooManyCustom =
  wxT("Too many custom variant types have been registered");
static wxChar* const SVarUnexpected = wxT("Unexpected variant error");

static wxChar* const SFallbackError =
  wxT("An error, whose error code is larger than can be returned to the OS, has occured"
  );

static wxChar* const SNoToolserver =
  wxT("Toolserver is not installed, cannot execute Tool");

static wxChar* const SShortMonthNameJan = wxT("Jan");
static wxChar* const SShortMonthNameFeb = wxT("Feb");
static wxChar* const SShortMonthNameMar = wxT("Mar");
static wxChar* const SShortMonthNameApr = wxT("Apr");
static wxChar* const SShortMonthNameMay = wxT("May");
static wxChar* const SShortMonthNameJun = wxT("Jun");
static wxChar* const SShortMonthNameJul = wxT("Jul");
static wxChar* const SShortMonthNameAug = wxT("Aug");
static wxChar* const SShortMonthNameSep = wxT("Sep");
static wxChar* const SShortMonthNameOct = wxT("Oct");
static wxChar* const SShortMonthNameNov = wxT("Nov");
static wxChar* const SShortMonthNameDec = wxT("Dec");

static wxChar* const SLongMonthNameJan = wxT("January");
static wxChar* const SLongMonthNameFeb = wxT("February");
static wxChar* const SLongMonthNameMar = wxT("March");
static wxChar* const SLongMonthNameApr = wxT("April");
static wxChar* const SLongMonthNameMay = wxT("May");
static wxChar* const SLongMonthNameJun = wxT("June");
static wxChar* const SLongMonthNameJul = wxT("July");
static wxChar* const SLongMonthNameAug = wxT("August");
static wxChar* const SLongMonthNameSep = wxT("September");
static wxChar* const SLongMonthNameOct = wxT("October");
static wxChar* const SLongMonthNameNov = wxT("November");
static wxChar* const SLongMonthNameDec = wxT("December");

static wxChar* const SShortDayNameMon = wxT("Mon");
static wxChar* const SShortDayNameTue = wxT("Tue");
static wxChar* const SShortDayNameWed = wxT("Wed");
static wxChar* const SShortDayNameThu = wxT("Thu");
static wxChar* const SShortDayNameFri = wxT("Fri");
static wxChar* const SShortDayNameSat = wxT("Sat");
static wxChar* const SShortDayNameSun = wxT("Sun");

static wxChar* const SLongDayNameMon = wxT("Monday");
static wxChar* const SLongDayNameTue = wxT("Tuesday");
static wxChar* const SLongDayNameWed = wxT("Wednesday");
static wxChar* const SLongDayNameThu = wxT("Thursday");
static wxChar* const SLongDayNameFri = wxT("Friday");
static wxChar* const SLongDayNameSat = wxT("Saturday");
static wxChar* const SLongDayNameSun = wxT("Sunday");

#endif//INCLUDED_SYSCONST_H
// END
