#include <iostream>
#include <node.h>
#include <nan.h>
#include "MusicVideoService_wrap.h"
#include "MusicVideo.h"
#include "MusicVideo_wrap.h"
#include "Song.h"
#include "Song_wrap.h"

Nan::Persistent<v8::Function> MusicVideoService::constructor;

MusicVideoService::MusicVideoService() : Nan::ObjectWrap(), musicvideoservice(NULL), ownWrappedObject(true) {};
MusicVideoService::MusicVideoService(dogatech::soulsifter::MusicVideoService* o) : Nan::ObjectWrap(), musicvideoservice(o), ownWrappedObject(true) {};
MusicVideoService::~MusicVideoService() { if (ownWrappedObject) delete musicvideoservice; };

void MusicVideoService::setNwcpValue(dogatech::soulsifter::MusicVideoService* v, bool own) {
  if (ownWrappedObject)
    delete musicvideoservice;
  musicvideoservice = v;
  ownWrappedObject = own;
}

void MusicVideoService::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MusicVideoService* obj = new MusicVideoService(new dogatech::soulsifter::MusicVideoService());
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> MusicVideoService::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void MusicVideoService::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MusicVideoService").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetMethod(tpl, "associateYouTubeVideo", associateYouTubeVideo);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New<v8::String>("MusicVideoService").ToLocalChecked(), tpl->GetFunction());
}

void MusicVideoService::associateYouTubeVideo(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  dogatech::soulsifter::Song* a0(Nan::ObjectWrap::Unwrap<Song>(info[0]->ToObject())->getNwcpValue());
  string a1(*v8::String::Utf8Value(info[1]->ToString()));
  dogatech::soulsifter::MusicVideo* result =
      dogatech::soulsifter::MusicVideoService::associateYouTubeVideo(a0, a1);

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = MusicVideo::NewInstance();
    MusicVideo* r = Nan::ObjectWrap::Unwrap<MusicVideo>(instance);
    r->setNwcpValue(result, false);

    info.GetReturnValue().Set(instance);
  }
}

