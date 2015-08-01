#ifndef Playlist_wrap_h
#define Playlist_wrap_h

#include <node.h>
#include <nan.h>
#include "Playlist.h"

class Playlist : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::Playlist* v, bool own);
  dogatech::soulsifter::Playlist* getNwcpValue() const { return playlist; }

 private:
  Playlist();
  explicit Playlist(dogatech::soulsifter::Playlist* playlist);
  ~Playlist();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByName);
  static NAN_METHOD(findAll);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(sync);
  static NAN_METHOD(erase);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getName);
  static NAN_SETTER(setName);
  static NAN_GETTER(getQuery);
  static NAN_SETTER(setQuery);
  static NAN_GETTER(getGmusicId);
  static NAN_SETTER(setGmusicId);
  static NAN_GETTER(getPlaylistEntryIds);
  static NAN_SETTER(setPlaylistEntryIds);
  static NAN_GETTER(getPlaylistEntries);
  static NAN_SETTER(setPlaylistEntries);
  static NAN_GETTER(getStyleIds);
  static NAN_SETTER(setStyleIds);
  static NAN_GETTER(getStyles);
  static NAN_SETTER(setStyles);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Playlist* playlist;
  bool ownWrappedObject;
};

#endif
