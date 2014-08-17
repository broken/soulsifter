#include <node.h>
#include "BasicGenre_wrap.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  BasicGenre::Init(exports);
}

NODE_MODULE(soulsifter, InitAll)