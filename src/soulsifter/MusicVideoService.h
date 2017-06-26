#ifndef __soul_sifter__MusicVideoService__
#define __soul_sifter__MusicVideoService__

#include <string>
#include <vector>

using namespace std;

namespace dogatech {
namespace soulsifter {

class Song;
class MusicVideo;

class MusicVideoService {
public:
  static MusicVideo* associateYouTubeVideo(Song* const song, const string& id);
  static vector<string> downloadYouTubeAudio(const string& id);
};

}  // namespace soulsifter
}  // namespace dogatech

#endif /* defined(__soul_sifter__MusicVideoService__) */
