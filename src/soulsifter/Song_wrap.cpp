#include <iostream>
#include <node.h>
#include <nan.h>
#include "Song_wrap.h"
#include "Album.h"
#include "AlbumPart.h"
#include "AlbumPart_wrap.h"
#include "Album_wrap.h"
#include "ResultSetIterator.h"
#include "Song.h"
#include "Song_wrap.h"
#include "Style.h"
#include "Style_wrap.h"

v8::Persistent<v8::Function> Song::constructor;

Song::Song() : ObjectWrap(), song(NULL), ownWrappedObject(true) {};
Song::Song(dogatech::soulsifter::Song* o) : ObjectWrap(), song(o), ownWrappedObject(true) {};
Song::~Song() { if (ownWrappedObject) delete song; };

void Song::setNwcpValue(dogatech::soulsifter::Song* v, bool own) {
  if (ownWrappedObject)
    delete song;
  song = v;
  ownWrappedObject = own;
}

NAN_METHOD(Song::New) {
  NanScope();

  dogatech::soulsifter::Song* wrappedObj = NULL;
  if (args.Length()) {
    dogatech::soulsifter::Song* xtmp(node::ObjectWrap::Unwrap<Song>(args[0]->ToObject())->getNwcpValue());
    dogatech::soulsifter::Song& x = *xtmp;
    wrappedObj = new dogatech::soulsifter::Song(x);
  } else {
    wrappedObj = new dogatech::soulsifter::Song();
  }

  Song* obj = new Song(wrappedObj);
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

v8::Local<v8::Object> Song::NewInstance() {
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  return instance;
}

void Song::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("Song"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByFilepath", NanNew<v8::FunctionTemplate>(findByFilepath)->GetFunction());
  NanSetTemplate(tpl, "findByRESongId", NanNew<v8::FunctionTemplate>(findByRESongId)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  // Unable to process createRESongFromSong
  NanSetPrototypeTemplate(tpl, "reAlbum", NanNew<v8::FunctionTemplate>(reAlbum)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("dateAddedString"), getDateAddedString);
  NanSetPrototypeTemplate(tpl, "setDateAddedToNow", NanNew<v8::FunctionTemplate>(setDateAddedToNow)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("id"), getId, setId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("artist"), getArtist, setArtist);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("track"), getTrack, setTrack);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("title"), getTitle, setTitle);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("remixer"), getRemixer, setRemixer);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("featuring"), getFeaturing, setFeaturing);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("filepath"), getFilepath, setFilepath);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("rating"), getRating, setRating);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("dateAdded"), getDateAdded, setDateAdded);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("bpm"), getBpm, setBpm);
  // Unable to process getTonicKeys
  // Unable to process setTonicKeys
  NanSetPrototypeTemplate(tpl, "addTonicKey", NanNew<v8::FunctionTemplate>(addTonicKey)->GetFunction());
  NanSetPrototypeTemplate(tpl, "removeTonicKey", NanNew<v8::FunctionTemplate>(removeTonicKey)->GetFunction());
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("tonicKey"), getTonicKey, setTonicKey);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("energy"), getEnergy, setEnergy);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("comments"), getComments, setComments);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("trashed"), getTrashed, setTrashed);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("lowQuality"), getLowQuality, setLowQuality);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("rESongId"), getRESongId, setRESongId);
  // Unable to process getRESong
  // Unable to process setRESong
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("albumId"), getAlbumId, setAlbumId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("album"), getAlbum, setAlbum);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("albumPartId"), getAlbumPartId, setAlbumPartId);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("albumPart"), getAlbumPart, setAlbumPart);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("styleIds"), getStyleIds, setStyleIds);
  tpl->InstanceTemplate()->SetAccessor(NanNew<v8::String>("styles"), getStyles, setStyles);

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("Song"), tpl->GetFunction());
}

NAN_METHOD(Song::clear) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->clear();

  NanReturnUndefined();
}

NAN_METHOD(Song::findById) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Song* result =
      dogatech::soulsifter::Song::findById(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Song::NewInstance();
  Song* r = ObjectWrap::Unwrap<Song>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Song::findByFilepath) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  dogatech::soulsifter::Song* result =
      dogatech::soulsifter::Song::findByFilepath(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Song::NewInstance();
  Song* r = ObjectWrap::Unwrap<Song>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Song::findByRESongId) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Song* result =
      dogatech::soulsifter::Song::findByRESongId(a0);

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Song::NewInstance();
  Song* r = ObjectWrap::Unwrap<Song>(instance);
  r->setNwcpValue(result, true);

  NanReturnValue(instance);
}

NAN_METHOD(Song::findAll) {
  NanScope();

  dogatech::ResultSetIterator<dogatech::soulsifter::Song>* result =
      dogatech::soulsifter::Song::findAll();

  vector<dogatech::soulsifter::Song*>* v = result->toVector();
  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) v->size());
  for (int i = 0; i < (int) v->size(); i++) {
    v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
    v8::Local<v8::Object> instance = cons->NewInstance();
    Song* o = ObjectWrap::Unwrap<Song>(instance);
    o->song = (*v)[i];
    a->Set(NanNew<v8::Number>(i), instance);
  }
  delete v;
  NanReturnValue(a);
}

NAN_METHOD(Song::update) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int result =  obj->song->update();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Song::save) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int result =  obj->song->save();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Song::sync) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  bool result =  obj->song->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(Song::reAlbum) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->reAlbum();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_GETTER(Song::getDateAddedString) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getDateAddedString();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setDateAddedToNow) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setDateAddedToNow();

  NanReturnUndefined();
}

NAN_GETTER(Song::getId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Song::setId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(value->Uint32Value());
  obj->song->setId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getArtist) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getArtist();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setArtist) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setArtist(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getTrack) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getTrack();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setTrack) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setTrack(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getTitle) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getTitle();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setTitle) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setTitle(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getRemixer) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getRemixer();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setRemixer) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setRemixer(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getFeaturing) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getFeaturing();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setFeaturing) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setFeaturing(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getFilepath) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getFilepath();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setFilepath) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setFilepath(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getRating) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getRating();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Song::setRating) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(value->Uint32Value());
  obj->song->setRating(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getDateAdded) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const time_t result =  obj->song->getDateAdded();

  NanReturnValue(NanNew<v8::Number>(result * 1000));
}

NAN_SETTER(Song::setDateAdded) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  time_t a0(value->Uint32Value() / 1000);
  obj->song->setDateAdded(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getBpm) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getBpm();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setBpm) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setBpm(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::addTonicKey) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->addTonicKey(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::removeTonicKey) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->removeTonicKey(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getTonicKey) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getTonicKey();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setTonicKey) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setTonicKey(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getEnergy) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getEnergy();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Song::setEnergy) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(value->Uint32Value());
  obj->song->setEnergy(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getComments) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getComments();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_SETTER(Song::setComments) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(value->ToString()));
  obj->song->setComments(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getTrashed) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const bool result =  obj->song->getTrashed();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_SETTER(Song::setTrashed) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  bool a0(value->BooleanValue());
  obj->song->setTrashed(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getLowQuality) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const bool result =  obj->song->getLowQuality();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_SETTER(Song::setLowQuality) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  bool a0(value->BooleanValue());
  obj->song->setLowQuality(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getRESongId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getRESongId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Song::setRESongId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(value->Uint32Value());
  obj->song->setRESongId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getAlbumId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getAlbumId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Song::setAlbumId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(value->Uint32Value());
  obj->song->setAlbumId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getAlbum) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  dogatech::soulsifter::Album* result =  obj->song->getAlbum();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = Album::NewInstance();
  Album* r = ObjectWrap::Unwrap<Album>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(Song::setAlbum) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  dogatech::soulsifter::Album* a0tmp(node::ObjectWrap::Unwrap<Album>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::Album& a0 = *a0tmp;
  obj->song->setAlbum(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getAlbumPartId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getAlbumPartId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_SETTER(Song::setAlbumPartId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(value->Uint32Value());
  obj->song->setAlbumPartId(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getAlbumPart) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  dogatech::soulsifter::AlbumPart* result =  obj->song->getAlbumPart();

  if (result == NULL) NanReturnUndefined();
  v8::Local<v8::Object> instance = AlbumPart::NewInstance();
  AlbumPart* r = ObjectWrap::Unwrap<AlbumPart>(instance);
  r->setNwcpValue(result, false);

  NanReturnValue(instance);
}

NAN_SETTER(Song::setAlbumPart) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  dogatech::soulsifter::AlbumPart* a0tmp(node::ObjectWrap::Unwrap<AlbumPart>(value->ToObject())->getNwcpValue());
  dogatech::soulsifter::AlbumPart& a0 = *a0tmp;
  obj->song->setAlbumPart(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getStyleIds) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const std::vector<int> result =  obj->song->getStyleIds();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    a->Set(NanNew<v8::Number>(i), NanNew<v8::Number>(result[i]));
  }
  NanReturnValue(a);
}

NAN_SETTER(Song::setStyleIds) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<int> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    int x(tmp->Uint32Value());
    a0.push_back(x);
  }
  obj->song->setStyleIds(a0);

  NanReturnUndefined();
}

NAN_GETTER(Song::getStyles) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const std::vector<dogatech::soulsifter::Style*> result =  obj->song->getStyles();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = Style::NewInstance();
    Style* r = ObjectWrap::Unwrap<Style>(instance);
    r->setNwcpValue((result)[i], false);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_SETTER(Song::setStyles) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  v8::Local<v8::Array> a0Array = v8::Local<v8::Array>::Cast(value);
  std::vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < a0Array->Length(); ++i) {
    v8::Local<v8::Value> tmp = a0Array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->song->setStyles(a0);

  NanReturnUndefined();
}

