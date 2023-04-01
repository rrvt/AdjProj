// AdjProjView.cpp : implementation of the AdjProjView class


#include "stdafx.h"
#include "AdjProjView.h"
#include "AdjProj.h"
#include "AdjProjDoc.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"
#include "RptOrientDlgOne.h"


// AdjProjView

IMPLEMENT_DYNCREATE(AdjProjView, CScrView)

BEGIN_MESSAGE_MAP(AdjProjView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


AdjProjView::AdjProjView() noexcept {

ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


void AdjProjView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void AdjProjView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl00 = _T("Media:");

  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);

  if (dlg.DoModal() == IDOK) {prtNote.prtrOrietn = printer.toOrient(dlg.ntpd);   saveNoteOrietn();}
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void AdjProjView::onBeginPrinting() {

  prtNote.onBeginPrinting(*this);
  }



void AdjProjView::onDisplayOutput() {dspNote.display(*this);}


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void AdjProjView::printFooter(DevBase& dev, int pageNo) {prtNote.prtFooter(dev, pageNo);}



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

AdjProjDoc* AdjProjView::GetDocument() const          // non-debug version is inline
            {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AdjProjDoc))); return (AdjProjDoc*)m_pDocument;}
#endif //_DEBUG
