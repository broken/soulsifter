//
//  Mix.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "Mix.h"

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
#include "Song.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    Mix::Mix() :
    id(0),
    outSongId(0),
    outSong(NULL),
    inSongId(0),
    inSong(NULL),
    bpmDiff(),
    rank(0),
    comments(),
    addon(false) {
    }

    Mix::Mix(const Mix& mix) :
    id(mix.getId()),
    outSongId(mix.getOutSongId()),
    outSong(NULL),
    inSongId(mix.getInSongId()),
    inSong(NULL),
    bpmDiff(mix.getBpmDiff()),
    rank(mix.getRank()),
    comments(mix.getComments()),
    addon(mix.getAddon()) {
        if (mix.outSong) setOutSong(*mix.outSong);
        if (mix.inSong) setInSong(*mix.inSong);
    }

    void Mix::operator=(const Mix& mix) {
        id = mix.getId();
        outSongId = mix.getOutSongId();
        if (!mix.getOutSongId() && mix.outSong) {
            if (!outSong) outSong = new Song(*mix.outSong);
            else *outSong = *mix.outSong;
        } else {
            delete outSong;
            outSong = NULL;
        }
        inSongId = mix.getInSongId();
        if (!mix.getInSongId() && mix.inSong) {
            if (!inSong) inSong = new Song(*mix.inSong);
            else *inSong = *mix.inSong;
        } else {
            delete inSong;
            inSong = NULL;
        }
        bpmDiff = mix.getBpmDiff();
        rank = mix.getRank();
        comments = mix.getComments();
        addon = mix.getAddon();
    }

    Mix::~Mix() {
        delete outSong;
        outSong = NULL;
        delete inSong;
        inSong = NULL;
    }

    void Mix::clear() {
        id = 0;
        outSongId = 0;
        delete outSong;
        outSong = NULL;
        inSongId = 0;
        delete inSong;
        inSong = NULL;
        bpmDiff.clear();
        rank = 0;
        comments.clear();
        addon = false;
    }

# pragma mark static methods

    void Mix::populateFields(const sql::ResultSet* rs, Mix* mix) {
        mix->setId(rs->getInt("id"));
        mix->setOutSongId(rs->getInt("outSongId"));
        mix->setInSongId(rs->getInt("inSongId"));
        mix->setBpmDiff(rs->getString("bpmDiff"));
        mix->setRank(rs->getInt("rank"));
        mix->setComments(rs->getString("comments"));
        mix->setAddon(rs->getBoolean("addon"));
    }

    Mix* Mix::findById(int id) {
        for (int i = 0; i < 3; ++i) {
            try {
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Mixes.* from Mixes where Mixes.id = ?");
                ps->setInt(1, id);
                sql::ResultSet *rs = ps->executeQuery();
                Mix *mix = NULL;
                if (rs->next()) {
                    mix = new Mix();
                    populateFields(rs, mix);
                }
                rs->close();
                delete rs;

                return mix;
            } catch (sql::SQLException &e) {
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    Mix* Mix::findByOutSongIdAndInSongId(int outSongId, int inSongId) {
        for (int i = 0; i < 3; ++i) {
            try {
                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Mixes.* from Mixes where ifnull(outSongId,0) = ifnull(?,0) and ifnull(inSongId,0) = ifnull(?,0)");
                if (outSongId > 0) ps->setInt(1, outSongId);
                else ps->setNull(1, sql::DataType::INTEGER);
                if (inSongId > 0) ps->setInt(2, inSongId);
                else ps->setNull(2, sql::DataType::INTEGER);
                sql::ResultSet *rs = ps->executeQuery();
                Mix *mix = NULL;
                if (rs->next()) {
                    mix = new Mix();
                    populateFields(rs, mix);
                }
                rs->close();
                delete rs;

                return mix;
            } catch (sql::SQLException &e) {
                LOG(WARNING) << "ERROR: SQLException in " << __FILE__ << " (" << __func__<< ") on line " << __LINE__;
                LOG(WARNING) << "ERROR: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << ")";
                bool reconnected = MysqlAccess::getInstance().reconnect();
                LOG(INFO) << (reconnected ? "Successful" : "Failed") << " mysql reconnection";
            }
        }
        LOG(FATAL) << "Unable to complete model operation";
    }

    ResultSetIterator<Mix>* Mix::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Mixes.* from Mixes");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<Mix> *dtrs = new ResultSetIterator<Mix>(rs);
        return dtrs;
    }

# pragma mark persistence

    int Mix::update() {
        for (int i = 0; i < 3; ++i) {
            try {
                if (outSong && outSong->sync()) {
                    if (outSong->getId()) {
                        outSong->update();
                    } else {
                        outSong->save();
                    }
                    outSongId = outSong->getId();
                } else if (!outSongId && outSong) {
                    outSongId = outSong->getId();
                }
                if (inSong && inSong->sync()) {
                    if (inSong->getId()) {
                        inSong->update();
                    } else {
                        inSong->save();
                    }
                    inSongId = inSong->getId();
                } else if (!inSongId && inSong) {
                    inSongId = inSong->getId();
                }

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Mixes set outSongId=?, inSongId=?, bpmDiff=?, rank=?, comments=?, addon=? where id=?");
                if (outSongId > 0) ps->setInt(1, outSongId);
                else ps->setNull(1, sql::DataType::INTEGER);
                if (inSongId > 0) ps->setInt(2, inSongId);
                else ps->setNull(2, sql::DataType::INTEGER);
                if (!bpmDiff.empty()) ps->setString(3, bpmDiff);
                else ps->setNull(3, sql::DataType::VARCHAR);
                if (rank > 0) ps->setInt(4, rank);
                else ps->setNull(4, sql::DataType::INTEGER);
                if (!comments.empty()) ps->setString(5, comments);
                else ps->setNull(5, sql::DataType::VARCHAR);
                ps->setBoolean(6, addon);
                ps->setInt(7, id);
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

    int Mix::save() {
        for (int i = 0; i < 3; ++i) {
            try {
                if (outSong && outSong->sync()) {
                    if (outSong->getId()) {
                        outSong->update();
                    } else {
                        outSong->save();
                    }
                    outSongId = outSong->getId();
                } else if (!outSongId && outSong) {
                    outSongId = outSong->getId();
                }
                if (inSong && inSong->sync()) {
                    if (inSong->getId()) {
                        inSong->update();
                    } else {
                        inSong->save();
                    }
                    inSongId = inSong->getId();
                } else if (!inSongId && inSong) {
                    inSongId = inSong->getId();
                }

                sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Mixes (outSongId, inSongId, bpmDiff, rank, comments, addon) values (?, ?, ?, ?, ?, ?)");
                if (outSongId > 0) ps->setInt(1, outSongId);
                else ps->setNull(1, sql::DataType::INTEGER);
                if (inSongId > 0) ps->setInt(2, inSongId);
                else ps->setNull(2, sql::DataType::INTEGER);
                if (!bpmDiff.empty()) ps->setString(3, bpmDiff);
                else ps->setNull(3, sql::DataType::VARCHAR);
                if (rank > 0) ps->setInt(4, rank);
                else ps->setNull(4, sql::DataType::INTEGER);
                if (!comments.empty()) ps->setString(5, comments);
                else ps->setNull(5, sql::DataType::VARCHAR);
                ps->setBoolean(6, addon);
                int saved = ps->executeUpdate();
                if (!saved) {
                    LOG(WARNING) << "Not able to save mix";
                    return saved;
                } else {
                    id = MysqlAccess::getInstance().getLastInsertId();
                    if (id == 0) {
                        LOG(WARNING) << "Inserted mix, but unable to retreive inserted ID.";
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

    bool Mix::sync() {
        Mix* mix = findById(id);
        if (!mix) {
            if (!outSongId && outSong) {
                outSong->sync();
                outSongId = outSong->getId();
            }
            if (!inSongId && inSong) {
                inSong->sync();
                inSongId = inSong->getId();
            }
        }
        if (!mix) mix = findByOutSongIdAndInSongId(getOutSongId(), getInSongId());
        if (!mix) return true;

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != mix->getId()) {
            if (id) {
                LOG(INFO) << "updating mix " << id << " id from " << mix->getId() << " to " << id;
                needsUpdate = true;
            } else {
                id = mix->getId();
            }
        }
        if (outSongId != mix->getOutSongId()) {
            if (outSongId) {
                LOG(INFO) << "updating mix " << id << " outSongId from " << mix->getOutSongId() << " to " << outSongId;
                needsUpdate = true;
            } else {
                outSongId = mix->getOutSongId();
            }
        }
        if (outSong) needsUpdate |= outSong->sync();
        if (inSongId != mix->getInSongId()) {
            if (inSongId) {
                LOG(INFO) << "updating mix " << id << " inSongId from " << mix->getInSongId() << " to " << inSongId;
                needsUpdate = true;
            } else {
                inSongId = mix->getInSongId();
            }
        }
        if (inSong) needsUpdate |= inSong->sync();
        if (bpmDiff.compare(mix->getBpmDiff())  && (!boost::regex_match(bpmDiff, match1, decimal) || !boost::regex_match(mix->getBpmDiff(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!bpmDiff.empty()) {
                LOG(INFO) << "updating mix " << id << " bpmDiff from " << mix->getBpmDiff() << " to " << bpmDiff;
                needsUpdate = true;
            } else {
                bpmDiff = mix->getBpmDiff();
            }
        }
        if (rank != mix->getRank()) {
            if (rank) {
                LOG(INFO) << "updating mix " << id << " rank from " << mix->getRank() << " to " << rank;
                needsUpdate = true;
            } else {
                rank = mix->getRank();
            }
        }
        if (comments.compare(mix->getComments())  && (!boost::regex_match(comments, match1, decimal) || !boost::regex_match(mix->getComments(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!comments.empty()) {
                LOG(INFO) << "updating mix " << id << " comments from " << mix->getComments() << " to " << comments;
                needsUpdate = true;
            } else {
                comments = mix->getComments();
            }
        }
        if (addon != mix->getAddon()) {
            if (addon) {
                LOG(INFO) << "updating mix " << id << " addon from " << mix->getAddon() << " to " << addon;
                needsUpdate = true;
            } else {
                addon = mix->getAddon();
            }
        }
        return needsUpdate;
    }


# pragma mark accessors

    const int Mix::getId() const { return id; }
    void Mix::setId(const int id) { this->id = id; }

    const int Mix::getOutSongId() const { 
        return (!outSongId && outSong) ? outSong->getId() : outSongId;
    }
    void Mix::setOutSongId(const int outSongId) {
        this->outSongId = outSongId;
        delete outSong;
        outSong = NULL;
    }

    Song* Mix::getOutSong() {
        if (!outSong && outSongId) {
            outSong = Song::findById(outSongId);
        }
        return outSong;
    }
    Song* Mix::getOutSongOnce() const {
        return (!outSong && outSongId) ? Song::findById(outSongId) : outSong;
    }
    void Mix::setOutSong(const Song& outSong) {
        this->outSongId = outSong.getId();
        delete this->outSong;
        this->outSong = new Song(outSong);
    }
    void Mix::setOutSong(Song* outSong) {
        this->outSongId = outSong->getId();
        delete this->outSong;
        this->outSong = outSong;
    }

    const int Mix::getInSongId() const { 
        return (!inSongId && inSong) ? inSong->getId() : inSongId;
    }
    void Mix::setInSongId(const int inSongId) {
        this->inSongId = inSongId;
        delete inSong;
        inSong = NULL;
    }

    Song* Mix::getInSong() {
        if (!inSong && inSongId) {
            inSong = Song::findById(inSongId);
        }
        return inSong;
    }
    Song* Mix::getInSongOnce() const {
        return (!inSong && inSongId) ? Song::findById(inSongId) : inSong;
    }
    void Mix::setInSong(const Song& inSong) {
        this->inSongId = inSong.getId();
        delete this->inSong;
        this->inSong = new Song(inSong);
    }
    void Mix::setInSong(Song* inSong) {
        this->inSongId = inSong->getId();
        delete this->inSong;
        this->inSong = inSong;
    }

    const string& Mix::getBpmDiff() const { return bpmDiff; }
    void Mix::setBpmDiff(const string& bpmDiff) { this->bpmDiff = bpmDiff; }

    const int Mix::getRank() const { return rank; }
    void Mix::setRank(const int rank) { this->rank = rank; }

    const string& Mix::getComments() const { return comments; }
    void Mix::setComments(const string& comments) { this->comments = comments; }

    const bool Mix::getAddon() const { return addon; }
    void Mix::setAddon(const bool addon) { this->addon = addon; }

}
}
