#include <iostream>
#include <node.h>
#include <nan.h>
#include "AudioAnalyzer_wrap.h"

Nan::Persistent<v8::Function> AudioAnalyzer::constructor;

AudioAnalyzer::AudioAnalyzer() : Nan::ObjectWrap(), audioanalyzer(NULL), ownWrappedObject(true) {};
AudioAnalyzer::AudioAnalyzer(dogatech::soulsifter::AudioAnalyzer* o) : Nan::ObjectWrap(), audioanalyzer(o), ownWrappedObject(true) {};
AudioAnalyzer::~AudioAnalyzer() { if (ownWrappedObject) delete audioanalyzer; };

void AudioAnalyzer::setNwcpValue(dogatech::soulsifter::AudioAnalyzer* v, bool own) {
  if (ownWrappedObject)
    delete audioanalyzer;
  audioanalyzer = v;
  ownWrappedObject = own;
}

void AudioAnalyzer::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  AudioAnalyzer* obj = new AudioAnalyzer(new dogatech::soulsifter::AudioAnalyzer());
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> AudioAnalyzer::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void AudioAnalyzer::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("AudioAnalyzer").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  // Unable to process analyzeKey
  // Unable to process analyzeBpm
  Nan::SetMethod(tpl, "analyzeBpms", analyzeBpms);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New<v8::String>("AudioAnalyzer").ToLocalChecked(), tpl->GetFunction());
}

void AudioAnalyzer::analyzeBpms(const Nan::FunctionCallbackInfo<v8::Value>& info) {

      dogatech::soulsifter::AudioAnalyzer::analyzeBpms();

  info.GetReturnValue().SetUndefined();
}

