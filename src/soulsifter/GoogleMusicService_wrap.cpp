#include <iostream>
#include <node.h>
#include <nan.h>
#include "GoogleMusicService_wrap.h"

Nan::Persistent<v8::Function> GoogleMusicService::constructor;

GoogleMusicService::GoogleMusicService() : Nan::ObjectWrap(), googlemusicservice(NULL), ownWrappedObject(true) {};
GoogleMusicService::GoogleMusicService(dogatech::soulsifter::GoogleMusicService* o) : Nan::ObjectWrap(), googlemusicservice(o), ownWrappedObject(true) {};
GoogleMusicService::~GoogleMusicService() { if (ownWrappedObject) delete googlemusicservice; };

void GoogleMusicService::setNwcpValue(dogatech::soulsifter::GoogleMusicService* v, bool own) {
  if (ownWrappedObject)
    delete googlemusicservice;
  googlemusicservice = v;
  ownWrappedObject = own;
}

void GoogleMusicService::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  GoogleMusicService* obj = new GoogleMusicService(new dogatech::soulsifter::GoogleMusicService());
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> GoogleMusicService::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void GoogleMusicService::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("GoogleMusicService").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetMethod(tpl, "syncGoogleMusicPlaylists", syncGoogleMusicPlaylists);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  exports->Set(Nan::New<v8::String>("GoogleMusicService").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

void GoogleMusicService::syncGoogleMusicPlaylists(const Nan::FunctionCallbackInfo<v8::Value>& info) {

      dogatech::soulsifter::GoogleMusicService::syncGoogleMusicPlaylists();

  info.GetReturnValue().SetUndefined();
}

