

#include "pch.h"
#include "Layers.h"


LayerBase::~LayerBase() { }


void LayerStore::addLayer(TCchar* id) {
Layer* p = getLayer();   if (!p) return;

  p->set(id, cur);   cur->add(p);   cur = p;
  }



void LayerStore::display() {
  notePad << nSetTab(5) << nSetTab(20) << nSetTab(30);
  header.display();
  }


void Layer::display() {
String     parentId = parent ? parent->getID() : _T("...");
LyrIter    iter(*this);
LayerBase* p;

  notePad << nCrlf;

  LayerBase::display();

  notePad << nTab << _T("Parent ID: ") << parentId << nCrlf;

  for (p = iter(); p; p = iter++) p->display();
  }


void AttrLine::display() {
  notePad << nTab;   LayerBase::display();   notePad << nTab << line << nCrlf;
  }


void LayerBase::display() {
String t;

  switch(typ) {
    case NilLyr   : t = _T("NilLyr");   break;
    case AttrLyr  : t = _T("AttrLyr");  break;
    case LayerLyr : t = _T("LayerLyr"); break;
    }

  notePad << t << nTab << key;
  }

