#include <iostream>
#include <node.h>
#include <nan.h>
#include "Style.h"
#include "Style_wrap.h"

v8::Persistent<v8::Function> Style::constructor;

Style::Style() : ObjectWrap(), style(new dogatech::soulsifter::Style()) {};
Style::Style(dogatech::soulsifter::Style* o) : ObjectWrap(), style(o) {};
Style::~Style() { delete style; };

NAN_METHOD(Style::New) {
  NanScope();

  Style* obj = new Style();
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

NAN_METHOD(Style::NewInstance) {
  NanScope();

  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  NanReturnValue(instance);
}

void Style::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("Style"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByREId", NanNew<v8::FunctionTemplate>(findByREId)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetTemplate(tpl, "findAllParents", NanNew<v8::FunctionTemplate>(findAllParents)->GetFunction());

  // Prototype
  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getId", NanNew<v8::FunctionTemplate>(getId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setId", NanNew<v8::FunctionTemplate>(setId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getName", NanNew<v8::FunctionTemplate>(getName)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setName", NanNew<v8::FunctionTemplate>(setName)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getREId", NanNew<v8::FunctionTemplate>(getREId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setREId", NanNew<v8::FunctionTemplate>(setREId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getRELabel", NanNew<v8::FunctionTemplate>(getRELabel)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setRELabel", NanNew<v8::FunctionTemplate>(setRELabel)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getChildren", NanNew<v8::FunctionTemplate>(getChildren)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setChildren", NanNew<v8::FunctionTemplate>(setChildren)->GetFunction());
  NanSetPrototypeTemplate(tpl, "addChildById", NanNew<v8::FunctionTemplate>(addChildById)->GetFunction());
  NanSetPrototypeTemplate(tpl, "removeChildById", NanNew<v8::FunctionTemplate>(removeChildById)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getParents", NanNew<v8::FunctionTemplate>(getParents)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setParents", NanNew<v8::FunctionTemplate>(setParents)->GetFunction());
  NanSetPrototypeTemplate(tpl, "addParentById", NanNew<v8::FunctionTemplate>(addParentById)->GetFunction());
  NanSetPrototypeTemplate(tpl, "removeParentById", NanNew<v8::FunctionTemplate>(removeParentById)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("Style"), tpl->GetFunction());
}


NAN_METHOD(Style::clear) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  obj->style->clear();

  NanReturnUndefined();
}

NAN_METHOD(Style::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Style* style =
      dogatech::soulsifter::Style::findById(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Style* obj = ObjectWrap::Unwrap<Style>(instance);
  obj->style = style;

  NanReturnValue(instance);
}

NAN_METHOD(Style::findByREId) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Style* style =
      dogatech::soulsifter::Style::findByREId(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Style* obj = ObjectWrap::Unwrap<Style>(instance);
  obj->style = style;

  NanReturnValue(instance);
}

NAN_METHOD(Style::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::Style>* result =
      dogatech::soulsifter::Style::findAll();

  vector<dogatech::soulsifter::Style*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Style* o = ObjectWrap::Unwrap<Style>(instance);
    o->style = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(Style::sync) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  bool result =  obj->style->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(Style::update) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int result =  obj->style->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Style::save) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int result =  obj->style->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Style::findAllParents) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::Style>* result =
      dogatech::soulsifter::Style::findAllParents();

  vector<dogatech::soulsifter::Style*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Style* o = ObjectWrap::Unwrap<Style>(instance);
    o->style = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(Style::getId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const int result =  obj->style->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Style::setId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(args[0]->Uint32Value());
  obj->style->setId(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::getName) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const string result =  obj->style->getName();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Style::setName) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->style->setName(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::getREId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const int result =  obj->style->getREId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Style::setREId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(args[0]->Uint32Value());
  obj->style->setREId(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::getRELabel) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const string result =  obj->style->getRELabel();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Style::setRELabel) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->style->setRELabel(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::getChildren) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const vector<dogatech::soulsifter::Style*> result =  obj->style->getChildren();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Style* o = ObjectWrap::Unwrap<Style>(instance);
    o->style = result[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_METHOD(Style::setChildren) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[0]);
  vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < array->Length(); ++i) {
    v8::Local<v8::Value> tmp = array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->style->setChildren(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::addChildById) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(args[0]->Uint32Value());
  obj->style->addChildById(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::removeChildById) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(args[0]->Uint32Value());
  obj->style->removeChildById(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::getParents) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const vector<dogatech::soulsifter::Style*> result =  obj->style->getParents();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Style* o = ObjectWrap::Unwrap<Style>(instance);
    o->style = result[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_METHOD(Style::setParents) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[0]);
  vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < array->Length(); ++i) {
    v8::Local<v8::Value> tmp = array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->style->setParents(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::addParentById) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(args[0]->Uint32Value());
  obj->style->addParentById(a0);

  NanReturnUndefined();
}

NAN_METHOD(Style::removeParentById) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(args[0]->Uint32Value());
  obj->style->removeParentById(a0);

  NanReturnUndefined();
}

