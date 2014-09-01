#include <node.h>
#include <nan.h>
#include "BasicGenre_wrap.h"
#include "Song_wrap.h"

void InitAll(v8::Handle<v8::Object> exports) {
  //BasicGenre::Init(exports);
  Song::Init(exports);
}

NODE_MODULE(soulsifter, InitAll)