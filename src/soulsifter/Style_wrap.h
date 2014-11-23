#ifndef Style_wrap_h
#define Style_wrap_h

#include <node.h>
#include <nan.h>
#include "Style.h"

class Style : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::Style* v, bool own);
  dogatech::soulsifter::Style* getNwcpValue() const { return style; }

 private:
  Style();
  explicit Style(dogatech::soulsifter::Style* style);
  ~Style();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByREId);
  static NAN_METHOD(findAll);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(findAllParents);
  // Unable to process findAllSortedByName
  // Unable to process findAllSortedByREId
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getName);
  static NAN_SETTER(setName);
  static NAN_GETTER(getREId);
  static NAN_SETTER(setREId);
  static NAN_GETTER(getRELabel);
  static NAN_SETTER(setRELabel);
  static NAN_GETTER(getChildIds);
  static NAN_SETTER(setChildIds);
  static NAN_GETTER(getChildren);
  static NAN_SETTER(setChildren);
  static NAN_GETTER(getParentIds);
  static NAN_SETTER(setParentIds);
  static NAN_GETTER(getParents);
  static NAN_SETTER(setParents);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Style* style;
  bool ownWrappedObject;
};

#endif
