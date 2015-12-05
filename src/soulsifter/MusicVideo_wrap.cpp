#include <iostream>
#include <node.h>
#include <nan.h>
#include "MusicVideo_wrap.h"
#include "MusicVideo.h"
#include "MusicVideo_wrap.h"
#include "ResultSetIterator.h"
#include "Song.h"
#include "Song_wrap.h"

v8::Persistent<v8::Function> MusicVideo::constructor;

MusicVideo::MusicVideo() : ObjectWrap(), musicvideo(NULL), ownWrappedObject(true) {};
MusicVideo::MusicVideo(dogatech::soulsifter::MusicVideo* o) : ObjectWrap(), musicvideo(o), ownWrappedObject(true) {};
MusicVideo::~MusicVideo() { if (ownWrappedObject) delete musicvideo; };

void MusicVideo::setNwcpValue(dogatech::soulsifter::MusicVideo* v, bool own) {
  if (ownWrappedObject)
    delete musicvideo;
  musicvideo = v;
  ownWrappedObject = own;
}

NAN_METHOD(MusicVideo::New) {
  NanScope();

  dogatech::soulsifter::MusicVideo* wrappedObj = NULL;
  if (args.Length()) {
    dogatech::soulsifter::MusicVideo* xtmp(node::ObjectWrap::Unwrap<MusicVideo>(args[0]->ToObject())->getNwcpValue());
    dogatech::soulsifter::MusicVideo& x = *xtmp;
    wrappedObj = new dogatech::soulsifter::MusicVideo(x);
  } else {
    wrappedObj = new dogatech::soulsifter::MusicVideo();
  }

  MusicVideo* obj = new MusicVideo(wrappedObj);
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> MusicVideo::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void MusicVideo::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("MusicVideo"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findBySongId", NanNew<v8::FunctionTemplate>(findBySongId)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("songId"), getSongId, setSongId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("song"), getSong, setSong);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("filePath"), getFilePath, setFilePath);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("thumbnailFilePath"), getThumbnailFilePath, setThumbnailFilePath);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("MusicVideo"), tpl->GetFunction());
}

NAN_METHOD(MusicVideo::clear) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  obj->musicvideo->clear();

  NanReturnUndefined();
}

NAN_METHOD(MusicVideo::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::MusicVideo* result =
      dogatech::soulsifter::MusicVideo::findById(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = MusicVideo::NewInstance();
  MusicVideo* r = ObjectWrap::Unwrap<MusicVideo>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(MusicVideo::findBySongId) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::MusicVideo* result =
      dogatech::soulsifter::MusicVideo::findBySongId(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = MusicVideo::NewInstance();
  MusicVideo* r = ObjectWrap::Unwrap<MusicVideo>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(MusicVideo::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::MusicVideo>* result =
      dogatech::soulsifter::MusicVideo::findAll();

  vector<dogatech::soulsifter::MusicVideo*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    MusicVideo* o = ObjectWrap::Unwrap<MusicVideo>(instance);
    o->musicvideo = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(MusicVideo::update) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  int result =  obj->musicvideo->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(MusicVideo::save) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  int result =  obj->musicvideo->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(MusicVideo::sync) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  bool result =  obj->musicvideo->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_GETTER(MusicVideo::getId) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  const int result =  obj->musicvideo->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(MusicVideo::setId) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  int a0(value->Uint32Value());
  obj->musicvideo->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(MusicVideo::getSongId) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  const int result =  obj->musicvideo->getSongId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(MusicVideo::setSongId) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  int a0(value->Uint32Value());
  obj->musicvideo->setSongId(a0);

  NanReturnUndefined();
}

NAN_GETTER(MusicVideo::getSong) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  dogatech::soulsifter::Song* result =  obj->musicvideo->getSong();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Song::NewInstance();
  Song* r = ObjectWrap::Unwrap<Song>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(MusicVideo::setSong) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  dogatech::soulsifter::Song* a0tmp(node::ObjectWrap::Unwrap<Song>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::Song& a0 = *a0tmp;
  obj->musicvideo->setSong(a0);

  NanReturnUndefined();
}

NAN_GETTER(MusicVideo::getFilePath) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  const string result =  obj->musicvideo->getFilePath();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(MusicVideo::setFilePath) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->musicvideo->setFilePath(a0);

  NanReturnUndefined();
}

NAN_GETTER(MusicVideo::getThumbnailFilePath) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  const string result =  obj->musicvideo->getThumbnailFilePath();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(MusicVideo::setThumbnailFilePath) {
  NanScope();

  MusicVideo* obj = ObjectWrap::Unwrap<MusicVideo>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->musicvideo->setThumbnailFilePath(a0);

  NanReturnUndefined();
}

