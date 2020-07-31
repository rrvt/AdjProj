// AdjProj.h : main header file for the AdjProj application

#pragma once
#include "CApp.h"
#include "IniFile.h"
#include "MainFrame.h"
//#include "resource.h"       // main symbols


class AdjProjDoc;
class AdjProjView;


// AdjProj:
// See AdjProj.cpp for the implementation of this class

class AdjProj : public CApp {
String       appID;

//AdjProjDoc*  doc;
//AdjProjView* view;

public:

String version;

               AdjProj() noexcept;

  virtual BOOL InitInstance();

  AdjProjDoc*  doc()  {return (AdjProjDoc*)  CApp::getDoc();}
  AdjProjView* view() {return (AdjProjView*) CApp::getView();}

  afx_msg void OnAppAbout();

  DECLARE_MESSAGE_MAP()
  };


extern AdjProj theApp;

inline void          invalidate() { theApp.invalidate();}
inline AdjProjDoc*   doc() { return theApp.doc();}
inline AdjProjView*  view() {return theApp.view();}

