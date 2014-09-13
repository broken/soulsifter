//
//  Search.h
//  soul-sifter
//
//  Created by Robby Neale on 7/7/14.
//
//

#ifndef __soul_sifter__Search__
#define __soul_sifter__Search__

#include <string>
#include <vector>

using namespace std;

namespace dogatech {
namespace soulsifter {
class Song;

class SearchUtil {
public:
  static vector<Song*>* searchSongs(const string& query);
};
  
}  // namespace soulsifter
}  // namespace dogatech

#endif /* defined(__soul_sifter__Search__) */
