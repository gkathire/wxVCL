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

#include "comctrls.h"

void wxSelectFirstListItem(wxListCtrl *lstvw)
{
	wxSelectListItem(lstvw, 0);
}

bool SetStringListLongListInCombo(wxComboBox *cbx, const wxArrayString &strData,
  const wxArrayLong &lgData)
{
	wxUnusedVar(lgData);
	cbx->Clear();
	for (size_t i = 0; i < strData.GetCount(); ++i)
	{
		cbx->AppendString(strData.Item(i));
	}
	return true;
}

bool wxSelectListItem(wxListCtrl *lstvw, int Row)
{
	bool Result = false;
	if (Row > lstvw->GetItemCount())
	{
		Result = false;
	}
	else
	{
		Result = true;
		lstvw->SetItemState(Row, wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED,
		  wxLIST_STATE_FOCUSED | wxLIST_STATE_SELECTED);
	}
	return Result;
}

wxTreeItemId wxGetSelectedTreeItem(wxTreeCtrl*treectrl)
{
	return treectrl->GetSelection();
}

int wxGetSelectedListItem(wxListCtrl *listctrl)
{
	long item = -1;
	item = listctrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	return item;
}

int GetTreeItemSelectedCount(wxTreeCtrl *tvCtrl, int SelImageIdx,
  const wxTreeItemId& idParent, wxTreeItemIdValue cookie)
{
	int Result = 0;
	wxTreeItemId id;
	if (!cookie)
		id = tvCtrl->GetFirstChild(idParent, cookie);
	else
		id = tvCtrl->GetNextChild(idParent, cookie);

	if (!id.IsOk())
		return Result;

	if (tvCtrl->GetItemImage(id) == SelImageIdx)
	{
		Result++;
	}
	if (tvCtrl->ItemHasChildren(id))
		Result += GetTreeItemSelectedCount(tvCtrl, SelImageIdx, id);

	Result += GetTreeItemSelectedCount(tvCtrl, SelImageIdx, idParent, cookie);

	return Result;
}

void SelectAllTreeItems(const wxString &searchStr, wxTreeCtrl *tvCtrl,
  int SelImageIdx, const wxTreeItemId& idParent, wxTreeItemIdValue cookie)
{
	wxTreeItemId id;
	if (!cookie)
		id = tvCtrl->GetFirstChild(idParent, cookie);
	else
		id = tvCtrl->GetNextChild(idParent, cookie);

	if (!id.IsOk())
		return;
	if (searchStr.Cmp(wxEmptyString) == 0)
		tvCtrl->SetItemImage(id, SelImageIdx);
	else
	{
		if (tvCtrl->GetItemText(id).Upper().Contains(searchStr.Upper()))
		{
			tvCtrl->SetItemImage(id, SelImageIdx);
		}
	}

	if (tvCtrl->ItemHasChildren(id))
		SelectAllTreeItems(searchStr, tvCtrl, SelImageIdx, id);

	SelectAllTreeItems(searchStr, tvCtrl, SelImageIdx, idParent, cookie);

}

void InverseSelectedTreeItems(wxTreeCtrl *tvCtrl, int SelImageIdx,
  int UnSelImageIdx, const wxTreeItemId& idParent, wxTreeItemIdValue cookie)
{
	wxTreeItemId id;
	if (!cookie)
		id = tvCtrl->GetFirstChild(idParent, cookie);
	else
		id = tvCtrl->GetNextChild(idParent, cookie);

	if (!id.IsOk())
		return;
	if (tvCtrl->GetItemImage(id) == SelImageIdx)
	{
		tvCtrl->SetItemImage(id, UnSelImageIdx);
	}
	else if (tvCtrl->GetItemImage(id) == UnSelImageIdx)
	{
		tvCtrl->SetItemImage(id, SelImageIdx);
	}

	if (tvCtrl->ItemHasChildren(id))
		InverseSelectedTreeItems(tvCtrl, SelImageIdx, UnSelImageIdx, id);

	InverseSelectedTreeItems(tvCtrl, SelImageIdx, UnSelImageIdx, idParent,
	  cookie);

}

// Returns the text of a cell, at a certain row and column
wxString GetListViewColumnText(wxListCtrl *lstCtrl, long row_number, int column)
{
	wxListItem row_info;
	wxString cell_contents_string;

	// Set what row it is
	row_info.m_itemId = row_number;
	// Set what column of that row we want to query for information.
	row_info.m_col = column;
	// Set text mask
	row_info.m_mask = wxLIST_MASK_TEXT;

	// Get the info and store it in row_info variable.
	lstCtrl->GetItem(row_info);

	// Extract the text out that cell
	cell_contents_string = row_info.m_text;

	return cell_contents_string;
}

// Returns the text of a cell, at a certain row and column
bool SetListViewColumnText(wxListCtrl *lstCtrl, long row_number, int column,
  const wxString &Content)
{
	wxListItem row_info;
	wxString cell_contents_string;

	// Set what row it is
	row_info.m_itemId = row_number;
	// Set what column of that row we want to query for information.
	row_info.m_col = column;
	// Set text mask
	row_info.m_mask = wxLIST_MASK_TEXT;

	// Get the info and store it in row_info variable.
	lstCtrl->GetItem(row_info);

	// Extract the text out that cell
	row_info.m_text = Content;

	return lstCtrl->SetItem(row_info); ;
}

// Returns the text of a cell, at a certain row and column
int GetListViewItemImageIndex(wxListCtrl *lstCtrl, long row_number)
{
	wxListItem row_info;
	// Set what row it is
	row_info.m_itemId = row_number;
	// Set what column of that row we want to query for information.
	row_info.m_col = 0;
	// Set text mask
	row_info.m_mask = wxLIST_MASK_IMAGE;

	// Get the info and store it in row_info variable.
	lstCtrl->GetItem(row_info);

	// Extract the  cell's Image
	return row_info.GetImage();
}

// Returns the text of a cell, at a certain row and column
bool SetListViewItemImageIndex(wxListCtrl *lstCtrl, long row_number,
  int imageidx)
{
	wxListItem row_info;
	// Set what row it is
	row_info.m_itemId = row_number;
	// Set what column of that row we want to query for information.
	row_info.m_col = 0;
	// Set text mask
	row_info.m_mask = wxLIST_MASK_IMAGE;

	// Get the info and store it in row_info variable.
	lstCtrl->GetItem(row_info);

	// Set the Image
	row_info.SetImage(imageidx);

	return lstCtrl->SetItem(row_info); ;
}

TStringList GetListBoxItems(wxListBox *lb)
{
	TStringList Result;
	if (lb->GetCount() > 0)
	{
		for (size_t i = 0; i < lb->GetCount(); i++)
		{
			Result.Add(lb->GetString(i));
		}
	}
	return Result;
}

void SetListBoxItems(wxListBox *lb, TStringList sl)
{
	lb->Clear();
	if (sl.GetCount() > 0)
	{
		for (size_t i = 0; i < sl.Count(); i++)
		{
			wxString st = sl.Item(i);
			lb->Append(st);
		}
	}
}
