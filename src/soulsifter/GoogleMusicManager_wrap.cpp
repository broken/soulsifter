#include <iostream>
#include <node.h>
#include <nan.h>
#include "GoogleMusicManager_wrap.h"

Nan::Persistent<v8::Function> GoogleMusicManager::constructor;

GoogleMusicManager::GoogleMusicManager() : Nan::ObjectWrap(), googlemusicmanager(NULL), ownWrappedObject(true) {};
GoogleMusicManager::GoogleMusicManager(dogatech::soulsifter::GoogleMusicManager* o) : Nan::ObjectWrap(), googlemusicmanager(o), ownWrappedObject(true) {};
GoogleMusicManager::~GoogleMusicManager() { if (ownWrappedObject) delete googlemusicmanager; };

void GoogleMusicManager::setNwcpValue(dogatech::soulsifter::GoogleMusicManager* v, bool own) {
  if (ownWrappedObject)
    delete googlemusicmanager;
  googlemusicmanager = v;
  ownWrappedObject = own;
}

void GoogleMusicManager::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  GoogleMusicManager* obj = new GoogleMusicManager(new dogatech::soulsifter::GoogleMusicManager());
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> GoogleMusicManager::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void GoogleMusicManager::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("GoogleMusicManager").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "login", login);
  Nan::SetPrototypeMethod(tpl, "logout", logout);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New<v8::String>("GoogleMusicManager").ToLocalChecked(), tpl->GetFunction());
}

void GoogleMusicManager::login(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  GoogleMusicManager* obj = Nan::ObjectWrap::Unwrap<GoogleMusicManager>(info.Holder());
  bool result =  obj->googlemusicmanager->login();

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

void GoogleMusicManager::logout(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  GoogleMusicManager* obj = Nan::ObjectWrap::Unwrap<GoogleMusicManager>(info.Holder());
  bool result =  obj->googlemusicmanager->logout();

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

