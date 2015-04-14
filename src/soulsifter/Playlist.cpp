//
//  Playlist.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "Playlist.h"

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
#include "PlaylistEntry.h"
#include "Style.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    Playlist::Playlist() :
    id(0),
    name(),
    query(),
    playlistEntryIds(),
    playlistEntries(),
    styleIds(),
    styles() {
    }

    Playlist::Playlist(const Playlist& playlist) :
    id(playlist.getId()),
    name(playlist.getName()),
    query(playlist.getQuery()),
    playlistEntryIds(playlist.getPlaylistEntryIds()),
    playlistEntries(),
    styleIds(playlist.getStyleIds()),
    styles() {
    }

    void Playlist::operator=(const Playlist& playlist) {
        id = playlist.getId();
        name = playlist.getName();
        query = playlist.getQuery();
        playlistEntryIds = playlist.getPlaylistEntryIds();
        deleteVectorPointers(&playlistEntries);
        styleIds = playlist.getStyleIds();
        deleteVectorPointers(&styles);
    }

    Playlist::~Playlist() {
        while (!playlistEntries.empty()) delete playlistEntries.back(), playlistEntries.pop_back();
        while (!styles.empty()) delete styles.back(), styles.pop_back();
    }

    void Playlist::clear() {
        id = 0;
        name.clear();
        query.clear();
        playlistEntryIds.clear();
        deleteVectorPointers(&playlistEntries);
        styleIds.clear();
        deleteVectorPointers(&styles);
    }

# pragma mark static methods

    void Playlist::populateFields(const sql::ResultSet* rs, Playlist* playlist) {
        playlist->setId(rs->getInt("id"));
        playlist->setName(rs->getString("name"));
        playlist->setQuery(rs->getString("query"));
        if (!rs->isNull("playlistEntryIds")) {
            string csv = rs->getString("playlistEntryIds");
            istringstream iss(csv);
            string id;
            while (getline(iss, id, ',')) {
              playlist->playlistEntryIds.push_back(atoi(id.c_str()));
            }
        }
        if (!rs->isNull("styleIds")) {
            string csv = rs->getString("styleIds");
            istringstream iss(csv);
            string id;
            while (getline(iss, id, ',')) {
              playlist->styleIds.push_back(atoi(id.c_str()));
            }
        }
    }

    Playlist* Playlist::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select *, group_concat(playlistEntries.id) as playlistEntryIds, group_concat(styles.styleId) as styleIds from Playlists left outer join PlaylistEntries playlistEntries on Playlists.id = playlistEntries.playlistId left outer join PlaylistStyles styles on Playlists.id = styles.playlistId where Playlists.id = ? group by Playlists.id");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            Playlist *playlist = NULL;
            if (rs->next()) {
                playlist = new Playlist();
                populateFields(rs, playlist);
            }
            rs->close();
            delete rs;

            return playlist;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    Playlist* Playlist::findByName(const string& name) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select *, group_concat(playlistEntries.id) as playlistEntryIds, group_concat(styles.styleId) as styleIds from Playlists left outer join PlaylistEntries playlistEntries on Playlists.id = playlistEntries.playlistId left outer join PlaylistStyles styles on Playlists.id = styles.playlistId where Playlists.name = ? group by Playlists.id");
            ps->setString(1, name);
            sql::ResultSet *rs = ps->executeQuery();
            Playlist *playlist = NULL;
            if (rs->next()) {
                playlist = new Playlist();
                populateFields(rs, playlist);
            }
            rs->close();
            delete rs;

            return playlist;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<Playlist>* Playlist::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select *, group_concat(playlistEntries.id) as playlistEntryIds, group_concat(styles.styleId) as styleIds from Playlists left outer join PlaylistEntries playlistEntries on Playlists.id = playlistEntries.playlistId left outer join PlaylistStyles styles on Playlists.id = styles.playlistId group by Playlists.id");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<Playlist> *dtrs = new ResultSetIterator<Playlist>(rs);
        return dtrs;
    }

# pragma mark persistence

    int Playlist::update() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Playlists set name=?, query=? where id=?");
            ps->setString(1, name);
            ps->setString(2, query);
            ps->setInt(3, id);
            int result = ps->executeUpdate();
            if (!playlistEntryIds.empty()) {
                stringstream ss("insert ignore into PlaylistEntries (playlistId, playlistEntryId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                for (int i = 1; i < playlistEntryIds.size(); ++i) {
                    ss << ", (?, ?)";
                }
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                for (int i = 0; i < playlistEntryIds.size(); ++i) {
                    ps->setInt(i * 2 + 1, id);
                    ps->setInt(i * 2 + 2, playlistEntryIds[i]);
                }
                ps->executeUpdate();
                ss.str(std::string());
                ss << "delete from PlaylistEntries where playlistId = ? and playlistEntryId not in (?";
                for (int i = 1; i < playlistEntryIds.size(); ++i) {
                    ss << ", ?";
                }
                ss << ")";
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                ps->setInt(1, id);
                for (int i = 0; i < playlistEntryIds.size(); ++i) {
                    ps->setInt(i + 2, playlistEntryIds[i]);
                }
                ps->executeUpdate();
            } else {
                ps = MysqlAccess::getInstance().getPreparedStatement("delete from PlaylistEntries where playlistId = ?");
                ps->setInt(1, id);
                ps->executeUpdate();
            }
            if (!styleIds.empty()) {
                stringstream ss("insert ignore into PlaylistStyles (playlistId, styleId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                for (int i = 1; i < styleIds.size(); ++i) {
                    ss << ", (?, ?)";
                }
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                for (int i = 0; i < styleIds.size(); ++i) {
                    ps->setInt(i * 2 + 1, id);
                    ps->setInt(i * 2 + 2, styleIds[i]);
                }
                ps->executeUpdate();
                ss.str(std::string());
                ss << "delete from PlaylistStyles where playlistId = ? and styleId not in (?";
                for (int i = 1; i < styleIds.size(); ++i) {
                    ss << ", ?";
                }
                ss << ")";
                ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                ps->setInt(1, id);
                for (int i = 0; i < styleIds.size(); ++i) {
                    ps->setInt(i + 2, styleIds[i]);
                }
                ps->executeUpdate();
            } else {
                ps = MysqlAccess::getInstance().getPreparedStatement("delete from PlaylistStyles where playlistId = ?");
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

    int Playlist::save() {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Playlists (name, query) values (?, ?)");
            ps->setString(1, name);
            ps->setString(2, query);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save playlist" << endl;
                return saved;
            } else {
                id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted playlist, but unable to retreive inserted ID." << endl;
                    return saved;
                }
                if (!playlistEntryIds.empty()) {
                    stringstream ss("insert ignore into PlaylistEntries (playlistId, playlistEntryId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                    for (int i = 1; i < playlistEntryIds.size(); ++i) {
                        ss << ", (?, ?)";
                    }
                    ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                    for (int i = 0; i < playlistEntryIds.size(); ++i) {
                        ps->setInt(i * 2 + 1, id);
                        ps->setInt(i * 2 + 2, playlistEntryIds[i]);
                    }
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save playlistEntry for playlist " << id << endl;
                    }
                }
                if (!styleIds.empty()) {
                    stringstream ss("insert ignore into PlaylistStyles (playlistId, styleId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                    for (int i = 1; i < styleIds.size(); ++i) {
                        ss << ", (?, ?)";
                    }
                    ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                    for (int i = 0; i < styleIds.size(); ++i) {
                        ps->setInt(i * 2 + 1, id);
                        ps->setInt(i * 2 + 2, styleIds[i]);
                    }
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save style for playlist " << id << endl;
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

    int Playlist::erase() {
        try {
            while (!getPlaylistEntries().empty()) {
                playlistEntries.back()->erase();
                delete playlistEntries.back();
                playlistEntries.pop_back();
            }
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("delete from Playlists where id=?");
            ps->setInt(1, id);
            int erased = ps->executeUpdate();
            if (!erased) {
                cerr << "Not able to erase playlist" << endl;
            }
            return erased;
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

    const int Playlist::getId() const { return id; }
    void Playlist::setId(const int id) { this->id = id; }

    const string& Playlist::getName() const { return name; }
    void Playlist::setName(const string& name) { this->name = name; }

    const string& Playlist::getQuery() const { return query; }
    void Playlist::setQuery(const string& query) { this->query = query; }

    const vector<int>& Playlist::getPlaylistEntryIds() const { return playlistEntryIds; }
    void Playlist::setPlaylistEntryIds(const vector<int>& playlistEntryIds) {
        while (!playlistEntries.empty()) delete playlistEntries.back(), playlistEntries.pop_back();
        this->playlistEntryIds.clear();
        this->playlistEntryIds = playlistEntryIds;
    }

    const vector<PlaylistEntry*>& Playlist::getPlaylistEntries() {
        if (playlistEntries.empty() && !playlistEntryIds.empty()) {
            for (vector<int>::const_iterator it = playlistEntryIds.begin(); it != playlistEntryIds.end(); ++it) {
                playlistEntries.push_back(PlaylistEntry::findById(*it));
            }
        }
        return playlistEntries;
    }
    void Playlist::setPlaylistEntries(const vector<PlaylistEntry*>& playlistEntries) {
        deleteVectorPointers<PlaylistEntry*>(&this->playlistEntries);
        this->playlistEntries = playlistEntries;
        this->playlistEntryIds.clear();
        for (vector<PlaylistEntry*>::const_iterator it = playlistEntries.begin(); it != playlistEntries.end(); ++it) {
            this->playlistEntryIds.push_back((*it)->getId());
        }
    }

    const vector<int>& Playlist::getStyleIds() const { return styleIds; }
    void Playlist::setStyleIds(const vector<int>& styleIds) {
        while (!styles.empty()) delete styles.back(), styles.pop_back();
        this->styleIds.clear();
        this->styleIds = styleIds;
    }

    const vector<Style*>& Playlist::getStyles() {
        if (styles.empty() && !styleIds.empty()) {
            for (vector<int>::const_iterator it = styleIds.begin(); it != styleIds.end(); ++it) {
                styles.push_back(Style::findById(*it));
            }
        }
        return styles;
    }
    void Playlist::setStyles(const vector<Style*>& styles) {
        deleteVectorPointers<Style*>(&this->styles);
        this->styles = styles;
        this->styleIds.clear();
        for (vector<Style*>::const_iterator it = styles.begin(); it != styles.end(); ++it) {
            this->styleIds.push_back((*it)->getId());
        }
    }

}
}
