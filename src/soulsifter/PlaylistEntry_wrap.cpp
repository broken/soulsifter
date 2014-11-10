#include <iostream>
#include <node.h>
#include <nan.h>
#include "PlaylistEntry_wrap.h"
#include "Song.h"
#include "Song_wrap.h"

v8::Persistent<v8::Function> PlaylistEntry::constructor;

PlaylistEntry::PlaylistEntry() : ObjectWrap(), playlistentry(NULL), ownWrappedObject(true) {};
PlaylistEntry::PlaylistEntry(dogatech::soulsifter::PlaylistEntry* o) : ObjectWrap(), playlistentry(o), ownWrappedObject(true) {};
PlaylistEntry::~PlaylistEntry() { if (ownWrappedObject) delete playlistentry; };

void PlaylistEntry::setNwcpValue(dogatech::soulsifter::PlaylistEntry* v, bool own) {
  if (ownWrappedObject)
    delete playlistentry;
  playlistentry = v;
  ownWrappedObject = own;
}

NAN_METHOD(PlaylistEntry::New) {
  NanScope();

  PlaylistEntry* obj = new PlaylistEntry(new dogatech::soulsifter::PlaylistEntry());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> PlaylistEntry::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void PlaylistEntry::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("PlaylistEntry"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  // Unable to process findById
  // Unable to process findByPlaylistIdAndSongId
  // Unable to process findAll
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("playlistId"), getPlaylistId, setPlaylistId);
  // Unable to process getPlaylist
  // Unable to process setPlaylist
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("songId"), getSongId, setSongId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("song"), getSong, setSong);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("position"), getPosition, setPosition);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("time"), getTime, setTime);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("PlaylistEntry"), tpl->GetFunction());
}

NAN_METHOD(PlaylistEntry::clear) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  obj->playlistentry->clear();

  NanReturnUndefined();
}

NAN_METHOD(PlaylistEntry::sync) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  bool result =  obj->playlistentry->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(PlaylistEntry::update) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  int result =  obj->playlistentry->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(PlaylistEntry::save) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  int result =  obj->playlistentry->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_GETTER(PlaylistEntry::getId) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  const int result =  obj->playlistentry->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(PlaylistEntry::setId) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  int a0(value->Uint32Value());
  obj->playlistentry->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(PlaylistEntry::getPlaylistId) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  const int result =  obj->playlistentry->getPlaylistId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(PlaylistEntry::setPlaylistId) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  int a0(value->Uint32Value());
  obj->playlistentry->setPlaylistId(a0);

  NanReturnUndefined();
}

NAN_GETTER(PlaylistEntry::getSongId) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  const int result =  obj->playlistentry->getSongId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(PlaylistEntry::setSongId) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  int a0(value->Uint32Value());
  obj->playlistentry->setSongId(a0);

  NanReturnUndefined();
}

NAN_GETTER(PlaylistEntry::getSong) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  dogatech::soulsifter::Song* result =  obj->playlistentry->getSong();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Song::NewInstance();
  Song* r = ObjectWrap::Unwrap<Song>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(PlaylistEntry::setSong) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  dogatech::soulsifter::Song* a0tmp(node::ObjectWrap::Unwrap<Song>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::Song& a0 = *a0tmp;
  obj->playlistentry->setSong(a0);

  NanReturnUndefined();
}

NAN_GETTER(PlaylistEntry::getPosition) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  const int result =  obj->playlistentry->getPosition();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(PlaylistEntry::setPosition) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  int a0(value->Uint32Value());
  obj->playlistentry->setPosition(a0);

  NanReturnUndefined();
}

NAN_GETTER(PlaylistEntry::getTime) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  const string result =  obj->playlistentry->getTime();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(PlaylistEntry::setTime) {
  NanScope();

  PlaylistEntry* obj = ObjectWrap::Unwrap<PlaylistEntry>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->playlistentry->setTime(a0);

  NanReturnUndefined();
}

