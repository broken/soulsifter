#include <iostream>
#include <node.h>
#include <nan.h>
#include "SearchUtil.h"
#include "Song_wrap.h"
#include "SearchUtil_wrap.h"

v8::Persistent<v8::Function> SearchUtil::constructor;

SearchUtil::SearchUtil() : ObjectWrap(), searchutil(new dogatech::soulsifter::SearchUtil()) {};
SearchUtil::SearchUtil(dogatech::soulsifter::SearchUtil* o) : ObjectWrap(), searchutil(o) {};
SearchUtil::~SearchUtil() { delete searchutil; };

NAN_METHOD(SearchUtil::New) {
  NanScope();

  SearchUtil* obj = new SearchUtil();
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

NAN_METHOD(SearchUtil::NewInstance) {
  NanScope();

  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  NanReturnValue(instance);
}

void SearchUtil::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("SearchUtil"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetTemplate(tpl, "searchSongs", NanNew<v8::FunctionTemplate>(searchSongs)->GetFunction());

  // Prototype

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("SearchUtil"), tpl->GetFunction());
}


NAN_METHOD(SearchUtil::searchSongs) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  vector<dogatech::soulsifter::Song*>* result =  dogatech::soulsifter::SearchUtil::searchSongs(a0);

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result->size());
  for (int i = 0; i < (int) result->size(); i++) {
    v8::Local<v8::Object> instance = Song::NewInstance();
    Song* o = ObjectWrap::Unwrap<Song>(instance);
    o->setNwcpValue((*result)[i]);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete result;
  NanReturnValue(a);
}

