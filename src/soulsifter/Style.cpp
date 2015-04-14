//
//  Style.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "Style.h"

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
#include "Style.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    Style::Style() :
    id(0),
    name(),
    reId(0),
    reLabel(),
    childIds(),
    children(),
    parentIds(),
    parents() {
    }

    Style::Style(const Style& style) :
    id(style.getId()),
    name(style.getName()),
    reId(style.getREId()),
    reLabel(style.getRELabel()),
    childIds(style.getChildIds()),
    children(),
    parentIds(style.getParentIds()),
    parents() {
    }

    void Style::operator=(const Style& style) {
        id = style.getId();
        name = style.getName();
        reId = style.getREId();
        reLabel = style.getRELabel();
        childIds = style.getChildIds();
        deleteVectorPointers(&children);
        parentIds = style.getParentIds();
        deleteVectorPointers(&parents);
    }

    Style::~Style() {
        while (!children.empty()) delete children.back(), children.pop_back();
        while (!parents.empty()) delete parents.back(), parents.pop_back();
    }

    void Style::clear() {
        id = 0;
        name.clear();
        reId = 0;
        reLabel.clear();
        childIds.clear();
        deleteVectorPointers(&children);
        parentIds.clear();
        deleteVectorPointers(&parents);
    }

# pragma mark static methods

    void Style::populateFields(const sql::ResultSet* rs, Style* style) {
        style->setId(rs->getInt("id"));
        style->setName(rs->getString("name"));
        style->setREId(rs->getInt("reId"));
        style->setRELabel(rs->getString("reLabel"));
        if (!rs->isNull("childIds")) {
            string csv = rs->getString("childIds");
            istringstream iss(csv);
            string id;
            while (getline(iss, id, ',')) {
              style->childIds.push_back(atoi(id.c_str()));
            }
        }
        if (!rs->isNull("parentIds")) {
            string csv = rs->getString("parentIds");
            istringstream iss(csv);
            string id;
            while (getline(iss, id, ',')) {
              style->parentIds.push_back(atoi(id.c_str()));
            }
        }
    }

    Style* Style::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Styles.*, group_concat(children.childId) as childIds, group_concat(parents.parentId) as parentIds from Styles left outer join StyleChildren children on Styles.id = children.parentId left outer join StyleChildren parents on Styles.id = parents.childId where Styles.id = ? group by Styles.id");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            Style *style = NULL;
            if (rs->next()) {
                style = new Style();
                populateFields(rs, style);
            }
            rs->close();
            delete rs;

            return style;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    Style* Style::findByREId(int reId) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Styles.*, group_concat(children.childId) as childIds, group_concat(parents.parentId) as parentIds from Styles left outer join StyleChildren children on Styles.id = children.parentId left outer join StyleChildren parents on Styles.id = parents.childId where reId = ? group by Styles.id");
            ps->setInt(1, reId);
            sql::ResultSet *rs = ps->executeQuery();
            Style *style = NULL;
            if (rs->next()) {
                style = new Style();
                populateFields(rs, style);
            }
            rs->close();
            delete rs;

            return style;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<Style>* Style::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Styles.*, group_concat(children.childId) as childIds, group_concat(parents.parentId) as parentIds from Styles left outer join StyleChildren children on Styles.id = children.parentId left outer join StyleChildren parents on Styles.id = parents.childId group by Styles.id");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<Style> *dtrs = new ResultSetIterator<Style>(rs);
        return dtrs;
    }

# pragma mark persistence

    int Style::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Styles set name=?, reId=?, reLabel=? where id=?");
            ps->setString(1, name);
            ps->setInt(2, reId);
            ps->setString(3, reLabel);
            ps->setInt(4, id);
            int result = ps->executeUpdate();
            if (!childIds.empty()) {
                stringstream ss("insert ignore into StyleChildren (parentId, childId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                for (int i = 1; i < childIds.size(); ++i) {
                    ss << ", (?, ?)";
                }
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                for (int i = 0; i < childIds.size(); ++i) {
                    ps->setInt(i * 2 + 1, id);
                    ps->setInt(i * 2 + 2, childIds[i]);
                }
                ps->executeUpdate();
                ss.str(std::string());
                ss << "delete from StyleChildren where parentId = ? and childId not in (?";
                for (int i = 1; i < childIds.size(); ++i) {
                    ss << ", ?";
                }
                ss << ")";
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                ps->setInt(1, id);
                for (int i = 0; i < childIds.size(); ++i) {
                    ps->setInt(i + 2, childIds[i]);
                }
                ps->executeUpdate();
            } else {
                ps = MysqlAccess::getInstance().getPreparedStatement("delete from StyleChildren where parentId = ?");
                ps->setInt(1, id);
                ps->executeUpdate();
            }
            if (!parentIds.empty()) {
                stringstream ss("insert ignore into StyleChildren (childId, parentId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                for (int i = 1; i < parentIds.size(); ++i) {
                    ss << ", (?, ?)";
                }
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                for (int i = 0; i < parentIds.size(); ++i) {
                    ps->setInt(i * 2 + 1, id);
                    ps->setInt(i * 2 + 2, parentIds[i]);
                }
                ps->executeUpdate();
                ss.str(std::string());
                ss << "delete from StyleChildren where childId = ? and parentId not in (?";
                for (int i = 1; i < parentIds.size(); ++i) {
                    ss << ", ?";
                }
                ss << ")";
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                ps->setInt(1, id);
                for (int i = 0; i < parentIds.size(); ++i) {
                    ps->setInt(i + 2, parentIds[i]);
                }
                ps->executeUpdate();
            } else {
                ps = MysqlAccess::getInstance().getPreparedStatement("delete from StyleChildren where childId = ?");
                ps->setInt(1, id);
                ps->executeUpdate();
            }
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

    int Style::save() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Styles (name, reId, reLabel) values (?, ?, ?)");
            ps->setString(1, name);
            ps->setInt(2, reId);
            ps->setString(3, reLabel);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save style" << endl;
                return saved;
            } else {
                id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted style, but unable to retreive inserted ID." << endl;
                    return saved;
                }
                if (!childIds.empty()) {
                    stringstream ss("insert ignore into StyleChildren (parentId, childId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                    for (int i = 1; i < childIds.size(); ++i) {
                        ss << ", (?, ?)";
                    }
                    ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                    for (int i = 0; i < childIds.size(); ++i) {
                        ps->setInt(i * 2 + 1, id);
                        ps->setInt(i * 2 + 2, childIds[i]);
                    }
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save child for style " << id << endl;
                    }
                }
                if (!parentIds.empty()) {
                    stringstream ss("insert ignore into StyleChildren (childId, parentId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                    for (int i = 1; i < parentIds.size(); ++i) {
                        ss << ", (?, ?)";
                    }
                    ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                    for (int i = 0; i < parentIds.size(); ++i) {
                        ps->setInt(i * 2 + 1, id);
                        ps->setInt(i * 2 + 2, parentIds[i]);
                    }
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save parent for style " << id << endl;
                    }
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

    const int Style::getId() const { return id; }
    void Style::setId(const int id) { this->id = id; }

    const string& Style::getName() const { return name; }
    void Style::setName(const string& name) { this->name = name; }

    const int Style::getREId() const { return reId; }
    void Style::setREId(const int reId) { this->reId = reId; }

    const string& Style::getRELabel() const { return reLabel; }
    void Style::setRELabel(const string& reLabel) { this->reLabel = reLabel; }

    const vector<int>& Style::getChildIds() const { return childIds; }
    void Style::setChildIds(const vector<int>& childIds) {
        while (!children.empty()) delete children.back(), children.pop_back();
        this->childIds.clear();
        this->childIds = childIds;
    }

    const vector<Style*>& Style::getChildren() {
        if (children.empty() && !childIds.empty()) {
            for (vector<int>::const_iterator it = childIds.begin(); it != childIds.end(); ++it) {
                children.push_back(Style::findById(*it));
            }
        }
        return children;
    }
    void Style::setChildren(const vector<Style*>& children) {
        deleteVectorPointers<Style*>(&this->children);
        this->children = children;
        this->childIds.clear();
        for (vector<Style*>::const_iterator it = children.begin(); it != children.end(); ++it) {
            this->childIds.push_back((*it)->getId());
        }
    }

    const vector<int>& Style::getParentIds() const { return parentIds; }
    void Style::setParentIds(const vector<int>& parentIds) {
        while (!parents.empty()) delete parents.back(), parents.pop_back();
        this->parentIds.clear();
        this->parentIds = parentIds;
    }

    const vector<Style*>& Style::getParents() {
        if (parents.empty() && !parentIds.empty()) {
            for (vector<int>::const_iterator it = parentIds.begin(); it != parentIds.end(); ++it) {
                parents.push_back(Style::findById(*it));
            }
        }
        return parents;
    }
    void Style::setParents(const vector<Style*>& parents) {
        deleteVectorPointers<Style*>(&this->parents);
        this->parents = parents;
        this->parentIds.clear();
        for (vector<Style*>::const_iterator it = parents.begin(); it != parents.end(); ++it) {
            this->parentIds.push_back((*it)->getId());
        }
    }

}
}
