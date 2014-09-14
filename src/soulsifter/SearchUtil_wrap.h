#ifndef SearchUtil_wrap_h
#define SearchUtil_wrap_h

#include <node.h>
#include <nan.h>
#include "SearchUtil.h"

class SearchUtil : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::SearchUtil* v) { searchutil = v; }
  dogatech::soulsifter::SearchUtil* getNwcpValue() const { return searchutil; }

 private:
  SearchUtil();
  explicit SearchUtil(dogatech::soulsifter::SearchUtil* searchutil);
  ~SearchUtil();

  static NAN_METHOD(New);

  static NAN_METHOD(searchSongs);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::SearchUtil* searchutil;
};

#endif
