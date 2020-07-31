// Data Store for Project Groups and Lines


#pragma once
#include "Archive.h"
#include "Expandable.h"
#include "IterT.h"
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
  XMLbase(XMLbase& x) : xmlType(x.xmlType), sortName(x.sortName) { }

  XMLbase& operator= (XMLbase& x) {xmlType = x.xmlType; sortName = x.sortName;}

  bool getFileName(String& line);

  bool operator== (XMLbase& x) {return _tcsicmp(sortName, x.sortName) == 0;}
  bool operator>  (XMLbase& x) {return _tcsicmp(sortName, x.sortName) >  0;}
  bool operator<= (XMLbase& x) {return _tcsicmp(sortName, x.sortName) <= 0;}

//  void examine(XMLbase& x, TCchar* where);
  };


struct XMLbasePtr {
XMLbase* p;

  XMLbasePtr() : p(0) { }
 ~XMLbasePtr() { }
  XMLbasePtr(XMLbasePtr& x) {p = x.p;}

  void        clear();

  bool        operator== (XMLbasePtr& x) {return *p == *x.p;}
  bool        operator>  (XMLbasePtr& x) {return *p >  *x.p;}
  bool        operator<= (XMLbasePtr& x) {return *p <= *x.p;}
  XMLbasePtr& operator=  (XMLbasePtr& x) {p = x.p; return *this;}
  };


struct Attrib : public XMLbase {
String line;

  Attrib()          : XMLbase() { }
  Attrib(Attrib& a) : XMLbase(a) {line = a.line; xmlType  = a.xmlType;   sortName = a.sortName;}
 ~Attrib() {clear();}

  void   clear() {line.clear();}

  bool   find(TCchar* s) {return line.find(s) >= 0;}

  bool   getFileName() {return XMLbase::getFileName(line);}

  void   display()           {notePad << line << nCrlf;}
  void   output(Archive& ar) {ar.write(line); ar.crlf();}

  Attrib& operator= (Attrib& a)
                            {line = a.line; xmlType  = a.xmlType;   sortName = a.sortName; return *this;}
  };


class Element;
typedef IterT<Element, XMLbase> ElIter;


class Element : public XMLbase {
Element* upLink;

int      loopX;

public:

String   name;
String   startTag;                                // BeginTag ("<tagName>") of element
String   endTag;                                  // EndTag ("</tagName>") of element

Expandable<XMLbasePtr, 2> items;                  // A list of elements (BeginTag ... EndTag

  Element() : XMLbase(), upLink(0), loopX(0) { }
  Element(Element& d) {*this = d;}
 ~Element() {clear();}

  void     clear();

  void     addAttrib(String& s) {
    NewAlloc(Attrib);  Attrib* p = AllocNode;
    items[items.end()].p = p;  p->xmlType = XMLAttrib; p->line = s;
    }

  Element* addElement() {
             NewAlloc(Element);
             Element* p = AllocNode; items[items.end()].p = p; p->xmlType = ElementTag;
             p->upLink = this;   return p;
             }

  Element* parent() {return upLink;}

  Element* find(TCchar* s);
  void     setSortNames();
  bool     getFileName() {return XMLbase::getFileName(startTag);}
  void     sort();
  void     reorder(Element* first, Element* second, Element* third);
  Element* getElement(int i);

  void     display();
  void     output(Archive& ar);

  Element& operator= (Element& d);

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  XMLbase* datum(int i) {return 0 <= i && i < nData() ? items[i].p : 0;}

  // returns number of data items in array
  int   nData()      {return items.end();}

  friend typename ElIter;
  };


class Store {
Element top;

public:

String xmlVersion;

  Store() { }
 ~Store() { }

  void     addAttrib(Element* e, String& s)  {return e ? e->addAttrib(s) : top.addAttrib(s);}
  Element* addElement(Element* e)            {return e ? e->addElement() : top.addElement();}

  void     clear() {top.clear();}

  Element* find(TCchar* s)     {return top.find(s);}

  void     reorder(Element* first, Element* second, Element* third);


  void     display()           {top.display();}

  void     output(Archive& ar) {top.output(ar);}

  Element* parent(Element* e) {return e->parent();}
  };


extern Store store;
