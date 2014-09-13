#include <node.h>
#include <nan.h>
//#include "BasicGenre_wrap.h"
#include "SearchUtil_wrap.h"
#include "Song_wrap.h"
#include "Style_wrap.h"

void InitAll(v8::Handle<v8::Object> exports) {
  //BasicGenre::Init(exports);
  SearchUtil::Init(exports);
  Song::Init(exports);
  Style::Init(exports);
}

NODE_MODULE(soulsifter, InitAll)