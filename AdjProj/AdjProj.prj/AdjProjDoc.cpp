// AdjProjDoc.cpp : implementation of the AdjProjDoc class


#include "stdafx.h"
#include "AdjProjDoc.h"
#include "AdjProj.h"
#include "AdjProjView.h"
#include "CopyFile.h"
#include "filename.h"
#include "filesrch.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Resource.h"
#include "ResourceExtra.h"
#include "Store.h"


static TCchar* FileSection = _T("FileSection");
static TCchar* FileName    = _T("Name");


// AdjProjDoc

IMPLEMENT_DYNCREATE(AdjProjDoc, CDocument)

BEGIN_MESSAGE_MAP(AdjProjDoc, CDocument)
  ON_COMMAND(ID_FILE_OPEN,       &OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,       &OnFileSave)
  ON_COMMAND(ID_Adjust,          &OnAdjust)
END_MESSAGE_MAP()


// AdjProjDoc construction/destruction

AdjProjDoc::AdjProjDoc() noexcept {
  dsc(_T("Adjust Project"), _T(""), _T("txt"), _T("*.txt"));
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


void AdjProjDoc::display() {
int i;

  notePad.clear();  for (i = 2; i < 50; i += 2) notePad << nSetTab(i);   store.display();

  invalidate();
  }



void AdjProjDoc::OnFileOpen() {
String name;

  store.clear();

  iniFile.read(FileSection, FileName, name);

  dsc(_T("Adjust Project"), name, _T("vcxproj"), _T("*.vcxproj"));

  if (!setOpenPath(dsc)) return;

  dsc.name = path;   iniFile.write(FileSection, FileName, path);

  if (OnOpenDocument(path)) display();
  }


void AdjProjDoc::OnFileSave() {

  if (!setIncSavePath(dsc)) return;   backupFile(3);   OnSaveDocument(path);

  iniFile.write(FileSection, FileName, path);
  }


// AdjProjDoc serialization

void AdjProjDoc::serialize(Archive& ar) {
  if (ar.isStoring()) xml.output(ar);
  else                xml.input(ar);
  }


// AdjProjDoc diagnostics

#ifdef _DEBUG
void AdjProjDoc::AssertValid() const {CDocument::AssertValid();}

void AdjProjDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG

