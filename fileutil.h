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
#ifndef FileUtilH
#define FileUtilH

#include "classes.h" 
#include "sysutils.h" 

// file attributes and states
int CompareFilenames( wxString const& Filename1, wxString const& Filename2);
int CompareFilenames( wxString const& Filename1, wxString const& Filename2, bool ResolveLinks);
int CompareFilenames(char* Filename1,  int Len1, char* Filename2,  int Len2,  bool ResolveLinks);
bool FilenameIsAbsolute( wxString const& TheFilename);
bool FilenameIsWinAbsolute( wxString const& TheFilename);
bool FilenameIsUnixAbsolute( wxString const& TheFilename);
void CheckIfFileIsExecutable( wxString const& AFilename);
void CheckIfFileIsSymlink( wxString const& AFilename);
bool FileIsReadable( wxString const& AFilename);
bool FileIsWritable( wxString const& AFilename);
bool FileIsText( wxString const& AFilename);
bool FileIsText( wxString const& AFilename,   bool & FileReadable);
bool FileIsExecutable( wxString const& AFilename);
bool FileIsSymlink( wxString const& AFilename);
wxULongLong FileSize( wxString const& Filename);
wxString GetFileDescription( wxString const& AFilename);
wxString ReadAllLinks( wxString const& Filename, 
                      bool ExceptionOnError);

// directories
bool DirPathExists( wxString const& Filename);
bool ForceDirectory(wxString DirectoryName);
bool DeleteDirectory( wxString const& DirectoryName,
  bool OnlyChilds);
wxString ProgramDirectory();
bool DirectoryIsWritable( wxString const& DirectoryName);

// filename parts

wxString ExtractFileNameOnly( wxString const& AFilename);
wxString ExtractFileNameWithoutExt( wxString const& AFilename);
int CompareFileExt( wxString const& Filename, wxString const& Ext, 
                        bool CaseSensitive);
int CompareFileExt( wxString const& Filename, wxString const& Ext);
bool FilenameIsPascalUnit( wxString const& Filename);
wxString AppendPathDelim( wxString const& Path);
wxString ChompPathDelim( wxString const& Path);
wxString TrimFilename( wxString const& AFilename);
wxString CleanAndExpandFilename( wxString const& Filename);
wxString CleanAndExpandDirectory( wxString const& Filename);
wxString CreateAbsoluteSearchPath( wxString const& SearchPath, wxString const& BaseDirectory);
wxString CreateRelativePath( wxString const& Filename, wxString const& BaseDirectory);
bool FileIsInPath( wxString const& Filename, wxString const& Path);
bool FileIsInDirectory( wxString const& Filename, wxString const& Directory);
bool FileInFilenameMasks( wxString const& Filename, wxString const& Masks);
// file search
enum TSearchFileInPathFlag { sffDontSearchInBasePath, sffSearchLoUpCase };
typedef  DelphiSet<TSearchFileInPathFlag> TSearchFileInPathFlags;

#ifdef WXMSW
static wxString const AllDirectoryEntriesMask = "*.*";
#else
static wxString const AllDirectoryEntriesMask = "*";
#endif

wxString GetAllFilesMask(void);
wxString GetExeExt(void);
wxString SearchFileInPath( wxString const& Filename, wxString const& BasePath, wxString const& SearchPath, wxString const& Delimiter,  TSearchFileInPathFlags Flags);
TStrings SearchAllFilesInPath( wxString const& Filename, wxString const& BasePath, wxString const& SearchPath, wxString const& Delimiter,  TSearchFileInPathFlags Flags);
wxString FindDiskFilename( wxString const& Filename);
wxString FindDiskFileCaseInsensitive( wxString const& Filename);
wxString FindDefaultExecutablePath( wxString const& Executable);

// file actions
wxString ReadFileToString( wxString const& Filename);
bool CopyFile( wxString const& SrcFilename, wxString const& DestFilename);
bool CopyFile( wxString const& SrcFilename, wxString const& DestFilename,  bool PreserveTime);
wxString GetTempFilename( wxString const& Directory, wxString const& Prefix);
TStringList GetFolderList(wxString baseFolder, bool includeFullFolderPath = true);
TStringList GetFileList(wxString folder, const wxString& mask, bool includeFullFolderPath = true);
#endif //FileUtilH

