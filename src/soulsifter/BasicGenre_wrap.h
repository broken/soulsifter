#ifndef BASICGENRE_WRAP_H
#define BASICGENRE_WRAP_H

#include <node.h>
#include "BasicGenre.h"

class BasicGenre : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

 private:
  BasicGenre();
  explicit BasicGenre(dogatech::soulsifter::BasicGenre* basicGenre);
  ~BasicGenre();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> create(const v8::Arguments& args);

  static v8::Handle<v8::Value> getId(const v8::Arguments& args);
  static v8::Handle<v8::Value> setId(const v8::Arguments& args);
  static v8::Handle<v8::Value> getName(const v8::Arguments& args);
  static v8::Handle<v8::Value> setName(const v8::Arguments& args);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::BasicGenre* basicGenre;
};

#endif