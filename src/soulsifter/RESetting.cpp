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
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select RESettings.* from RESettings where RESettings.id = ?");
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
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select RESettings.* from RESettings where name = ?");
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
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select RESettings.* from RESettings");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<RESetting> *dtrs = new ResultSetIterator<RESetting>(rs);
        return dtrs;
    }

# pragma mark persistence

    int RESetting::update() {
        try {

            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update RESettings set name=?, value=? where id=?");
            if (!name.empty()) ps->setString(1, name);
            else ps->setNull(1, sql::DataType::VARCHAR);
            if (!value.empty()) ps->setString(2, value);
            else ps->setNull(2, sql::DataType::VARCHAR);
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
            if (!name.empty()) ps->setString(1, name);
            else ps->setNull(1, sql::DataType::VARCHAR);
            if (!value.empty()) ps->setString(2, value);
            else ps->setNull(2, sql::DataType::VARCHAR);
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

    bool RESetting::sync() {
        RESetting* reSetting = findById(id);
        if (!reSetting) reSetting = findByName(name);
        if (!reSetting) {
            return true;
        }

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != reSetting->getId()) {
            if (id) {
                cout << "updating reSetting " << id << " id from " << reSetting->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = reSetting->getId();
            }
        }
        if (name.compare(reSetting->getName())  && (!boost::regex_match(name, match1, decimal) || !boost::regex_match(reSetting->getName(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!name.empty()) {
                cout << "updating reSetting " << id << " name from " << reSetting->getName() << " to " << name << endl;
                needsUpdate = true;
            } else {
                name = reSetting->getName();
            }
        }
        if (value.compare(reSetting->getValue())  && (!boost::regex_match(value, match1, decimal) || !boost::regex_match(reSetting->getValue(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!value.empty()) {
                cout << "updating reSetting " << id << " value from " << reSetting->getValue() << " to " << value << endl;
                needsUpdate = true;
            } else {
                value = reSetting->getValue();
            }
        }
        return needsUpdate;
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
