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
        if (mix.getOutSong()) setOutSong(*mix.getOutSong());
        if (mix.getInSong()) setInSong(*mix.getInSong());
    }

    void Mix::operator=(const Mix& mix) {
        id = mix.getId();
        outSongId = mix.getOutSongId();
        outSong = NULL;
        inSongId = mix.getInSongId();
        inSong = NULL;
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
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    Mix* Mix::findByOutSongIdAndInSongId(int outSongId, int inSongId) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Mixes.* from Mixes where outSongId = ? and inSongId = ?");
            ps->setInt(1, outSongId);
            ps->setInt(2, inSongId);
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
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<Mix>* Mix::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Mixes.* from Mixes");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<Mix> *dtrs = new ResultSetIterator<Mix>(rs);
        return dtrs;
    }

# pragma mark persistence

    int Mix::update() {
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
            ps->setInt(1, outSongId);
            ps->setInt(2, inSongId);
            ps->setString(3, bpmDiff);
            ps->setInt(4, rank);
            ps->setString(5, comments);
            ps->setBoolean(6, addon);
            ps->setInt(7, id);
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

    int Mix::save() {
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
            ps->setInt(1, outSongId);
            ps->setInt(2, inSongId);
            ps->setString(3, bpmDiff);
            ps->setInt(4, rank);
            ps->setString(5, comments);
            ps->setBoolean(6, addon);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save mix" << endl;
                return saved;
            } else {
                id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted mix, but unable to retreive inserted ID." << endl;
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

    bool Mix::sync() {
        Mix* mix = findById(id);
        if (!mix) mix = findByOutSongIdAndInSongId(outSongId, inSongId);
        if (!mix) {
            if (!outSongId && outSong) {
                outSong->sync();
                outSongId = outSong->getId();
            }
            if (!inSongId && inSong) {
                inSong->sync();
                inSongId = inSong->getId();
            }
            return true;
        }

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != mix->getId()) {
            if (id) {
                cout << "updating mix " << id << " id from " << mix->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = mix->getId();
            }
        }
        if (outSongId != mix->getOutSongId()) {
            if (outSongId) {
                cout << "updating mix " << id << " outSongId from " << mix->getOutSongId() << " to " << outSongId << endl;
                needsUpdate = true;
            } else {
                outSongId = mix->getOutSongId();
            }
        }
        if (outSong) needsUpdate |= outSong->sync();
        if (inSongId != mix->getInSongId()) {
            if (inSongId) {
                cout << "updating mix " << id << " inSongId from " << mix->getInSongId() << " to " << inSongId << endl;
                needsUpdate = true;
            } else {
                inSongId = mix->getInSongId();
            }
        }
        if (inSong) needsUpdate |= inSong->sync();
        if (bpmDiff.compare(mix->getBpmDiff())  && (!boost::regex_match(bpmDiff, match1, decimal) || !boost::regex_match(mix->getBpmDiff(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!bpmDiff.empty()) {
                cout << "updating mix " << id << " bpmDiff from " << mix->getBpmDiff() << " to " << bpmDiff << endl;
                needsUpdate = true;
            } else {
                bpmDiff = mix->getBpmDiff();
            }
        }
        if (rank != mix->getRank()) {
            if (rank) {
                cout << "updating mix " << id << " rank from " << mix->getRank() << " to " << rank << endl;
                needsUpdate = true;
            } else {
                rank = mix->getRank();
            }
        }
        if (comments.compare(mix->getComments())  && (!boost::regex_match(comments, match1, decimal) || !boost::regex_match(mix->getComments(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!comments.empty()) {
                cout << "updating mix " << id << " comments from " << mix->getComments() << " to " << comments << endl;
                needsUpdate = true;
            } else {
                comments = mix->getComments();
            }
        }
        if (addon != mix->getAddon()) {
            if (addon) {
                cout << "updating mix " << id << " addon from " << mix->getAddon() << " to " << addon << endl;
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

    const int Mix::getOutSongId() const { return outSongId; }
    void Mix::setOutSongId(const int outSongId) {
        this->outSongId = outSongId;
        delete outSong;
        outSong = NULL;
    }

    Song* Mix::getOutSong() const {
        if (!outSong && outSongId)
            return Song::findById(outSongId);
        return outSong;
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

    const int Mix::getInSongId() const { return inSongId; }
    void Mix::setInSongId(const int inSongId) {
        this->inSongId = inSongId;
        delete inSong;
        inSong = NULL;
    }

    Song* Mix::getInSong() const {
        if (!inSong && inSongId)
            return Song::findById(inSongId);
        return inSong;
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
