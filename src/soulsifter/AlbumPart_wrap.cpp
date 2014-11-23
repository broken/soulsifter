#include <iostream>
#include <node.h>
#include <nan.h>
#include "AlbumPart_wrap.h"
#include "Album.h"
#include "AlbumPart.h"
#include "AlbumPart_wrap.h"
#include "Album_wrap.h"
#include "ResultSetIterator.h"

v8::Persistent<v8::Function> AlbumPart::constructor;

AlbumPart::AlbumPart() : ObjectWrap(), albumpart(NULL), ownWrappedObject(true) {};
AlbumPart::AlbumPart(dogatech::soulsifter::AlbumPart* o) : ObjectWrap(), albumpart(o), ownWrappedObject(true) {};
AlbumPart::~AlbumPart() { if (ownWrappedObject) delete albumpart; };

void AlbumPart::setNwcpValue(dogatech::soulsifter::AlbumPart* v, bool own) {
  if (ownWrappedObject)
    delete albumpart;
  albumpart = v;
  ownWrappedObject = own;
}

NAN_METHOD(AlbumPart::New) {
  NanScope();

  AlbumPart* obj = new AlbumPart(new dogatech::soulsifter::AlbumPart());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> AlbumPart::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void AlbumPart::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("AlbumPart"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByPosAndAlbumId", NanNew<v8::FunctionTemplate>(findByPosAndAlbumId)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("pos"), getPos, setPos);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("name"), getName, setName);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("albumId"), getAlbumId, setAlbumId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("album"), getAlbum, setAlbum);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("AlbumPart"), tpl->GetFunction());
}

NAN_METHOD(AlbumPart::clear) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  obj->albumpart->clear();

  NanReturnUndefined();
}

NAN_METHOD(AlbumPart::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::AlbumPart* result =
      dogatech::soulsifter::AlbumPart::findById(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = AlbumPart::NewInstance();
  AlbumPart* r = ObjectWrap::Unwrap<AlbumPart>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(AlbumPart::findByPosAndAlbumId) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  int a1(args[1]->Uint32Value());
  dogatech::soulsifter::AlbumPart* result =
      dogatech::soulsifter::AlbumPart::findByPosAndAlbumId(a0, a1);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = AlbumPart::NewInstance();
  AlbumPart* r = ObjectWrap::Unwrap<AlbumPart>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(AlbumPart::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::AlbumPart>* result =
      dogatech::soulsifter::AlbumPart::findAll();

  vector<dogatech::soulsifter::AlbumPart*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    AlbumPart* o = ObjectWrap::Unwrap<AlbumPart>(instance);
    o->albumpart = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(AlbumPart::update) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  int result =  obj->albumpart->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(AlbumPart::save) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  int result =  obj->albumpart->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_GETTER(AlbumPart::getId) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  const int result =  obj->albumpart->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(AlbumPart::setId) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  int a0(value->Uint32Value());
  obj->albumpart->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(AlbumPart::getPos) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  const string result =  obj->albumpart->getPos();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(AlbumPart::setPos) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->albumpart->setPos(a0);

  NanReturnUndefined();
}

NAN_GETTER(AlbumPart::getName) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  const string result =  obj->albumpart->getName();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(AlbumPart::setName) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->albumpart->setName(a0);

  NanReturnUndefined();
}

NAN_GETTER(AlbumPart::getAlbumId) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  const int result =  obj->albumpart->getAlbumId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(AlbumPart::setAlbumId) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  int a0(value->Uint32Value());
  obj->albumpart->setAlbumId(a0);

  NanReturnUndefined();
}

NAN_GETTER(AlbumPart::getAlbum) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  dogatech::soulsifter::Album* result =  obj->albumpart->getAlbum();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Album::NewInstance();
  Album* r = ObjectWrap::Unwrap<Album>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(AlbumPart::setAlbum) {
  NanScope();

  AlbumPart* obj = ObjectWrap::Unwrap<AlbumPart>(args.This());
  dogatech::soulsifter::Album* a0tmp(node::ObjectWrap::Unwrap<Album>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::Album& a0 = *a0tmp;
  obj->albumpart->setAlbum(a0);

  NanReturnUndefined();
}

