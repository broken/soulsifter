//
//  BasicGenre.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__BasicGenre__
#define __soul_sifter__BasicGenre__

#include <set>
#include <string>
#include <vector>

//#include "ResultSetIterator.h"

namespace sql {
    class ResultSet;
}

using namespace std;

namespace dogatech {
namespace soulsifter {

    class BasicGenre {
    public:
        BasicGenre();
        explicit BasicGenre(const BasicGenre& basicGenre);
        ~BasicGenre();
        void clear();

        static BasicGenre* findById(int id);
        /*static BasicGenre* findByName(const string& name);
        static ResultSetIterator<BasicGenre>* findAll();

        bool sync();
        int update();
        int save();

        static const BasicGenre* findByFilepath(const string& filepath);
        static void findAll(const vector<const BasicGenre*>** genresPtr);*/

        const int getId() const;
        void setId(int id);
        const string& getName() const;
        void setName(const string& name);

        //friend ResultSetIterator<BasicGenre>;

    private:
        int id;
        string name;

        static void populateFields(const sql::ResultSet* rs, BasicGenre* basicGenre);

        void operator=(const BasicGenre& basicGenre);
    };

}
}

#endif /* defined(__soul_sifter__BasicGenre__) */
