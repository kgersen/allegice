// TreeViewExt.cpp : implementation file
//

#include "stdafx.h"
#include "ICE.h"
#include "TreeViewExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeViewExt

IMPLEMENT_DYNCREATE(CTreeViewExt, CTreeView)

CTreeViewExt::CTreeViewExt()
{
	m_bDraggingNow		= FALSE;
	m_hDraggedItem		= NULL;
	m_pDragImageList	= NULL;
}

CTreeViewExt::~CTreeViewExt()
{
}

BEGIN_MESSAGE_MAP(CTreeViewExt, CTreeView)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTreeViewExt message handlers

void CTreeViewExt::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (!m_bDraggingNow)
	{
		if (ItemCanBeDragged(pNMTreeView->itemNew.hItem))
		{
			CTreeCtrl& tree = GetTreeCtrl();
			tree.SetCapture();
			m_bDraggingNow = TRUE;
			m_hDraggedItem = pNMTreeView->itemNew.hItem;
			tree.Select(m_hDraggedItem, TVGN_CARET);
			m_pDragImageList = tree.CreateDragImage(m_hDraggedItem);
			m_pDragImageList->DragEnter(&tree, pNMTreeView->ptDrag);
			m_pDragImageList->BeginDrag(0, CPoint(0, 0));
		}
	}
	
	*pResult = 0;
}

void CTreeViewExt::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDraggingNow)
	{
		CTreeCtrl& tree = GetTreeCtrl();
		m_pDragImageList->DragEnter(&tree, point);
		m_pDragImageList->DragMove(point);
	}
	
	CTreeView::OnMouseMove(nFlags, point);
}

void CTreeViewExt::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bDraggingNow)
	{
		ReleaseCapture();

		m_bDraggingNow = FALSE;
		m_pDragImageList->EndDrag();
		delete m_pDragImageList;
		m_pDragImageList = NULL;

		CTreeCtrl& tree = GetTreeCtrl();
		UINT flags;
		HTREEITEM hTargetItem = tree.HitTest(point, &flags);
		if (hTargetItem != NULL && IsItemCanBeDroppedOn(m_hDraggedItem, hTargetItem))
		{
			HTREEITEM hNewItem = tree.InsertItem("Untitled", hTargetItem);
			CopyItemProperties(hNewItem, m_hDraggedItem);
			if (nFlags != MK_CONTROL)
				tree.DeleteItem(m_hDraggedItem);
		}	

		m_hDraggedItem = NULL;
	}
	
	CTreeView::OnLButtonUp(nFlags, point);
}

BOOL CTreeViewExt::ItemCanBeDragged(HTREEITEM hItem)
{
	return FALSE;
}

BOOL CTreeViewExt::IsItemCanBeDroppedOn(HTREEITEM hSource, HTREEITEM hTarget)
{
	return FALSE;
}

void CTreeViewExt::CopyItemProperties(HTREEITEM hNewItem, HTREEITEM hDraggedItem)
{

}
