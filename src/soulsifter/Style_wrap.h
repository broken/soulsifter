#ifndef Style_wrap_h
#define Style_wrap_h

#include <node.h>
#include <nan.h>
#include "Style.h"

class Style : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static NAN_METHOD(NewInstance);

  void setNwcpValue(dogatech::soulsifter::Style* s) { style = s; }

 private:
  Style();
  explicit Style(dogatech::soulsifter::Style* style);
  ~Style();

  static NAN_METHOD(New);

  dogatech::soulsifter::Style* getNwcpValue() const { return style; }

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByREId);
  static NAN_METHOD(findAll);
  static NAN_METHOD(sync);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(findAllParents);
  static NAN_METHOD(getId);
  static NAN_METHOD(setId);
  static NAN_METHOD(getName);
  static NAN_METHOD(setName);
  static NAN_METHOD(getREId);
  static NAN_METHOD(setREId);
  static NAN_METHOD(getRELabel);
  static NAN_METHOD(setRELabel);
  static NAN_METHOD(getChildren);
  static NAN_METHOD(setChildren);
  static NAN_METHOD(addChildById);
  static NAN_METHOD(removeChildById);
  static NAN_METHOD(getParents);
  static NAN_METHOD(setParents);
  static NAN_METHOD(addParentById);
  static NAN_METHOD(removeParentById);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Style* style;
};

#endif
