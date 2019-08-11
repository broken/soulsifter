#ifndef GoogleMusicService_wrap_h
#define GoogleMusicService_wrap_h

#include <node.h>
#include <nan.h>
#include "GoogleMusicService.h"

class GoogleMusicService : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::GoogleMusicService* v, bool own);
  dogatech::soulsifter::GoogleMusicService* getNwcpValue() const { return googlemusicservice; }

 private:
  GoogleMusicService();
  explicit GoogleMusicService(dogatech::soulsifter::GoogleMusicService* googlemusicservice);
  ~GoogleMusicService();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void syncGoogleMusicPlaylists(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static Nan::Persistent<v8::Function> constructor;
  dogatech::soulsifter::GoogleMusicService* googlemusicservice;
  bool ownWrappedObject;
};

#endif
