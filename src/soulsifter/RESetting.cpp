//
//  RESetting.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "RESetting.h"

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

    RESetting::RESetting() :
    id(0),
    name(),
    value() {
    }

    RESetting::RESetting(const RESetting& reSetting) :
    id(reSetting.getId()),
    name(reSetting.getName()),
    value(reSetting.getValue()) {
    }

    void RESetting::operator=(const RESetting& reSetting) {
        id = reSetting.getId();
        name = reSetting.getName();
        value = reSetting.getValue();
    }

    RESetting::~RESetting() {
    }

    void RESetting::clear() {
        id = 0;
        name.clear();
        value.clear();
    }

# pragma mark static methods

    void RESetting::populateFields(const sql::ResultSet* rs, RESetting* reSetting) {
        reSetting->setId(rs->getInt("id"));
        reSetting->setName(rs->getString("name"));
        reSetting->setValue(rs->getString("value"));
    }

    RESetting* RESetting::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESettings where id = ?");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            RESetting *reSetting = NULL;
            if (rs->next()) {
                reSetting = new RESetting();
                populateFields(rs, reSetting);
            }
            rs->close();
            delete rs;

            return reSetting;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    RESetting* RESetting::findByName(const string& name) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESettings where name = ?");
            ps->setString(1, name);
            sql::ResultSet *rs = ps->executeQuery();
            RESetting *reSetting = NULL;
            if (rs->next()) {
                reSetting = new RESetting();
                populateFields(rs, reSetting);
            }
            rs->close();
            delete rs;

            return reSetting;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<RESetting>* RESetting::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select * from RESettings");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<RESetting> *dtrs = new ResultSetIterator<RESetting>(rs);
        return dtrs;
    }

# pragma mark persistence

    int RESetting::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update RESettings set name=?, value=? where id=?");
            ps->setString(1, name);
            ps->setString(2, value);
            ps->setInt(3, id);
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

    int RESetting::save() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into RESettings (name, value) values (?, ?)");
            ps->setString(1, name);
            ps->setString(2, value);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save reSetting" << endl;
                return saved;
            } else {
                id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted reSetting, but unable to retreive inserted ID." << endl;
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


# pragma mark accessors

    const int RESetting::getId() const { return id; }
    void RESetting::setId(const int id) { this->id = id; }

    const string& RESetting::getName() const { return name; }
    void RESetting::setName(const string& name) { this->name = name; }

    const string& RESetting::getValue() const { return value; }
    void RESetting::setValue(const string& value) { this->value = value; }

}
}
