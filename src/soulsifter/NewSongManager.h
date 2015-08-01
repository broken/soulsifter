#ifndef __soul_sifter__NewSongManager__
#define __soul_sifter__NewSongManager__

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

using namespace std;

namespace dogatech {
namespace soulsifter {

class FilesToAdd;
class Song;

class NewSongManager {
public:
  NewSongManager();
  ~NewSongManager();
  /**
   * When wanting to add files, the first step will be to import a list
   * of file paths. You should only import one album at a time.
   */
  void import(const vector<string>& filepaths);

  /**
   * After importing the file paths, you can pull off songs to import. The
   * first song will be "optimized" for creation by using previous song
   * creations, while the second will be the original mp3 tagged song. This
   * method returns false when there are no more songs to process.
   */
  bool nextSong(Song** updatedSong, Song** originalSong);

  /**
   * This will return the cover image file path associated with the album.
   */
  string coverImagePath();

  /**
   * Use this to save a song after editing. It allows for future imports to
   * proceed based off changes and performs other misc functions.
   */
  bool processSong(Song* song);

  /**
   * Special method to process a song, but to trash and mark/add as removed.
   */
  void trashMusicFile(Song* song);

private:
  bool hasMovedFile;
  FilesToAdd* filesToAdd;
  vector<string> filesToTrash;

  void preprocessAllFiles(const vector<boost::filesystem::path>& filepaths);

  // cannot be copied
  NewSongManager(NewSongManager const&);
  void operator=(NewSongManager const&);
};

}  // namespace soulsifter
}  // namespace dogatech

#endif /* defined(__soul_sifter__NewSongManager__) */
