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

  NanSetPrototypeTemplate(tpl, "getString", NanNew<v8::FunctionTemplate>(getString)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("SoulSifterSettings"), tpl->GetFunction());
}

NAN_METHOD(SoulSifterSettings::getString) {
  NanScope();

  SoulSifterSettings* obj = ObjectWrap::Unwrap<SoulSifterSettings>(args.This());
  std::string a0(*v8::String::Utf8Value(args[0]->ToString()));
  const std::string result = obj->soulsiftersettings->get<std::string>(a0);

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}
