#ifndef Song_wrap_h
#define Song_wrap_h

#include <node.h>
#include "Song.h"

class Song : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

 private:
  Song();
  explicit Song(dogatech::soulsifter::Song* song);
  ~Song();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  static v8::Handle<v8::Value> clear(const v8::Arguments& args);
  static v8::Handle<v8::Value> findById(const v8::Arguments& args);
  static v8::Handle<v8::Value> findByFilepath(const v8::Arguments& args);
  static v8::Handle<v8::Value> findByRESongId(const v8::Arguments& args);
  static v8::Handle<v8::Value> sync(const v8::Arguments& args);
  static v8::Handle<v8::Value> update(const v8::Arguments& args);
  static v8::Handle<v8::Value> save(const v8::Arguments& args);
  static v8::Handle<v8::Value> reAlbum(const v8::Arguments& args);
  static v8::Handle<v8::Value> getDateAddedString(const v8::Arguments& args);
  static v8::Handle<v8::Value> setDateAddedToNow(const v8::Arguments& args);
  static v8::Handle<v8::Value> getId(const v8::Arguments& args);
  static v8::Handle<v8::Value> setId(const v8::Arguments& args);
  static v8::Handle<v8::Value> getArtist(const v8::Arguments& args);
  static v8::Handle<v8::Value> setArtist(const v8::Arguments& args);
  static v8::Handle<v8::Value> getTrack(const v8::Arguments& args);
  static v8::Handle<v8::Value> setTrack(const v8::Arguments& args);
  static v8::Handle<v8::Value> getTitle(const v8::Arguments& args);
  static v8::Handle<v8::Value> setTitle(const v8::Arguments& args);
  static v8::Handle<v8::Value> getRemixer(const v8::Arguments& args);
  static v8::Handle<v8::Value> setRemixer(const v8::Arguments& args);
  static v8::Handle<v8::Value> getFeaturing(const v8::Arguments& args);
  static v8::Handle<v8::Value> setFeaturing(const v8::Arguments& args);
  static v8::Handle<v8::Value> getFilepath(const v8::Arguments& args);
  static v8::Handle<v8::Value> setFilepath(const v8::Arguments& args);
  static v8::Handle<v8::Value> getRating(const v8::Arguments& args);
  static v8::Handle<v8::Value> setRating(const v8::Arguments& args);
  static v8::Handle<v8::Value> getDateAdded(const v8::Arguments& args);
  static v8::Handle<v8::Value> setDateAdded(const v8::Arguments& args);
  static v8::Handle<v8::Value> getBpm(const v8::Arguments& args);
  static v8::Handle<v8::Value> setBpm(const v8::Arguments& args);
  static v8::Handle<v8::Value> addTonicKey(const v8::Arguments& args);
  static v8::Handle<v8::Value> removeTonicKey(const v8::Arguments& args);
  static v8::Handle<v8::Value> getComments(const v8::Arguments& args);
  static v8::Handle<v8::Value> setComments(const v8::Arguments& args);
  static v8::Handle<v8::Value> getTrashed(const v8::Arguments& args);
  static v8::Handle<v8::Value> setTrashed(const v8::Arguments& args);
  static v8::Handle<v8::Value> getLowQuality(const v8::Arguments& args);
  static v8::Handle<v8::Value> setLowQuality(const v8::Arguments& args);
  static v8::Handle<v8::Value> getRESongId(const v8::Arguments& args);
  static v8::Handle<v8::Value> setRESongId(const v8::Arguments& args);
  static v8::Handle<v8::Value> getAlbumId(const v8::Arguments& args);
  static v8::Handle<v8::Value> setAlbumId(const v8::Arguments& args);
  static v8::Handle<v8::Value> getAlbumPartId(const v8::Arguments& args);
  static v8::Handle<v8::Value> setAlbumPartId(const v8::Arguments& args);
  static v8::Handle<v8::Value> addStyleById(const v8::Arguments& args);
  static v8::Handle<v8::Value> removeStyleById(const v8::Arguments& args);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::Song* song;
};

#endif
