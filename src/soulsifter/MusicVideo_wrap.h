#ifndef MusicVideo_wrap_h
#define MusicVideo_wrap_h

#include <node.h>
#include <nan.h>
#include "MusicVideo.h"

class MusicVideo : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::MusicVideo* v, bool own);
  dogatech::soulsifter::MusicVideo* getNwcpValue() const { return musicvideo; }

 private:
  MusicVideo();
  explicit MusicVideo(dogatech::soulsifter::MusicVideo* musicvideo);
  ~MusicVideo();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findBySongId);
  static NAN_METHOD(findAll);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(sync);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getSongId);
  static NAN_SETTER(setSongId);
  static NAN_GETTER(getSong);
  static NAN_GETTER(getSongOnce);
  static NAN_SETTER(setSong);
  static NAN_GETTER(getFilePath);
  static NAN_SETTER(setFilePath);
  static NAN_GETTER(getThumbnailFilePath);
  static NAN_SETTER(setThumbnailFilePath);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::MusicVideo* musicvideo;
  bool ownWrappedObject;
};

#endif
