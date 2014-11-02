#ifndef AudioAnalyzer_wrap_h
#define AudioAnalyzer_wrap_h

#include <node.h>
#include <nan.h>
#include "AudioAnalyzer.h"

class AudioAnalyzer : public node::ObjectWrap {
 public:
  static void Init(v8::Handle<v8::Object> exports);
  static v8::Local<v8::Object> NewInstance();

  void setNwcpValue(dogatech::soulsifter::AudioAnalyzer* v, bool own);
  dogatech::soulsifter::AudioAnalyzer* getNwcpValue() const { return audioanalyzer; }

 private:
  AudioAnalyzer();
  explicit AudioAnalyzer(dogatech::soulsifter::AudioAnalyzer* audioanalyzer);
  ~AudioAnalyzer();

  static NAN_METHOD(New);

  // Unable to process analyzeKey
  // Unable to process analyzeBpm
  static NAN_METHOD(analyzeBpms);

  static v8::Persistent<v8::Function> constructor;
  dogatech::soulsifter::AudioAnalyzer* audioanalyzer;
  bool ownWrappedObject;
};

#endif
