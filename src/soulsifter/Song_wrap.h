#ifndef Song_wrap_h
#define Song_wrap_h

#include <node.h>
#include <nan.h>
#include "Song.h"

class Song : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::Song* v, bool own);
  dogatech::soulsifter::Song* getNwcpValue() const { return song; }

 private:
  Song();
  explicit Song(dogatech::soulsifter::Song* song);
  ~Song();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByFilepath);
  static NAN_METHOD(findByRESongId);
  static NAN_METHOD(findAll);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  // Unable to process createRESongFromSong
  static NAN_METHOD(reAlbum);
  static NAN_GETTER(getDateAddedString);
  static NAN_METHOD(setDateAddedToNow);
  static NAN_GETTER(getId);
  static NAN_SETTER(setId);
  static NAN_GETTER(getArtist);
  static NAN_SETTER(setArtist);
  static NAN_GETTER(getTrack);
  static NAN_SETTER(setTrack);
  static NAN_GETTER(getTitle);
  static NAN_SETTER(setTitle);
  static NAN_GETTER(getRemixer);
  static NAN_SETTER(setRemixer);
  static NAN_GETTER(getFeaturing);
  static NAN_SETTER(setFeaturing);
  static NAN_GETTER(getFilepath);
  static NAN_SETTER(setFilepath);
  static NAN_GETTER(getRating);
  static NAN_SETTER(setRating);
  static NAN_GETTER(getDateAdded);
  static NAN_SETTER(setDateAdded);
  static NAN_GETTER(getBpm);
  static NAN_SETTER(setBpm);
  // Unable to process getTonicKeys
  // Unable to process setTonicKeys
  static NAN_METHOD(addTonicKey);
  static NAN_METHOD(removeTonicKey);
  static NAN_GETTER(getTonicKey);
  static NAN_SETTER(setTonicKey);
  static NAN_GETTER(getComments);
  static NAN_SETTER(setComments);
  static NAN_GETTER(getTrashed);
  static NAN_SETTER(setTrashed);
  static NAN_GETTER(getLowQuality);
  static NAN_SETTER(setLowQuality);
  static NAN_GETTER(getRESongId);
  static NAN_SETTER(setRESongId);
  // Unable to process getRESong
  // Unable to process setRESong
  static NAN_GETTER(getAlbumId);
  static NAN_SETTER(setAlbumId);
  static NAN_GETTER(getAlbum);
  static NAN_SETTER(setAlbum);
  static NAN_GETTER(getAlbumPartId);
  static NAN_SETTER(setAlbumPartId);
  static NAN_GETTER(getAlbumPart);
  static NAN_SETTER(setAlbumPart);
  static NAN_GETTER(getStyleIds);
  static NAN_SETTER(setStyleIds);
  static NAN_GETTER(getStyles);
  static NAN_SETTER(setStyles);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Song* song;
  bool ownWrappedObject;
};

#endif
