//
//  Song.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__Song__
#define __soul_sifter__Song__

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

    class RESong;
    class Album;
    class AlbumPart;
    class MusicVideo;
    class Style;

    class Song {
    public:
        Song();
        explicit Song(const Song& song);
        void operator=(const Song& song);
        ~Song();
        void clear();

        static Song* findById(int id);
        static Song* findByFilepath(const string& filepath);
        static Song* findByGoogleSongId(const string& googleSongId);
        static Song* findByYoutubeSongId(const string& youtubeSongId);
        static Song* findByRESongId(int reSongId);
        static ResultSetIterator<Song>* findAll();

        int update();
        int save();
        // sync with db & return true if object needs saving or updating
        bool sync();

        explicit Song(RESong* song);

        static RESong* createRESongFromSong(Song& song);

        const string reAlbum();
        const string getDateAddedString() const;
        void setDateAddedToNow();

        const int getId() const;
        void setId(int id);
        const string& getArtist() const;
        void setArtist(const string& artist);
        const string& getTrack() const;
        void setTrack(const string& track);
        const string& getTitle() const;
        void setTitle(const string& title);
        const string& getRemixer() const;
        void setRemixer(const string& remixer);
        const string& getFeaturing() const;
        void setFeaturing(const string& featuring);
        const string& getFilepath() const;
        void setFilepath(const string& filepath);
        const int getRating() const;
        void setRating(int rating);
        const time_t getDateAdded() const;
        void setDateAdded(time_t dateAdded);
        const string& getBpm() const;
        void setBpm(const string& bpm);
        const string& getTonicKey() const;
        void setTonicKey(const string& tonicKey);
        const int getEnergy() const;
        void setEnergy(int energy);
        const string& getComments() const;
        void setComments(const string& comments);
        const bool getTrashed() const;
        void setTrashed(bool trashed);
        const bool getLowQuality() const;
        void setLowQuality(bool lowQuality);
        const string& getGoogleSongId() const;
        void setGoogleSongId(const string& googleSongId);
        const string& getYoutubeSongId() const;
        void setYoutubeSongId(const string& youtubeSongId);
        const int getDurationInMs() const;
        void setDurationInMs(int durationInMs);
        const string& getCurator() const;
        void setCurator(const string& curator);
        const int getRESongId() const;
        void setRESongId(int reSongId);
        RESong* getRESong();
        RESong* getRESongConst() const;
        void setRESong(const RESong& reSong);
        void setRESong(RESong* reSong);  // takes ownership
        const int getAlbumId() const;
        void setAlbumId(int albumId);
        Album* getAlbum();
        Album* getAlbumConst() const;
        void setAlbum(const Album& album);
        void setAlbum(Album* album);  // takes ownership
        const int getAlbumPartId() const;
        void setAlbumPartId(int albumPartId);
        AlbumPart* getAlbumPart();
        AlbumPart* getAlbumPartConst() const;
        void setAlbumPart(const AlbumPart& albumPart);
        void setAlbumPart(AlbumPart* albumPart);  // takes ownership
        const int getMusicVideoId() const;
        void setMusicVideoId(int musicVideoId);
        MusicVideo* getMusicVideo();
        MusicVideo* getMusicVideoConst() const;
        void setMusicVideo(const MusicVideo& musicVideo);
        void setMusicVideo(MusicVideo* musicVideo);  // takes ownership
        const vector<int>& getStyleIds() const;
        void setStyleIds(const vector<int>& styleIds);
        const vector<Style*>& getStyles();
        void setStyles(const vector<Style*>& styles);
        const bool getBpmLock() const;
        void setBpmLock(bool bpmLock);
        const bool getTonicKeyLock() const;
        void setTonicKeyLock(bool tonicKeyLock);

        friend ResultSetIterator<Song>;
        friend class SearchUtil;

    private:
        int id;
        string artist;
        string track;
        string title;
        string remixer;
        string featuring;
        string filepath;
        int rating;
        time_t dateAdded;
        string bpm;
        string tonicKey;
        int energy;
        string comments;
        bool trashed;
        bool lowQuality;
        string googleSongId;
        string youtubeSongId;
        int durationInMs;
        string curator;
        int reSongId;
        RESong* reSong;
        int albumId;
        Album* album;
        int albumPartId;
        AlbumPart* albumPart;
        int musicVideoId;
        MusicVideo* musicVideo;
        vector<int> styleIds;
        vector<Style*> styles;
        bool bpmLock;
        bool tonicKeyLock;

        static void populateFields(const sql::ResultSet* rs, Song* song);
    };

}
}

#endif /* defined(__soul_sifter__Song__) */
