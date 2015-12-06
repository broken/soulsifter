#include <iostream>
#include <node.h>
#include <nan.h>
#include "MusicVideoService_wrap.h"
#include "MusicVideo.h"
#include "MusicVideo_wrap.h"
#include "Song.h"
#include "Song_wrap.h"

v8::Persistent<v8::Function> MusicVideoService::constructor;

MusicVideoService::MusicVideoService() : ObjectWrap(), musicvideoservice(NULL), ownWrappedObject(true) {};
MusicVideoService::MusicVideoService(dogatech::soulsifter::MusicVideoService* o) : ObjectWrap(), musicvideoservice(o), ownWrappedObject(true) {};
MusicVideoService::~MusicVideoService() { if (ownWrappedObject) delete musicvideoservice; };

void MusicVideoService::setNwcpValue(dogatech::soulsifter::MusicVideoService* v, bool own) {
  if (ownWrappedObject)
    delete musicvideoservice;
  musicvideoservice = v;
  ownWrappedObject = own;
}

NAN_METHOD(MusicVideoService::New) {
  NanScope();

  MusicVideoService* obj = new MusicVideoService(new dogatech::soulsifter::MusicVideoService());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> MusicVideoService::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void MusicVideoService::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("MusicVideoService"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetTemplate(tpl, "associateYouTubeVideo", NanNew<v8::FunctionTemplate>(associateYouTubeVideo)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("MusicVideoService"), tpl->GetFunction());
}

NAN_METHOD(MusicVideoService::associateYouTubeVideo) {
  NanScope();

  dogatech::soulsifter::Song* a0(node::ObjectWrap::Unwrap<Song>(args[0]->ToObject())->getNwcpValue());
  string a1(*v8::String::Utf8Value(args[1]->ToString()));
  dogatech::soulsifter::MusicVideo* result =
      dogatech::soulsifter::MusicVideoService::associateYouTubeVideo(a0, a1);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = MusicVideo::NewInstance();
  MusicVideo* r = ObjectWrap::Unwrap<MusicVideo>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

