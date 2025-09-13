// Layers -- Each Layer may be sorted and a layer may have multiple layers below it


#pragma once
#include "ExpandableP.h"
#include "FileName.h"
#include "IterT.h"



enum LyrType {NilLyr, AttrLyr, LayerLyr};


class LayerBase {
protected:

LyrType typ;
String  key;

public:

               LayerBase()                     : typ(NilLyr)    { }
               LayerBase(LyrType t)            : typ(t)         { }
               LayerBase(LyrType t, TCchar* k) : typ(t), key(k) { }
  virtual     ~LayerBase() = 0;

  virtual void clear() {typ = NilLyr;   key.clear();}

  virtual void load(TCchar* tc) { }

  virtual void display();
  };


class AttrLine : public LayerBase {

String line;

public:

  AttrLine() : LayerBase(AttrLyr) { }
 ~AttrLine() { }

  void clear() override {LayerBase::clear();   line.clear();}

  void load(TCchar* tc) override {line = tc;   key = getMainName(line);}

  void display() override;
  };



class Layer;
typedef DatumPtrT<  LayerBase, String>              LyrBaseP;
typedef ExpandableP<LayerBase, String, LyrBaseP, 2> LyrData;
typedef IterT<Layer, LayerBase>                     LyrIter;        // Iterator for the Layer


class Layer : public LayerBase {

Layer*  parent;
LyrData data;

public:

  Layer()           : LayerBase(LayerLyr)     { }
  Layer(TCchar* tc) : LayerBase(LayerLyr, tc) { }
 ~Layer() {parent = 0;}

  void clear() override {LayerBase::clear();   parent = 0;   data.clear();}

  void set(TCchar* id, Layer* parent) {key = id;   this->parent = parent;}

  TCchar* getID() {return key;}

  void add(LayerBase* p) {data += p;}

  void display() override;

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  LayerBase* datum(int i) {return 0 <= i && i < nData() ? data[i] : 0;}

  int        nData()      {return data.end();}            // returns number of data items in array

  void       removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename LyrIter;
  };


class LayerStore {

Layer  header;                      // Points to the top of the tree, has no data
Layer* cur;                         // Current layer being used to store data

public:

  LayerStore() : cur(&header) {header.set(_T("Header"), 0);}
 ~LayerStore() { }

  AttrLine* getAttrLine() {NewAlloc(AttrLine);   return AllocNode;}
  Layer*    getLayer()    {NewAlloc(Layer);      return AllocNode;}

  void addLayer(TCchar* id);
  void add(AttrLine* p) {cur->add(p);}

  void display();
  };

