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


static TCchar* FileSection = _T("FileSection");
static TCchar* FileName    = _T("Name");


// AdjProjDoc

IMPLEMENT_DYNCREATE(AdjProjDoc, CDocument)

BEGIN_MESSAGE_MAP(AdjProjDoc, CDocument)
  ON_COMMAND(ID_FILE_OPEN,       &onFileOpen)
  ON_COMMAND(ID_FILE_SAVE,       &onFileSave)
  ON_COMMAND(ID_Adjust,          &onAdjust)
END_MESSAGE_MAP()


// AdjProjDoc construction/destruction

AdjProjDoc::AdjProjDoc() noexcept {
  dsc(_T("Adjust Project"), _T(""), _T("txt"), _T("*.txt"));
  }

AdjProjDoc::~AdjProjDoc() { }


// AdjProjDoc commands


void AdjProjDoc::onAdjust() {
XMLbase* res;
XMLbase* non;
XMLbase* img;

notePad.clear();

#if 1
  onAdjust(_T("ClInclude Include"));

  onAdjust(_T("ClCompile Include"));
  non = onAdjust(_T("None Include"));
  img = onAdjust(_T("Image Include"));
  res = onAdjust(_T("ResourceCompile Include"));

  xmlStore.reorder(res, non, img);
#else
  p   = xmlStore.find(_T("ClInclude Include"));

  if (p)   {  p->setSortNames();   p->sort();}
  p   = xmlStore.find();

  if (p)   {  p->setSortNames();   p->sort();}

  non = xmlStore.find(_T("None Include"));

  if (non) {non->setSortNames(); non->sort();}

  img = xmlStore.find(_T("Image Include"));

  if (img) {img->setSortNames(); img->sort();}

  res = xmlStore.find(_T("ResourceCompile Include"));
#endif

  display();

  invalidate();
  }


XMLbase* AdjProjDoc::onAdjust(TCchar* txt) {
XMLbase* p = xmlStore.findParent(txt);    if (!p) return 0;

  p->setSortNames();   p->sort();   return p;
  }


void AdjProjDoc::display() {
int i;

  notePad.clear();  for (i = 2; i < 50; i += 2) notePad << nSetTab(i);

  xmlStore.display();
  }



void AdjProjDoc::onFileOpen() {
String name;

  xmlStore.clear();

  iniFile.read(FileSection, FileName, name);

  dsc(_T("Adjust Project"), name, _T("vcxproj"), _T("*.vcxproj"));

  if (!setOpenPath(dsc)) return;

  dsc.name = path;   iniFile.write(FileSection, FileName, path);

  if (OnOpenDocument(path)) display();

  invalidate();
  }


void AdjProjDoc::onFileSave() {

  if (!setIncSavePath(dsc)) return;   backupFile(3);   OnSaveDocument(path);

  iniFile.write(FileSection, FileName, path);
  }


// AdjProjDoc serialization

void AdjProjDoc::serialize(Archive& ar) {
  if (ar.isStoring()) xmlStore.output(ar);
  else                xmlStore.load(ar);
  }


// AdjProjDoc diagnostics

#ifdef _DEBUG
void AdjProjDoc::AssertValid() const          {CDocument::AssertValid();}
void AdjProjDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG

