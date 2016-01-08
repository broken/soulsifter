//
//  MusicVideo.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__MusicVideo__
#define __soul_sifter__MusicVideo__

#include <set>
#include <string>
#include <vector>

#include "ResultSetIterator.h"

namespace sql {
    class ResultSet;
}

using namespace std;

namespace dogatech {
namespace soulsifter {

    class Song;

    class MusicVideo {
    public:
        MusicVideo();
        explicit MusicVideo(const MusicVideo& musicVideo);
        void operator=(const MusicVideo& musicVideo);
        ~MusicVideo();
        void clear();

        static MusicVideo* findById(int id);
        static MusicVideo* findBySongId(int songId);
        static ResultSetIterator<MusicVideo>* findAll();

        int update();
        int save();
        // sync with db & return true if object needs saving or updating
        bool sync();

        const int getId() const;
        void setId(int id);
        const int getSongId() const;
        void setSongId(int songId);
        Song* getSong();
        Song* getSongOnce() const;
        void setSong(const Song& song);
        void setSong(Song* song);  // takes ownership
        const string& getFilePath() const;
        void setFilePath(const string& filePath);
        const string& getThumbnailFilePath() const;
        void setThumbnailFilePath(const string& thumbnailFilePath);

        friend ResultSetIterator<MusicVideo>;

    private:
        int id;
        int songId;
        Song* song;
        string filePath;
        string thumbnailFilePath;

        static void populateFields(const sql::ResultSet* rs, MusicVideo* musicVideo);
    };

}
}

#endif /* defined(__soul_sifter__MusicVideo__) */
