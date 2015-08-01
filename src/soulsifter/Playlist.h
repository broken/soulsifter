//
//  Playlist.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__Playlist__
#define __soul_sifter__Playlist__

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

    class PlaylistEntry;
    class Style;

    class Playlist {
    public:
        Playlist();
        explicit Playlist(const Playlist& playlist);
        ~Playlist();
        void clear();

        static Playlist* findById(int id);
        static Playlist* findByName(const string& name);
        static ResultSetIterator<Playlist>* findAll();

        int update();
        int save();
        // sync with db & return true if object needs saving or updating
        bool sync();
        int erase();

        const int getId() const;
        void setId(int id);
        const string& getName() const;
        void setName(const string& name);
        const string& getQuery() const;
        void setQuery(const string& query);
        const string& getGmusicId() const;
        void setGmusicId(const string& gmusicId);
        const vector<int>& getPlaylistEntryIds() const;
        void setPlaylistEntryIds(const vector<int>& playlistEntryIds);
        const vector<PlaylistEntry*>& getPlaylistEntries();
        void setPlaylistEntries(const vector<PlaylistEntry*>& playlistEntries);
        const vector<int>& getStyleIds() const;
        void setStyleIds(const vector<int>& styleIds);
        const vector<Style*>& getStyles();
        void setStyles(const vector<Style*>& styles);

        friend ResultSetIterator<Playlist>;

    private:
        int id;
        string name;
        string query;
        string gmusicId;
        vector<int> playlistEntryIds;
        vector<PlaylistEntry*> playlistEntries;
        vector<int> styleIds;
        vector<Style*> styles;

        static void populateFields(const sql::ResultSet* rs, Playlist* playlist);

        void operator=(const Playlist& playlist);
    };

}
}

#endif /* defined(__soul_sifter__Playlist__) */
