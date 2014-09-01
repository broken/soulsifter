#ifndef Song_wrap_h
#define Song_wrap_h

#include <node.h>
#include <nan.h>
#include "Song.h"

class Song : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);

 private:
  Song();
  explicit Song(dogatech::soulsifter::Song* song);
  ~Song();

  static NAN_METHOD(New);

  static NAN_METHOD(clear);
  static NAN_METHOD(findById);
  static NAN_METHOD(findByFilepath);
  static NAN_METHOD(findByRESongId);
  static NAN_METHOD(sync);
  static NAN_METHOD(update);
  static NAN_METHOD(save);
  static NAN_METHOD(reAlbum);
  static NAN_METHOD(getDateAddedString);
  static NAN_METHOD(setDateAddedToNow);
  static NAN_METHOD(getId);
  static NAN_METHOD(setId);
  static NAN_METHOD(getArtist);
  static NAN_METHOD(setArtist);
  static NAN_METHOD(getTrack);
  static NAN_METHOD(setTrack);
  static NAN_METHOD(getTitle);
  static NAN_METHOD(setTitle);
  static NAN_METHOD(getRemixer);
  static NAN_METHOD(setRemixer);
  static NAN_METHOD(getFeaturing);
  static NAN_METHOD(setFeaturing);
  static NAN_METHOD(getFilepath);
  static NAN_METHOD(setFilepath);
  static NAN_METHOD(getRating);
  static NAN_METHOD(setRating);
  static NAN_METHOD(getDateAdded);
  static NAN_METHOD(setDateAdded);
  static NAN_METHOD(getBpm);
  static NAN_METHOD(setBpm);
  static NAN_METHOD(addTonicKey);
  static NAN_METHOD(removeTonicKey);
  static NAN_METHOD(getComments);
  static NAN_METHOD(setComments);
  static NAN_METHOD(getTrashed);
  static NAN_METHOD(setTrashed);
  static NAN_METHOD(getLowQuality);
  static NAN_METHOD(setLowQuality);
  static NAN_METHOD(getRESongId);
  static NAN_METHOD(setRESongId);
  static NAN_METHOD(getAlbumId);
  static NAN_METHOD(setAlbumId);
  static NAN_METHOD(getAlbumPartId);
  static NAN_METHOD(setAlbumPartId);
  static NAN_METHOD(addStyleById);
  static NAN_METHOD(removeStyleById);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Song* song;
};

#endif
