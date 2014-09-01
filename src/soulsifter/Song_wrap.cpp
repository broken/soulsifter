#include <iostream>
#include <node.h>
#include "Song.h"
#include "Song_wrap.h"

using namespace v8;

Persistent<Function> Song::constructor;

Song::Song() : ObjectWrap(), song(new dogatech::soulsifter::Song()) {};
Song::Song(dogatech::soulsifter::Song* o) : ObjectWrap(), song(o) {};
Song::~Song() { delete song; };

Handle<Value> Song::New(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = new Song();
  obj->Wrap(args.This());

  return args.This();
}


Handle<Value> Song::clear(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->clear();

  return Undefined();
}

Handle<Value> Song::findById(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findById(args[0]->Uint32Value());
  const unsigned argc = 0;
  Handle<Value> argv[argc] = { };
  Local<Object> instance = constructor->NewInstance(argc, argv);

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  return scope.Close(instance);
}

Handle<Value> Song::findByFilepath(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findByFilepath(*v8::String::Utf8Value(args[0]->ToString()));
  const unsigned argc = 0;
  Handle<Value> argv[argc] = { };
  Local<Object> instance = constructor->NewInstance(argc, argv);

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  return scope.Close(instance);
}

Handle<Value> Song::findByRESongId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findByRESongId(args[0]->Uint32Value());
  const unsigned argc = 0;
  Handle<Value> argv[argc] = { };
  Local<Object> instance = constructor->NewInstance(argc, argv);

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  return scope.Close(instance);
}

Handle<Value> Song::sync(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  bool result =  obj->song->sync();

  return scope.Close(Boolean::New(result));
}

Handle<Value> Song::update(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int result =  obj->song->update();

  return scope.Close(Number::New(result));
}

Handle<Value> Song::save(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int result =  obj->song->save();

  return scope.Close(Number::New(result));
}

Handle<Value> Song::reAlbum(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->reAlbum();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::getDateAddedString(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getDateAddedString();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setDateAddedToNow(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setDateAddedToNow();

  return Undefined();
}

Handle<Value> Song::getId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getId();

  return scope.Close(Number::New(result));
}

Handle<Value> Song::setId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setId(args[0]->Uint32Value());

  return Undefined();
}

Handle<Value> Song::getArtist(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getArtist();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setArtist(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setArtist(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getTrack(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getTrack();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setTrack(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setTrack(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getTitle(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getTitle();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setTitle(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setTitle(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getRemixer(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getRemixer();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setRemixer(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setRemixer(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getFeaturing(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getFeaturing();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setFeaturing(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setFeaturing(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getFilepath(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getFilepath();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setFilepath(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setFilepath(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getRating(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getRating();

  return scope.Close(Number::New(result));
}

Handle<Value> Song::setRating(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setRating(args[0]->Uint32Value());

  return Undefined();
}

Handle<Value> Song::getDateAdded(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const time_t result =  obj->song->getDateAdded();

  return scope.Close(Number::New(result* 1000));
}

Handle<Value> Song::setDateAdded(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setDateAdded(args[0]->Uint32Value() / 1000);

  return Undefined();
}

Handle<Value> Song::getBpm(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getBpm();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setBpm(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setBpm(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::addTonicKey(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->addTonicKey(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::removeTonicKey(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->removeTonicKey(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getComments(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string& result =  obj->song->getComments();

  return scope.Close(String::New(result.c_str(), result.length()));
}

Handle<Value> Song::setComments(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setComments(*v8::String::Utf8Value(args[0]->ToString()));

  return Undefined();
}

Handle<Value> Song::getTrashed(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const bool result =  obj->song->getTrashed();

  return scope.Close(Boolean::New(result));
}

Handle<Value> Song::setTrashed(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setTrashed(args[0]->BooleanValue());

  return Undefined();
}

Handle<Value> Song::getLowQuality(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const bool result =  obj->song->getLowQuality();

  return scope.Close(Boolean::New(result));
}

Handle<Value> Song::setLowQuality(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setLowQuality(args[0]->BooleanValue());

  return Undefined();
}

Handle<Value> Song::getRESongId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getRESongId();

  return scope.Close(Number::New(result));
}

Handle<Value> Song::setRESongId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setRESongId(args[0]->Uint32Value());

  return Undefined();
}

Handle<Value> Song::getAlbumId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getAlbumId();

  return scope.Close(Number::New(result));
}

Handle<Value> Song::setAlbumId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setAlbumId(args[0]->Uint32Value());

  return Undefined();
}

Handle<Value> Song::getAlbumPartId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const int result =  obj->song->getAlbumPartId();

  return scope.Close(Number::New(result));
}

Handle<Value> Song::setAlbumPartId(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->setAlbumPartId(args[0]->Uint32Value());

  return Undefined();
}

Handle<Value> Song::addStyleById(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->addStyleById(args[0]->Uint32Value());

  return Undefined();
}

Handle<Value> Song::removeStyleById(const Arguments& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  obj->song->removeStyleById(args[0]->Uint32Value());

  return Undefined();
}

void Song::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("Song"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  tpl->Set(String::NewSymbol("findById"),
      FunctionTemplate::New(findById)->GetFunction());
  tpl->Set(String::NewSymbol("findByFilepath"),
      FunctionTemplate::New(findByFilepath)->GetFunction());
  tpl->Set(String::NewSymbol("findByRESongId"),
      FunctionTemplate::New(findByRESongId)->GetFunction());

  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("clear"),
      FunctionTemplate::New(clear)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("sync"),
      FunctionTemplate::New(sync)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("update"),
      FunctionTemplate::New(update)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("save"),
      FunctionTemplate::New(save)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("reAlbum"),
      FunctionTemplate::New(reAlbum)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getDateAddedString"),
      FunctionTemplate::New(getDateAddedString)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setDateAddedToNow"),
      FunctionTemplate::New(setDateAddedToNow)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getId"),
      FunctionTemplate::New(getId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setId"),
      FunctionTemplate::New(setId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getArtist"),
      FunctionTemplate::New(getArtist)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setArtist"),
      FunctionTemplate::New(setArtist)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getTrack"),
      FunctionTemplate::New(getTrack)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setTrack"),
      FunctionTemplate::New(setTrack)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getTitle"),
      FunctionTemplate::New(getTitle)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setTitle"),
      FunctionTemplate::New(setTitle)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getRemixer"),
      FunctionTemplate::New(getRemixer)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setRemixer"),
      FunctionTemplate::New(setRemixer)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getFeaturing"),
      FunctionTemplate::New(getFeaturing)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setFeaturing"),
      FunctionTemplate::New(setFeaturing)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getFilepath"),
      FunctionTemplate::New(getFilepath)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setFilepath"),
      FunctionTemplate::New(setFilepath)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getRating"),
      FunctionTemplate::New(getRating)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setRating"),
      FunctionTemplate::New(setRating)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getDateAdded"),
      FunctionTemplate::New(getDateAdded)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setDateAdded"),
      FunctionTemplate::New(setDateAdded)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getBpm"),
      FunctionTemplate::New(getBpm)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setBpm"),
      FunctionTemplate::New(setBpm)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("addTonicKey"),
      FunctionTemplate::New(addTonicKey)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("removeTonicKey"),
      FunctionTemplate::New(removeTonicKey)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getComments"),
      FunctionTemplate::New(getComments)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setComments"),
      FunctionTemplate::New(setComments)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getTrashed"),
      FunctionTemplate::New(getTrashed)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setTrashed"),
      FunctionTemplate::New(setTrashed)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getLowQuality"),
      FunctionTemplate::New(getLowQuality)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setLowQuality"),
      FunctionTemplate::New(setLowQuality)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getRESongId"),
      FunctionTemplate::New(getRESongId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setRESongId"),
      FunctionTemplate::New(setRESongId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getAlbumId"),
      FunctionTemplate::New(getAlbumId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setAlbumId"),
      FunctionTemplate::New(setAlbumId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("getAlbumPartId"),
      FunctionTemplate::New(getAlbumPartId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("setAlbumPartId"),
      FunctionTemplate::New(setAlbumPartId)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("addStyleById"),
      FunctionTemplate::New(addStyleById)->GetFunction());
  tpl->PrototypeTemplate()->Set(String::NewSymbol("removeStyleById"),
      FunctionTemplate::New(removeStyleById)->GetFunction());

  constructor = Persistent<Function>::New(isolate, tpl->GetFunction());
  exports->Set(String::NewSymbol("Song"), constructor);
}
