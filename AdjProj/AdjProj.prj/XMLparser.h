// XML Parser -- Data goes into the Store (see Store.h)


#pragma once
#include "Archive.h"
#include "Store.h"


// Used to find all the tags in a line

class Tag {
TCchar* p;

public:

  Tag(String& s) :p(s.str()) { }                    // line on which to work

  XMLType next(String& name);

private:

  Tag() : p(0){ }
  };



class XMLparser {
TCchar* p;
public:

  XMLparser() { }
 ~XMLparser() { }

  void input(Archive& ar);
  void output(Archive& ar) {store.output(ar);}

private:

  bool    readLine(Archive& ar, String& s);
  XMLType getType(String& s, String& elementName);
  };

