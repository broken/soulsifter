//
// Handcrafted
//

#include <iostream>
#include <node.h>
#include <nan.h>
#include "SoulSifterSettings_wrap.h"

v8::Persistent<v8::Function> SoulSifterSettings::constructor;

SoulSifterSettings::SoulSifterSettings() : ObjectWrap(), soulsiftersettings(NULL), ownWrappedObject(true) {};
SoulSifterSettings::SoulSifterSettings(dogatech::soulsifter::SoulSifterSettings* o) : ObjectWrap(), soulsiftersettings(o), ownWrappedObject(true) {};
SoulSifterSettings::~SoulSifterSettings() { };

void SoulSifterSettings::setNwcpValue(dogatech::soulsifter::SoulSifterSettings* v, bool own) {
  if (ownWrappedObject)
    delete soulsiftersettings;
  soulsiftersettings = v;
  ownWrappedObject = own;
}

NAN_METHOD(SoulSifterSettings::New) {
  NanScope();

  dogatech::soulsifter::SoulSifterSettings& ss = dogatech::soulsifter::SoulSifterSettings::getInstance();
  SoulSifterSettings* obj = new SoulSifterSettings(&ss);
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> SoulSifterSettings::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void SoulSifterSettings::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("SoulSifterSettings"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getString", NanNew<v8::FunctionTemplate>(getString)->GetFunction());
  NanSetPrototypeTemplate(tpl, "putString", NanNew<v8::FunctionTemplate>(putString)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getInt", NanNew<v8::FunctionTemplate>(getInt)->GetFunction());
  NanSetPrototypeTemplate(tpl, "putInt", NanNew<v8::FunctionTemplate>(putInt)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("SoulSifterSettings"), tpl->GetFunction());
}

NAN_METHOD(SoulSifterSettings::save) {
  NanScope();

  SoulSifterSettings* obj = ObjectWrap::Unwrap<SoulSifterSettings>(args.This());
  obj->soulsiftersettings->save();

  NanReturnUndefined();
}

NAN_METHOD(SoulSifterSettings::getString) {
  NanScope();

  SoulSifterSettings* obj = ObjectWrap::Unwrap<SoulSifterSettings>(args.This());
  std::string a0(*v8::String::Utf8Value(args[0]->ToString()));
  const std::string result = obj->soulsiftersettings->get<std::string>(a0);

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(SoulSifterSettings::putString) {
  NanScope();

  SoulSifterSettings* obj = ObjectWrap::Unwrap<SoulSifterSettings>(args.This());
  std::string a0(*v8::String::Utf8Value(args[0]->ToString()));
  std::string a1(*v8::String::Utf8Value(args[1]->ToString()));
  obj->soulsiftersettings->put<std::string>(a0, a1);

  NanReturnUndefined();
}

NAN_METHOD(SoulSifterSettings::getInt) {
  NanScope();

  SoulSifterSettings* obj = ObjectWrap::Unwrap<SoulSifterSettings>(args.This());
  std::string a0(*v8::String::Utf8Value(args[0]->ToString()));
  const int result = obj->soulsiftersettings->get<int>(a0);

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(SoulSifterSettings::putInt) {
  NanScope();

  SoulSifterSettings* obj = ObjectWrap::Unwrap<SoulSifterSettings>(args.This());
  std::string a0(*v8::String::Utf8Value(args[0]->ToString()));
  int a1(args[1]->Uint32Value());
  obj->soulsiftersettings->put<int>(a0, a1);

  NanReturnUndefined();
}
