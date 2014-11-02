#include <iostream>
#include <node.h>
#include <nan.h>
#include "SearchUtil_wrap.h"
#include "Song.h"
#include "Song_wrap.h"
#include "Style.h"
#include "Style_wrap.h"

v8::Persistent<v8::Function> SearchUtil::constructor;

SearchUtil::SearchUtil() : ObjectWrap(), searchutil(NULL), ownWrappedObject(true) {};
SearchUtil::SearchUtil(dogatech::soulsifter::SearchUtil* o) : ObjectWrap(), searchutil(o), ownWrappedObject(true) {};
SearchUtil::~SearchUtil() { if (ownWrappedObject) delete searchutil; };

void SearchUtil::setNwcpValue(dogatech::soulsifter::SearchUtil* v, bool own) {
  if (ownWrappedObject)
    delete searchutil;
  searchutil = v;
  ownWrappedObject = own;
}

NAN_METHOD(SearchUtil::New) {
  NanScope();

  SearchUtil* obj = new SearchUtil(new dogatech::soulsifter::SearchUtil());
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

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("SearchUtil"), tpl->GetFunction());
}

NAN_METHOD(SearchUtil::searchSongs) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  int a1(args[1]->Uint32Value());
  int a2(args[2]->Uint32Value());
  string a3(*v8::String::Utf8Value(args[3]->ToString()));
  v8::Local<v8::Array> a4Array = v8::Local<v8::Array>::Cast(args[4]);
  std::vector<dogatech::soulsifter::Style*> a4;
  for (int i = 0; i < a4Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a4Array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a4.push_back(x);
  }
  int a5(args[5]->Uint32Value());
  std::vector<dogatech::soulsifter::Song*>* result =
      dogatech::soulsifter::SearchUtil::searchSongs(a0, a1, a2, a3, a4, a5);

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result->size());
  for (int i = 0; i < (int) result->size(); i++) {
    v8::Local<v8::Object> instance = Song::NewInstance();
    Song* r = ObjectWrap::Unwrap<Song>(instance);
    r->setNwcpValue((*result)[i], true);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete result;
  NanReturnValue(a);
}

