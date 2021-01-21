// AdjProjView.cpp : implementation of the AdjProjView class


#include "stdafx.h"
#include "AdjProjView.h"
#include "AdjProj.h"
#include "AdjProjDoc.h"
#include "Options.h"
#include "Resources.h"


// AdjProjView

IMPLEMENT_DYNCREATE(AdjProjView, CScrView)

BEGIN_MESSAGE_MAP(AdjProjView, CScrView)
END_MESSAGE_MAP()


AdjProjView::AdjProjView() noexcept : dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {

ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }



void AdjProjView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void AdjProjView::onPrepareOutput(bool printing) {
DataSource ds   = doc()->dataSrc();

  if (printing) prtNote.print(*this);
  else          dspNote.display(*this);

  CScrView::onPrepareOutput(printing);
  }


void AdjProjView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    }

  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void AdjProjView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
    }
  }



void AdjProjView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }


void AdjProjView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    }
  }




// AdjProjView diagnostics

#ifdef _DEBUG
void AdjProjView::AssertValid() const {CScrollView::AssertValid();}

void AdjProjView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

AdjProjDoc* AdjProjView::GetDocument() const // non-debug version is inline
            {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AdjProjDoc))); return (AdjProjDoc*)m_pDocument;}
#endif //_DEBUG
