#ifndef AlbumPart_wrap_h
#define AlbumPart_wrap_h

#include <node.h>
#include <nan.h>
#include "AlbumPart.h"

class AlbumPart : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::AlbumPart* v, bool own);
  dogatech::soulsifter::AlbumPart* getNwcpValue() const { return albumpart; }

 private:
  AlbumPart();
  explicit AlbumPart(dogatech::soulsifter::AlbumPart* albumpart);
  ~AlbumPart();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByPosAndAlbumId);
  static NAN_METHOD(findAll);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(sync);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getPos);
  static NAN_SETTER(setPos);
  static NAN_GETTER(getName);
  static NAN_SETTER(setName);
  static NAN_GETTER(getAlbumId);
  static NAN_SETTER(setAlbumId);
  static NAN_GETTER(getAlbum);
  static NAN_GETTER(getAlbumOnce);
  static NAN_SETTER(setAlbum);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::AlbumPart* albumpart;
  bool ownWrappedObject;
};

#endif
