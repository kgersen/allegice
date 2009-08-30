/////////////////////////////////////////////////////////////////////////////
// CTreeViewExt view

class CTreeViewExt : public CTreeView
{
protected:
	CTreeViewExt();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTreeViewExt)

// Attributes
public:

// Operations
public:

// Implementation
protected:
	HTREEITEM m_hDraggedItem;
	BOOL m_bDraggingNow;
	CImageList *m_pDragImageList;
	virtual ~CTreeViewExt();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	virtual void CopyItemProperties(HTREEITEM hNewItem, HTREEITEM hDraggedItem);
	virtual BOOL IsItemCanBeDroppedOn(HTREEITEM hSource, HTREEITEM hTarget);
	virtual BOOL ItemCanBeDragged(HTREEITEM hItem);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};
