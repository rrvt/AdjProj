// AdjProjView.h : interface of the AdjProjView class


#pragma once
#include "CScrView.h"
#include "ReportNtPd.h"


class AdjProjDoc;


class AdjProjView : public CScrView {

protected:

  AdjProjView() noexcept;
  DECLARE_DYNCREATE(AdjProjView)

public:

  virtual           ~AdjProjView() { }

  virtual void       initNoteOrietn() { }
  virtual void       saveNoteOrietn() { }
  virtual void       initRptOrietn()  { }
  virtual void       saveRptOrietn()  { }
  virtual PrtrOrient getOrientation() {return prtNote.prtrOrietn;}

  virtual void       onDisplayOutput();
  virtual void       onPreparePrinting(CPrintInfo* info) {prtNote.onPreparePrinting(info);}
  virtual void       onBeginPrinting();

  virtual void       printFooter(DevStream& dev, int pageNo);
  virtual void       OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  AdjProjDoc*        GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in AdjProjView.cpp
inline AdjProjDoc* AdjProjView::GetDocument() const
                                              {return reinterpret_cast<AdjProjDoc*>(m_pDocument);}
#endif

