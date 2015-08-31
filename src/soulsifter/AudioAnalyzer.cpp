//
//  AudioAnalyzer.cpp
//  soul-sifter
//
//  Created by Robby Neale on 11/9/13.
//
//

#include "AudioAnalyzer.h"

#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <utility>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include "madlld.h"
#include "MiniBpm.h"
#include "SearchUtil.h"
#include "Song.h"

namespace dogatech {
  namespace soulsifter {
    
    namespace {
      bool keyPairCompare(std::pair<string, float> first, std::pair<string, float> second) {
        return first.second > second.second;
      }
    }
    
    const vector<double> AudioAnalyzer::analyzeBpm(Song *song) {
      cout << "analyze bpm" << endl;

      struct stat statBuffer;
      if (stat(song->getFilepath().c_str(), &statBuffer) != 0) {
        cerr << "File does not exist for song " << song->getId() << endl;
        vector<double> bpms;
        return bpms;
      }
      
      breakfastquay::MiniBPM miniBpm(44100);
      
      if (boost::algorithm::iends_with(song->getFilepath(), ".mp3")) {
        detectBpm(song->getFilepath().c_str(), boost::bind(&breakfastquay::MiniBPM::process, boost::ref(miniBpm), _1, _2));
      } else {
        cerr << "Unrecognizable file type when analyzing BPM for " << song->getFilepath() << endl;
        vector<double> bpms;
        return bpms;
      }
    
      char buffer[8];
      sprintf(buffer, "%.2f", miniBpm.estimateTempo());
      song->setBpm(buffer);
      
      return miniBpm.getTempoCandidates();
    }

    void AudioAnalyzer::analyzeBpms() {
      cout << "analyze bpms" << endl;

      vector<Style*> emptyStyles;
      vector<Song*> emptySongs;
      string query = "id:\"(select max(id) from songs)\"";
      vector<Song*>* songs = SearchUtil::searchSongs(query, 0, 0, "", emptyStyles, emptySongs, 1);
      int maxId = 0;
      for (Song* song : *songs) {
        maxId = song->getId();
      }

      int span = 100;
      for (int i = 0; i <= maxId; i += span) {
        stringstream ss;
        ss << "q:\"s.id >= " << i << "\" q:\"s.id < " << (i + span) << "\"";
        ss << " trashed:0 q:\"bpm is null\"";
        query = ss.str();
        songs = SearchUtil::searchSongs(query, 0, 0, "", emptyStyles, emptySongs, span);

        for (Song* song : *songs) {
          string bpm = song->getBpm();
          AudioAnalyzer::analyzeBpm(song);
          if (bpm.compare(song->getBpm())) {
            song->update();
          }
        }
      }
    }
    
    const Keys* AudioAnalyzer::analyzeKey(Song *song) {
      cout << "analyze key" << endl;
      
      FILE *fpipe;
      stringstream command;
      command << "/Users/rneale/sonic-annotator -d vamp:qm-vamp-plugins:qm-keydetector:key -w csv --csv-stdout ";
      command << "\"" << song->getFilepath() << "\"";
      char buffer[1024];
      
      if (!(fpipe = (FILE*)popen(command.str().c_str(), "r")) ) {
        // If fpipe is NULL
        cerr << "Problems with sonic annotator pipe." << endl;
        return new Keys();
      }
      
      stringstream ss;
      while (fgets(buffer, sizeof buffer, fpipe)) {
        cout << buffer;
        ss << buffer;
      }
      cout << endl;
      
      pclose(fpipe);
      
      float lastTime(0);
      map<string, float> keys;
      string output(ss.str());
      vector<string> lines;
      boost::split(lines, output, boost::is_any_of("\n"));
      for (string line : lines) {
        vector<string> parts;
        boost::split(parts, line, boost::is_any_of(","));
        if (parts.size() == 4) {
          float time = stof(parts[1]);
          if (time > 10) {
            string strKey = parts[3].substr(1, parts[3].length()-2);
            if (keys.count(strKey) > 0) {
              keys[strKey] += time - lastTime;
            } else {
              keys[strKey] = time - lastTime;
            }
          }
          lastTime = time;
        }
      }
      
      Keys* results = new Keys(keys.begin(), keys.end());
      sort(results->candidate.begin(), results->candidate.end(), &keyPairCompare);

      return results;
    }
    
  }
}
