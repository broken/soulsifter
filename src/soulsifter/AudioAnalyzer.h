//
//  AudioAnalyzer.h
//  soul-sifter
//
//  Created by Robby Neale on 11/15/13.
//
//

#ifndef soul_sifter_AudioAnalyzer_h
#define soul_sifter_AudioAnalyzer_h

#include <string>
#include <utility>
#include <vector>

namespace dogatech {
  namespace soulsifter {
    
    class Song;
    
    struct Bpms {
      float candidate[3];
    };
    
    struct Keys {
      std::vector<std::pair<std::string, float> > candidate;
      
      template <class TI>
      Keys(TI first, TI second) : candidate(first, second) { }
      Keys() { }
    };
    
    class AudioAnalyzer {
    public:
      static const Keys* analyzeKey(Song* song);
      
      static const Bpms* analyzeBpm(Song* song);
      static void analyzeBpms();
    };
    
  }
}

#endif
