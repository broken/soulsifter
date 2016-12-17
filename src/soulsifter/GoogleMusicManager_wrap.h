#ifndef GoogleMusicManager_wrap_h
#define GoogleMusicManager_wrap_h

#include <node.h>
#include <nan.h>
#include "GoogleMusicManager.h"

class GoogleMusicManager : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::GoogleMusicManager* v, bool own);
  dogatech::soulsifter::GoogleMusicManager* getNwcpValue() const { return googlemusicmanager; }

 private:
  GoogleMusicManager();
  explicit GoogleMusicManager(dogatech::soulsifter::GoogleMusicManager* googlemusicmanager);
  ~GoogleMusicManager();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void login(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void logout(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void isAuthenticated(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static Nan::Persistent<v8::Function> constructor;
  dogatech::soulsifter::GoogleMusicManager* googlemusicmanager;
  bool ownWrappedObject;
};

#endif
