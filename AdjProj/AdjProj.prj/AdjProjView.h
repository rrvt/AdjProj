// AdjProjView.h : interface of the AdjProjView class


#pragma once
#include "CScrView.h"


class AdjProjDoc;


class AdjProjView : public CScrView {

protected: // create from serialization only

  AdjProjView() noexcept { }
  DECLARE_DYNCREATE(AdjProjView)

public:

  virtual ~AdjProjView() { }

  AdjProjDoc* GetDocument() const;


public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:
  DECLARE_MESSAGE_MAP()
  };

#ifndef _DEBUG  // debug version in AdjProjView.cpp
inline AdjProjDoc* AdjProjView::GetDocument() const
   { return reinterpret_cast<AdjProjDoc*>(m_pDocument); }
#endif

