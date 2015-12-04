//
//  Search.h
//  soul-sifter
//
//  Created by Robby Neale on 7/7/14.
//
//

#ifndef __soul_sifter__Search__
#define __soul_sifter__Search__

#include <set>
#include <string>
#include <vector>

using namespace std;

namespace dogatech {
namespace soulsifter {
class Song;
class Style;

class SearchUtil {
public:
  static vector<Song*>* searchSongs(const string& query, int min_bpm, int max_bpm, const set<string>& keys, const vector<Style*>& styles, const vector<Song*>& songsToOmit, int limit);
};
  
}  // namespace soulsifter
}  // namespace dogatech

#endif /* defined(__soul_sifter__Search__) */
