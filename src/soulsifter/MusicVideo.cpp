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
#include <g3log/g3log.hpp>

#include "MysqlAccess.h"
#include "DTVectorUtil.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    MusicVideo::MusicVideo() :
    id(0),
    filePath(),
    thumbnailFilePath() {
    }

    MusicVideo::MusicVideo(const MusicVideo& musicVideo) :
    id(musicVideo.getId()),
    filePath(musicVideo.getFilePath()),
    thumbnailFilePath(musicVideo.getThumbnailFilePath()) {
    }

    void MusicVideo::operator=(const MusicVideo& musicVideo) {
        id = musicVideo.getId();
        filePath = musicVideo.getFilePath();
        thumbnailFilePath = musicVideo.getThumbnailFilePath();
    }

    MusicVideo::~MusicVideo() {
    }

    void MusicVideo::clear() {
        id = 0;
        filePath.clear();
        thumbnailFilePath.clear();
    }

# pragma mark static methods

    void MusicVideo::populateFields(const sql::ResultSet* rs, MusicVideo* musicVideo) {
        musicVideo->setId(rs->getInt("id"));
        musicVideo->setFilePath(rs->getString("filePath"));
        musicVideo->setThumbnailFilePath(rs->getString("thumbnailFilePath"));
    }

    MusicVideo* MusicVideo::findById(int id) {
        for (int i = 0; i < 2; ++i) {
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
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    ResultSetIterator<MusicVideo>* MusicVideo::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select MusicVideos.* from MusicVideos");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<MusicVideo> *dtrs = new ResultSetIterator<MusicVideo>(rs);
        return dtrs;
    }

# pragma mark persistence

    int MusicVideo::update() {
        for (int i = 0; i < 2; ++i) {
            try {

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update MusicVideos set filePath=?, thumbnailFilePath=? where id=?");
                if (!filePath.empty()) ps->setString(1, filePath);
                else ps->setNull(1, sql::DataType::VARCHAR);
                if (!thumbnailFilePath.empty()) ps->setString(2, thumbnailFilePath);
                else ps->setNull(2, sql::DataType::VARCHAR);
                ps->setInt(3, id);
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

    int MusicVideo::save() {
        for (int i = 0; i < 2; ++i) {
            try {

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into MusicVideos (filePath, thumbnailFilePath) values (?, ?)");
                if (!filePath.empty()) ps->setString(1, filePath);
                else ps->setNull(1, sql::DataType::VARCHAR);
                if (!thumbnailFilePath.empty()) ps->setString(2, thumbnailFilePath);
                else ps->setNull(2, sql::DataType::VARCHAR);
                int saved = ps->executeUpdate();
                if (!saved) {
                    LOG(WARNING) << "Not able to save musicVideo";
                    return saved;
                } else {
                    id = MysqlAccess::getInstance().getLastInsertId();
                    if (id == 0) {
                        LOG(WARNING) << "Inserted musicVideo, but unable to retreive inserted ID.";
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

    bool MusicVideo::sync() {
        MusicVideo* musicVideo = findById(id);
        if (!musicVideo) return true;

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != musicVideo->getId()) {
            if (id) {
                LOG(INFO) << "updating musicVideo " << id << " id from " << musicVideo->getId() << " to " << id;
                needsUpdate = true;
            } else {
                id = musicVideo->getId();
            }
        }
        if (filePath.compare(musicVideo->getFilePath())  && (!boost::regex_match(filePath, match1, decimal) || !boost::regex_match(musicVideo->getFilePath(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!filePath.empty()) {
                LOG(INFO) << "updating musicVideo " << id << " filePath from " << musicVideo->getFilePath() << " to " << filePath;
                needsUpdate = true;
            } else {
                filePath = musicVideo->getFilePath();
            }
        }
        if (thumbnailFilePath.compare(musicVideo->getThumbnailFilePath())  && (!boost::regex_match(thumbnailFilePath, match1, decimal) || !boost::regex_match(musicVideo->getThumbnailFilePath(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!thumbnailFilePath.empty()) {
                LOG(INFO) << "updating musicVideo " << id << " thumbnailFilePath from " << musicVideo->getThumbnailFilePath() << " to " << thumbnailFilePath;
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

    const string& MusicVideo::getFilePath() const { return filePath; }
    void MusicVideo::setFilePath(const string& filePath) { this->filePath = filePath; }

    const string& MusicVideo::getThumbnailFilePath() const { return thumbnailFilePath; }
    void MusicVideo::setThumbnailFilePath(const string& thumbnailFilePath) { this->thumbnailFilePath = thumbnailFilePath; }

}
}
