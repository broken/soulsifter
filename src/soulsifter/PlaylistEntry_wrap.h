#ifndef PlaylistEntry_wrap_h
#define PlaylistEntry_wrap_h

#include <node.h>
#include <nan.h>
#include "PlaylistEntry.h"

class PlaylistEntry : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::PlaylistEntry* v, bool own);
  dogatech::soulsifter::PlaylistEntry* getNwcpValue() const { return playlistentry; }

 private:
  PlaylistEntry();
  explicit PlaylistEntry(dogatech::soulsifter::PlaylistEntry* playlistentry);
  ~PlaylistEntry();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  // Unable to process findById
  // Unable to process findByPlaylistIdAndSongId
  // Unable to process findAll
  static NAN_METHOD(sync);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getPlaylistId);
  static NAN_SETTER(setPlaylistId);
  // Unable to process getPlaylist
  // Unable to process setPlaylist
  static NAN_GETTER(getSongId);
  static NAN_SETTER(setSongId);
  static NAN_GETTER(getSong);
  static NAN_SETTER(setSong);
  static NAN_GETTER(getPosition);
  static NAN_SETTER(setPosition);
  static NAN_GETTER(getTime);
  static NAN_SETTER(setTime);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::PlaylistEntry* playlistentry;
  bool ownWrappedObject;
};

#endif
