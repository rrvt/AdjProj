// AdjProjView.h : interface of the AdjProjView class


#pragma once
#include "DisplayView.h"

class AdjProjDoc;


class AdjProjView : public CScrollView {

protected: // create from serialization only

  AdjProjView() noexcept;
  DECLARE_DYNCREATE(AdjProjView)

// Attributes

DisplayView dspView;
DisplayView prtView;

String      author;
String      font;

public:

  AdjProjDoc* GetDocument() const;

// Operations
public:

          void setAuthor(TCchar* a) {author = a;}
          void setFont(  TCchar* f) {font   = f;}

// Overrides
public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb);
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

  virtual void OnInitialUpdate(); // called first time after construct
  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void OnPrint(        CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

          void printFooter();

private:
          void setScrollSize(DisplayView& dv);

// Implementation
public:
  virtual ~AdjProjView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AdjProjView.cpp
inline AdjProjDoc* AdjProjView::GetDocument() const
   { return reinterpret_cast<AdjProjDoc*>(m_pDocument); }
#endif

