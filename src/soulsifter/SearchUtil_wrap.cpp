#include <iostream>
#include <node.h>
#include <nan.h>
#include "SearchUtil.h"
#include "SearchUtil_wrap.h"
#include "Song.h"
#include "Song_wrap.h"
#include "Style.h"
#include "Style_wrap.h"

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

v8::Local<v8::Object> SearchUtil::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void SearchUtil::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("SearchUtil"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetTemplate(tpl, "searchSongs", NanNew<v8::FunctionTemplate>(searchSongs)->GetFunction());

  // Prototype

  // Accessors

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("SearchUtil"), tpl->GetFunction());
}


NAN_METHOD(SearchUtil::searchSongs) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  int a1(args[1]->Uint32Value());
  int a2(args[2]->Uint32Value());
  string a3(*v8::String::Utf8Value(args[3]->ToString()));
  v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[4]);
  std::vector<dogatech::soulsifter::Style*> a4;
  for (int i = 0; i < array->Length(); ++i) {
    v8::Local<v8::Value> tmp = array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a4.push_back(x);
  }
  int a5(args[5]->Uint32Value());
  vector<dogatech::soulsifter::Song*>* result =  dogatech::soulsifter::SearchUtil::searchSongs(a0, a1, a2, a3, a4, a5);

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

