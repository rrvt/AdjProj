// Data Store for Project Groups and Lines


#pragma once
#include "Archive.h"
#include "Expandable.h"
#include "NotePad.h"


enum XMLType {XMLnil, ElementTag, StartTag, EndTag, EmptyTag, XMLAttrib, XMLdeclaration};


//  *p == *q
//  *p >  *q
//  *p <= *q
//  *s =  *p

class XMLbase {
public:

XMLType xmlType;
String  sortName;

  XMLbase() : xmlType(XMLnil) { }
  XMLbase(XMLbase& x) : xmlType(x.xmlType) { }

  bool getFileName(String& line);

  bool operator== (XMLbase& x) {return _tcsicmp(sortName, x.sortName) == 0;}
  bool operator>  (XMLbase& x) {return _tcsicmp(sortName, x.sortName) >  0;}
  bool operator<= (XMLbase& x) {return _tcsicmp(sortName, x.sortName) <= 0;}
  };


struct XMLbasePtr {
XMLbase* p;

  XMLbasePtr() : p(0) { }
 ~XMLbasePtr() { }
  XMLbasePtr(XMLbasePtr& x) {p = x.p;}

  bool        operator== (XMLbasePtr& x) {return *p == *x.p;}
  bool        operator>  (XMLbasePtr& x) {return *p >  *x.p;}
  bool        operator<= (XMLbasePtr& x) {return *p <= *x.p;}
  XMLbasePtr& operator=  (XMLbasePtr& x) {p = x.p; return *this;}
  };

struct Attrib : public XMLbase {
String line;

  Attrib()          : XMLbase() { }
  Attrib(Attrib& a) : XMLbase(a) {line = a.line;}
 ~Attrib() { }

  bool   find(TCchar* s) {return line.find(s) >= 0;}

  bool   getFileName() {return XMLbase::getFileName(line);}

  void   display()           {notePad << line << nCrlf;}
  void   output(Archive& ar) {ar.write(line); ar.crlf();}

  Attrib& operator= (Attrib& a) {xmlType = a.xmlType; line = a.line; return *this;}
  };


class Element : public XMLbase {
Element* upLink;

int      curX;
int      loopX;

public:

String name;
String startTag;                                  // BeginTag ("<tagName>") of element

Expandable<XMLbasePtr, 8> items;                    // A list of elements (BeginTag ... EndTag

String endTag;                                    // EndTag ("</tagName>") of element

  Element() : XMLbase(), upLink(0), curX(0), loopX(0) { }
  Element(Element& d) {*this = d;}
 ~Element() { }

  void     addAttrib(String& s)
             {Attrib* p = new Attrib; items[curX++].p = p;  p->xmlType = XMLAttrib; p->line = s;}

  Element* addElement() {
             Element* p = new Element; items[curX++].p = p; p->xmlType = ElementTag; p->upLink = this;
             return p;
             }

  Element* parent() {return upLink;}

  Element* find(TCchar* s);
  void     setSortNames();
  bool     getFileName() {return XMLbase::getFileName(startTag);}
  void     sort();
  void     swap(Element* p, Element* q);

  void     display();
  void     output(Archive& ar);

  Element& operator= (Element& d);

  XMLbase* startLoop() {loopX = -1; return nextItem();}
  XMLbase* nextItem()  {return ++loopX < items.end() ? items[loopX].p : 0;}

private:

  int      findX(Element* p);
  };


class Store {
Element top;

public:

String xmlVersion;

  Store() { }
 ~Store() { }

  void     addAttrib(Element* e, String& s)  {return e ? e->addAttrib(s) : top.addAttrib(s);}
  Element* addElement(Element* e)            {return e ? e->addElement() : top.addElement();}

  Element* find(TCchar* s)     {return top.find(s);}

  void     display()           {top.display();}

  void     output(Archive& ar) {top.output(ar);}

  Element* parent(Element* e) {return e->parent();}
  };


extern Store store;
