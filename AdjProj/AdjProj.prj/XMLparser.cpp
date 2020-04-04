// XML Parser -- Data goes into the Store (see Store.h)


#include "stdafx.h"
#include "XMLparser.h"
#include "MessageBox.h"


void XMLparser::input(Archive& ar) {
String   line;
XMLType  ty;
String   elementName;
Element* element = 0;

  while (readLine(ar, line)) {

    ty = getType(line, elementName);

    switch (ty) {
      case StartTag : element = store.addElement(element); element->name = elementName;
                      element->startTag = line; break;

      case EndTag   : element->endTag = line;
                      if (elementName != element->name) {
                        messageBox(_T("End Tag name does not match Start Tag name.")); return;
                        }
                      element = store.parent(element);    break;

      default       : store.addAttrib(element, line); break;
      }
    }
  }



bool XMLparser::readLine(Archive& ar, String& s) {
Tchar  tch;

  s.clear();

  while (ar.read(tch)) {
    if (tch == _T('\n')) return true;
    if (tch == _T('\r')) continue;
    s += tch;
    }

  return !s.isEmpty();
  }


XMLType XMLparser::getType(String& s, String& name) {
int     i;
int     n   = s.length();

Tag     tag(s);
String  names[10];
XMLType typ[10];

  name.clear();

  for (i = 0; i < noElements(names); i++) {
    typ[i] = tag.next(names[i]);  if (typ[i] == XMLnil) break;
    }

  if (i == 1) {name = names[0]; return typ[0];}

  if (i == 2 && typ[0] == StartTag && typ[1] == EndTag && names[0] == names[1])
                                                                    {name = names[0]; return ElementTag;}
  if (i > 2) {messageBox(_T("More than two tags in line"));
  }


  name = names[0]; return typ[0];
  }


XMLType Tag::next(String& name) {
Tchar   tch;
int     state   = 0;
XMLType typ     = XMLnil;
bool    collect = true;

  if (!p) return XMLnil;    name.clear();

  for (tch = *p++; tch; tch = *p++) {
    switch (state) {

      case 0: if (tch == _T('<')) {state = 1; typ = StartTag;}   break;

      case 1: if (tch == _T('/')) {state = 4; typ = EndTag; break;}
              if (tch == _T('?')) return XMLdeclaration;
              state = 2;

      case 2: if (tch == _T('>')) return typ;
              if (tch == _T('/')) {state = 3; break;}
              if (tch == _T(' ')) {collect = false; break;}
              if (collect) name += tch;
              break;

      case 3: if (tch == _T('>')) return EmptyTag;
              if (collect) {name += _T('/'); name += tch;}
              state = 2; break;

      case 4: if (tch == _T('>')) return typ;
              if (tch == _T(' ')) collect = false;
              if (collect) name += tch;
              state = 2; break;
      }
    }

  return XMLnil;
  }

