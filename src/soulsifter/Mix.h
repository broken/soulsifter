//
//  Mix.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__Mix__
#define __soul_sifter__Mix__

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

    class Mix {
    public:
        Mix();
        explicit Mix(const Mix& mix);
        void operator=(const Mix& mix);
        ~Mix();
        void clear();

        static Mix* findById(int id);
        static Mix* findByOutSongIdAndInSongId(int outSongId, int inSongId);
        static ResultSetIterator<Mix>* findByOutSongId(int outSongId);
        static ResultSetIterator<Mix>* findByInSongId(int inSongId);
        static ResultSetIterator<Mix>* findAll();

        int update();
        int save();
        // sync with db & return true if object needs saving or updating
        bool sync();

        friend class RapidEvolutionDatabaseMixoutsMixoutHandler;

        static int mixoutCountForRESongId(int outSongId);

        const int getId() const;
        void setId(int id);
        const int getOutSongId() const;
        void setOutSongId(int outSongId);
        Song* getOutSong();
        Song* getOutSongOnce() const;
        void setOutSong(const Song& outSong);
        void setOutSong(Song* outSong);  // takes ownership
        const int getInSongId() const;
        void setInSongId(int inSongId);
        Song* getInSong();
        Song* getInSongOnce() const;
        void setInSong(const Song& inSong);
        void setInSong(Song* inSong);  // takes ownership
        const string& getBpmDiff() const;
        void setBpmDiff(const string& bpmDiff);
        const int getRank() const;
        void setRank(int rank);
        const string& getComments() const;
        void setComments(const string& comments);
        const bool getAddon() const;
        void setAddon(bool addon);

        friend ResultSetIterator<Mix>;
        friend class SearchUtil;

    private:
        int id;
        int outSongId;
        Song* outSong;
        int inSongId;
        Song* inSong;
        string bpmDiff;
        int rank;
        string comments;
        bool addon;

        static void populateFields(const sql::ResultSet* rs, Mix* mix);
    };

}
}

#endif /* defined(__soul_sifter__Mix__) */
