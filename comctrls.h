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
#ifndef ComCtrlsH
#define ComCtrlsH

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>

bool SetListViewColumnText( wxListCtrl *lstCtrl, long row_number, int column , const wxString & Content);
wxString GetListViewColumnText(wxListCtrl *lstCtrl, long row_number, int column );
void InverseSelectedTreeItems(wxTreeCtrl *tvCtrl,int SelImageIdx, int UnSelImageIdx,const wxTreeItemId& idParent, wxTreeItemIdValue cookie = 0);
void SelectAllTreeItems(const wxString & searchStr,wxTreeCtrl *tvCtrl,int SelImageIdx, const wxTreeItemId& idParent, wxTreeItemIdValue cookie = 0);
int GetTreeItemSelectedCount(wxTreeCtrl *tvCtrl,int SelImageIdx, const wxTreeItemId& idParent, wxTreeItemIdValue cookie = 0);
int wxGetSelectedListItem(wxListCtrl *listctrl);
wxTreeItemId wxGetSelectedTreeItem(wxTreeCtrl*treectrl);
bool wxSelectListItem(wxListCtrl *lstvw, int Row);
bool SetStringListLongListInCombo(wxComboBox *cbx,const wxArrayString &strData,const wxArrayLong &lgData);
void wxSelectFirstListItem(wxListCtrl *lstvw);
int GetListViewItemImageIndex(wxListCtrl *lstCtrl, long row_number );
bool SetListViewItemImageIndex( wxListCtrl *lstCtrl, long row_number, int imageidx);
#endif //ComCtrlsH
 
