// AdjProj.h : main header file for the AdjProj application

#pragma once
#include "resource.h"       // main symbols
#include "IniFile.h"
#include "MainFrame.h"


class AdjProjDoc;
class AdjProjView;


// AdjProj:
// See AdjProj.cpp for the implementation of this class

class AdjProj : public CWinAppEx {
String       appID;

AdjProjDoc*  doc;
AdjProjView* view;

public:

String version;

               AdjProj() noexcept;

  virtual BOOL InitInstance();

          void setAppName(TCchar* appName) {getMainFrame()->setAppName(appName);}   // Title left part
          void setTitle(TCchar* rightPart) {getMainFrame()->setTitle(rightPart);}    // title right part

          void invalidate();

  // Implementation

  afx_msg void OnAppAbout();
  DECLARE_MESSAGE_MAP()

private:

  MainFrame*   getMainFrame() {return (MainFrame*) m_pMainWnd;}
  AdjProjDoc*  getDocument();
  AdjProjView* getView();

public:
  friend AdjProjDoc* doc();
  };


extern AdjProj theApp;

inline void invalidate() {theApp.invalidate();}
inline  AdjProjDoc*   doc() {return theApp.getDocument();}

