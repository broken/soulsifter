#include <node.h>
#include "BasicGenre.h"
#include "basicgenre_wrap.h"

using namespace v8;

BasicGenre::BasicGenre() : ObjectWrap(), basicGenre(new dogatech::soulsifter::BasicGenre()) {};
BasicGenre::~BasicGenre() { delete basicGenre; };

void BasicGenre::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("BasicGenre"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getId"),
      FunctionTemplate::New(getId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setId"),
      FunctionTemplate::New(setId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getName"),
      FunctionTemplate::New(getName)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setName"),
      FunctionTemplate::New(setName)->GetFunction());

  Persistent<Function> constructor
      = Persistent<Function>::New(isolate, tpl->GetFunction());

  exports->Set(String::NewSymbol("BasicGenre"), constructor);
}

Handle<Value> BasicGenre::New(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BasicGenre* obj = new BasicGenre();
  obj->Wrap(args.This());

  return args.This();
}

Handle<Value> BasicGenre::getId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  int id = obj->basicGenre->getId();

  return scope.Close(Number::New(id));
}

Handle<Value> BasicGenre::setId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  obj->basicGenre->setId(args[0]->Uint32Value());

  return Undefined();
}

Handle<Value> BasicGenre::getName(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  string name = obj->basicGenre->getName();

  return scope.Close(String::New(name.c_str(), name.length()));
}

Handle<Value> BasicGenre::setName(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  BasicGenre* obj = ObjectWrap::Unwrap<BasicGenre>(args.This());
  std::string name(*v8::String::Utf8Value(args[0]->ToString()));
  obj->basicGenre->setName(name);

  return Undefined();
}
