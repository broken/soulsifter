#include <iostream>
#include <node.h>
#include <nan.h>
#include "SearchUtil_wrap.h"
#include "Song.h"
#include "Song_wrap.h"
#include "Style.h"
#include "Style_wrap.h"

Nan::Persistent<v8::Function> SearchUtil::constructor;

SearchUtil::SearchUtil() : Nan::ObjectWrap(), searchutil(NULL), ownWrappedObject(true) {};
SearchUtil::SearchUtil(dogatech::soulsifter::SearchUtil* o) : Nan::ObjectWrap(), searchutil(o), ownWrappedObject(true) {};
SearchUtil::~SearchUtil() { if (ownWrappedObject) delete searchutil; };

void SearchUtil::setNwcpValue(dogatech::soulsifter::SearchUtil* v, bool own) {
  if (ownWrappedObject)
    delete searchutil;
  searchutil = v;
  ownWrappedObject = own;
}

void SearchUtil::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  SearchUtil* obj = new SearchUtil(new dogatech::soulsifter::SearchUtil());
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> SearchUtil::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void SearchUtil::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("SearchUtil").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetMethod(tpl, "searchSongs", searchSongs);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  exports->Set(Nan::New<v8::String>("SearchUtil").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

void SearchUtil::searchSongs(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  string a0(*v8::String::Utf8Value(info[0]->ToString()));
  int a1(info[1]->IntegerValue());
  v8::Local<v8::Array> a2Array = v8::Local<v8::Array>::Cast(info[2]);
  std::set<string> a2;
  for (int i = 0; i < a2Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a2Array->Get(i);
    string x(*v8::String::Utf8Value(tmp->ToString()));
    a2.insert(x);
  }
  v8::Local<v8::Array> a3Array = v8::Local<v8::Array>::Cast(info[3]);
  std::vector<dogatech::soulsifter::Style*> a3;
  for (int i = 0; i < a3Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a3Array->Get(i);
    dogatech::soulsifter::Style* x(Nan::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a3.push_back(x);
  }
  v8::Local<v8::Array> a4Array = v8::Local<v8::Array>::Cast(info[4]);
  std::vector<dogatech::soulsifter::Song*> a4;
  for (int i = 0; i < a4Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a4Array->Get(i);
    dogatech::soulsifter::Song* x(Nan::ObjectWrap::Unwrap<Song>(tmp->ToObject())->getNwcpValue());
    a4.push_back(x);
  }
  int a5(info[5]->IntegerValue());
  std::vector<dogatech::soulsifter::Song*>* result =
      dogatech::soulsifter::SearchUtil::searchSongs(a0, a1, a2, a3, a4, a5);

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result->size());
  for (int i = 0; i < (int) result->size(); i++) {
    v8::Local<v8::Object> instance = Song::NewInstance();
    Song* r = Nan::ObjectWrap::Unwrap<Song>(instance);
    r->setNwcpValue((*result)[i], true);
    a->Set(Nan::New<v8::Number>(i), instance);
  }
  delete result;
  info.GetReturnValue().Set(a);
}

