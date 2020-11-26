// AdjProjDoc.cpp : implementation of the AdjProjDoc class


#include "stdafx.h"
#include "AdjProjDoc.h"
#include "AdjProj.h"
#include "AdjProjView.h"
#include "CopyFile.h"
#include "filename.h"
#include "filesrch.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "Store.h"


// AdjProjDoc

IMPLEMENT_DYNCREATE(AdjProjDoc, CDocument)

BEGIN_MESSAGE_MAP(AdjProjDoc, CDocument)
  ON_COMMAND(ID_FILE_OPEN,  &OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,  &OnFileSave)
  ON_COMMAND(ID_Test,       &OnTest)
  ON_COMMAND(ID_Adjust,     &OnAdjust)
  ON_COMMAND(ID_Options,    &OnOptions)

END_MESSAGE_MAP()


// AdjProjDoc construction/destruction

AdjProjDoc::AdjProjDoc() noexcept {
  saveAsTitle = _T("Adjust Project");   defExt = _T("txt");   defFilePat = _T("*.txt");
  }

AdjProjDoc::~AdjProjDoc() { }


// AdjProjDoc commands


void AdjProjDoc::OnAdjust() {
Element* p;
Element* res;
Element* non;
Element* img;

  p   = store.find(_T("ClInclude Include")); if (p)   {  p->setSortNames();   p->sort();}
  p   = store.find(_T("ClCompile Include")); if (p)   {  p->setSortNames();   p->sort();}
  non = store.find(_T("None Include"));      if (non) {non->setSortNames(); non->sort();}
  img = store.find(_T("Image Include"));     if (img) {img->setSortNames(); img->sort();}
  res = store.find(_T("ResourceCompile Include"));
                                  if (res && (non || img)) {store.reorder(res, non, img);}
  display();
  }


void AdjProjDoc::OnOptions() {options();  view()->setOrientation(options.orient);}



void AdjProjDoc::OnTest() {

  theApp.setTitle(_T("My Test"));

  notePad.clear();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void AdjProjDoc::display() {
int i;

  notePad.clear();  for (i = 2; i < 50; i += 2) notePad << nSetTab(i);   store.display();

  invalidate();
  }



void AdjProjDoc::OnFileOpen() {
String path;

  store.clear();

  saveAsTitle = _T("Adjust Project");   defExt = _T("vcxproj");   defFilePat = _T("*.vcxproj");

  if (!getPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  if (OnOpenDocument(path)) display();
  }


void AdjProjDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  backupFile(path, 3);

  OnSaveDocument(path);
  }


// AdjProjDoc serialization

void AdjProjDoc::serialize(Archive& ar) {
  if (ar.isStoring()) xml.output(ar);
  else                xml.input(ar);
  }


// AdjProjDoc diagnostics

#ifdef _DEBUG
void AdjProjDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void AdjProjDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


