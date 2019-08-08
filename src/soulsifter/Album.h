//
//  Album.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__Album__
#define __soul_sifter__Album__

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

    class BasicGenre;

    class Album {
    public:
        Album();
        explicit Album(const Album& album);
        void operator=(const Album& album);
        ~Album();
        void clear();

        static Album* findById(int id);
        static Album* findByCoverFilepath(const string& coverFilepath);
        static Album* findByNameAndArtist(const string& name, const string& artist);
        static ResultSetIterator<Album>* findByName(string name);
        static ResultSetIterator<Album>* findByArtist(string artist);
        static ResultSetIterator<Album>* findAll();

        int update();
        int save();
        // sync with db & return true if object needs saving or updating
        bool sync();

        const string reReleaseDate() const;

        const int getId() const;
        void setId(int id);
        const string& getName() const;
        void setName(const string& name);
        const string& getArtist() const;
        void setArtist(const string& artist);
        const string& getCoverFilepath() const;
        void setCoverFilepath(const string& coverFilepath);
        const bool getMixed() const;
        void setMixed(bool mixed);
        const string& getLabel() const;
        void setLabel(const string& label);
        const string& getCatalogId() const;
        void setCatalogId(const string& catalogId);
        const int getReleaseDateYear() const;
        void setReleaseDateYear(int releaseDateYear);
        const int getReleaseDateMonth() const;
        void setReleaseDateMonth(int releaseDateMonth);
        const int getReleaseDateDay() const;
        void setReleaseDateDay(int releaseDateDay);
        const int getBasicGenreId() const;
        void setBasicGenreId(int basicGenreId);
        BasicGenre* getBasicGenre();
        BasicGenre* getBasicGenreOnce() const;
        void setBasicGenre(const BasicGenre& basicGenre);
        void setBasicGenre(BasicGenre* basicGenre);  // takes ownership

        friend ResultSetIterator<Album>;

    private:
        int id;
        string name;
        string artist;
        string coverFilepath;
        bool mixed;
        string label;
        string catalogId;
        int releaseDateYear;
        int releaseDateMonth;
        int releaseDateDay;
        int basicGenreId;
        BasicGenre* basicGenre;

        static void populateFields(const sql::ResultSet* rs, Album* album);
    };

}
}

#endif /* defined(__soul_sifter__Album__) */
