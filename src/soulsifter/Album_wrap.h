#ifndef Album_wrap_h
#define Album_wrap_h

#include <node.h>
#include <nan.h>
#include "Album.h"

class Album : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::Album* v, bool own);
  dogatech::soulsifter::Album* getNwcpValue() const { return album; }

 private:
  Album();
  explicit Album(dogatech::soulsifter::Album* album);
  ~Album();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByCoverFilepath);
  static NAN_METHOD(findByNameAndArtist);
  static NAN_METHOD(findAll);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(sync);
  static NAN_METHOD(reReleaseDate);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getName);
  static NAN_SETTER(setName);
  static NAN_GETTER(getArtist);
  static NAN_SETTER(setArtist);
  static NAN_GETTER(getCoverFilepath);
  static NAN_SETTER(setCoverFilepath);
  static NAN_GETTER(getMixed);
  static NAN_SETTER(setMixed);
  static NAN_GETTER(getLabel);
  static NAN_SETTER(setLabel);
  static NAN_GETTER(getCatalogId);
  static NAN_SETTER(setCatalogId);
  static NAN_GETTER(getReleaseDateYear);
  static NAN_SETTER(setReleaseDateYear);
  static NAN_GETTER(getReleaseDateMonth);
  static NAN_SETTER(setReleaseDateMonth);
  static NAN_GETTER(getReleaseDateDay);
  static NAN_SETTER(setReleaseDateDay);
  static NAN_GETTER(getBasicGenreId);
  static NAN_SETTER(setBasicGenreId);
  static NAN_GETTER(getBasicGenre);
  static NAN_GETTER(getBasicGenreOnce);
  static NAN_SETTER(setBasicGenre);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Album* album;
  bool ownWrappedObject;
};

#endif
