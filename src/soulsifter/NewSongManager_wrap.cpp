#include <iostream>
#include <node.h>
#include <nan.h>
#include "NewSongManager_wrap.h"
#include "Song.h"
#include "Song_wrap.h"

v8::Persistent<v8::Function> NewSongManager::constructor;

NewSongManager::NewSongManager() : ObjectWrap(), newsongmanager(NULL), ownWrappedObject(true) {};
NewSongManager::NewSongManager(dogatech::soulsifter::NewSongManager* o) : ObjectWrap(), newsongmanager(o), ownWrappedObject(true) {};
NewSongManager::~NewSongManager() { if (ownWrappedObject) delete newsongmanager; };

void NewSongManager::setNwcpValue(dogatech::soulsifter::NewSongManager* v, bool own) {
  if (ownWrappedObject)
    delete newsongmanager;
  newsongmanager = v;
  ownWrappedObject = own;
}

NAN_METHOD(NewSongManager::New) {
  NanScope();

  NewSongManager* obj = new NewSongManager(new dogatech::soulsifter::NewSongManager());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> NewSongManager::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void NewSongManager::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("NewSongManager"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "import", NanNew<v8::FunctionTemplate>(import)->GetFunction());
  NanSetPrototypeTemplate(tpl, "nextSong", NanNew<v8::FunctionTemplate>(nextSong)->GetFunction());
  NanSetPrototypeTemplate(tpl, "coverImagePath", NanNew<v8::FunctionTemplate>(coverImagePath)->GetFunction());
  NanSetPrototypeTemplate(tpl, "processSong", NanNew<v8::FunctionTemplate>(processSong)->GetFunction());
  NanSetPrototypeTemplate(tpl, "trashMusicFile", NanNew<v8::FunctionTemplate>(trashMusicFile)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("NewSongManager"), tpl->GetFunction());
}

NAN_METHOD(NewSongManager::import) {
  NanScope();

  NewSongManager* obj = ObjectWrap::Unwrap<NewSongManager>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(args[0]);
  std::vector<string> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    string x(*v8::String::Utf8Value(tmp->ToString()));
    a0.push_back(x);
  }
  obj->newsongmanager->import(a0);

  NanReturnUndefined();
}

NAN_METHOD(NewSongManager::nextSong) {
  NanScope();

  NewSongManager* obj = ObjectWrap::Unwrap<NewSongManager>(args.This());
  dogatech::soulsifter::Song* a0(node::ObjectWrap::Unwrap<Song>(args[0]->ToObject())->getNwcpValue());
  dogatech::soulsifter::Song* a1(node::ObjectWrap::Unwrap<Song>(args[1]->ToObject())->getNwcpValue());
  bool result =  obj->newsongmanager->nextSong(&a0, &a1);

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(NewSongManager::coverImagePath) {
  NanScope();

  NewSongManager* obj = ObjectWrap::Unwrap<NewSongManager>(args.This());
  string result =  obj->newsongmanager->coverImagePath();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(NewSongManager::processSong) {
  NanScope();

  NewSongManager* obj = ObjectWrap::Unwrap<NewSongManager>(args.This());
  dogatech::soulsifter::Song* a0(node::ObjectWrap::Unwrap<Song>(args[0]->ToObject())->getNwcpValue());
  bool result =  obj->newsongmanager->processSong(a0);

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(NewSongManager::trashMusicFile) {
  NanScope();

  NewSongManager* obj = ObjectWrap::Unwrap<NewSongManager>(args.This());
  dogatech::soulsifter::Song* a0(node::ObjectWrap::Unwrap<Song>(args[0]->ToObject())->getNwcpValue());
  obj->newsongmanager->trashMusicFile(a0);

  NanReturnUndefined();
}

