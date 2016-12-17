#include <node.h>
#include <nan.h>
#include "Album_wrap.h"
#include "AlbumPart_wrap.h"
#include "AudioAnalyzer_wrap.h"
#include "BasicGenre_wrap.h"
#include "GoogleMusicManager_wrap.h"
#include "Mix_wrap.h"
#include "MusicVideo_wrap.h"
#include "MusicVideoService_wrap.h"
#include "NewSongManager_wrap.h"
#include "Playlist_wrap.h"
#include "PlaylistEntry_wrap.h"
#include "SearchUtil_wrap.h"
#include "Song_wrap.h"
#include "SoulSifterSettings_wrap.h"
#include "Style_wrap.h"
#include "TagService_wrap.h"

void InitAll(v8::Handle<v8::Object> exports) {
  // model
  Album::Init(exports);
  AlbumPart::Init(exports);
  BasicGenre::Init(exports);
  Mix::Init(exports);
  MusicVideo::Init(exports);
  Playlist::Init(exports);
  PlaylistEntry::Init(exports);
  Song::Init(exports);
  Style::Init(exports);

  // services
  AudioAnalyzer::Init(exports);
  GoogleMusicManager::Init(exports);
  MusicVideoService::Init(exports);
  NewSongManager::Init(exports);
  SearchUtil::Init(exports);
  TagService::Init(exports);

  // not auto-generated
  SoulSifterSettings::Init(exports);
}

NODE_MODULE(soulsifter, InitAll)
