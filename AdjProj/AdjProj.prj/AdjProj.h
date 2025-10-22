// AdjProj.h : main header file for the AdjProj application

#pragma once
#include "CApp.h"
#include "IniFileEx.h"
#include "MainFrame.h"


class AdjProjDoc;
class AdjProjView;


// AdjProj:
// See AdjProj.cpp for the implementation of this class

class AdjProj : public CApp {

String appID;

public:

String version;

               AdjProj() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

  AdjProjDoc*  doc()  {return (AdjProjDoc*)  CApp::getDoc();}
  AdjProjView* view() {return (AdjProjView*) CApp::getView();}

  afx_msg void OnAppAbout();
  afx_msg void OnHelp();

  DECLARE_MESSAGE_MAP()
  };


extern AdjProj theApp;


inline AdjProjDoc*   doc() { return theApp.doc();}
inline AdjProjView*  view() {return theApp.view();}

