// AdjProjDoc.h : interface of the AdjProjDoc class


#pragma once
#include "CDoc.h"
#include "XMLstore.h"


enum DataSource {NotePadSrc};


class AdjProjDoc : public CDoc {

DataSource  dataSource;
PathDlgDsc  dsc;

XMLstore    xmlStore;

protected: // create from serialization only

  AdjProjDoc() noexcept;
  DECLARE_DYNCREATE(AdjProjDoc)

public:
  virtual ~AdjProjDoc();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  void       setSortName();
  void       display();

  virtual void serialize(Archive& ar);



#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  XMLbase* onAdjust(TCchar* txt);

protected:

  DECLARE_MESSAGE_MAP()

public:
  afx_msg void onFileOpen();
  afx_msg void onAdjust();

  afx_msg void onFileSave();
  };
