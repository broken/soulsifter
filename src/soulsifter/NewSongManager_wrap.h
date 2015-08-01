#ifndef NewSongManager_wrap_h
#define NewSongManager_wrap_h

#include <node.h>
#include <nan.h>
#include "NewSongManager.h"

class NewSongManager : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::NewSongManager* v, bool own);
  dogatech::soulsifter::NewSongManager* getNwcpValue() const { return newsongmanager; }

 private:
  NewSongManager();
  explicit NewSongManager(dogatech::soulsifter::NewSongManager* newsongmanager);
  ~NewSongManager();

  static NAN_METHOD(New);

  // Unable to process import
  static NAN_METHOD(nextSong);
  // Unable to process coverImagePath
  static NAN_METHOD(processSong);
  static NAN_METHOD(trashMusicFile);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::NewSongManager* newsongmanager;
  bool ownWrappedObject;
};

#endif
