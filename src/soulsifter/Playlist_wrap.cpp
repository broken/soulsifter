#include <iostream>
#include <node.h>
#include <nan.h>
#include "Playlist_wrap.h"
#include "Playlist.h"
#include "PlaylistEntry.h"
#include "PlaylistEntry_wrap.h"
#include "Playlist_wrap.h"
#include "ResultSetIterator.h"
#include "Style.h"
#include "Style_wrap.h"

Nan::Persistent<v8::Function> Playlist::constructor;

Playlist::Playlist() : Nan::ObjectWrap(), playlist(NULL), ownWrappedObject(true) {};
Playlist::Playlist(dogatech::soulsifter::Playlist* o) : Nan::ObjectWrap(), playlist(o), ownWrappedObject(true) {};
Playlist::~Playlist() { if (ownWrappedObject) delete playlist; };

void Playlist::setNwcpValue(dogatech::soulsifter::Playlist* v, bool own) {
  if (ownWrappedObject)
    delete playlist;
  playlist = v;
  ownWrappedObject = own;
}

void Playlist::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  dogatech::soulsifter::Playlist* wrappedObj = NULL;
  if (info.Length()) {
    dogatech::soulsifter::Playlist* xtmp(Nan::ObjectWrap::Unwrap<Playlist>(info[0]->ToObject())->getNwcpValue());
    dogatech::soulsifter::Playlist& x = *xtmp;
    wrappedObj = new dogatech::soulsifter::Playlist(x);
  } else {
    wrappedObj = new dogatech::soulsifter::Playlist();
  }

  Playlist* obj = new Playlist(wrappedObj);
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> Playlist::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void Playlist::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Playlist").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "clear", clear);
  Nan::SetMethod(tpl, "findById", findById);
  Nan::SetMethod(tpl, "findByName", findByName);
  Nan::SetMethod(tpl, "findAll", findAll);
  Nan::SetPrototypeMethod(tpl, "update", update);
  Nan::SetPrototypeMethod(tpl, "save", save);
  Nan::SetPrototypeMethod(tpl, "sync", sync);
  Nan::SetPrototypeMethod(tpl, "erase", erase);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("id").ToLocalChecked(), getId, setId);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("name").ToLocalChecked(), getName, setName);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("query").ToLocalChecked(), getQuery, setQuery);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("gmusicId").ToLocalChecked(), getGmusicId, setGmusicId);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("playlistEntryIds").ToLocalChecked(), getPlaylistEntryIds, setPlaylistEntryIds);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("playlistEntries").ToLocalChecked(), getPlaylistEntries, setPlaylistEntries);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("styleIds").ToLocalChecked(), getStyleIds, setStyleIds);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("styles").ToLocalChecked(), getStyles, setStyles);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New<v8::String>("Playlist").ToLocalChecked(), tpl->GetFunction());
}

void Playlist::clear(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  obj->playlist->clear();

  info.GetReturnValue().SetUndefined();
}

void Playlist::findById(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  int a0(info[0]->IntegerValue());
  dogatech::soulsifter::Playlist* result =
      dogatech::soulsifter::Playlist::findById(a0);

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Playlist::NewInstance();
    Playlist* r = Nan::ObjectWrap::Unwrap<Playlist>(instance);
    r->setNwcpValue(result, true);

    info.GetReturnValue().Set(instance);
  }
}

void Playlist::findByName(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  string a0(*v8::String::Utf8Value(info[0]->ToString()));
  dogatech::soulsifter::Playlist* result =
      dogatech::soulsifter::Playlist::findByName(a0);

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Playlist::NewInstance();
    Playlist* r = Nan::ObjectWrap::Unwrap<Playlist>(instance);
    r->setNwcpValue(result, true);

    info.GetReturnValue().Set(instance);
  }
}

void Playlist::findAll(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  dogatech::ResultSetIterator<dogatech::soulsifter::Playlist>* result =
      dogatech::soulsifter::Playlist::findAll();

  vector<dogatech::soulsifter::Playlist*>* v = result->toVector();
  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Playlist* o = Nan::ObjectWrap::Unwrap<Playlist>(instance);
    o->playlist = (*v)[i];
    a->Set(Nan::New<v8::Number>(i), instance);
  }
  delete v;
  info.GetReturnValue().Set(a);
}

void Playlist::update(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  int result =  obj->playlist->update();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

void Playlist::save(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  int result =  obj->playlist->save();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

void Playlist::sync(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  bool result =  obj->playlist->sync();

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

void Playlist::erase(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  int result =  obj->playlist->erase();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_GETTER(Playlist::getId) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const int result =  obj->playlist->getId();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Playlist::setId) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  int a0(value->IntegerValue());
  obj->playlist->setId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Playlist::getName) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const string result =  obj->playlist->getName();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Playlist::setName) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->playlist->setName(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Playlist::getQuery) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const string result =  obj->playlist->getQuery();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Playlist::setQuery) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->playlist->setQuery(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Playlist::getGmusicId) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const string result =  obj->playlist->getGmusicId();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Playlist::setGmusicId) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->playlist->setGmusicId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Playlist::getPlaylistEntryIds) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const std::vector<int> result =  obj->playlist->getPlaylistEntryIds();

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(Nan::New<v8::Number>(i), Nan::New<v8::Integer>(result[i]));
  }
  info.GetReturnValue().Set(a);
}

NAN_SETTER(Playlist::setPlaylistEntryIds) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->IntegerValue());
    a0.push_back(x);
  }
  obj->playlist->setPlaylistEntryIds(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Playlist::getPlaylistEntries) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const std::vector<dogatech::soulsifter::PlaylistEntry*> result =  obj->playlist->getPlaylistEntries();

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = PlaylistEntry::NewInstance();
    PlaylistEntry* r = Nan::ObjectWrap::Unwrap<PlaylistEntry>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(Nan::New<v8::Number>(i), instance);
  }
  info.GetReturnValue().Set(a);
}

NAN_SETTER(Playlist::setPlaylistEntries) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::PlaylistEntry*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::PlaylistEntry* x(Nan::ObjectWrap::Unwrap<PlaylistEntry>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->playlist->setPlaylistEntries(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Playlist::getStyleIds) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const std::vector<int> result =  obj->playlist->getStyleIds();

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(Nan::New<v8::Number>(i), Nan::New<v8::Integer>(result[i]));
  }
  info.GetReturnValue().Set(a);
}

NAN_SETTER(Playlist::setStyleIds) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->IntegerValue());
    a0.push_back(x);
  }
  obj->playlist->setStyleIds(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Playlist::getStyles) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  const std::vector<dogatech::soulsifter::Style*> result =  obj->playlist->getStyles();

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = Style::NewInstance();
    Style* r = Nan::ObjectWrap::Unwrap<Style>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(Nan::New<v8::Number>(i), instance);
  }
  info.GetReturnValue().Set(a);
}

NAN_SETTER(Playlist::setStyles) {
  Playlist* obj = Nan::ObjectWrap::Unwrap<Playlist>(info.Holder());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::Style* x(Nan::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->playlist->setStyles(a0);

  info.GetReturnValue().SetUndefined();
}

