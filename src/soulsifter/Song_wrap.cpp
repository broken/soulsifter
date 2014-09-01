#include <iostream>
#include <node.h>
#include <nan.h>
#include "Song.h"
#include "Song_wrap.h"

v8::Persistent<v8::Function> Song::constructor;

Song::Song() : ObjectWrap(), song(new dogatech::soulsifter::Song()) {};
Song::Song(dogatech::soulsifter::Song* o) : ObjectWrap(), song(o) {};
Song::~Song() { delete song; };

NAN_METHOD(Song::New) {
  NanScope();

  Song* obj = new Song();
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}


NAN_METHOD(Song::clear) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->clear();

  NanReturnUndefined();
}

NAN_METHOD(Song::findById) {
  NanScope();

  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findById(args[0]->Uint32Value());
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  NanReturnValue(instance);
}

NAN_METHOD(Song::findByFilepath) {
  NanScope();

  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findByFilepath(*v8::String::Utf8Value(args[0]->ToString()));
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  NanReturnValue(instance);
}

NAN_METHOD(Song::findByRESongId) {
  NanScope();

  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findByRESongId(args[0]->Uint32Value());
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  NanReturnValue(instance);
}

NAN_METHOD(Song::sync) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  bool result =  obj->song->sync();

  NanReturnValue(NanNew<v8::Boolean>(result));
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

NAN_METHOD(Song::reAlbum) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->reAlbum();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::getDateAddedString) {
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

NAN_METHOD(Song::getId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Song::setId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setId(args[0]->Uint32Value());

  NanReturnUndefined();
}

NAN_METHOD(Song::getArtist) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getArtist();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setArtist) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setArtist(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getTrack) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getTrack();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setTrack) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setTrack(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getTitle) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getTitle();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setTitle) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setTitle(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getRemixer) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getRemixer();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setRemixer) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setRemixer(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getFeaturing) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getFeaturing();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setFeaturing) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setFeaturing(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getFilepath) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getFilepath();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setFilepath) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setFilepath(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getRating) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getRating();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Song::setRating) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setRating(args[0]->Uint32Value());

  NanReturnUndefined();
}

NAN_METHOD(Song::getDateAdded) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const time_t result =  obj->song->getDateAdded();

  NanReturnValue(NanNew<v8::Number>(result* 1000));
}

NAN_METHOD(Song::setDateAdded) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setDateAdded(args[0]->Uint32Value() / 1000);

  NanReturnUndefined();
}

NAN_METHOD(Song::getBpm) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getBpm();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setBpm) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setBpm(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::addTonicKey) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->addTonicKey(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::removeTonicKey) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->removeTonicKey(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getComments) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getComments();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setComments) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setComments(*v8::String::Utf8Value(args[0]->ToString()));

  NanReturnUndefined();
}

NAN_METHOD(Song::getTrashed) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const bool result =  obj->song->getTrashed();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(Song::setTrashed) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setTrashed(args[0]->BooleanValue());

  NanReturnUndefined();
}

NAN_METHOD(Song::getLowQuality) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const bool result =  obj->song->getLowQuality();

  NanReturnValue(NanNew<v8::Boolean>(result));
}

NAN_METHOD(Song::setLowQuality) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setLowQuality(args[0]->BooleanValue());

  NanReturnUndefined();
}

NAN_METHOD(Song::getRESongId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getRESongId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Song::setRESongId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setRESongId(args[0]->Uint32Value());

  NanReturnUndefined();
}

NAN_METHOD(Song::getAlbumId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getAlbumId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Song::setAlbumId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setAlbumId(args[0]->Uint32Value());

  NanReturnUndefined();
}

NAN_METHOD(Song::getAlbumPartId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getAlbumPartId();

  NanReturnValue(NanNew<v8::Number>(result));
}

NAN_METHOD(Song::setAlbumPartId) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setAlbumPartId(args[0]->Uint32Value());

  NanReturnUndefined();
}

NAN_METHOD(Song::addStyleById) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->addStyleById(args[0]->Uint32Value());

  NanReturnUndefined();
}

NAN_METHOD(Song::removeStyleById) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->removeStyleById(args[0]->Uint32Value());

  NanReturnUndefined();
}

void Song::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = NanNew<v8::FunctionTemplate>(New);
  tpl->SetClassName(NanNew<v8::String>("Song"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  tpl->Set(NanNew<v8::String>("findById"),
      NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  tpl->Set(NanNew<v8::String>("findByFilepath"),
      NanNew<v8::FunctionTemplate>(findByFilepath)->GetFunction());
  tpl->Set(NanNew<v8::String>("findByRESongId"),
      NanNew<v8::FunctionTemplate>(findByRESongId)->GetFunction());

  // Prototype
  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::String>("clear prop?"));
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::String>("sync prop?"));
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::String>("update prop?"));
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::String>("save prop?"));
  NanSetPrototypeTemplate(tpl, "reAlbum", NanNew<v8::String>("reAlbum prop?"));
  NanSetPrototypeTemplate(tpl, "getDateAddedString", NanNew<v8::String>("getDateAddedString prop?"));
  NanSetPrototypeTemplate(tpl, "setDateAddedToNow", NanNew<v8::String>("setDateAddedToNow prop?"));
  NanSetPrototypeTemplate(tpl, "getId", NanNew<v8::String>("getId prop?"));
  NanSetPrototypeTemplate(tpl, "setId", NanNew<v8::String>("setId prop?"));
  NanSetPrototypeTemplate(tpl, "getArtist", NanNew<v8::String>("getArtist prop?"));
  NanSetPrototypeTemplate(tpl, "setArtist", NanNew<v8::String>("setArtist prop?"));
  NanSetPrototypeTemplate(tpl, "getTrack", NanNew<v8::String>("getTrack prop?"));
  NanSetPrototypeTemplate(tpl, "setTrack", NanNew<v8::String>("setTrack prop?"));
  NanSetPrototypeTemplate(tpl, "getTitle", NanNew<v8::String>("getTitle prop?"));
  NanSetPrototypeTemplate(tpl, "setTitle", NanNew<v8::String>("setTitle prop?"));
  NanSetPrototypeTemplate(tpl, "getRemixer", NanNew<v8::String>("getRemixer prop?"));
  NanSetPrototypeTemplate(tpl, "setRemixer", NanNew<v8::String>("setRemixer prop?"));
  NanSetPrototypeTemplate(tpl, "getFeaturing", NanNew<v8::String>("getFeaturing prop?"));
  NanSetPrototypeTemplate(tpl, "setFeaturing", NanNew<v8::String>("setFeaturing prop?"));
  NanSetPrototypeTemplate(tpl, "getFilepath", NanNew<v8::String>("getFilepath prop?"));
  NanSetPrototypeTemplate(tpl, "setFilepath", NanNew<v8::String>("setFilepath prop?"));
  NanSetPrototypeTemplate(tpl, "getRating", NanNew<v8::String>("getRating prop?"));
  NanSetPrototypeTemplate(tpl, "setRating", NanNew<v8::String>("setRating prop?"));
  NanSetPrototypeTemplate(tpl, "getDateAdded", NanNew<v8::String>("getDateAdded prop?"));
  NanSetPrototypeTemplate(tpl, "setDateAdded", NanNew<v8::String>("setDateAdded prop?"));
  NanSetPrototypeTemplate(tpl, "getBpm", NanNew<v8::String>("getBpm prop?"));
  NanSetPrototypeTemplate(tpl, "setBpm", NanNew<v8::String>("setBpm prop?"));
  NanSetPrototypeTemplate(tpl, "addTonicKey", NanNew<v8::String>("addTonicKey prop?"));
  NanSetPrototypeTemplate(tpl, "removeTonicKey", NanNew<v8::String>("removeTonicKey prop?"));
  NanSetPrototypeTemplate(tpl, "getComments", NanNew<v8::String>("getComments prop?"));
  NanSetPrototypeTemplate(tpl, "setComments", NanNew<v8::String>("setComments prop?"));
  NanSetPrototypeTemplate(tpl, "getTrashed", NanNew<v8::String>("getTrashed prop?"));
  NanSetPrototypeTemplate(tpl, "setTrashed", NanNew<v8::String>("setTrashed prop?"));
  NanSetPrototypeTemplate(tpl, "getLowQuality", NanNew<v8::String>("getLowQuality prop?"));
  NanSetPrototypeTemplate(tpl, "setLowQuality", NanNew<v8::String>("setLowQuality prop?"));
  NanSetPrototypeTemplate(tpl, "getRESongId", NanNew<v8::String>("getRESongId prop?"));
  NanSetPrototypeTemplate(tpl, "setRESongId", NanNew<v8::String>("setRESongId prop?"));
  NanSetPrototypeTemplate(tpl, "getAlbumId", NanNew<v8::String>("getAlbumId prop?"));
  NanSetPrototypeTemplate(tpl, "setAlbumId", NanNew<v8::String>("setAlbumId prop?"));
  NanSetPrototypeTemplate(tpl, "getAlbumPartId", NanNew<v8::String>("getAlbumPartId prop?"));
  NanSetPrototypeTemplate(tpl, "setAlbumPartId", NanNew<v8::String>("setAlbumPartId prop?"));
  NanSetPrototypeTemplate(tpl, "addStyleById", NanNew<v8::String>("addStyleById prop?"));
  NanSetPrototypeTemplate(tpl, "removeStyleById", NanNew<v8::String>("removeStyleById prop?"));

  NanAssignPersistent<v8::Function>(constructor, tpl->GetFunction());
  exports->Set(NanNew<v8::String>("Song"), tpl->GetFunction());
}
