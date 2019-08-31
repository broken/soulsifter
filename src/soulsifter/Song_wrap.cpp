#include <iostream>
#include <node.h>
#include <nan.h>
#include "Song_wrap.h"
#include "Album.h"
#include "AlbumPart.h"
#include "AlbumPart_wrap.h"
#include "Album_wrap.h"
#include "MusicVideo.h"
#include "MusicVideo_wrap.h"
#include "ResultSetIterator.h"
#include "Song.h"
#include "Song_wrap.h"
#include "Style.h"
#include "Style_wrap.h"

Nan::Persistent<v8::Function> Song::constructor;

Song::Song() : Nan::ObjectWrap(), song(NULL), ownWrappedObject(true) {};
Song::Song(dogatech::soulsifter::Song* o) : Nan::ObjectWrap(), song(o), ownWrappedObject(true) {};
Song::~Song() { if (ownWrappedObject) delete song; };

void Song::setNwcpValue(dogatech::soulsifter::Song* v, bool own) {
  if (ownWrappedObject)
    delete song;
  song = v;
  ownWrappedObject = own;
}

void Song::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  dogatech::soulsifter::Song* wrappedObj = NULL;
  if (info.Length()) {
    dogatech::soulsifter::Song* xtmp(Nan::ObjectWrap::Unwrap<Song>(info[0]->ToObject())->getNwcpValue());
    dogatech::soulsifter::Song& x = *xtmp;
    wrappedObj = new dogatech::soulsifter::Song(x);
  } else {
    wrappedObj = new dogatech::soulsifter::Song();
  }

  Song* obj = new Song(wrappedObj);
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> Song::NewInstance() {
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  return Nan::NewInstance(cons).ToLocalChecked();
}

void Song::Init(v8::Local<v8::Object> exports) {
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Song").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "clear", clear);
  Nan::SetMethod(tpl, "findById", findById);
  Nan::SetMethod(tpl, "findByFilepath", findByFilepath);
  Nan::SetMethod(tpl, "findByGoogleSongId", findByGoogleSongId);
  Nan::SetMethod(tpl, "findByRESongId", findByRESongId);
  Nan::SetMethod(tpl, "findAll", findAll);
  Nan::SetPrototypeMethod(tpl, "update", update);
  Nan::SetPrototypeMethod(tpl, "save", save);
  Nan::SetPrototypeMethod(tpl, "sync", sync);
  // Unable to process createRESongFromSong
  Nan::SetPrototypeMethod(tpl, "reAlbum", reAlbum);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("dateAddedString").ToLocalChecked(), getDateAddedString);
  Nan::SetPrototypeMethod(tpl, "setDateAddedToNow", setDateAddedToNow);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("id").ToLocalChecked(), getId, setId);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("artist").ToLocalChecked(), getArtist, setArtist);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("track").ToLocalChecked(), getTrack, setTrack);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("title").ToLocalChecked(), getTitle, setTitle);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("remixer").ToLocalChecked(), getRemixer, setRemixer);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("featuring").ToLocalChecked(), getFeaturing, setFeaturing);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("filepath").ToLocalChecked(), getFilepath, setFilepath);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("rating").ToLocalChecked(), getRating, setRating);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("dateAdded").ToLocalChecked(), getDateAdded, setDateAdded);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("bpm").ToLocalChecked(), getBpm, setBpm);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("tonicKeys").ToLocalChecked(), getTonicKeys, setTonicKeys);
  Nan::SetPrototypeMethod(tpl, "addTonicKey", addTonicKey);
  Nan::SetPrototypeMethod(tpl, "removeTonicKey", removeTonicKey);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("tonicKey").ToLocalChecked(), getTonicKey, setTonicKey);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("energy").ToLocalChecked(), getEnergy, setEnergy);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("comments").ToLocalChecked(), getComments, setComments);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("trashed").ToLocalChecked(), getTrashed, setTrashed);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("lowQuality").ToLocalChecked(), getLowQuality, setLowQuality);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("googleSongId").ToLocalChecked(), getGoogleSongId, setGoogleSongId);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("durationInMs").ToLocalChecked(), getDurationInMs, setDurationInMs);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("curator").ToLocalChecked(), getCurator, setCurator);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("rESongId").ToLocalChecked(), getRESongId, setRESongId);
  // Unable to process getRESong
  // Unable to process getRESongOnce
  // Unable to process setRESong
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("albumId").ToLocalChecked(), getAlbumId, setAlbumId);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("album").ToLocalChecked(), getAlbum, setAlbum);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("albumOnce").ToLocalChecked(), getAlbumOnce);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("albumPartId").ToLocalChecked(), getAlbumPartId, setAlbumPartId);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("albumPart").ToLocalChecked(), getAlbumPart, setAlbumPart);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("albumPartOnce").ToLocalChecked(), getAlbumPartOnce);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("musicVideoId").ToLocalChecked(), getMusicVideoId, setMusicVideoId);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("musicVideo").ToLocalChecked(), getMusicVideo, setMusicVideo);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("musicVideoOnce").ToLocalChecked(), getMusicVideoOnce);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("styleIds").ToLocalChecked(), getStyleIds, setStyleIds);
  Nan::SetAccessor(tpl->InstanceTemplate(), Nan::New<v8::String>("styles").ToLocalChecked(), getStyles, setStyles);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  exports->Set(Nan::New<v8::String>("Song").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

void Song::clear(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  obj->song->clear();

  info.GetReturnValue().SetUndefined();
}

void Song::findById(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  int a0(info[0]->IntegerValue());
  dogatech::soulsifter::Song* result =
      dogatech::soulsifter::Song::findById(a0);

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Song::NewInstance();
    Song* r = Nan::ObjectWrap::Unwrap<Song>(instance);
    r->setNwcpValue(result, true);

    info.GetReturnValue().Set(instance);
  }
}

void Song::findByFilepath(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  string a0(*v8::String::Utf8Value(info[0]->ToString()));
  dogatech::soulsifter::Song* result =
      dogatech::soulsifter::Song::findByFilepath(a0);

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Song::NewInstance();
    Song* r = Nan::ObjectWrap::Unwrap<Song>(instance);
    r->setNwcpValue(result, true);

    info.GetReturnValue().Set(instance);
  }
}

void Song::findByGoogleSongId(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  string a0(*v8::String::Utf8Value(info[0]->ToString()));
  dogatech::soulsifter::Song* result =
      dogatech::soulsifter::Song::findByGoogleSongId(a0);

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Song::NewInstance();
    Song* r = Nan::ObjectWrap::Unwrap<Song>(instance);
    r->setNwcpValue(result, true);

    info.GetReturnValue().Set(instance);
  }
}

void Song::findByRESongId(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  int a0(info[0]->IntegerValue());
  dogatech::soulsifter::Song* result =
      dogatech::soulsifter::Song::findByRESongId(a0);

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Song::NewInstance();
    Song* r = Nan::ObjectWrap::Unwrap<Song>(instance);
    r->setNwcpValue(result, true);

    info.GetReturnValue().Set(instance);
  }
}

void Song::findAll(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  dogatech::ResultSetIterator<dogatech::soulsifter::Song>* result =
      dogatech::soulsifter::Song::findAll();

  vector<dogatech::soulsifter::Song*>* v = result->toVector();
  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> instance = Nan::NewInstance(cons).ToLocalChecked();
    Song* o = Nan::ObjectWrap::Unwrap<Song>(instance);
    o->song = (*v)[i];
    a->Set(Nan::New<v8::Number>(i), instance);
  }
  delete v;
  info.GetReturnValue().Set(a);
}

void Song::update(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int result =  obj->song->update();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

void Song::save(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int result =  obj->song->save();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

void Song::sync(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  bool result =  obj->song->sync();

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

void Song::reAlbum(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->reAlbum();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_GETTER(Song::getDateAddedString) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getDateAddedString();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

void Song::setDateAddedToNow(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  obj->song->setDateAddedToNow();

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getId();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getArtist) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getArtist();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setArtist) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setArtist(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getTrack) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getTrack();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setTrack) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setTrack(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getTitle) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getTitle();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setTitle) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setTitle(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getRemixer) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getRemixer();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setRemixer) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setRemixer(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getFeaturing) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getFeaturing();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setFeaturing) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setFeaturing(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getFilepath) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getFilepath();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setFilepath) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setFilepath(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getRating) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getRating();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setRating) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setRating(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getDateAdded) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const time_t result =  obj->song->getDateAdded();

  info.GetReturnValue().Set(Nan::New<v8::Number>(result * 1000));
}

NAN_SETTER(Song::setDateAdded) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  time_t a0(value->IntegerValue() / 1000);
  obj->song->setDateAdded(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getBpm) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getBpm();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setBpm) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setBpm(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getTonicKeys) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const std::set<string> result =  obj->song->getTonicKeys();

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result.size());
  int idx = 0;
  for (const auto& element : result) {
    a->Set(Nan::New<v8::Number>(idx), Nan::New<v8::String>(element).ToLocalChecked());
    ++idx;
  }
  info.GetReturnValue().Set(a);
}

NAN_SETTER(Song::setTonicKeys) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::set<string> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    string x(*v8::String::Utf8Value(tmp->ToString()));
    a0.insert(x);
  }
  obj->song->setTonicKeys(a0);

  info.GetReturnValue().SetUndefined();
}

void Song::addTonicKey(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(info[0]->ToString()));
  obj->song->addTonicKey(a0);

  info.GetReturnValue().SetUndefined();
}

void Song::removeTonicKey(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(info[0]->ToString()));
  obj->song->removeTonicKey(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getTonicKey) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getTonicKey();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setTonicKey) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setTonicKey(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getEnergy) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getEnergy();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setEnergy) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setEnergy(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getComments) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getComments();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setComments) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setComments(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getTrashed) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const bool result =  obj->song->getTrashed();

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

NAN_SETTER(Song::setTrashed) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  bool a0(value->BooleanValue());
  obj->song->setTrashed(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getLowQuality) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const bool result =  obj->song->getLowQuality();

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}

NAN_SETTER(Song::setLowQuality) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  bool a0(value->BooleanValue());
  obj->song->setLowQuality(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getGoogleSongId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getGoogleSongId();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setGoogleSongId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setGoogleSongId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getDurationInMs) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getDurationInMs();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setDurationInMs) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setDurationInMs(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getCurator) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const string result =  obj->song->getCurator();

  info.GetReturnValue().Set(Nan::New<v8::String>(result).ToLocalChecked());
}

NAN_SETTER(Song::setCurator) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setCurator(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getRESongId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getRESongId();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setRESongId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setRESongId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getAlbumId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getAlbumId();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setAlbumId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setAlbumId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getAlbum) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::Album* result =  obj->song->getAlbum();

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Album::NewInstance();
    Album* r = Nan::ObjectWrap::Unwrap<Album>(instance);
    r->setNwcpValue(result, false);

    info.GetReturnValue().Set(instance);
  }
}

NAN_GETTER(Song::getAlbumOnce) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::Album* result =  obj->song->getAlbumOnce();

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = Album::NewInstance();
    Album* r = Nan::ObjectWrap::Unwrap<Album>(instance);
    r->setNwcpValue(result, false);

    info.GetReturnValue().Set(instance);
  }
}

NAN_SETTER(Song::setAlbum) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::Album* a0tmp(Nan::ObjectWrap::Unwrap<Album>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::Album& a0 = *a0tmp;
  obj->song->setAlbum(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getAlbumPartId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getAlbumPartId();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setAlbumPartId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setAlbumPartId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getAlbumPart) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::AlbumPart* result =  obj->song->getAlbumPart();

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = AlbumPart::NewInstance();
    AlbumPart* r = Nan::ObjectWrap::Unwrap<AlbumPart>(instance);
    r->setNwcpValue(result, false);

    info.GetReturnValue().Set(instance);
  }
}

NAN_GETTER(Song::getAlbumPartOnce) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::AlbumPart* result =  obj->song->getAlbumPartOnce();

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = AlbumPart::NewInstance();
    AlbumPart* r = Nan::ObjectWrap::Unwrap<AlbumPart>(instance);
    r->setNwcpValue(result, false);

    info.GetReturnValue().Set(instance);
  }
}

NAN_SETTER(Song::setAlbumPart) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::AlbumPart* a0tmp(Nan::ObjectWrap::Unwrap<AlbumPart>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::AlbumPart& a0 = *a0tmp;
  obj->song->setAlbumPart(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getMusicVideoId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const int result =  obj->song->getMusicVideoId();

  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}

NAN_SETTER(Song::setMusicVideoId) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  int a0(value->IntegerValue());
  obj->song->setMusicVideoId(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getMusicVideo) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::MusicVideo* result =  obj->song->getMusicVideo();

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = MusicVideo::NewInstance();
    MusicVideo* r = Nan::ObjectWrap::Unwrap<MusicVideo>(instance);
    r->setNwcpValue(result, false);

    info.GetReturnValue().Set(instance);
  }
}

NAN_GETTER(Song::getMusicVideoOnce) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::MusicVideo* result =  obj->song->getMusicVideoOnce();

  if (result == NULL) {
    info.GetReturnValue().SetNull();
  } else {
    v8::Local<v8::Object> instance = MusicVideo::NewInstance();
    MusicVideo* r = Nan::ObjectWrap::Unwrap<MusicVideo>(instance);
    r->setNwcpValue(result, false);

    info.GetReturnValue().Set(instance);
  }
}

NAN_SETTER(Song::setMusicVideo) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  dogatech::soulsifter::MusicVideo* a0tmp(Nan::ObjectWrap::Unwrap<MusicVideo>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::MusicVideo& a0 = *a0tmp;
  obj->song->setMusicVideo(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getStyleIds) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const std::vector<int> result =  obj->song->getStyleIds();

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(Nan::New<v8::Number>(i), Nan::New<v8::Integer>(result[i]));
  }
  info.GetReturnValue().Set(a);
}

NAN_SETTER(Song::setStyleIds) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->IntegerValue());
    a0.push_back(x);
  }
  obj->song->setStyleIds(a0);

  info.GetReturnValue().SetUndefined();
}

NAN_GETTER(Song::getStyles) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  const std::vector<dogatech::soulsifter::Style*> result =  obj->song->getStyles();

  v8::Local<v8::Array> a = Nan::New<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = Style::NewInstance();
    Style* r = Nan::ObjectWrap::Unwrap<Style>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(Nan::New<v8::Number>(i), instance);
  }
  info.GetReturnValue().Set(a);
}

NAN_SETTER(Song::setStyles) {
  Song* obj = Nan::ObjectWrap::Unwrap<Song>(info.Holder());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::Style* x(Nan::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->song->setStyles(a0);

  info.GetReturnValue().SetUndefined();
}

