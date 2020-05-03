// AdjProjDoc.cpp : implementation of the AdjProjDoc class


#include "stdafx.h"
#include "AdjProjDoc.h"
#include "AdjProj.h"
#include "CopyFile.h"
#include "filename.h"
#include "filesrch.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Store.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// AdjProjDoc

IMPLEMENT_DYNCREATE(AdjProjDoc, CDocument)

BEGIN_MESSAGE_MAP(AdjProjDoc, CDocument)
  ON_COMMAND(ID_FILE_OPEN,  &AdjProjDoc::OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,  &AdjProjDoc::OnFileSave)
  ON_COMMAND(ID_Test,       &AdjProjDoc::OnTest)
  ON_COMMAND(ID_Adjust,     &AdjProjDoc::OnAdjust)

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

  p   = store.find(_T("ClInclude"));      if (p)   {  p->setSortNames();   p->sort();}
  p   = store.find(_T("ClCompile"));      if (p)   {  p->setSortNames();   p->sort();}
  non = store.find(_T("None Include"));   if (non) {non->setSortNames(); non->sort();}
  img = store.find(_T("Image Include"));  if (img) {img->setSortNames(); img->sort();}
  res = store.find(_T("ResourceCompile Include"));

  if (res && (non || img)) {

    store.reorder(res, non, img);


#if 0
    Element* parent;
    //    parent = res->parent();
    bool     seenRes;
    bool     seenNon;
    bool     seenImg;

    for (p = (Element*) parent->startLoop(); p; p = (Element*) parent->nextItem()) {
      if (p == res) seenRes = true;
      if (p == non) seenNon = true;
      if (p == img) seenImg = true;

      if (seenNon && !seenRes) {parent->swap(res, non); break;}
      if (seenImg && !seenRes) {parent->swap(res, img); break;}
      }

    if (seenImg && img && non) parent->swap(img, non);
#endif
    }

  display();
  }



void AdjProjDoc::OnTest() {

  theApp.setTitle(_T("My Test"));

  notePad.close();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void AdjProjDoc::display() {
int i;

  notePad.close();  for (i = 2; i < 50; i += 2) notePad << nSetTab(i);   store.display();

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

