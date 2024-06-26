// AdjProjDoc.h : interface of the AdjProjDoc class


#pragma once
#include "CDoc.h"
#include "XMLparser.h"


enum DataSource {NotePadSrc};


class AdjProjDoc : public CDoc {

DataSource  dataSource;
PathDlgDsc  dsc;
XMLparser   xml;

protected: // create from serialization only

  AdjProjDoc() noexcept;
  DECLARE_DYNCREATE(AdjProjDoc)

public:

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  void       setSortName();
  void       display();

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
  afx_msg void OnFileOpen();
  afx_msg void OnAdjust();

  afx_msg void OnFileSave();
  };
