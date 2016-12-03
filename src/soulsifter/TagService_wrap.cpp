#include <iostream>
#include <node.h>
#include <nan.h>
#include "TagService_wrap.h"
#include "Song.h"
#include "Song_wrap.h"

Nan::Persistent<v8::Function> TagService::constructor;

TagService::TagService() : Nan::ObjectWrap(), tagservice(NULL), ownWrappedObject(true) {};
TagService::TagService(dogatech::soulsifter::TagService* o) : Nan::ObjectWrap(), tagservice(o), ownWrappedObject(true) {};
TagService::~TagService() { if (ownWrappedObject) delete tagservice; };

void TagService::setNwcpValue(dogatech::soulsifter::TagService* v, bool own) {
  if (ownWrappedObject)
    delete tagservice;
  tagservice = v;
  ownWrappedObject = own;
}

void TagService::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  TagService* obj = new TagService(new dogatech::soulsifter::TagService());
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> TagService::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void TagService::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("TagService").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetMethod(tpl, "readId3v2Tag", readId3v2Tag);
  Nan::SetMethod(tpl, "updateSongAttributesFromTags", updateSongAttributesFromTags);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New<v8::String>("TagService").ToLocalChecked(), tpl->GetFunction());
}

void TagService::readId3v2Tag(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  dogatech::soulsifter::Song* a0(Nan::ObjectWrap::Unwrap<Song>(info[0]->ToObject())->getNwcpValue());

      dogatech::soulsifter::TagService::readId3v2Tag(a0);

  info.GetReturnValue().SetUndefined();
}

void TagService::updateSongAttributesFromTags(const Nan::FunctionCallbackInfo<v8::Value>& info) {

      dogatech::soulsifter::TagService::updateSongAttributesFromTags();

  info.GetReturnValue().SetUndefined();
}

