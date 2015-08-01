#ifndef Mix_wrap_h
#define Mix_wrap_h

#include <node.h>
#include <nan.h>
#include "Mix.h"

class Mix : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::Mix* v, bool own);
  dogatech::soulsifter::Mix* getNwcpValue() const { return mix; }

 private:
  Mix();
  explicit Mix(dogatech::soulsifter::Mix* mix);
  ~Mix();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByOutSongIdAndInSongId);
  static NAN_METHOD(findAll);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(sync);
  static NAN_METHOD(mixoutCountForRESongId);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getOutSongId);
  static NAN_SETTER(setOutSongId);
  static NAN_GETTER(getOutSong);
  static NAN_SETTER(setOutSong);
  static NAN_GETTER(getInSongId);
  static NAN_SETTER(setInSongId);
  static NAN_GETTER(getInSong);
  static NAN_SETTER(setInSong);
  static NAN_GETTER(getBpmDiff);
  static NAN_SETTER(setBpmDiff);
  static NAN_GETTER(getRank);
  static NAN_SETTER(setRank);
  static NAN_GETTER(getComments);
  static NAN_SETTER(setComments);
  static NAN_GETTER(getAddon);
  static NAN_SETTER(setAddon);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Mix* mix;
  bool ownWrappedObject;
};

#endif
