#include <iostream>
#include <node.h>
#include <nan.h>
#include "Album_wrap.h"
#include "Album.h"
#include "Album_wrap.h"
#include "BasicGenre.h"
#include "BasicGenre_wrap.h"
#include "ResultSetIterator.h"

v8::Persistent<v8::Function> Album::constructor;

Album::Album() : ObjectWrap(), album(NULL), ownWrappedObject(true) {};
Album::Album(dogatech::soulsifter::Album* o) : ObjectWrap(), album(o), ownWrappedObject(true) {};
Album::~Album() { if (ownWrappedObject) delete album; };

void Album::setNwcpValue(dogatech::soulsifter::Album* v, bool own) {
  if (ownWrappedObject)
    delete album;
  album = v;
  ownWrappedObject = own;
}

NAN_METHOD(Album::New) {
  NanScope();

  Album* obj = new Album(new dogatech::soulsifter::Album());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> Album::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void Album::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("Album"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByCoverFilepath", NanNew<v8::FunctionTemplate>(findByCoverFilepath)->GetFunction());
  NanSetTemplate(tpl, "findByNameAndArtist", NanNew<v8::FunctionTemplate>(findByNameAndArtist)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  NanSetPrototypeTemplate(tpl, "reReleaseDate", NanNew<v8::FunctionTemplate>(reReleaseDate)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("name"), getName, setName);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("artist"), getArtist, setArtist);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("coverFilepath"), getCoverFilepath, setCoverFilepath);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("mixed"), getMixed, setMixed);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("label"), getLabel, setLabel);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("catalogId"), getCatalogId, setCatalogId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("releaseDateYear"), getReleaseDateYear, setReleaseDateYear);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("releaseDateMonth"), getReleaseDateMonth, setReleaseDateMonth);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("releaseDateDay"), getReleaseDateDay, setReleaseDateDay);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("basicGenreId"), getBasicGenreId, setBasicGenreId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("basicGenre"), getBasicGenre, setBasicGenre);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("Album"), tpl->GetFunction());
}

NAN_METHOD(Album::clear) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  obj->album->clear();

  NanReturnUndefined();
}

NAN_METHOD(Album::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Album* result =
      dogatech::soulsifter::Album::findById(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Album::NewInstance();
  Album* r = ObjectWrap::Unwrap<Album>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Album::findByCoverFilepath) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  dogatech::soulsifter::Album* result =
      dogatech::soulsifter::Album::findByCoverFilepath(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Album::NewInstance();
  Album* r = ObjectWrap::Unwrap<Album>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Album::findByNameAndArtist) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  string a1(*v8::String::Utf8Value(args[1]->ToString()));
  dogatech::soulsifter::Album* result =
      dogatech::soulsifter::Album::findByNameAndArtist(a0, a1);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Album::NewInstance();
  Album* r = ObjectWrap::Unwrap<Album>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Album::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::Album>* result =
      dogatech::soulsifter::Album::findAll();

  vector<dogatech::soulsifter::Album*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Album* o = ObjectWrap::Unwrap<Album>(instance);
    o->album = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(Album::update) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  int result =  obj->album->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Album::save) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  int result =  obj->album->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Album::sync) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  bool result =  obj->album->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(Album::reReleaseDate) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const string result =  obj->album->reReleaseDate();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_GETTER(Album::getId) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const int result =  obj->album->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Album::setId) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  int a0(value->Uint32Value());
  obj->album->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getName) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const string result =  obj->album->getName();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Album::setName) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->album->setName(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getArtist) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const string result =  obj->album->getArtist();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Album::setArtist) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->album->setArtist(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getCoverFilepath) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const string result =  obj->album->getCoverFilepath();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Album::setCoverFilepath) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->album->setCoverFilepath(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getMixed) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const bool result =  obj->album->getMixed();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_SETTER(Album::setMixed) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  bool a0(value->BooleanValue());
  obj->album->setMixed(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getLabel) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const string result =  obj->album->getLabel();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Album::setLabel) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->album->setLabel(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getCatalogId) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const string result =  obj->album->getCatalogId();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Album::setCatalogId) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->album->setCatalogId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getReleaseDateYear) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const int result =  obj->album->getReleaseDateYear();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Album::setReleaseDateYear) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  int a0(value->Uint32Value());
  obj->album->setReleaseDateYear(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getReleaseDateMonth) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const int result =  obj->album->getReleaseDateMonth();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Album::setReleaseDateMonth) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  int a0(value->Uint32Value());
  obj->album->setReleaseDateMonth(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getReleaseDateDay) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const int result =  obj->album->getReleaseDateDay();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Album::setReleaseDateDay) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  int a0(value->Uint32Value());
  obj->album->setReleaseDateDay(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getBasicGenreId) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  const int result =  obj->album->getBasicGenreId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Album::setBasicGenreId) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  int a0(value->Uint32Value());
  obj->album->setBasicGenreId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Album::getBasicGenre) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  dogatech::soulsifter::BasicGenre* result =  obj->album->getBasicGenre();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = BasicGenre::NewInstance();
  BasicGenre* r = ObjectWrap::Unwrap<BasicGenre>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(Album::setBasicGenre) {
  NanScope();

  Album* obj = ObjectWrap::Unwrap<Album>(args.This());
  dogatech::soulsifter::BasicGenre* a0tmp(node::ObjectWrap::Unwrap<BasicGenre>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::BasicGenre& a0 = *a0tmp;
  obj->album->setBasicGenre(a0);

  NanReturnUndefined();
}

