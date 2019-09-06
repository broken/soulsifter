//
//  PlaylistEntry.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "PlaylistEntry.h"

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
#include "Playlist.h"
#include "Song.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    PlaylistEntry::PlaylistEntry() :
    id(0),
    playlistId(0),
    playlist(NULL),
    songId(0),
    song(NULL),
    position(0),
    time() {
    }

    PlaylistEntry::PlaylistEntry(const PlaylistEntry& playlistEntry) :
    id(playlistEntry.getId()),
    playlistId(playlistEntry.getPlaylistId()),
    playlist(NULL),
    songId(playlistEntry.getSongId()),
    song(NULL),
    position(playlistEntry.getPosition()),
    time(playlistEntry.getTime()) {
        if (playlistEntry.playlist) setPlaylist(*playlistEntry.playlist);
        if (playlistEntry.song) setSong(*playlistEntry.song);
    }

    void PlaylistEntry::operator=(const PlaylistEntry& playlistEntry) {
        id = playlistEntry.getId();
        playlistId = playlistEntry.getPlaylistId();
        if (!playlistEntry.getPlaylistId() && playlistEntry.playlist) {
            if (!playlist) playlist = new Playlist(*playlistEntry.playlist);
            else *playlist = *playlistEntry.playlist;
        } else {
            delete playlist;
            playlist = NULL;
        }
        songId = playlistEntry.getSongId();
        if (!playlistEntry.getSongId() && playlistEntry.song) {
            if (!song) song = new Song(*playlistEntry.song);
            else *song = *playlistEntry.song;
        } else {
            delete song;
            song = NULL;
        }
        position = playlistEntry.getPosition();
        time = playlistEntry.getTime();
    }

    PlaylistEntry::~PlaylistEntry() {
        delete playlist;
        playlist = NULL;
        delete song;
        song = NULL;
    }

    void PlaylistEntry::clear() {
        id = 0;
        playlistId = 0;
        delete playlist;
        playlist = NULL;
        songId = 0;
        delete song;
        song = NULL;
        position = 0;
        time.clear();
    }

# pragma mark static methods

    void PlaylistEntry::populateFields(const sql::ResultSet* rs, PlaylistEntry* playlistEntry) {
        playlistEntry->setId(rs->getInt("id"));
        playlistEntry->setPlaylistId(rs->getInt("playlistId"));
        playlistEntry->setSongId(rs->getInt("songId"));
        playlistEntry->setPosition(rs->getInt("position"));
        playlistEntry->setTime(rs->getString("time"));
    }

    PlaylistEntry* PlaylistEntry::findById(int id) {
        for (int i = 0; i < 3; ++i) {
            try {
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select PlaylistEntries.* from PlaylistEntries where PlaylistEntries.id = ?");
                ps->setInt(1, id);
                sql::ResultSet *rs = ps->executeQuery();
                PlaylistEntry *playlistEntry = NULL;
                if (rs->next()) {
                    playlistEntry = new PlaylistEntry();
                    populateFields(rs, playlistEntry);
                }
                rs->close();
                delete rs;

                return playlistEntry;
            } catch (sql::SQLException &e) {
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    PlaylistEntry* PlaylistEntry::findByPlaylistIdAndSongId(int playlistId, int songId) {
        for (int i = 0; i < 3; ++i) {
            try {
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select PlaylistEntries.* from PlaylistEntries where ifnull(playlistId,0) = ifnull(?,0) and ifnull(songId,0) = ifnull(?,0)");
                if (playlistId > 0) ps->setInt(1, playlistId);
                else ps->setNull(1, sql::DataType::INTEGER);
                if (songId > 0) ps->setInt(2, songId);
                else ps->setNull(2, sql::DataType::INTEGER);
                sql::ResultSet *rs = ps->executeQuery();
                PlaylistEntry *playlistEntry = NULL;
                if (rs->next()) {
                    playlistEntry = new PlaylistEntry();
                    populateFields(rs, playlistEntry);
                }
                rs->close();
                delete rs;

                return playlistEntry;
            } catch (sql::SQLException &e) {
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    ResultSetIterator<PlaylistEntry>* PlaylistEntry::findByPlaylistId(int playlistId) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select PlaylistEntries.* from PlaylistEntries where ifnull(playlistId,0) = ifnull(?,0)");
        if (playlistId > 0) ps->setInt(1, playlistId);
        else ps->setNull(1, sql::DataType::INTEGER);
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<PlaylistEntry> *dtrs = new ResultSetIterator<PlaylistEntry>(rs);
        return dtrs;
    }

    ResultSetIterator<PlaylistEntry>* PlaylistEntry::findBySongId(int songId) {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select PlaylistEntries.* from PlaylistEntries where ifnull(songId,0) = ifnull(?,0)");
        if (songId > 0) ps->setInt(1, songId);
        else ps->setNull(1, sql::DataType::INTEGER);
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<PlaylistEntry> *dtrs = new ResultSetIterator<PlaylistEntry>(rs);
        return dtrs;
    }

    ResultSetIterator<PlaylistEntry>* PlaylistEntry::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select PlaylistEntries.* from PlaylistEntries");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<PlaylistEntry> *dtrs = new ResultSetIterator<PlaylistEntry>(rs);
        return dtrs;
    }

# pragma mark persistence

    int PlaylistEntry::update() {
        for (int i = 0; i < 3; ++i) {
            try {
                if (playlist && playlist->sync()) {
                    if (playlist->getId()) {
                        playlist->update();
                    } else {
                        playlist->save();
                    }
                    playlistId = playlist->getId();
                } else if (!playlistId && playlist) {
                    playlistId = playlist->getId();
                }
                if (song && song->sync()) {
                    if (song->getId()) {
                        song->update();
                    } else {
                        song->save();
                    }
                    songId = song->getId();
                } else if (!songId && song) {
                    songId = song->getId();
                }

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update PlaylistEntries set playlistId=?, songId=?, position=?, time=? where id=?");
                if (playlistId > 0) ps->setInt(1, playlistId);
                else ps->setNull(1, sql::DataType::INTEGER);
                if (songId > 0) ps->setInt(2, songId);
                else ps->setNull(2, sql::DataType::INTEGER);
                ps->setInt(3, position);
                if (!time.empty()) ps->setString(4, time);
                else ps->setNull(4, sql::DataType::VARCHAR);
                ps->setInt(5, id);
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

    int PlaylistEntry::save() {
        for (int i = 0; i < 3; ++i) {
            try {
                if (playlist && playlist->sync()) {
                    if (playlist->getId()) {
                        playlist->update();
                    } else {
                        playlist->save();
                    }
                    playlistId = playlist->getId();
                } else if (!playlistId && playlist) {
                    playlistId = playlist->getId();
                }
                if (song && song->sync()) {
                    if (song->getId()) {
                        song->update();
                    } else {
                        song->save();
                    }
                    songId = song->getId();
                } else if (!songId && song) {
                    songId = song->getId();
                }

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into PlaylistEntries (playlistId, songId, position, time) values (?, ?, ?, ?)");
                if (playlistId > 0) ps->setInt(1, playlistId);
                else ps->setNull(1, sql::DataType::INTEGER);
                if (songId > 0) ps->setInt(2, songId);
                else ps->setNull(2, sql::DataType::INTEGER);
                ps->setInt(3, position);
                if (!time.empty()) ps->setString(4, time);
                else ps->setNull(4, sql::DataType::VARCHAR);
                int saved = ps->executeUpdate();
                if (!saved) {
                    LOG(WARNING) << "Not able to save playlistEntry";
                    return saved;
                } else {
                    id = MysqlAccess::getInstance().getLastInsertId();
                    if (id == 0) {
                        LOG(WARNING) << "Inserted playlistEntry, but unable to retreive inserted ID.";
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

    bool PlaylistEntry::sync() {
        PlaylistEntry* playlistEntry = findById(id);
        if (!playlistEntry) {
            if (!playlistId && playlist) {
                playlist->sync();
                playlistId = playlist->getId();
            }
            if (!songId && song) {
                song->sync();
                songId = song->getId();
            }
        }
        if (!playlistEntry) playlistEntry = findByPlaylistIdAndSongId(getPlaylistId(), getSongId());
        if (!playlistEntry) return true;

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != playlistEntry->getId()) {
            if (id) {
                LOG(INFO) << "updating playlistEntry " << id << " id from " << playlistEntry->getId() << " to " << id;
                needsUpdate = true;
            } else {
                id = playlistEntry->getId();
            }
        }
        if (playlistId != playlistEntry->getPlaylistId()) {
            if (playlistId) {
                LOG(INFO) << "updating playlistEntry " << id << " playlistId from " << playlistEntry->getPlaylistId() << " to " << playlistId;
                needsUpdate = true;
            } else {
                playlistId = playlistEntry->getPlaylistId();
            }
        }
        if (playlist) needsUpdate |= playlist->sync();
        if (songId != playlistEntry->getSongId()) {
            if (songId) {
                LOG(INFO) << "updating playlistEntry " << id << " songId from " << playlistEntry->getSongId() << " to " << songId;
                needsUpdate = true;
            } else {
                songId = playlistEntry->getSongId();
            }
        }
        if (song) needsUpdate |= song->sync();
        if (position != playlistEntry->getPosition()) {
            if (position) {
                LOG(INFO) << "updating playlistEntry " << id << " position from " << playlistEntry->getPosition() << " to " << position;
                needsUpdate = true;
            } else {
                position = playlistEntry->getPosition();
            }
        }
        if (time.compare(playlistEntry->getTime())  && (!boost::regex_match(time, match1, decimal) || !boost::regex_match(playlistEntry->getTime(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!time.empty()) {
                LOG(INFO) << "updating playlistEntry " << id << " time from " << playlistEntry->getTime() << " to " << time;
                needsUpdate = true;
            } else {
                time = playlistEntry->getTime();
            }
        }
        return needsUpdate;
    }

    int PlaylistEntry::erase() {
        for (int i = 0; i < 3; ++i) {
            try {
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("delete from PlaylistEntries where id=?");
                ps->setInt(1, id);
                int erased = ps->executeUpdate();
                if (!erased) {
                    LOG(WARNING) << "Not able to erase playlistEntry";
                }
                return erased;
            } catch (sql::SQLException &e) {
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }


# pragma mark accessors

    const int PlaylistEntry::getId() const { return id; }
    void PlaylistEntry::setId(const int id) { this->id = id; }

    const int PlaylistEntry::getPlaylistId() const { 
        return (!playlistId && playlist) ? playlist->getId() : playlistId;
    }
    void PlaylistEntry::setPlaylistId(const int playlistId) {
        this->playlistId = playlistId;
        delete playlist;
        playlist = NULL;
    }

    Playlist* PlaylistEntry::getPlaylist() {
        if (!playlist && playlistId) {
            playlist = Playlist::findById(playlistId);
        }
        return playlist;
    }
    Playlist* PlaylistEntry::getPlaylistConst() const {
        return (!playlist && playlistId) ? Playlist::findById(playlistId) : playlist;
    }
    void PlaylistEntry::setPlaylist(const Playlist& playlist) {
        this->playlistId = playlist.getId();
        delete this->playlist;
        this->playlist = new Playlist(playlist);
    }
    void PlaylistEntry::setPlaylist(Playlist* playlist) {
        this->playlistId = playlist->getId();
        delete this->playlist;
        this->playlist = playlist;
    }

    const int PlaylistEntry::getSongId() const { 
        return (!songId && song) ? song->getId() : songId;
    }
    void PlaylistEntry::setSongId(const int songId) {
        this->songId = songId;
        delete song;
        song = NULL;
    }

    Song* PlaylistEntry::getSong() {
        if (!song && songId) {
            song = Song::findById(songId);
        }
        return song;
    }
    Song* PlaylistEntry::getSongConst() const {
        return (!song && songId) ? Song::findById(songId) : song;
    }
    void PlaylistEntry::setSong(const Song& song) {
        this->songId = song.getId();
        delete this->song;
        this->song = new Song(song);
    }
    void PlaylistEntry::setSong(Song* song) {
        this->songId = song->getId();
        delete this->song;
        this->song = song;
    }

    const int PlaylistEntry::getPosition() const { return position; }
    void PlaylistEntry::setPosition(const int position) { this->position = position; }

    const string& PlaylistEntry::getTime() const { return time; }
    void PlaylistEntry::setTime(const string& time) { this->time = time; }

}
}
