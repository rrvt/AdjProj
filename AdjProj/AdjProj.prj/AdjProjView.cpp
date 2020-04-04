// AdjProjView.cpp : implementation of the AdjProjView class


#include "stdafx.h"
#include "AdjProjView.h"
#include "AdjProj.h"
#include "AdjProjDoc.h"
#include "DisplayView.h"
#include "Display.h"
#include "NotePad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// AdjProjView

IMPLEMENT_DYNCREATE(AdjProjView, CScrollView)

BEGIN_MESSAGE_MAP(AdjProjView, CScrollView)
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT,         &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()


// AdjProjView construction/destruction

AdjProjView::AdjProjView() noexcept : font(_T("Arial")), author(_T("sde")) { }


AdjProjView::~AdjProjView() { }


BOOL AdjProjView::PreCreateWindow(CREATESTRUCT& cs) {return CScrollView::PreCreateWindow(cs);}


void AdjProjView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb)
                                                            {CScrollView::OnVScroll(nSBCode, nPos, sb);}


void AdjProjView::OnInitialUpdate() {CScrollView::OnInitialUpdate();}


void AdjProjView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
                                  {setScrollSize(dspView); CScrollView::OnUpdate(pSender, lHint, pHint);}


// AdjProjView printing
/* The following functions are called for printing a page in the order given with one exception:
BOOL OnPreparePrinting(        CPrintInfo* pInfo);  -- 1st
void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);  -- 2nd
     CDC::StartDoc()                                -- 3rd
void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo);  -- 4th                         <-
     CDC::StartPage()                               -- 5th                          ^
void OnPrint(        CDC* pDC, CPrintInfo* pInfo);  -- 6th                          ^
     CDC::EndPage()                                 -- 7th then loops for each page ^
     CDC::EndDoc()                                  -- after last page
void OnEndPrinting(  CDC* pDC, CPrintInfo* pInfo);  -- last
*/

BOOL AdjProjView::OnPreparePrinting(CPrintInfo* pInfo) {
BOOL rslt;

  pInfo->m_nNumPreviewPages = 0;

  prtView.OnPreparePrinting(pInfo);

  rslt = DoPreparePrinting(pInfo);                  // Get printer dialog box

  return rslt;
  }


void AdjProjView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
                       {Date d;   d.getToday();  prtView.OnBeginPrinting(pDC, pInfo, author, d);}


void AdjProjView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
DisplayView* dv = pInfo ? &prtView : &dspView;

  dv->OnPreparePrinting(pInfo);

  CScrollView::OnPrepareDC(pDC, pInfo);

  dv->OnPrepareDC(font, 120, pDC, pInfo);
  }


void AdjProjView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {prtView.OnPrint(pInfo);}


void AdjProjView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {if (!pInfo->m_bPreview) invalidate();}


// AdjProjView drawing

void AdjProjView::OnDraw(CDC* pDC) {dspView.OnDraw(); setScrollSize(dspView);}


void AdjProjView::setScrollSize(DisplayView& dv) {
RECT  winSize;
CSize s;
CSize pageSize;
CSize scrollSize;

  GetClientRect(&winSize); dv.getScrollSize(winSize, s, pageSize, scrollSize);

  SetScrollSizes(MM_TEXT, s, pageSize, scrollSize);
  }


// AdjProjView diagnostics

#ifdef _DEBUG
void AdjProjView::AssertValid() const
{
  CScrollView::AssertValid();
}

void AdjProjView::Dump(CDumpContext& dc) const
{
  CScrollView::Dump(dc);
}

AdjProjDoc* AdjProjView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AdjProjDoc)));
  return (AdjProjDoc*)m_pDocument;
}
#endif //_DEBUG


// AdjProjView message handlers
