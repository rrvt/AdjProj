// AdjProjView.cpp : implementation of the AdjProjView class


#include "stdafx.h"
#include "AdjProjView.h"
#include "AdjProjDoc.h"


// AdjProjView

IMPLEMENT_DYNCREATE(AdjProjView, CScrView)

BEGIN_MESSAGE_MAP(AdjProjView, CScrView)
END_MESSAGE_MAP()


// AdjProjView diagnostics

#ifdef _DEBUG
void AdjProjView::AssertValid() const {CScrollView::AssertValid();}

void AdjProjView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

AdjProjDoc* AdjProjView::GetDocument() const // non-debug version is inline
            {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AdjProjDoc))); return (AdjProjDoc*)m_pDocument;}
#endif //_DEBUG
