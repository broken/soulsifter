//
//  AlbumPart.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__AlbumPart__
#define __soul_sifter__AlbumPart__

#include <set>
#include <string>
#include <vector>

#include "ResultSetIterator.h"
#include "Album.h"

namespace sql {
    class ResultSet;
}

using namespace std;

namespace dogatech {
namespace soulsifter {

    class AlbumPart {
    public:
        AlbumPart();
        explicit AlbumPart(const AlbumPart& albumPart);
        ~AlbumPart();
        void clear();

        static AlbumPart* findById(int id);
        static AlbumPart* findByPosAndAlbumId(const string& pos, int albumId);
        static ResultSetIterator<AlbumPart>* findAll();

        bool sync();
        int update();
        int save();

        const int getId() const;
        void setId(int id);
        const string& getPos() const;
        void setPos(const string& pos);
        const string& getName() const;
        void setName(const string& name);
        const int getAlbumId() const;
        void setAlbumId(int albumId);
        Album* getAlbum() const;
        void setAlbum(const Album& album);
        void setAlbum(Album* album);  // takes ownership

        friend ResultSetIterator<AlbumPart>;

    private:
        int id;
        string pos;
        string name;
        int albumId;
        Album* album;

        static void populateFields(const sql::ResultSet* rs, AlbumPart* albumPart);

        void operator=(const AlbumPart& albumPart);
    };

}
}

#endif /* defined(__soul_sifter__AlbumPart__) */
