#include <node.h>
#include <nan.h>
#include "Album_wrap.h"
#include "AudioAnalyzer_wrap.h"
//#include "BasicGenre_wrap.h"
#include "SearchUtil_wrap.h"
#include "Song_wrap.h"
#include "Style_wrap.h"

void InitAll(v8::Handle<v8::Object> exports) {
  Album::Init(exports);
  AudioAnalyzer::Init(exports);
  //BasicGenre::Init(exports);
  SearchUtil::Init(exports);
  Song::Init(exports);
  Style::Init(exports);
}

NODE_MODULE(soulsifter, InitAll)