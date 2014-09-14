#include <iostream>
#include <node.h>
#include <nan.h>
#include "Song.h"
#include "Song_wrap.h"
#include "Style.h"
#include "Style_wrap.h"

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

  NanSetTemplate(tpl, "findById", NanNew<v8::FunctionTemplate>(findById)->GetFunction());
  NanSetTemplate(tpl, "findByFilepath", NanNew<v8::FunctionTemplate>(findByFilepath)->GetFunction());
  NanSetTemplate(tpl, "findByRESongId", NanNew<v8::FunctionTemplate>(findByRESongId)->GetFunction());
  NanSetTemplate(tpl, "findAll", NanNew<v8::FunctionTemplate>(findAll)->GetFunction());

  // Prototype
  NanSetPrototypeTemplate(tpl, "clear", NanNew<v8::FunctionTemplate>(clear)->GetFunction());
  NanSetPrototypeTemplate(tpl, "sync", NanNew<v8::FunctionTemplate>(sync)->GetFunction());
  NanSetPrototypeTemplate(tpl, "update", NanNew<v8::FunctionTemplate>(update)->GetFunction());
  NanSetPrototypeTemplate(tpl, "save", NanNew<v8::FunctionTemplate>(save)->GetFunction());
  NanSetPrototypeTemplate(tpl, "reAlbum", NanNew<v8::FunctionTemplate>(reAlbum)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getDateAddedString", NanNew<v8::FunctionTemplate>(getDateAddedString)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setDateAddedToNow", NanNew<v8::FunctionTemplate>(setDateAddedToNow)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getId", NanNew<v8::FunctionTemplate>(getId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setId", NanNew<v8::FunctionTemplate>(setId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getArtist", NanNew<v8::FunctionTemplate>(getArtist)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setArtist", NanNew<v8::FunctionTemplate>(setArtist)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getTrack", NanNew<v8::FunctionTemplate>(getTrack)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setTrack", NanNew<v8::FunctionTemplate>(setTrack)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getTitle", NanNew<v8::FunctionTemplate>(getTitle)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setTitle", NanNew<v8::FunctionTemplate>(setTitle)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getRemixer", NanNew<v8::FunctionTemplate>(getRemixer)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setRemixer", NanNew<v8::FunctionTemplate>(setRemixer)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getFeaturing", NanNew<v8::FunctionTemplate>(getFeaturing)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setFeaturing", NanNew<v8::FunctionTemplate>(setFeaturing)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getFilepath", NanNew<v8::FunctionTemplate>(getFilepath)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setFilepath", NanNew<v8::FunctionTemplate>(setFilepath)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getRating", NanNew<v8::FunctionTemplate>(getRating)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setRating", NanNew<v8::FunctionTemplate>(setRating)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getDateAdded", NanNew<v8::FunctionTemplate>(getDateAdded)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setDateAdded", NanNew<v8::FunctionTemplate>(setDateAdded)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getBpm", NanNew<v8::FunctionTemplate>(getBpm)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setBpm", NanNew<v8::FunctionTemplate>(setBpm)->GetFunction());
  NanSetPrototypeTemplate(tpl, "addTonicKey", NanNew<v8::FunctionTemplate>(addTonicKey)->GetFunction());
  NanSetPrototypeTemplate(tpl, "removeTonicKey", NanNew<v8::FunctionTemplate>(removeTonicKey)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getComments", NanNew<v8::FunctionTemplate>(getComments)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setComments", NanNew<v8::FunctionTemplate>(setComments)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getTrashed", NanNew<v8::FunctionTemplate>(getTrashed)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setTrashed", NanNew<v8::FunctionTemplate>(setTrashed)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getLowQuality", NanNew<v8::FunctionTemplate>(getLowQuality)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setLowQuality", NanNew<v8::FunctionTemplate>(setLowQuality)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getRESongId", NanNew<v8::FunctionTemplate>(getRESongId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setRESongId", NanNew<v8::FunctionTemplate>(setRESongId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getAlbumId", NanNew<v8::FunctionTemplate>(getAlbumId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setAlbumId", NanNew<v8::FunctionTemplate>(setAlbumId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getAlbumPartId", NanNew<v8::FunctionTemplate>(getAlbumPartId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setAlbumPartId", NanNew<v8::FunctionTemplate>(setAlbumPartId)->GetFunction());
  NanSetPrototypeTemplate(tpl, "getStyles", NanNew<v8::FunctionTemplate>(getStyles)->GetFunction());
  NanSetPrototypeTemplate(tpl, "setStyles", NanNew<v8::FunctionTemplate>(setStyles)->GetFunction());
  NanSetPrototypeTemplate(tpl, "addStyleById", NanNew<v8::FunctionTemplate>(addStyleById)->GetFunction());
  NanSetPrototypeTemplate(tpl, "removeStyleById", NanNew<v8::FunctionTemplate>(removeStyleById)->GetFunction());

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
  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findById(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  NanReturnValue(instance);
}

NAN_METHOD(Song::findByFilepath) {
  NanScope();

  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findByFilepath(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

  NanReturnValue(instance);
}

NAN_METHOD(Song::findByRESongId) {
  NanScope();

  int a0(args[0]->Uint32Value());
  dogatech::soulsifter::Song* song =
      dogatech::soulsifter::Song::findByRESongId(a0);
  v8::Local<v8::Function> cons = NanNew<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();

  Song* obj = ObjectWrap::Unwrap<Song>(instance);
  obj->song = song;

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
  int a0(args[0]->Uint32Value());
  obj->song->setId(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getArtist) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getArtist();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setArtist) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->setArtist(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getTrack) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getTrack();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setTrack) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->setTrack(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getTitle) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getTitle();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setTitle) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->setTitle(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getRemixer) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getRemixer();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setRemixer) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->setRemixer(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getFeaturing) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getFeaturing();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setFeaturing) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->setFeaturing(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getFilepath) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getFilepath();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setFilepath) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->setFilepath(a0);

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
  int a0(args[0]->Uint32Value());
  obj->song->setRating(a0);

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
  time_t a0(args[0]->Uint32Value() / 1000);
  obj->song->setDateAdded(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getBpm) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getBpm();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setBpm) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
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

NAN_METHOD(Song::getComments) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const string result =  obj->song->getComments();

  NanReturnValue(NanNew<v8::String>(result.c_str(), result.length()));
}

NAN_METHOD(Song::setComments) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  string a0(*v8::String::Utf8Value(args[0]->ToString()));
  obj->song->setComments(a0);

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
  bool a0(args[0]->BooleanValue());
  obj->song->setTrashed(a0);

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
  bool a0(args[0]->BooleanValue());
  obj->song->setLowQuality(a0);

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
  int a0(args[0]->Uint32Value());
  obj->song->setRESongId(a0);

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
  int a0(args[0]->Uint32Value());
  obj->song->setAlbumId(a0);

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
  int a0(args[0]->Uint32Value());
  obj->song->setAlbumPartId(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::getStyles) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  const vector<dogatech::soulsifter::Style*> result =  obj->song->getStyles();

  v8::Handle<v8::Array> a = NanNew<v8::Array>((int) result.size());
  for (int i = 0; i < (int) result.size(); i++) {
    v8::Local<v8::Object> instance = Style::NewInstance();
    Style* o = ObjectWrap::Unwrap<Style>(instance);
    o->setNwcpValue((result)[i]);
    a->Set(NanNew<v8::Number>(i), instance);
  }
  NanReturnValue(a);
}

NAN_METHOD(Song::setStyles) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(args[0]);
  std::vector<dogatech::soulsifter::Style*> a0;
  for (int i = 0; i < array->Length(); ++i) {
    v8::Local<v8::Value> tmp = array->Get(i);
    dogatech::soulsifter::Style* x(node::ObjectWrap::Unwrap<Style>(tmp->ToObject())->getNwcpValue());
    a0.push_back(x);
  }
  obj->song->setStyles(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::addStyleById) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(args[0]->Uint32Value());
  obj->song->addStyleById(a0);

  NanReturnUndefined();
}

NAN_METHOD(Song::removeStyleById) {
  NanScope();

  Song* obj = ObjectWrap::Unwrap<Song>(args.This());
  int a0(args[0]->Uint32Value());
  obj->song->removeStyleById(a0);

  NanReturnUndefined();
}

