#include <iostream>
#include <node.h>
#include <nan.h>
#include "BasicGenre.h"
#include "BasicGenre_wrap.h"

v8::Persistent<v8::Function> BasicGenre::constructor;

BasicGenre::BasicGenre() : ObjectWrap(), basicgenre(new dogatech::soulsifter::BasicGenre()) {};
BasicGenre::BasicGenre(dogatech::soulsifter::BasicGenre* o) : ObjectWrap(), basicgenre(o) {};
BasicGenre::~BasicGenre() { delete basicgenre; };

NAN_METHOD(BasicGenre::New) {
  NanScope();

  BasicGenre* obj = new BasicGenre();
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> BasicGenre::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void BasicGenre::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("BasicGenre"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByName", NanNew<v8::FunctionTemplate>(findByName)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetTemplate(tpl, "findByFilepath", NanNew<v8::FunctionTemplate>(findByFilepath)->GetFunction());

  // Prototype
  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());

  // Accessors
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("name"), getName, setName);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("BasicGenre"), tpl->GetFunction());
}


NAN_METHOD(BasicGenre::clear) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  obj->basicgenre->clear();

  NanReturnUndefined();
}

NAN_METHOD(BasicGenre::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::BasicGenre* basicgenre =
      dogatech::soulsifter::BasicGenre::findById(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(instance);
  obj->basicgenre = basicgenre;

  NanReturnValue(instance);
}

NAN_METHOD(BasicGenre::findByName) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  dogatech::soulsifter::BasicGenre* basicgenre =
      dogatech::soulsifter::BasicGenre::findByName(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(instance);
  obj->basicgenre = basicgenre;

  NanReturnValue(instance);
}

NAN_METHOD(BasicGenre::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::BasicGenre>* result =
      dogatech::soulsifter::BasicGenre::findAll();

  vector<dogatech::soulsifter::BasicGenre*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    BasicGenre* o = ObjectWrap::Unwrap<BasicGenre>(instance);
    o->basicgenre = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(BasicGenre::sync) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  bool result =  obj->basicgenre->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(BasicGenre::update) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  int result =  obj->basicgenre->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(BasicGenre::save) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  int result =  obj->basicgenre->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(BasicGenre::findByFilepath) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  dogatech::soulsifter::BasicGenre* basicgenre =
      dogatech::soulsifter::BasicGenre::findByFilepath(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(instance);
  obj->basicgenre = basicgenre;

  NanReturnValue(instance);
}

NAN_GETTER(BasicGenre::getId) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  const int result =  obj->basicgenre->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(BasicGenre::setId) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  int a0(value->Uint32Value());
  obj->basicgenre->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(BasicGenre::getName) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  const string result =  obj->basicgenre->getName();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(BasicGenre::setName) {
  NanScope();

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->basicgenre->setName(a0);

  NanReturnUndefined();
}

