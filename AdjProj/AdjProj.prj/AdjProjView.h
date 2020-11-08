// AdjProjView.h : interface of the AdjProjView class


#pragma once
#include "CScrView.h"
#include "NoteRpt.h"


class AdjProjDoc;


class AdjProjView : public CScrView {

NoteRptB dspNote;
NoteRptB prtNote;

protected: // create from serialization only

  AdjProjView() noexcept;
  DECLARE_DYNCREATE(AdjProjView)

public:

  virtual ~AdjProjView() { }

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool isNotePad, bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Display& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  AdjProjDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);

  };

#ifndef _DEBUG  // debug version in AdjProjView.cpp
inline AdjProjDoc* AdjProjView::GetDocument() const
   { return reinterpret_cast<AdjProjDoc*>(m_pDocument); }
#endif

