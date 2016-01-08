//
//  BasicGenre.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "BasicGenre.h"

#include <cmath>
#include <string>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>

#include "MysqlAccess.h"
#include "DTVectorUtil.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    BasicGenre::BasicGenre() :
    id(0),
    name() {
    }

    BasicGenre::BasicGenre(const BasicGenre& basicGenre) :
    id(basicGenre.getId()),
    name(basicGenre.getName()) {
    }

    void BasicGenre::operator=(const BasicGenre& basicGenre) {
        id = basicGenre.getId();
        name = basicGenre.getName();
    }

    BasicGenre::~BasicGenre() {
    }

    void BasicGenre::clear() {
        id = 0;
        name.clear();
    }

# pragma mark static methods

    void BasicGenre::populateFields(const sql::ResultSet* rs, BasicGenre* basicGenre) {
        basicGenre->setId(rs->getInt("id"));
        basicGenre->setName(rs->getString("name"));
    }

    BasicGenre* BasicGenre::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select BasicGenres.* from BasicGenres where BasicGenres.id = ?");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            BasicGenre *basicGenre = NULL;
            if (rs->next()) {
                basicGenre = new BasicGenre();
                populateFields(rs, basicGenre);
            }
            rs->close();
            delete rs;

            return basicGenre;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    BasicGenre* BasicGenre::findByName(const string& name) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select BasicGenres.* from BasicGenres where name = ?");
            if (!name.empty()) ps->setString(1, name);
            else ps->setNull(1, sql::DataType::VARCHAR);
            sql::ResultSet *rs = ps->executeQuery();
            BasicGenre *basicGenre = NULL;
            if (rs->next()) {
                basicGenre = new BasicGenre();
                populateFields(rs, basicGenre);
            }
            rs->close();
            delete rs;

            return basicGenre;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<BasicGenre>* BasicGenre::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select BasicGenres.* from BasicGenres");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<BasicGenre> *dtrs = new ResultSetIterator<BasicGenre>(rs);
        return dtrs;
    }

# pragma mark persistence

    int BasicGenre::update() {
        try {

            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update BasicGenres set name=? where id=?");
            if (!name.empty()) ps->setString(1, name);
            else ps->setNull(1, sql::DataType::VARCHAR);
            ps->setInt(2, id);
            int result = ps->executeUpdate();
            return result;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    int BasicGenre::save() {
        try {

            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into BasicGenres (name) values (?)");
            if (!name.empty()) ps->setString(1, name);
            else ps->setNull(1, sql::DataType::VARCHAR);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save basicGenre" << endl;
                return saved;
            } else {
                id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted basicGenre, but unable to retreive inserted ID." << endl;
                    return saved;
                }
                return saved;
            }
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    bool BasicGenre::sync() {
        BasicGenre* basicGenre = findById(id);
        if (!basicGenre) basicGenre = findByName(getName());
        if (!basicGenre) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != basicGenre->getId()) {
            if (id) {
                cout << "updating basicGenre " << id << " id from " << basicGenre->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = basicGenre->getId();
            }
        }
        if (name.compare(basicGenre->getName())  && (!boost::regex_match(name, match1, decimal) || !boost::regex_match(basicGenre->getName(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!name.empty()) {
                cout << "updating basicGenre " << id << " name from " << basicGenre->getName() << " to " << name << endl;
                needsUpdate = true;
            } else {
                name = basicGenre->getName();
            }
        }
        return needsUpdate;
    }


# pragma mark accessors

    const int BasicGenre::getId() const { return id; }
    void BasicGenre::setId(const int id) { this->id = id; }

    const string& BasicGenre::getName() const { return name; }
    void BasicGenre::setName(const string& name) { this->name = name; }

}
}
