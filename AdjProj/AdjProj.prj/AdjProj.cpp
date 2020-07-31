// AdjProj.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "AdjProj.h"
#include "About.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "Resources.h"
#include "AdjProjDoc.h"
#include "AdjProjView.h"


AdjProj theApp;                       // The one and only AdjProj object
IniFile iniFile;


// AdjProj

BEGIN_MESSAGE_MAP(AdjProj, CWinAppEx)
  ON_COMMAND(ID_APP_ABOUT,        &AdjProj::OnAppAbout)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// AdjProj construction

AdjProj::AdjProj() noexcept {
ResourceData res;

  res.getVersion(version);

  if (res.getAppID(appID)) SetAppID(appID);
  }


// AdjProj initialization

BOOL AdjProj::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(AdjProjDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(AdjProjView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("AdjProj"));  setTitle(_T("Adjust Project Files"));

  view()->setFont(_T("Courier New"), 120);

  // The one and only window has been initialized, so show and update it

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


#if 0
void AdjProj::invalidate() {if (getView()) view->Invalidate();}


AdjProjView* AdjProj::getView() {
POSITION   pos;

  if (view) return view;

  if (!getDocument()) return 0;

  pos  = doc->GetFirstViewPosition();   if (!pos)  return 0;

  return view = (AdjProjView*) doc->GetNextView(pos);
  }



AdjProjDoc* AdjProj::getDocument() {

  if (doc) return doc;

  POSITION      pos = GetFirstDocTemplatePosition(); if (!pos) return 0;
  CDocTemplate* t   = GetNextDocTemplate(pos);       if (!t)   return 0;

  pos = t->GetFirstDocPosition();                    if (!pos) return 0;

  return doc = (AdjProjDoc*) t->GetNextDoc(pos);
  }
#endif


void AdjProj::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


