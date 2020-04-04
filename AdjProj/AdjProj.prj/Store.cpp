// Data Store for Project Groups and Lines


#include "stdafx.h"
#include "Store.h"
#include "qsort.h"


Store store;                                          // The place where the file is stored


Element& Element::operator= (Element& e) {
  name = e.name; xmlType = e.xmlType;

  for (int i = 0; i < items.end(); i++) items[i] = e.items[i];

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
      case ElementTag : el = (Element*) p; elem = el->find(s);  if (elem) return elem;
      }
    }

  return 0;
  }


void Element::sort() {
int n = items.end();

  qsort(&items[0], &items[n-1]);
  }


void Element::swap(Element* p, Element* q) {
int x = findX(p);  if (x < 0) return;
int y = findX(q);  if (y < 0) return;

  items[x].p = q; items[y].p = p;
  }


int Element::findX(Element* p) {
int n = items.end();
int i;

  for (i = 0; i < n; i++) if (items[i].p == p) return i;

  return -1;
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
XMLbase* base;
Element* el;
Attrib*  at;

  if (name != _T("ItemGroup")) return;

  for (base = startLoop(); base; base = nextItem()) {
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

  endPos = line.findLast(_T('"'));
  begPos = line.findLast(_T('\\'), endPos);   if (begPos < 0) begPos = line.find(_T('"'));
  begPos++;

  if (begPos < 0 || endPos <= begPos) return false;

  sortName = line.substr(begPos, endPos-begPos);  return true;
  }

