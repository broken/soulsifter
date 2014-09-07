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

using namespace std;

namespace dogatech {
namespace soulsifter {

namespace proto {
  class GetGenresRequest;
  class GetGenresResponse;
  class FindSongsRequest;
  class FindSongsResponse;
}

void getGenres(const proto::GetGenresRequest& request, proto::GetGenresResponse* response);
void searchSongs(const proto::FindSongsRequest& request, proto::FindSongsResponse* response);
  
}  // namespace soulsifter
}  // namespace dogatech

#endif /* defined(__soul_sifter__Search__) */
