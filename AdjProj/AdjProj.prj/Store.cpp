// Data Store for Project Groups and Lines


#include "stdafx.h"
#include "Store.h"
#include "qsort.h"


Store store;                    // The place where the file is stored



Element& Element::operator= (Element& e) {
int n = items.end();

  xmlType  = e.xmlType;   sortName = e.sortName;   name     = e.name;
  upLink   = e.upLink;    loopX    = e.loopX;      startTag = e.startTag;
  endTag   = e.endTag;

  for (int i = 0; i < n; i++) items[i] = e.items[i];

  return *this;
  }


Element* Element::find(TCchar* s) {
int      n = items.end();
int      i;
bool     rslt = false;
Element* elem;

  for (i = 0; i < n; i++) {
    XMLbase* p = items[i].p;    if (!p) return 0;
    Element* el;
    Attrib*  at;

    switch (p->xmlType) {
      case XMLAttrib  : at = (Attrib*)  p; if (at->find(s)) return this; break;
      case ElementTag : el = (Element*) p;
                        if (el->startTag.find(s) >= 0) return this;
                        elem = el->find(s);  if (elem) return elem;
                        break;
      }
    }

  return 0;
  }


void Element::sort() {int n = items.end();   qsort(&items[0], &items[n-1]);}


void Element::clear() {
int       n = items.end();
int       i;
XMLbaseP* rcdP;

  for (i = 0; i < n; i++) {rcdP = items.getRcdPtr(i);   if (rcdP) rcdP->clear();}

  upLink = 0; loopX = 0; name.clear(); startTag.clear(); endTag.clear();
  }


// The free node included in the template doesn't work for multiple node sizes.  Leaves lost memory, UGH!

void XMLbaseP::clear() {

  if (!p) return;

  switch(p->xmlType) {
    case ElementTag : {NewAlloc(Element); Element* q = (Element*) p;  FreeNode(q);} break;
    case XMLAttrib  : {NewAlloc(Attrib);  Attrib*  q = (Attrib*)  p;  FreeNode(q);} break;
    }

  p = 0;
  }


void Store::reorder(Element* first, Element* second, Element* third) {
int n = top.items.end();
int i;

  for (i = 0; i < n; i++) {
    Element* proj = top.getElement(i);

    if (proj && proj->startTag.find(_T("<Project")) >= 0) {
      proj->reorder(first, second, third);  break;
      }
    }
  }


void Element::reorder(Element* first, Element* second, Element* third) {
int n = items.end();
int i;

  for (i = 0; i < n; i++) {
    Element* p = getElement(i);   if (!p) continue;
    if (p == first)
      break;
    if (p == second || p == third)
      {items[i].p = first; break;}
    }
  for (i++; i < n; i++) {
    Element* p = getElement(i);   if (!p) continue;
    if (p == second)
      break;
    if (p == first || p == third)
      {items[i].p = second; break;}
    }
  for (i++; i < n; i++) {
    Element* p = getElement(i);   if (!p) continue;
    if (p == third)
      break;
    if (p == first || p == second)
      {items[i].p = third; break;}
    }
  }


Element* Element::getElement(int i) {
XMLbase* p = items[i].p;

  return p && p->xmlType == ElementTag ? (Element*) p : 0;
  }


void Element::display() {
int n = items.end();
int i;

  if (!startTag.isEmpty()) notePad << startTag << nCrlf;

  for (i = 0; i < n; i++) {
    XMLbase* p = items[i].p;    if (!p) return;
    Element* el;
    Attrib*  at;

    switch (p->xmlType) {
      case XMLAttrib  : at = (Attrib*)  p; at->display(); break;
      case ElementTag : el = (Element*) p; el->display(); break;
      }
    }

  if (!startTag.isEmpty()) notePad << endTag << nCrlf;
  }


void Element::output(Archive& ar) {
int n = items.end();
int i;

  if (!startTag.isEmpty()) {ar.write(startTag); ar.crlf();}

  for (i = 0; i < n; i++) {
    XMLbase* p = items[i].p;    if (!p) return;
    Element* el;
    Attrib*  at;

    switch (p->xmlType) {
      case XMLAttrib  : at = (Attrib*)  p; at->output(ar); break;
      case ElementTag : el = (Element*) p; el->output(ar); break;
      }
    }

  if (!startTag.isEmpty()) {ar.write(endTag); ar.crlf();}
  }


void Element::setSortNames() {
ElIter   iter(*this);
XMLbase* base;
Element* el;
Attrib*  at;

  if (name != _T("ItemGroup")) return;

  for (base = iter(); base; base = iter++) {
    switch (base->xmlType) {
      case XMLAttrib  : at = (Attrib*)  base; at->getFileName(); break;
      case ElementTag : el = (Element*) base; el->getFileName(); break;
      }
    }
  }




bool XMLbase::getFileName(String& line) {
int    begPos;
int    endPos;

int x = line.length();

  endPos = line.findLastOf(_T('"'));
  begPos = line.findLastOf(_T('\\'), endPos);   if (begPos < 0) begPos = line.find(_T('"'));
  begPos++;

  if (begPos < 0 || endPos <= begPos) return false;

  sortName = line.substr(begPos, endPos-begPos);   return true;
  }

