#ifndef TagService_wrap_h
#define TagService_wrap_h

#include <node.h>
#include <nan.h>
#include "TagService.h"

class TagService : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::TagService* v, bool own);
  dogatech::soulsifter::TagService* getNwcpValue() const { return tagservice; }

 private:
  TagService();
  explicit TagService(dogatech::soulsifter::TagService* tagservice);
  ~TagService();

  static NAN_METHOD(New);

  static NAN_METHOD(readId3v2Tag);
  static NAN_METHOD(updateSongAttributesFromTags);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::TagService* tagservice;
  bool ownWrappedObject;
};

#endif
