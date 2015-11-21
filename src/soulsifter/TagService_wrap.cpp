#include <iostream>
#include <node.h>
#include <nan.h>
#include "TagService_wrap.h"
#include "Song.h"
#include "Song_wrap.h"

v8::Persistent<v8::Function> TagService::constructor;

TagService::TagService() : ObjectWrap(), tagservice(NULL), ownWrappedObject(true) {};
TagService::TagService(dogatech::soulsifter::TagService* o) : ObjectWrap(), tagservice(o), ownWrappedObject(true) {};
TagService::~TagService() { if (ownWrappedObject) delete tagservice; };

void TagService::setNwcpValue(dogatech::soulsifter::TagService* v, bool own) {
  if (ownWrappedObject)
    delete tagservice;
  tagservice = v;
  ownWrappedObject = own;
}

NAN_METHOD(TagService::New) {
  NanScope();

  TagService* obj = new TagService(new dogatech::soulsifter::TagService());
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> TagService::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void TagService::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("TagService"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetTemplate(tpl, "readId3v2Tag", NanNew<v8::FunctionTemplate>(readId3v2Tag)->GetFunction());
  NanSetTemplate(tpl, "updateSongAttributesFromTags", NanNew<v8::FunctionTemplate>(updateSongAttributesFromTags)->GetFunction());

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("TagService"), tpl->GetFunction());
}

NAN_METHOD(TagService::readId3v2Tag) {
  NanScope();

  dogatech::soulsifter::Song* a0(node::ObjectWrap::Unwrap<Song>(args[0]->ToObject())->getNwcpValue());

      dogatech::soulsifter::TagService::readId3v2Tag(a0);

  NanReturnUndefined();
}

NAN_METHOD(TagService::updateSongAttributesFromTags) {
  NanScope();


      dogatech::soulsifter::TagService::updateSongAttributesFromTags();

  NanReturnUndefined();
}

