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
#include <g3log/g3log.hpp>

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
        for (int i = 0; i < 2; ++i) {
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
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    BasicGenre* BasicGenre::findByName(const string& name) {
        for (int i = 0; i < 2; ++i) {
            try {
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select BasicGenres.* from BasicGenres where ifnull(name,'') = ifnull(?,'')");
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
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    ResultSetIterator<BasicGenre>* BasicGenre::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select BasicGenres.* from BasicGenres");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<BasicGenre> *dtrs = new ResultSetIterator<BasicGenre>(rs);
        return dtrs;
    }

# pragma mark persistence

    int BasicGenre::update() {
        for (int i = 0; i < 2; ++i) {
            try {

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update BasicGenres set name=? where id=?");
                if (!name.empty()) ps->setString(1, name);
                else ps->setNull(1, sql::DataType::VARCHAR);
                ps->setInt(2, id);
                int result = ps->executeUpdate();
                return result;
            } catch (sql::SQLException &e) {
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    int BasicGenre::save() {
        for (int i = 0; i < 2; ++i) {
            try {

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into BasicGenres (name) values (?)");
                if (!name.empty()) ps->setString(1, name);
                else ps->setNull(1, sql::DataType::VARCHAR);
                int saved = ps->executeUpdate();
                if (!saved) {
                    LOG(WARNING) << "Not able to save basicGenre";
                    return saved;
                } else {
                    id = MysqlAccess::getInstance().getLastInsertId();
                    if (id == 0) {
                        LOG(WARNING) << "Inserted basicGenre, but unable to retreive inserted ID.";
                        return saved;
                    }
                    return saved;
                }
            } catch (sql::SQLException &e) {
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    bool BasicGenre::sync() {
        BasicGenre* basicGenre = findById(id);
        if (!basicGenre) basicGenre = findByName(getName());
        if (!basicGenre) return true;

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != basicGenre->getId()) {
            if (id) {
                LOG(INFO) << "updating basicGenre " << id << " id from " << basicGenre->getId() << " to " << id;
                needsUpdate = true;
            } else {
                id = basicGenre->getId();
            }
        }
        if (name.compare(basicGenre->getName())  && (!boost::regex_match(name, match1, decimal) || !boost::regex_match(basicGenre->getName(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!name.empty()) {
                LOG(INFO) << "updating basicGenre " << id << " name from " << basicGenre->getName() << " to " << name;
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
