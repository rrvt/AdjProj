// AdjProjDoc.h : interface of the AdjProjDoc class


#pragma once
#include "CDoc.h"
#include "XMLparser.h"


class AdjProjDoc : public CDoc {

String    saveAsTitle;                                            // Save As Parameters, examples:
String    defFileName;                                            // _T("mumble.txt")
String    defExt;                                                 // _T("txt")
String    defFilePat;                                             // _T("*.txt")

XMLparser xml;

protected: // create from serialization only

  AdjProjDoc() noexcept;
  DECLARE_DYNCREATE(AdjProjDoc)

public:

          void setSortName();
          void display();

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~AdjProjDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnTest();
  afx_msg void OnFileOpen();
  afx_msg void OnAdjust();
  afx_msg void OnFileSave();
};
