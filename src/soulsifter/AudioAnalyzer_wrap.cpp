#include <iostream>
#include <node.h>
#include <nan.h>
#include "AudioAnalyzer_wrap.h"

v8::Persistent<v8::Function> AudioAnalyzer::constructor;

AudioAnalyzer::AudioAnalyzer() : ObjectWrap(), audioanalyzer(NULL), ownWrappedObject(true) {};
AudioAnalyzer::AudioAnalyzer(dogatech::soulsifter::AudioAnalyzer* o) : ObjectWrap(), audioanalyzer(o), ownWrappedObject(true) {};
AudioAnalyzer::~AudioAnalyzer() { if (ownWrappedObject) delete audioanalyzer; };

void AudioAnalyzer::setNwcpValue(dogatech::soulsifter::AudioAnalyzer* v, bool own) {
  if (ownWrappedObject)
    delete audioanalyzer;
  audioanalyzer = v;
  ownWrappedObject = own;
}

NAN_METHOD(AudioAnalyzer::New) {
  NanScope();

  AudioAnalyzer* obj = new AudioAnalyzer(new dogatech::soulsifter::AudioAnalyzer());
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

  // Unable to process analyzeKey
  // Unable to process analyzeBpm
  NanSetTemplate(tpl, "analyzeBpms", NanNew<v8::FunctionTemplate>(analyzeBpms)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("AudioAnalyzer"), tpl->GetFunction());
}

NAN_METHOD(AudioAnalyzer::analyzeBpms) {
  NanScope();


      dogatech::soulsifter::AudioAnalyzer::analyzeBpms();

  NanReturnUndefined();
}

