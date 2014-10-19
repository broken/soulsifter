#include <iostream>
#include <node.h>
#include <nan.h>
#include "AudioAnalyzer.h"
#include "AudioAnalyzer_wrap.h"
#include "Song.h"
#include "Song_wrap.h"
#include "Style.h"
#include "Style_wrap.h"

v8::Persistent<v8::Function> AudioAnalyzer::constructor;

AudioAnalyzer::AudioAnalyzer() : ObjectWrap(), audioAnalyzer(new dogatech::soulsifter::AudioAnalyzer()) {};
AudioAnalyzer::AudioAnalyzer(dogatech::soulsifter::AudioAnalyzer* o) : ObjectWrap(), audioAnalyzer(o) {};
AudioAnalyzer::~AudioAnalyzer() { delete audioAnalyzer; };

NAN_METHOD(AudioAnalyzer::New) {
  NanScope();

  AudioAnalyzer* obj = new AudioAnalyzer();
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> AudioAnalyzer::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void AudioAnalyzer::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("AudioAnalyzer"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetTemplate(tpl, "analyzeBpms", NanNew<v8::FunctionTemplate>(analyzeBpms)->GetFunction());

  // Prototype

  // Accessors

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("AudioAnalyzer"), tpl->GetFunction());
}


NAN_METHOD(AudioAnalyzer::analyzeBpms) {
  NanScope();

  dogatech::soulsifter::AudioAnalyzer::analyzeBpms();

  NanReturnUndefined();
}
