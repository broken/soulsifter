//
//  MusicVideo.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "MusicVideo.h"

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
#include "Song.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    MusicVideo::MusicVideo() :
    id(0),
    songId(0),
    song(NULL),
    filePath(),
    thumbnailFilePath() {
    }

    MusicVideo::MusicVideo(const MusicVideo& musicVideo) :
    id(musicVideo.getId()),
    songId(musicVideo.getSongId()),
    song(NULL),
    filePath(musicVideo.getFilePath()),
    thumbnailFilePath(musicVideo.getThumbnailFilePath()) {
        if (musicVideo.getSong()) setSong(*musicVideo.getSong());
    }

    void MusicVideo::operator=(const MusicVideo& musicVideo) {
        id = musicVideo.getId();
        songId = musicVideo.getSongId();
        if (!musicVideo.getSongId() && musicVideo.getSong()) {
            if (!song) song = new Song(*musicVideo.getSong());
            else *song = *musicVideo.getSong();
        } else {
            delete song;
            song = NULL;
        }
        filePath = musicVideo.getFilePath();
        thumbnailFilePath = musicVideo.getThumbnailFilePath();
    }

    MusicVideo::~MusicVideo() {
        delete song;
        song = NULL;
    }

    void MusicVideo::clear() {
        id = 0;
        songId = 0;
        delete song;
        song = NULL;
        filePath.clear();
        thumbnailFilePath.clear();
    }

# pragma mark static methods

    void MusicVideo::populateFields(const sql::ResultSet* rs, MusicVideo* musicVideo) {
        musicVideo->setId(rs->getInt("id"));
        musicVideo->setSongId(rs->getInt("songId"));
        musicVideo->setFilePath(rs->getString("filePath"));
        musicVideo->setThumbnailFilePath(rs->getString("thumbnailFilePath"));
    }

    MusicVideo* MusicVideo::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select MusicVideos.* from MusicVideos where MusicVideos.id = ?");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            MusicVideo *musicVideo = NULL;
            if (rs->next()) {
                musicVideo = new MusicVideo();
                populateFields(rs, musicVideo);
            }
            rs->close();
            delete rs;

            return musicVideo;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    MusicVideo* MusicVideo::findBySongId(int songId) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select MusicVideos.* from MusicVideos where MusicVideos.songId = ?");
            ps->setInt(1, songId);
            sql::ResultSet *rs = ps->executeQuery();
            MusicVideo *musicVideo = NULL;
            if (rs->next()) {
                musicVideo = new MusicVideo();
                populateFields(rs, musicVideo);
            }
            rs->close();
            delete rs;

            return musicVideo;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<MusicVideo>* MusicVideo::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select MusicVideos.* from MusicVideos");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<MusicVideo> *dtrs = new ResultSetIterator<MusicVideo>(rs);
        return dtrs;
    }

# pragma mark persistence

    int MusicVideo::update() {
        try {
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

            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update MusicVideos set songId=?, filePath=?, thumbnailFilePath=? where id=?");
            if (songId > 0) ps->setInt(1, songId);
            else ps->setNull(1, sql::DataType::INTEGER);
            if (!filePath.empty()) ps->setString(2, filePath);
            else ps->setNull(2, sql::DataType::VARCHAR);
            if (!thumbnailFilePath.empty()) ps->setString(3, thumbnailFilePath);
            else ps->setNull(3, sql::DataType::VARCHAR);
            ps->setInt(4, id);
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

    int MusicVideo::save() {
        try {
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

            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into MusicVideos (songId, filePath, thumbnailFilePath) values (?, ?, ?)");
            if (songId > 0) ps->setInt(1, songId);
            else ps->setNull(1, sql::DataType::INTEGER);
            if (!filePath.empty()) ps->setString(2, filePath);
            else ps->setNull(2, sql::DataType::VARCHAR);
            if (!thumbnailFilePath.empty()) ps->setString(3, thumbnailFilePath);
            else ps->setNull(3, sql::DataType::VARCHAR);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save musicVideo" << endl;
                return saved;
            } else {
                id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted musicVideo, but unable to retreive inserted ID." << endl;
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

    bool MusicVideo::sync() {
        MusicVideo* musicVideo = findById(id);
        if (!musicVideo) {
            if (!songId && song) {
                song->sync();
                songId = song->getId();
            }
            return true;
        }

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != musicVideo->getId()) {
            if (id) {
                cout << "updating musicVideo " << id << " id from " << musicVideo->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = musicVideo->getId();
            }
        }
        if (songId != musicVideo->getSongId()) {
            if (songId) {
                cout << "updating musicVideo " << id << " songId from " << musicVideo->getSongId() << " to " << songId << endl;
                needsUpdate = true;
            } else {
                songId = musicVideo->getSongId();
            }
        }
        if (song) needsUpdate |= song->sync();
        if (filePath.compare(musicVideo->getFilePath())  && (!boost::regex_match(filePath, match1, decimal) || !boost::regex_match(musicVideo->getFilePath(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!filePath.empty()) {
                cout << "updating musicVideo " << id << " filePath from " << musicVideo->getFilePath() << " to " << filePath << endl;
                needsUpdate = true;
            } else {
                filePath = musicVideo->getFilePath();
            }
        }
        if (thumbnailFilePath.compare(musicVideo->getThumbnailFilePath())  && (!boost::regex_match(thumbnailFilePath, match1, decimal) || !boost::regex_match(musicVideo->getThumbnailFilePath(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!thumbnailFilePath.empty()) {
                cout << "updating musicVideo " << id << " thumbnailFilePath from " << musicVideo->getThumbnailFilePath() << " to " << thumbnailFilePath << endl;
                needsUpdate = true;
            } else {
                thumbnailFilePath = musicVideo->getThumbnailFilePath();
            }
        }
        return needsUpdate;
    }


# pragma mark accessors

    const int MusicVideo::getId() const { return id; }
    void MusicVideo::setId(const int id) { this->id = id; }

    const int MusicVideo::getSongId() const { return songId; }
    void MusicVideo::setSongId(const int songId) {
        this->songId = songId;
        delete song;
        song = NULL;
    }

    Song* MusicVideo::getSong() const {
        if (!song && songId)
            return Song::findById(songId);
        return song;
    }
    void MusicVideo::setSong(const Song& song) {
        this->songId = song.getId();
        delete this->song;
        this->song = new Song(song);
    }
    void MusicVideo::setSong(Song* song) {
        this->songId = song->getId();
        delete this->song;
        this->song = song;
    }

    const string& MusicVideo::getFilePath() const { return filePath; }
    void MusicVideo::setFilePath(const string& filePath) { this->filePath = filePath; }

    const string& MusicVideo::getThumbnailFilePath() const { return thumbnailFilePath; }
    void MusicVideo::setThumbnailFilePath(const string& thumbnailFilePath) { this->thumbnailFilePath = thumbnailFilePath; }

}
}
