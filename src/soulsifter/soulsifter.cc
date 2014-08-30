#include <node.h>
#include "BasicGenre_wrap.h"

using namespace v8;

Handle<Value> CreateObject(const Arguments& args) {
  HandleScope scope;
  return scope.Close(BasicGenre::NewInstance(args));
}

void InitAll(Handle<Object> exports) {
  BasicGenre::Init(exports);

  exports->Set(String::NewSymbol("createObject"),
      FunctionTemplate::New(CreateObject)->GetFunction());
}

NODE_MODULE(soulsifter, InitAll)