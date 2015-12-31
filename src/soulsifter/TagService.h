#ifndef soul_sifter_TagService_h
#define soul_sifter_TagService_h

namespace dogatech {
namespace soulsifter {
    
class Song;

class TagService {
public:
  static void readId3v2Tag(Song* song);
  static void updateSongAttributesFromTags();
};
    
}  // namespace soulsifter
}  // namespace dogatech

#endif