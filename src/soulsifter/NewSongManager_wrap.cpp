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

  // Unable to process import
  NanSetPrototypeTemplate(tpl, "nextSong", NanNew<v8::FunctionTemplate>(nextSong)->GetFunction());
  // Unable to process coverImagePath
  NanSetPrototypeTemplate(tpl, "processSong", NanNew<v8::FunctionTemplate>(processSong)->GetFunction());
  NanSetPrototypeTemplate(tpl, "trashMusicFile", NanNew<v8::FunctionTemplate>(trashMusicFile)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("NewSongManager"), tpl->GetFunction());
}

NAN_METHOD(NewSongManager::nextSong) {
  NanScope();

  NewSongManager* obj = ObjectWrap::Unwrap<NewSongManager>(args.This());
  dogatech::soulsifter::Song* a0(node::ObjectWrap::Unwrap<Song>(args[0]->ToObject())->getNwcpValue());
  dogatech::soulsifter::Song* a1(node::ObjectWrap::Unwrap<Song>(args[1]->ToObject())->getNwcpValue());
  bool result =  obj->newsongmanager->nextSong(a0, a1);

  NanReturnValue(NanNew<v8::Boolean>(result));
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

