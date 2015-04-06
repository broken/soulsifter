//
// This was not auto-generated unlike the others.

#ifndef SoulSifterSettings_wrap_h
#define SoulSifterSettings_wrap_h

#include <node.h>
#include <nan.h>
#include "SoulSifterSettings.h"

class SoulSifterSettings : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::SoulSifterSettings* v, bool own);
  dogatech::soulsifter::SoulSifterSettings* getNwcpValue() const { return soulsiftersettings; }

 private:
  SoulSifterSettings();
  explicit SoulSifterSettings(dogatech::soulsifter::SoulSifterSettings* soulsiftersettings);
  ~SoulSifterSettings();

  static NAN_METHOD(New);

  static NAN_METHOD(getString);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::SoulSifterSettings* soulsiftersettings;
  bool ownWrappedObject;
};

#endif
