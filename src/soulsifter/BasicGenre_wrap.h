#ifndef BasicGenre_wrap_h
#define BasicGenre_wrap_h

#include <node.h>
#include <nan.h>
#include "BasicGenre.h"

class BasicGenre : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::BasicGenre* v, bool own);
  dogatech::soulsifter::BasicGenre* getNwcpValue() const { return basicgenre; }

 private:
  BasicGenre();
  explicit BasicGenre(dogatech::soulsifter::BasicGenre* basicgenre);
  ~BasicGenre();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByName);
  static NAN_METHOD(findAll);
  static NAN_METHOD(sync);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(findByFilepath);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getName);
  static NAN_SETTER(setName);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::BasicGenre* basicgenre;
  bool ownWrappedObject;
};

#endif
