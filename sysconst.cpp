#include "sysconst.h"

wxString GetRunError ( unsigned short Errno )
{
  wxString result;
  switch ( Errno )
  {
    case 0:
      result = SNoError;
    case 1:
      result = SOutOfMemory;
    case 2:
      result = SFileNotFound;
    case 3:
      result = SInValidFileName;
    case 4:
      result = STooManyOpenFiles;
    case 5:
      result = SAccessDenied;
    case 6:
      result = SInvalidFileHandle;
    case 15:
      result = SInvalidDrive;
    case 100:
      result = SEndOfFile;
    case 101:
      result = SDiskFull;
    case 102:
      result = SFileNotAssigned;
    case 103:
      result = SFileNotOpen;
    case 104:
      result = SFileNotOpenForInput;
    case 105:
      result = SFileNotOpenForOutput;
    case 106:
      result = SInvalidInput;
    case 200:
      result = SDivByZero;
    case 201:
      result = SRangeError;
    case 203:
      result = SOutOfMemory;
    case 204:
      result = SInvalidPointer;
    case 205:
      result = SOverflow;
    case 206:
      result = SUnderflow;
    case 207:
      result = SInvalidOp;
    case 211:
      result = SAbstractError;
    case 214:
      result = SBusError;
    case 215:
      result = SIntOverflow;
    case 216:
      result = SAccessViolation;
    case 217:
      result = SPrivilege;
    case 218:
      result = SControlC;
    case 219:
      result = SInvalidCast;
    case 220:
      result = SInvalidVarCast;
    case 221:
      result = SInvalidVarOp;
    case 222:
      result = SDispatchError;
    case 223:
      result = SVarArrayCreate;
    case 224:
      result = SVarNotArray;
    case 225:
      result = SVarArrayBounds;
    case 227:
      result = SAssertionFailed;
    case 228:
      result = SExternalException;
    case 229:
      result = SIntfCastError;
    case 230:
      result = SSafecallException;
    case 231:
      result = SExceptionStack;
    case 232:
      result = SNoThreadSupport;

    case 255:
      result = SFallbackError;

      /*Error codes larger than 255 cannot be returned as an exit code to the OS,
       for some OS's. If this happens, error 255 is returned instead.
       Errors for which it is important that they can be distinguished,
       shall be below 255*/

      /*Error in the range 900 - 999 is considered platform specific*/
    case 900:
      result = SNoToolserver;   /*Mac OS specific*/
  }
  if (  result.Length() == 0 )
  {
    //Errno = result;
    result = SUnknown + result;
  }
  return result;
}
