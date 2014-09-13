#ifndef SearchUtil_wrap_h
#define SearchUtil_wrap_h

#include <node.h>
#include <nan.h>
#include "SearchUtil.h"

class SearchUtil : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static NAN_METHOD(NewInstance);

 private:
  SearchUtil();
  explicit SearchUtil(dogatech::soulsifter::SearchUtil* searchutil);
  ~SearchUtil();

  static NAN_METHOD(New);

  dogatech::soulsifter::SearchUtil* getNwcpValue() const { return searchutil; }

  static NAN_METHOD(searchSongs);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::SearchUtil* searchutil;
};

#endif
