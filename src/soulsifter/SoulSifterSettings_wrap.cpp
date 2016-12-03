//
// Handcrafted
//

#include <iostream>
#include <node.h>
#include <nan.h>
#include "SoulSifterSettings_wrap.h"

Nan::Persistent<v8::Function> SoulSifterSettings::constructor;

SoulSifterSettings::SoulSifterSettings() : Nan::ObjectWrap(), soulsiftersettings(NULL), ownWrappedObject(true) {};
SoulSifterSettings::SoulSifterSettings(dogatech::soulsifter::SoulSifterSettings* o) : Nan::ObjectWrap(), soulsiftersettings(o), ownWrappedObject(true) {};
SoulSifterSettings::~SoulSifterSettings() { };

void SoulSifterSettings::setNwcpValue(dogatech::soulsifter::SoulSifterSettings* v, bool own) {
  if (ownWrappedObject)
    delete soulsiftersettings;
  soulsiftersettings = v;
  ownWrappedObject = own;
}

void SoulSifterSettings::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  dogatech::soulsifter::SoulSifterSettings& ss = dogatech::soulsifter::SoulSifterSettings::getInstance();
  SoulSifterSettings* obj = new SoulSifterSettings(&ss);
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> SoulSifterSettings::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void SoulSifterSettings::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("SoulSifterSettings").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "save", save);
  Nan::SetPrototypeMethod(tpl, "getString", getString);
  Nan::SetPrototypeMethod(tpl, "putString", putString);
  Nan::SetPrototypeMethod(tpl, "getInt", getInt);
  Nan::SetPrototypeMethod(tpl, "putInt", putInt);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New<v8::String>("SoulSifterSettings").ToLocalChecked(), tpl->GetFunction());
}

void SoulSifterSettings::save(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  SoulSifterSettings* obj = Nan::ObjectWrap::Unwrap<SoulSifterSettings>(info.Holder());
  obj->soulsiftersettings->save();

  info.GetReturnValue().SetUndefined();
}

void SoulSifterSettings::getString(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  SoulSifterSettings* obj = Nan::ObjectWrap::Unwrap<SoulSifterSettings>(info.Holder());
  std::string a0(*v8::String::Utf8Value(info[0]->ToString()));
  const std::string result = obj->soulsiftersettings->get<std::string>(a0);

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

void SoulSifterSettings::putString(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  SoulSifterSettings* obj = Nan::ObjectWrap::Unwrap<SoulSifterSettings>(info.Holder());
  std::string a0(*v8::String::Utf8Value(info[0]->ToString()));
  std::string a1(*v8::String::Utf8Value(info[1]->ToString()));
  obj->soulsiftersettings->put<std::string>(a0, a1);

  info.GetReturnValue().SetUndefined();
}

void SoulSifterSettings::getInt(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  SoulSifterSettings* obj = Nan::ObjectWrap::Unwrap<SoulSifterSettings>(info.Holder());
  std::string a0(*v8::String::Utf8Value(info[0]->ToString()));
  const int result = obj->soulsiftersettings->get<int>(a0);

  info.GetReturnValue().Set(Nan::New<v8::Number>(result));
}

void SoulSifterSettings::putInt(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  SoulSifterSettings* obj = Nan::ObjectWrap::Unwrap<SoulSifterSettings>(info.Holder());
  std::string a0(*v8::String::Utf8Value(info[0]->ToString()));
  int a1(info[1]->IntegerValue());
  obj->soulsiftersettings->put<int>(a0, a1);

  info.GetReturnValue().SetUndefined();
}
