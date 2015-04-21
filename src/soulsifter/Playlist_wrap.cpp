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

v8::Persistent<v8::Function> Playlist::constructor;

Playlist::Playlist() : ObjectWrap(), playlist(NULL), ownWrappedObject(true) {};
Playlist::Playlist(dogatech::soulsifter::Playlist* o) : ObjectWrap(), playlist(o), ownWrappedObject(true) {};
Playlist::~Playlist() { if (ownWrappedObject) delete playlist; };

void Playlist::setNwcpValue(dogatech::soulsifter::Playlist* v, bool own) {
  if (ownWrappedObject)
    delete playlist;
  playlist = v;
  ownWrappedObject = own;
}

NAN_METHOD(Playlist::New) {
  NanScope();

  Playlist* obj = new Playlist(new dogatech::soulsifter::Playlist());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> Playlist::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void Playlist::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("Playlist"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByName", NanNew<v8::FunctionTemplate>(findByName)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "erase", NanNew<v8::FunctionTemplate>(erase)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("name"), getName, setName);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("query"), getQuery, setQuery);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("gmusicId"), getGmusicId, setGmusicId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("playlistEntryIds"), getPlaylistEntryIds, setPlaylistEntryIds);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("playlistEntries"), getPlaylistEntries, setPlaylistEntries);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("styleIds"), getStyleIds, setStyleIds);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("styles"), getStyles, setStyles);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("Playlist"), tpl->GetFunction());
}

NAN_METHOD(Playlist::clear) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  obj->playlist->clear();

  NanReturnUndefined();
}

NAN_METHOD(Playlist::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Playlist* result =
      dogatech::soulsifter::Playlist::findById(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Playlist::NewInstance();
  Playlist* r = ObjectWrap::Unwrap<Playlist>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Playlist::findByName) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  dogatech::soulsifter::Playlist* result =
      dogatech::soulsifter::Playlist::findByName(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Playlist::NewInstance();
  Playlist* r = ObjectWrap::Unwrap<Playlist>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Playlist::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::Playlist>* result =
      dogatech::soulsifter::Playlist::findAll();

  vector<dogatech::soulsifter::Playlist*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Playlist* o = ObjectWrap::Unwrap<Playlist>(instance);
    o->playlist = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(Playlist::update) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  int result =  obj->playlist->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Playlist::save) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  int result =  obj->playlist->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Playlist::erase) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  int result =  obj->playlist->erase();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_GETTER(Playlist::getId) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const int result =  obj->playlist->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Playlist::setId) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  int a0(value->Uint32Value());
  obj->playlist->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Playlist::getName) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const string result =  obj->playlist->getName();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Playlist::setName) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->playlist->setName(a0);

  NanReturnUndefined();
}

NAN_GETTER(Playlist::getQuery) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const string result =  obj->playlist->getQuery();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Playlist::setQuery) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->playlist->setQuery(a0);

  NanReturnUndefined();
}

NAN_GETTER(Playlist::getGmusicId) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const string result =  obj->playlist->getGmusicId();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Playlist::setGmusicId) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->playlist->setGmusicId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Playlist::getPlaylistEntryIds) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const std::vector<int> result =  obj->playlist->getPlaylistEntryIds();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(NanNew<v8::Number>(i), NanNew<v8::Number>(result[i]));
  }
  NanReturnValue(a);
}

NAN_SETTER(Playlist::setPlaylistEntryIds) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->Uint32Value());
    a0.push_back(x);
  }
  obj->playlist->setPlaylistEntryIds(a0);

  NanReturnUndefined();
}

NAN_GETTER(Playlist::getPlaylistEntries) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const std::vector<dogatech::soulsifter::PlaylistEntry*> result =  obj->playlist->getPlaylistEntries();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = PlaylistEntry::NewInstance();
    PlaylistEntry* r = ObjectWrap::Unwrap<PlaylistEntry>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_SETTER(Playlist::setPlaylistEntries) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::PlaylistEntry*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::PlaylistEntry* x(node::ObjectWrap::Unwrap<PlaylistEntry>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->playlist->setPlaylistEntries(a0);

  NanReturnUndefined();
}

NAN_GETTER(Playlist::getStyleIds) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const std::vector<int> result =  obj->playlist->getStyleIds();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(NanNew<v8::Number>(i), NanNew<v8::Number>(result[i]));
  }
  NanReturnValue(a);
}

NAN_SETTER(Playlist::setStyleIds) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->Uint32Value());
    a0.push_back(x);
  }
  obj->playlist->setStyleIds(a0);

  NanReturnUndefined();
}

NAN_GETTER(Playlist::getStyles) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  const std::vector<dogatech::soulsifter::Style*> result =  obj->playlist->getStyles();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = Style::NewInstance();
    Style* r = ObjectWrap::Unwrap<Style>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_SETTER(Playlist::setStyles) {
  NanScope();

  Playlist* obj = ObjectWrap::Unwrap<Playlist>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->playlist->setStyles(a0);

  NanReturnUndefined();
}

