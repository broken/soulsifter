#ifndef AudioAnalyzer_wrap_h
#define AudioAnalyzer_wrap_h

#include <node.h>
#include <nan.h>
#include "AudioAnalyzer.h"

class AudioAnalyzer : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::AudioAnalyzer* v) { audioAnalyzer = v; }
  dogatech::soulsifter::AudioAnalyzer* getNwcpValue() const { return audioAnalyzer; }

 private:
  AudioAnalyzer();
  explicit AudioAnalyzer(dogatech::soulsifter::AudioAnalyzer* audioAnalyzer);
  ~AudioAnalyzer();

  static NAN_METHOD(New);

  static NAN_METHOD(analyzeBpms);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::AudioAnalyzer* audioAnalyzer;
};

#endif
