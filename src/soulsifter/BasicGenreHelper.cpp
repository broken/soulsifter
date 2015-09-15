//
//  BasicGenreHelper.cpp
//  soul-sifter
//
//  Created by Robby Neale on 1/21/13.
//
//

#include "BasicGenre.h"

#include <string>
#include <vector>

#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

#include "MysqlAccess.h"


namespace dogatech {
namespace soulsifter {
    
    BasicGenre* BasicGenre::findByFilepath(const string& filepath) {
        unsigned long pos = filepath.find("/mp3/");
        if (pos != string::npos) {
            pos += 5;
            unsigned long pos2 = filepath.find("/", pos);
            return findByName(filepath.substr(pos, pos2-pos));
        }
        pos = filepath.find("/staging/");
        if (pos != string::npos) {
            pos += 9;
            unsigned long pos2 = filepath.find("/", pos);
            return findByName(filepath.substr(pos, pos2-pos));
        }
        // TODO remove mixes once they're moved
        pos = filepath.find("/mixes/");
        if (pos != string::npos) {
            pos += 7;
            unsigned long pos2 = filepath.find("/", pos);
            return findByName(filepath.substr(pos, pos2-pos));
        }
        return NULL;
    }
    
    void BasicGenre::findAll(const vector<const BasicGenre*>** genresPtr) {
        static vector<const BasicGenre*> basicGenres;
        if (basicGenres.size() == 0) {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from BasicGenres");
            sql::ResultSet *rs = ps->executeQuery();
            while (rs->next()) {
                for (vector<const BasicGenre*>::iterator it = basicGenres.begin(); it != basicGenres.end(); ++it) {
                    if ((*it)->id == rs->getInt("id")) {
                        continue;
                    }
                }
                BasicGenre *genre = new BasicGenre();
                populateFields(rs, genre);
                basicGenres.push_back(genre);
            }
            rs->close();
            delete rs;
        }
        (*genresPtr) = &basicGenres;
    }

    BasicGenre* BasicGenre::findByArtist(const string& artist) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select g.*, count(*) as cnt from Albums a join BasicGenres g on a.basicGenreId=g.id where a.artist=? group by g.id order by cnt desc limit 1");
            ps->setString(1, artist);
            sql::ResultSet *rs = ps->executeQuery();
            BasicGenre* basicGenre = NULL;
            if (rs->next()) {
                basicGenre = new BasicGenre();
                populateFields(rs, basicGenre);
            }
            rs->close();
            delete rs;

            return basicGenre;
        } catch (sql::SQLException &e) {
            cerr << "ERRO: SQLExceptionR in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }
    
}
}
