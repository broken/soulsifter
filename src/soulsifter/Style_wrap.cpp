#include <iostream>
#include <node.h>
#include <nan.h>
#include "Style_wrap.h"
#include "ResultSetIterator.h"
#include "Style.h"
#include "Style_wrap.h"

v8::Persistent<v8::Function> Style::constructor;

Style::Style() : ObjectWrap(), style(NULL), ownWrappedObject(true) {};
Style::Style(dogatech::soulsifter::Style* o) : ObjectWrap(), style(o), ownWrappedObject(true) {};
Style::~Style() { if (ownWrappedObject) delete style; };

void Style::setNwcpValue(dogatech::soulsifter::Style* v, bool own) {
  if (ownWrappedObject)
    delete style;
  style = v;
  ownWrappedObject = own;
}

NAN_METHOD(Style::New) {
  NanScope();

  dogatech::soulsifter::Style* wrappedObj = NULL;
  if (args.Length()) {
    dogatech::soulsifter::Style* xtmp(node::ObjectWrap::Unwrap<Style>(args[0]->ToObject())->getNwcpValue());
    dogatech::soulsifter::Style& x = *xtmp;
    wrappedObj = new dogatech::soulsifter::Style(x);
  } else {
    wrappedObj = new dogatech::soulsifter::Style();
  }

  Style* obj = new Style(wrappedObj);
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> Style::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void Style::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("Style"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByREId", NanNew<v8::FunctionTemplate>(findByREId)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  NanSetTemplate(tpl, "findAllParents", NanNew<v8::FunctionTemplate>(findAllParents)->GetFunction());
  // Unable to process findAllSortedByName
  // Unable to process findAllSortedByREId
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("name"), getName, setName);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("rEId"), getREId, setREId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("rELabel"), getRELabel, setRELabel);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("childIds"), getChildIds, setChildIds);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("children"), getChildren, setChildren);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("parentIds"), getParentIds, setParentIds);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("parents"), getParents, setParents);

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
  dogatech::soulsifter::Style* result =
      dogatech::soulsifter::Style::findById(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Style::NewInstance();
  Style* r = ObjectWrap::Unwrap<Style>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Style::findByREId) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Style* result =
      dogatech::soulsifter::Style::findByREId(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Style::NewInstance();
  Style* r = ObjectWrap::Unwrap<Style>(instance);
  r->setNwcpValue(result, true);

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

NAN_METHOD(Style::sync) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  bool result =  obj->style->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
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

NAN_GETTER(Style::getId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const int result =  obj->style->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Style::setId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(value->Uint32Value());
  obj->style->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Style::getName) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const string result =  obj->style->getName();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Style::setName) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->style->setName(a0);

  NanReturnUndefined();
}

NAN_GETTER(Style::getREId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const int result =  obj->style->getREId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Style::setREId) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  int a0(value->Uint32Value());
  obj->style->setREId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Style::getRELabel) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const string result =  obj->style->getRELabel();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Style::setRELabel) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->style->setRELabel(a0);

  NanReturnUndefined();
}

NAN_GETTER(Style::getChildIds) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const std::vector<int> result =  obj->style->getChildIds();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(NanNew<v8::Number>(i), NanNew<v8::Number>(result[i]));
  }
  NanReturnValue(a);
}

NAN_SETTER(Style::setChildIds) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->Uint32Value());
    a0.push_back(x);
  }
  obj->style->setChildIds(a0);

  NanReturnUndefined();
}

NAN_GETTER(Style::getChildren) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const std::vector<dogatech::soulsifter::Style*> result =  obj->style->getChildren();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = Style::NewInstance();
    Style* r = ObjectWrap::Unwrap<Style>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_SETTER(Style::setChildren) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->style->setChildren(a0);

  NanReturnUndefined();
}

NAN_GETTER(Style::getParentIds) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const std::vector<int> result =  obj->style->getParentIds();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(NanNew<v8::Number>(i), NanNew<v8::Number>(result[i]));
  }
  NanReturnValue(a);
}

NAN_SETTER(Style::setParentIds) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->Uint32Value());
    a0.push_back(x);
  }
  obj->style->setParentIds(a0);

  NanReturnUndefined();
}

NAN_GETTER(Style::getParents) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  const std::vector<dogatech::soulsifter::Style*> result =  obj->style->getParents();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = Style::NewInstance();
    Style* r = ObjectWrap::Unwrap<Style>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_SETTER(Style::setParents) {
  NanScope();

  Style* obj = ObjectWrap::Unwrap<Style>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->style->setParents(a0);

  NanReturnUndefined();
}

