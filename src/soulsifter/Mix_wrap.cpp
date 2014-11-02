#include <iostream>
#include <node.h>
#include <nan.h>
#include "Mix_wrap.h"
#include "Mix.h"
#include "Mix_wrap.h"
#include "ResultSetIterator.h"
#include "Song.h"
#include "Song_wrap.h"

v8::Persistent<v8::Function> Mix::constructor;

Mix::Mix() : ObjectWrap(), mix(NULL), ownWrappedObject(true) {};
Mix::Mix(dogatech::soulsifter::Mix* o) : ObjectWrap(), mix(o), ownWrappedObject(true) {};
Mix::~Mix() { if (ownWrappedObject) delete mix; };

void Mix::setNwcpValue(dogatech::soulsifter::Mix* v, bool own) {
  if (ownWrappedObject)
    delete mix;
  mix = v;
  ownWrappedObject = own;
}

NAN_METHOD(Mix::New) {
  NanScope();

  Mix* obj = new Mix(new dogatech::soulsifter::Mix());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> Mix::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void Mix::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("Mix"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByOutSongIdAndInSongId", NanNew<v8::FunctionTemplate>(findByOutSongIdAndInSongId)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetTemplate(tpl, "mixoutCountForRESongId", NanNew<v8::FunctionTemplate>(mixoutCountForRESongId)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("outSongId"), getOutSongId, setOutSongId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("outSong"), getOutSong, setOutSong);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("inSongId"), getInSongId, setInSongId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("inSong"), getInSong, setInSong);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("bpmDiff"), getBpmDiff, setBpmDiff);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("rank"), getRank, setRank);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("comments"), getComments, setComments);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("addon"), getAddon, setAddon);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("Mix"), tpl->GetFunction());
}

NAN_METHOD(Mix::clear) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  obj->mix->clear();

  NanReturnUndefined();
}

NAN_METHOD(Mix::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Mix* result =
      dogatech::soulsifter::Mix::findById(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Mix::NewInstance();
  Mix* r = ObjectWrap::Unwrap<Mix>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Mix::findByOutSongIdAndInSongId) {
  NanScope();

  int a0(args[0]->Uint32Value());
  int a1(args[1]->Uint32Value());
  dogatech::soulsifter::Mix* result =
      dogatech::soulsifter::Mix::findByOutSongIdAndInSongId(a0, a1);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Mix::NewInstance();
  Mix* r = ObjectWrap::Unwrap<Mix>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Mix::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::Mix>* result =
      dogatech::soulsifter::Mix::findAll();

  vector<dogatech::soulsifter::Mix*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Mix* o = ObjectWrap::Unwrap<Mix>(instance);
    o->mix = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(Mix::sync) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  bool result =  obj->mix->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(Mix::update) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  int result =  obj->mix->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Mix::save) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  int result =  obj->mix->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Mix::mixoutCountForRESongId) {
  NanScope();

  int a0(args[0]->Uint32Value());
  int result =
      dogatech::soulsifter::Mix::mixoutCountForRESongId(a0);

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_GETTER(Mix::getId) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  const int result =  obj->mix->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Mix::setId) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  int a0(value->Uint32Value());
  obj->mix->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getOutSongId) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  const int result =  obj->mix->getOutSongId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Mix::setOutSongId) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  int a0(value->Uint32Value());
  obj->mix->setOutSongId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getOutSong) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  dogatech::soulsifter::Song* result =  obj->mix->getOutSong();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Song::NewInstance();
  Song* r = ObjectWrap::Unwrap<Song>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(Mix::setOutSong) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  dogatech::soulsifter::Song* a0tmp(node::ObjectWrap::Unwrap<Song>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::Song& a0 = *a0tmp;
  obj->mix->setOutSong(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getInSongId) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  const int result =  obj->mix->getInSongId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Mix::setInSongId) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  int a0(value->Uint32Value());
  obj->mix->setInSongId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getInSong) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  dogatech::soulsifter::Song* result =  obj->mix->getInSong();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Song::NewInstance();
  Song* r = ObjectWrap::Unwrap<Song>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(Mix::setInSong) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  dogatech::soulsifter::Song* a0tmp(node::ObjectWrap::Unwrap<Song>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::Song& a0 = *a0tmp;
  obj->mix->setInSong(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getBpmDiff) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  const string result =  obj->mix->getBpmDiff();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Mix::setBpmDiff) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->mix->setBpmDiff(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getRank) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  const int result =  obj->mix->getRank();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Mix::setRank) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  int a0(value->Uint32Value());
  obj->mix->setRank(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getComments) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  const string result =  obj->mix->getComments();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Mix::setComments) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->mix->setComments(a0);

  NanReturnUndefined();
}

NAN_GETTER(Mix::getAddon) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  const bool result =  obj->mix->getAddon();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_SETTER(Mix::setAddon) {
  NanScope();

  Mix* obj = ObjectWrap::Unwrap<Mix>(args.This());
  bool a0(value->BooleanValue());
  obj->mix->setAddon(a0);

  NanReturnUndefined();
}

