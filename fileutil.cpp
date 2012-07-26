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

#include "fileutil.h"
#include "strutils.h"
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/file.h"
#include "wx/filefn.h"
#include "sysutils.h"
#include "sysset.h"
#include "classes.h"
#include <wx/filename.h>
#include <wx/wfstream.h>

bool DirPathExists( wxString const& Filename )
{
    return wxDir::Exists( Filename );
}

int CompareFilenames( wxString const& Filename1, wxString const& Filename2 )
{
#ifdef WXMSW
    return AnsiCompareText( Filename1 , Filename2 );
#else
    return AnsiCompareStr( Filename1 , Filename2 );
#endif
}

int CompareFilenames( wxString const& Filename1, wxString const& Filename2, bool ResolveLinks )
{
    int result;
    wxString File1;
    wxString File2;

    File1 = Filename1;
    File2 = Filename2;
    if (  ResolveLinks )
    {
        File1 = ReadAllLinks( File1, false );
        if (  ( File1 == "" ) ) File1 = Filename1;
        File2 = ReadAllLinks( File2, false );
        if (  ( File2 == "" ) ) File2 = Filename2;
    }
    result = CompareFilenames( File1, File2 );
    return result;
}

int CompareFilenames( char* Filename1,  int Len1, char* Filename2,  int Len2,  bool ResolveLinks )
{
    THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function FilenameIsAbsolute(const TheFilename: string):boolean;
 ------------------------------------------------------------------------------*/
bool FilenameIsAbsolute( wxString const& TheFilename )
{
#ifdef WXMSW
    return FilenameIsWinAbsolute( TheFilename );
#else
    return FilenameIsUnixAbsolute( TheFilename );
#endif
}

bool FilenameIsWinAbsolute( wxString const& TheFilename )
{
    return ( ( Length( TheFilename ) >= 2 ) && ( AllEnglishCharSet.Contains( TheFilename[ 0 ] ) )
             && ( TheFilename[ 1 ] == ':' ) ) || ( ( Length( TheFilename ) >= 2 )
                                                   && ( TheFilename[ 0 ] == '\\' ) && ( TheFilename[ 1 ] == '\\' ) );
}

bool FilenameIsUnixAbsolute( wxString const& TheFilename )
{
    return ( TheFilename.Length() != 0  ) && ( TheFilename[ 0 ] == '/' );
}

/*------------------------------------------------------------------------------
  function FilenameIsPascalUnit(const Filename: string): boolean;
 ------------------------------------------------------------------------------*/
bool FilenameIsPascalUnit( wxString const& Filename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function AppendPathDelim(const Path: string): string;
 ------------------------------------------------------------------------------*/
wxString AppendPathDelim( wxString const& Path )
{
    wxString result;
    if (  ( Path.Length() != 0 ) && ( Path.Last() != PathDelim ) )
        result = Path + PathDelim;
    else
        result = Path;
    return result;
}

/*------------------------------------------------------------------------------
  function TrimFilename(const AFilename: string): string;
 ------------------------------------------------------------------------------*/
wxString TrimFilename( wxString const& AFilename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

wxString ExtractFileNameWithoutExt( wxString const& AFilename )
{
    wxFileName fnobj(AFilename);
    return fnobj.GetName();
}

/*------------------------------------------------------------------------------
  function CompareFileExt(const Filename, Ext: string;
    CaseSensitive: boolean): integer;
 ------------------------------------------------------------------------------*/
int CompareFileExt( wxString const& Filename, wxString const& Ext, bool CaseSensitive )
{
  wxString FileExt = ExtractFileExt(Filename);
  if (CaseSensitive)
    return CompareStr(FileExt,Ext);
  else
    return CompareText(FileExt,Ext);  
}

int CompareFileExt( wxString const& Filename, wxString const& Ext )
{
  return CompareFileExt( Filename, Ext, false );
}

/*------------------------------------------------------------------------------
  function ChompPathDelim(const Path: string): string;
 ------------------------------------------------------------------------------*/
wxString ChompPathDelim( wxString const& Path )
{
    if (  ( Path.Length() != 0 ) && ( Path.Last() == PathDelim ) )
        return LeftStr( Path, Length( Path ) - 1 );
    else
        return Path;
}
/*------------------------------------------------------------------------------
  function FileIsText(const AFilename: string): boolean;
 ------------------------------------------------------------------------------*/
bool FileIsText( wxString const& AFilename )
{
    bool result;
    bool FileReadable;
    result = FileIsText( AFilename, FileReadable );
    if (  FileReadable )
      return result;
    else
      return false;
}

bool FileIsText( wxString const& AFilename,   bool &/*OUT-only*/ FileReadable )
{
  wxFileInputStream filestream(AFilename);
  if (filestream.IsOk() == false)
    return false;

  bool hit = false;
  do
  {
    wxChar a;
    filestream.Read(&a,1);
    if ( ( (int)a < 7 ) || ( ((int)a>=14) && ((int)a<=31)) )
      hit = true;
  } while ((filestream.Eof() == false) || hit);  
  return !hit;
}

/*------------------------------------------------------------------------------
  procedure CheckIfFileIsSymlink(const AFilename: string);
 ------------------------------------------------------------------------------*/
void CheckIfFileIsSymlink( wxString const& AFilename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function FileIsSymlink(const AFilename: string): boolean;
 ------------------------------------------------------------------------------*/
bool FileIsSymlink( wxString const& AFilename )
{
#ifdef WXMSW
    return false;
#else
    THROW_NOT_IMPLEMENTED_ERROR;
#endif
}

/*------------------------------------------------------------------------------
  function FileIsReadable(const AFilename: string): boolean;
 ------------------------------------------------------------------------------*/
bool FileIsReadable( wxString const& AFilename )
{
  return (wxAccess(AFilename.c_str(),04) == 0);
}

/*------------------------------------------------------------------------------
  FileIsWritable
 ------------------------------------------------------------------------------*/
bool FileIsWritable( wxString const& AFilename )
{
  return (wxAccess(AFilename.c_str(),02) == 0);
}

wxULongLong  FileSize( wxString const& Filename )
{
  return wxFileName::GetSize( Filename );
}

/*------------------------------------------------------------------------------
  GetFileDescription
 ------------------------------------------------------------------------------*/
wxString GetFileDescription( wxString const& AFilename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function ReadAllLinks(const Filename: string;
    ExceptionOnError: boolean): string;
 ------------------------------------------------------------------------------*/
wxString ReadAllLinks( wxString const& Filename,
                       bool ExceptionOnError )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function ExtractFileNameOnly(const AFilename: string): string;
 ------------------------------------------------------------------------------*/
wxString ExtractFileNameOnly( wxString const& AFilename )
{
  return ExtractFileNameWithoutExt(AFilename);
}

/*------------------------------------------------------------------------------
  function FileIsExecutable(const AFilename: string): boolean;
 ------------------------------------------------------------------------------*/
bool FileIsExecutable( wxString const& AFilename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  procedure CheckIfFileIsExecutable(const AFilename: string);
 ------------------------------------------------------------------------------*/
void CheckIfFileIsExecutable( wxString const& AFilename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function ForceDirectory(DirectoryName: string): boolean;
 ------------------------------------------------------------------------------*/
bool ForceDirectory( wxString DirectoryName )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function DeleteDirectory(const DirectoryName: string;
    OnlyChilds: boolean): boolean;
 ------------------------------------------------------------------------------*/
bool DeleteDirectory( wxString const& DirectoryName,
                      bool OnlyChilds )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function ProgramDirectory: string;
 ------------------------------------------------------------------------------*/
wxString ProgramDirectory()
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

bool DirectoryIsWritable( wxString const& DirectoryName )
{
    bool result = false;
    wxString  TempFilename = GetTempFilename( DirectoryName, "tstperm" );
    wxFileOutputStream fileStream(TempFilename);
    if (fileStream.IsOk()== false )
      return false;
    if (fileStream.Write("Test",4).IsOk() == false)
      result = false;
    else
      result = true;
    DeleteFile( TempFilename );
    return result;
}

/*------------------------------------------------------------------------------
  function CleanAndExpandFilename(const Filename: string): string;
 ------------------------------------------------------------------------------*/
wxString CleanAndExpandFilename( wxString const& Filename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function CleanAndExpandDirectory(const Filename: string): string;
 ------------------------------------------------------------------------------*/
wxString CleanAndExpandDirectory( wxString const& Filename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

wxString CreateAbsoluteSearchPath( wxString const& SearchPath, wxString const& BaseDirectory )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

wxString CreateRelativePath( wxString const& Filename, wxString const& BaseDirectory )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function FileIsInPath(const Filename, Path: string): boolean;
 ------------------------------------------------------------------------------*/
bool FileIsInPath( wxString const& Filename, wxString const& Path )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function FileIsInPath(const Filename, Path: string): boolean;
 ------------------------------------------------------------------------------*/
bool FileIsInDirectory( wxString const& Filename, wxString const& Directory )
{
    bool result;
    wxString ExpFile;
    wxString ExpDir;
    int LenFile;
    int LenDir;
    long p;

    ExpFile = CleanAndExpandFilename( Filename );
    ExpDir = CleanAndExpandDirectory( Directory );
    LenFile = Length( ExpFile );
    LenDir = Length( ExpDir );
    p = LenFile;
    while (  ( p > 0 ) && ( ExpFile[ (unsigned int)p ] != PathDelim ) ) --p;
    result = ( p == LenDir ) && ( p < LenFile )
             && ( CompareFilenames( ExpDir, LeftStr( ExpFile, p ) ) == 0 );
    return result;
}

/*------------------------------------------------------------------------------
  function FileInFilenameMasks(const Filename, Masks: string): boolean;

  Checks if 'Filename' fits to one of the mask in 'Masks'.
  Note: It checks the whole Filename. So, for example /somewhere/unit1.pas does
  not fit the mask 'unit*.pas', but it will fit '*.pas'.

  Masks is delimited by semicolon.
  Masks allows asterisk (*) for arbitrary text and question mark (?) for one
  arbitrary character.
  Examples:
    '*.pas;*.pp;*.inc'
    '*.tar.*'
    'lazarus*.xpm'
 ------------------------------------------------------------------------------*/
bool FileInFilenameMasks( wxString const& Filename, wxString const& Masks )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

/*------------------------------------------------------------------------------
  function CopyFile(const SrcFilename, DestFilename: string): boolean;
 ------------------------------------------------------------------------------*/
bool CopyFile( wxString const& SrcFilename, wxString const& DestFilename )
{
    bool result;
    result = CopyFile( SrcFilename , DestFilename , false );
    return result;
}

/*------------------------------------------------------------------------------
  function CopyFile(const SrcFilename, DestFilename: string PreserveTime:
    boolean): boolean;
 ------------------------------------------------------------------------------*/
bool CopyFile( wxString const& SrcFilename, wxString const& DestFilename,  bool PreserveTime )
{
    if (wxCopyFile(SrcFilename, DestFilename,true))
    {
     //fixme: if (PreserveTime)
    }
    return false;
}

/*------------------------------------------------------------------------------
  function GetTempFilename(const Directory, Prefix: string): string;
 ------------------------------------------------------------------------------*/
wxString GetTempFilename( wxString const& Directory, wxString const& Prefix )
{
    wxString result;
    int i;
    wxString CurPath;

    CurPath = AppendPathDelim( Directory ) + Prefix;
    i = 1;
    do
    {
        result = CurPath + IntToStr( i ) + ".tmp";
        if (  !FileExists( result ) ) return result;
        ++i;
    }
    while ( !(  false ) );
    return result;
}

/*------------------------------------------------------------------------------
  function SearchFileInPath(const Filename, BasePath, SearchPath,
    Delimiter: string; Flags: TSearchFileInPathFlags): string;
 ------------------------------------------------------------------------------*/
wxString SearchFileInPath( wxString const& Filename, wxString const& BasePath, wxString const& SearchPath, wxString const& Delimiter,  TSearchFileInPathFlags Flags )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

TStrings SearchAllFilesInPath( wxString const& Filename, wxString const& BasePath, wxString const& SearchPath, wxString const& Delimiter,  TSearchFileInPathFlags Flags )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

wxString FindDiskFilename( wxString const& Filename )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

wxString FindDiskFileCaseInsensitive( wxString const& Filename )
{
    wxString result = "";
    wxString ShortFilename;
    wxString CurDir;
    wxDir dir;
    CurDir = ExtractFilePath( Filename );
    wxArrayString FileList;
    dir.GetAllFiles(CurDir,&FileList,GetAllFilesMask(),wxDIR_DEFAULT);

    for (size_t i = 0; i < FileList.GetCount(); i++)
    {
        ShortFilename = ExtractFileName( Filename );
        if (  CompareText( FileList[i], ShortFilename ) == 0 )
        {
          if ( CompareStr(FileList[i] , ShortFilename ) == 0 )
          {
            // fits exactly
            result = Filename;
            break;
          }
          // fits case insensitive
          result = CurDir + FileList[i];
          // search further
          }
    }
    return result;
}

wxString FindDefaultExecutablePath( wxString const& Executable )
{
  THROW_NOT_IMPLEMENTED_ERROR;
}

wxString GetAllFilesMask( void )
{
    return AllDirectoryEntriesMask;
}

wxString GetExeExt( void )
{
    wxString result;
#ifdef _WXMSW_
    result = ".exe";
#else
    result = "";
#endif
    return result;
}

/*------------------------------------------------------------------------------
  function ReadFileToString(const Filename: string): string;
 ------------------------------------------------------------------------------*/
wxString ReadFileToString( wxString const& Filename )
{
    wxArrayString str;
    LoadFromFile( Filename, str );
    return ArrayStringToString(str);
}





