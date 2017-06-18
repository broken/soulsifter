//
//  Song.cpp
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#include "Song.h"

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
#include "RESong.h"
#include "Album.h"
#include "AlbumPart.h"
#include "Style.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

# pragma mark initialization

    Song::Song() :
    id(0),
    artist(),
    track(),
    title(),
    remixer(),
    featuring(),
    filepath(),
    rating(0),
    dateAdded(NULL),
    bpm(),
    tonicKeys(),
    tonicKey(),
    energy(0),
    comments(),
    trashed(false),
    lowQuality(false),
    googleSongId(),
    durationInMs(0),
    curator(),
    reSongId(0),
    reSong(NULL),
    albumId(0),
    album(NULL),
    albumPartId(0),
    albumPart(NULL),
    styleIds(),
    styles() {
    }

    Song::Song(const Song& song) :
    id(song.getId()),
    artist(song.getArtist()),
    track(song.getTrack()),
    title(song.getTitle()),
    remixer(song.getRemixer()),
    featuring(song.getFeaturing()),
    filepath(song.getFilepath()),
    rating(song.getRating()),
    dateAdded(song.getDateAdded()),
    bpm(song.getBpm()),
    tonicKeys(song.getTonicKeys()),
    tonicKey(song.getTonicKey()),
    energy(song.getEnergy()),
    comments(song.getComments()),
    trashed(song.getTrashed()),
    lowQuality(song.getLowQuality()),
    googleSongId(song.getGoogleSongId()),
    durationInMs(song.getDurationInMs()),
    curator(song.getCurator()),
    reSongId(song.getRESongId()),
    reSong(NULL),
    albumId(song.getAlbumId()),
    album(NULL),
    albumPartId(song.getAlbumPartId()),
    albumPart(NULL),
    styleIds(song.getStyleIds()),
    styles() {
        if (song.reSong) setRESong(*song.reSong);
        if (song.album) setAlbum(*song.album);
        if (song.albumPart) setAlbumPart(*song.albumPart);
    }

    void Song::operator=(const Song& song) {
        id = song.getId();
        artist = song.getArtist();
        track = song.getTrack();
        title = song.getTitle();
        remixer = song.getRemixer();
        featuring = song.getFeaturing();
        filepath = song.getFilepath();
        rating = song.getRating();
        dateAdded = song.getDateAdded();
        bpm = song.getBpm();
        tonicKeys = song.getTonicKeys();
        tonicKey = song.getTonicKey();
        energy = song.getEnergy();
        comments = song.getComments();
        trashed = song.getTrashed();
        lowQuality = song.getLowQuality();
        googleSongId = song.getGoogleSongId();
        durationInMs = song.getDurationInMs();
        curator = song.getCurator();
        reSongId = song.getRESongId();
        if (!song.getRESongId() && song.reSong) {
            if (!reSong) reSong = new RESong(*song.reSong);
            else *reSong = *song.reSong;
        } else {
            delete reSong;
            reSong = NULL;
        }
        albumId = song.getAlbumId();
        if (!song.getAlbumId() && song.album) {
            if (!album) album = new Album(*song.album);
            else *album = *song.album;
        } else {
            delete album;
            album = NULL;
        }
        albumPartId = song.getAlbumPartId();
        if (!song.getAlbumPartId() && song.albumPart) {
            if (!albumPart) albumPart = new AlbumPart(*song.albumPart);
            else *albumPart = *song.albumPart;
        } else {
            delete albumPart;
            albumPart = NULL;
        }
        styleIds = song.getStyleIds();
        deleteVectorPointers(&styles);
    }

    Song::~Song() {
        delete reSong;
        reSong = NULL;
        delete album;
        album = NULL;
        delete albumPart;
        albumPart = NULL;
        while (!styles.empty()) delete styles.back(), styles.pop_back();
    }

    void Song::clear() {
        id = 0;
        artist.clear();
        track.clear();
        title.clear();
        remixer.clear();
        featuring.clear();
        filepath.clear();
        rating = 0;
        dateAdded = 0;
        bpm.clear();
        tonicKeys.clear();
        tonicKey.clear();
        energy = 0;
        comments.clear();
        trashed = false;
        lowQuality = false;
        googleSongId.clear();
        durationInMs = 0;
        curator.clear();
        reSongId = 0;
        delete reSong;
        reSong = NULL;
        albumId = 0;
        delete album;
        album = NULL;
        albumPartId = 0;
        delete albumPart;
        albumPart = NULL;
        styleIds.clear();
        deleteVectorPointers(&styles);
    }

# pragma mark static methods

    void Song::populateFields(const sql::ResultSet* rs, Song* song) {
        song->setId(rs->getInt("id"));
        song->setArtist(rs->getString("artist"));
        song->setTrack(rs->getString("track"));
        song->setTitle(rs->getString("title"));
        song->setRemixer(rs->getString("remixer"));
        song->setFeaturing(rs->getString("featuring"));
        song->setFilepath(rs->getString("filepath"));
        song->setRating(rs->getInt("rating"));
        song->setDateAdded(timeFromString(rs->getString("dateAdded")));
        song->setBpm(rs->getString("bpm"));
        song->setTonicKey(rs->getString("tonicKey"));
        song->setEnergy(rs->getInt("energy"));
        song->setComments(rs->getString("comments"));
        song->setTrashed(rs->getBoolean("trashed"));
        song->setLowQuality(rs->getBoolean("lowQuality"));
        song->setGoogleSongId(rs->getString("googleSongId"));
        song->setDurationInMs(rs->getInt("durationInMs"));
        song->setCurator(rs->getString("curator"));
        song->setRESongId(rs->getInt("reSongId"));
        song->setAlbumId(rs->getInt("albumId"));
        song->setAlbumPartId(rs->getInt("albumPartId"));
        if (!rs->isNull("styleIds")) {
            string csv = rs->getString("styleIds");
            istringstream iss(csv);
            string id;
            while (getline(iss, id, ',')) {
              song->styleIds.push_back(atoi(id.c_str()));
            }
        }
        if (!rs->isNull("tonicKeys")) {
            string dbSet = rs->getString("tonicKeys");
            boost::split(song->tonicKeys, dbSet, boost::is_any_of(","));
        }
    }

    Song* Song::findById(int id) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Songs.*, group_concat(styles.styleId) as styleIds from Songs left outer join SongStyles styles on Songs.id = styles.songId where Songs.id = ? group by Songs.id");
            ps->setInt(1, id);
            sql::ResultSet *rs = ps->executeQuery();
            Song *song = NULL;
            if (rs->next()) {
                song = new Song();
                populateFields(rs, song);
            }
            rs->close();
            delete rs;

            return song;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    Song* Song::findByFilepath(const string& filepath) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Songs.*, group_concat(styles.styleId) as styleIds from Songs left outer join SongStyles styles on Songs.id = styles.songId where Songs.filepath = ? group by Songs.id");
            ps->setString(1, filepath);
            sql::ResultSet *rs = ps->executeQuery();
            Song *song = NULL;
            if (rs->next()) {
                song = new Song();
                populateFields(rs, song);
            }
            rs->close();
            delete rs;

            return song;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    Song* Song::findByGoogleSongId(const string& googleSongId) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Songs.*, group_concat(styles.styleId) as styleIds from Songs left outer join SongStyles styles on Songs.id = styles.songId where Songs.googleSongId = ? group by Songs.id");
            ps->setString(1, googleSongId);
            sql::ResultSet *rs = ps->executeQuery();
            Song *song = NULL;
            if (rs->next()) {
                song = new Song();
                populateFields(rs, song);
            }
            rs->close();
            delete rs;

            return song;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    Song* Song::findByRESongId(int reSongId) {
        try {
            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Songs.*, group_concat(styles.styleId) as styleIds from Songs left outer join SongStyles styles on Songs.id = styles.songId where reSongId = ? group by Songs.id");
            if (reSongId > 0) ps->setInt(1, reSongId);
            else ps->setNull(1, sql::DataType::INTEGER);
            sql::ResultSet *rs = ps->executeQuery();
            Song *song = NULL;
            if (rs->next()) {
                song = new Song();
                populateFields(rs, song);
            }
            rs->close();
            delete rs;

            return song;
        } catch (sql::SQLException &e) {
            cerr << "ERROR: SQLException in " << __FILE__;
            cerr << " (" << __func__<< ") on line " << __LINE__ << endl;
            cerr << "ERROR: " << e.what();
            cerr << " (MySQL error code: " << e.getErrorCode();
            cerr << ", SQLState: " << e.getSQLState() << ")" << endl;
            exit(1);
        }
    }

    ResultSetIterator<Song>* Song::findAll() {
        sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("select Songs.*, group_concat(styles.styleId) as styleIds from Songs left outer join SongStyles styles on Songs.id = styles.songId group by Songs.id");
        sql::ResultSet *rs = ps->executeQuery();
        ResultSetIterator<Song> *dtrs = new ResultSetIterator<Song>(rs);
        return dtrs;
    }

# pragma mark persistence

    int Song::update() {
        try {
            if (reSong && reSong->sync()) {
                if (reSong->getId()) {
                    reSong->update();
                } else {
                    reSong->save();
                }
                reSongId = reSong->getId();
            } else if (!reSongId && reSong) {
                reSongId = reSong->getId();
            }
            if (album && album->sync()) {
                if (album->getId()) {
                    album->update();
                } else {
                    album->save();
                }
                albumId = album->getId();
            } else if (!albumId && album) {
                albumId = album->getId();
            }
            if (albumPart && albumPart->sync()) {
                if (albumPart->getId()) {
                    albumPart->update();
                } else {
                    albumPart->save();
                }
                albumPartId = albumPart->getId();
            } else if (!albumPartId && albumPart) {
                albumPartId = albumPart->getId();
            }

            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("update Songs set artist=?, track=?, title=?, remixer=?, featuring=?, filepath=?, rating=?, dateAdded=?, bpm=?, tonicKeys=?, tonicKey=?, energy=?, comments=?, trashed=?, lowQuality=?, googleSongId=?, durationInMs=?, curator=?, reSongId=?, albumId=?, albumPartId=? where id=?");
            if (!artist.empty()) ps->setString(1, artist);
            else ps->setNull(1, sql::DataType::VARCHAR);
            if (!track.empty()) ps->setString(2, track);
            else ps->setNull(2, sql::DataType::VARCHAR);
            if (!title.empty()) ps->setString(3, title);
            else ps->setNull(3, sql::DataType::VARCHAR);
            if (!remixer.empty()) ps->setString(4, remixer);
            else ps->setNull(4, sql::DataType::VARCHAR);
            if (!featuring.empty()) ps->setString(5, featuring);
            else ps->setNull(5, sql::DataType::VARCHAR);
            if (!filepath.empty()) ps->setString(6, filepath);
            else ps->setNull(6, sql::DataType::VARCHAR);
            ps->setInt(7, rating);
            ps->setString(8, stringFromTime(dateAdded));
            if (!bpm.empty()) ps->setString(9, bpm);
            else ps->setNull(9, sql::DataType::VARCHAR);
            ps->setString(10, setToCsv(tonicKeys));
            if (!tonicKey.empty()) ps->setString(11, tonicKey);
            else ps->setNull(11, sql::DataType::VARCHAR);
            if (energy > 0) ps->setInt(12, energy);
            else ps->setNull(12, sql::DataType::INTEGER);
            if (!comments.empty()) ps->setString(13, comments);
            else ps->setNull(13, sql::DataType::VARCHAR);
            ps->setBoolean(14, trashed);
            ps->setBoolean(15, lowQuality);
            if (!googleSongId.empty()) ps->setString(16, googleSongId);
            else ps->setNull(16, sql::DataType::VARCHAR);
            if (durationInMs > 0) ps->setInt(17, durationInMs);
            else ps->setNull(17, sql::DataType::INTEGER);
            if (!curator.empty()) ps->setString(18, curator);
            else ps->setNull(18, sql::DataType::VARCHAR);
            if (reSongId > 0) ps->setInt(19, reSongId);
            else ps->setNull(19, sql::DataType::INTEGER);
            if (albumId > 0) ps->setInt(20, albumId);
            else ps->setNull(20, sql::DataType::INTEGER);
            if (albumPartId > 0) ps->setInt(21, albumPartId);
            else ps->setNull(21, sql::DataType::INTEGER);
            ps->setInt(22, id);
            int result = ps->executeUpdate();
            if (!styleIds.empty()) {
                stringstream ss("insert ignore into SongStyles (songId, styleId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
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
                ss << "delete ignore from SongStyles where songId = ? and styleId not in (?";
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
                ps = MysqlAccess::getInstance().getPreparedStatement("delete ignore from SongStyles where songId = ?");
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

    int Song::save() {
        try {
            if (reSong && reSong->sync()) {
                if (reSong->getId()) {
                    reSong->update();
                } else {
                    reSong->save();
                }
                reSongId = reSong->getId();
            } else if (!reSongId && reSong) {
                reSongId = reSong->getId();
            }
            if (album && album->sync()) {
                if (album->getId()) {
                    album->update();
                } else {
                    album->save();
                }
                albumId = album->getId();
            } else if (!albumId && album) {
                albumId = album->getId();
            }
            if (albumPart && albumPart->sync()) {
                if (albumPart->getId()) {
                    albumPart->update();
                } else {
                    albumPart->save();
                }
                albumPartId = albumPart->getId();
            } else if (!albumPartId && albumPart) {
                albumPartId = albumPart->getId();
            }

            sql::PreparedStatement *ps = MysqlAccess::getInstance().getPreparedStatement("insert into Songs (artist, track, title, remixer, featuring, filepath, rating, dateAdded, bpm, tonicKeys, tonicKey, energy, comments, trashed, lowQuality, googleSongId, durationInMs, curator, reSongId, albumId, albumPartId) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
            if (!artist.empty()) ps->setString(1, artist);
            else ps->setNull(1, sql::DataType::VARCHAR);
            if (!track.empty()) ps->setString(2, track);
            else ps->setNull(2, sql::DataType::VARCHAR);
            if (!title.empty()) ps->setString(3, title);
            else ps->setNull(3, sql::DataType::VARCHAR);
            if (!remixer.empty()) ps->setString(4, remixer);
            else ps->setNull(4, sql::DataType::VARCHAR);
            if (!featuring.empty()) ps->setString(5, featuring);
            else ps->setNull(5, sql::DataType::VARCHAR);
            if (!filepath.empty()) ps->setString(6, filepath);
            else ps->setNull(6, sql::DataType::VARCHAR);
            ps->setInt(7, rating);
            ps->setString(8, stringFromTime(dateAdded));
            if (!bpm.empty()) ps->setString(9, bpm);
            else ps->setNull(9, sql::DataType::VARCHAR);
            ps->setString(10, setToCsv(tonicKeys));
            if (!tonicKey.empty()) ps->setString(11, tonicKey);
            else ps->setNull(11, sql::DataType::VARCHAR);
            if (energy > 0) ps->setInt(12, energy);
            else ps->setNull(12, sql::DataType::INTEGER);
            if (!comments.empty()) ps->setString(13, comments);
            else ps->setNull(13, sql::DataType::VARCHAR);
            ps->setBoolean(14, trashed);
            ps->setBoolean(15, lowQuality);
            if (!googleSongId.empty()) ps->setString(16, googleSongId);
            else ps->setNull(16, sql::DataType::VARCHAR);
            if (durationInMs > 0) ps->setInt(17, durationInMs);
            else ps->setNull(17, sql::DataType::INTEGER);
            if (!curator.empty()) ps->setString(18, curator);
            else ps->setNull(18, sql::DataType::VARCHAR);
            if (reSongId > 0) ps->setInt(19, reSongId);
            else ps->setNull(19, sql::DataType::INTEGER);
            if (albumId > 0) ps->setInt(20, albumId);
            else ps->setNull(20, sql::DataType::INTEGER);
            if (albumPartId > 0) ps->setInt(21, albumPartId);
            else ps->setNull(21, sql::DataType::INTEGER);
            int saved = ps->executeUpdate();
            if (!saved) {
                cerr << "Not able to save song" << endl;
                return saved;
            } else {
                id = MysqlAccess::getInstance().getLastInsertId();
                if (id == 0) {
                    cerr << "Inserted song, but unable to retreive inserted ID." << endl;
                    return saved;
                }
                if (!styleIds.empty()) {
                    stringstream ss("insert ignore into SongStyles (songId, styleId) values (?, ?)", ios_base::app | ios_base::out | ios_base::ate);
                    for (int i = 1; i < styleIds.size(); ++i) {
                        ss << ", (?, ?)";
                    }
                    ps = MysqlAccess::getInstance().getPreparedStatement(ss.str());
                    for (int i = 0; i < styleIds.size(); ++i) {
                        ps->setInt(i * 2 + 1, id);
                        ps->setInt(i * 2 + 2, styleIds[i]);
                    }
                    if (!ps->executeUpdate()) {
                        cerr << "Did not save style for song " << id << endl;
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

    bool Song::sync() {
        Song* song = findById(id);
        if (!song) song = findByRESongId(getRESongId());
        if (!song) {
            if (!reSongId && reSong) {
                reSong->sync();
                reSongId = reSong->getId();
            }
            if (!albumId && album) {
                album->sync();
                albumId = album->getId();
            }
            if (!albumPartId && albumPart) {
                albumPart->sync();
                albumPartId = albumPart->getId();
            }
            return true;
        }

        // check fields
        bool needsUpdate = false;
        boost::regex decimal("(-?\\d+)\\.?\\d*");
        boost::smatch match1;
        boost::smatch match2;
        if (id != song->getId()) {
            if (id) {
                cout << "updating song " << id << " id from " << song->getId() << " to " << id << endl;
                needsUpdate = true;
            } else {
                id = song->getId();
            }
        }
        if (artist.compare(song->getArtist())  && (!boost::regex_match(artist, match1, decimal) || !boost::regex_match(song->getArtist(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!artist.empty()) {
                cout << "updating song " << id << " artist from " << song->getArtist() << " to " << artist << endl;
                needsUpdate = true;
            } else {
                artist = song->getArtist();
            }
        }
        if (track.compare(song->getTrack())  && (!boost::regex_match(track, match1, decimal) || !boost::regex_match(song->getTrack(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!track.empty()) {
                cout << "updating song " << id << " track from " << song->getTrack() << " to " << track << endl;
                needsUpdate = true;
            } else {
                track = song->getTrack();
            }
        }
        if (title.compare(song->getTitle())  && (!boost::regex_match(title, match1, decimal) || !boost::regex_match(song->getTitle(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!title.empty()) {
                cout << "updating song " << id << " title from " << song->getTitle() << " to " << title << endl;
                needsUpdate = true;
            } else {
                title = song->getTitle();
            }
        }
        if (remixer.compare(song->getRemixer())  && (!boost::regex_match(remixer, match1, decimal) || !boost::regex_match(song->getRemixer(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!remixer.empty()) {
                cout << "updating song " << id << " remixer from " << song->getRemixer() << " to " << remixer << endl;
                needsUpdate = true;
            } else {
                remixer = song->getRemixer();
            }
        }
        if (featuring.compare(song->getFeaturing())  && (!boost::regex_match(featuring, match1, decimal) || !boost::regex_match(song->getFeaturing(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!featuring.empty()) {
                cout << "updating song " << id << " featuring from " << song->getFeaturing() << " to " << featuring << endl;
                needsUpdate = true;
            } else {
                featuring = song->getFeaturing();
            }
        }
        if (filepath.compare(song->getFilepath())  && (!boost::regex_match(filepath, match1, decimal) || !boost::regex_match(song->getFilepath(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!filepath.empty()) {
                cout << "updating song " << id << " filepath from " << song->getFilepath() << " to " << filepath << endl;
                needsUpdate = true;
            } else {
                filepath = song->getFilepath();
            }
        }
        if (rating != song->getRating()) {
            if (rating) {
                cout << "updating song " << id << " rating from " << song->getRating() << " to " << rating << endl;
                needsUpdate = true;
            } else {
                rating = song->getRating();
            }
        }
        if (dateAdded != song->getDateAdded()) {
            if (!song->getDateAdded()) {
                cout << "updating song " << id << " dateAdded from " << song->getDateAdded() << " to " << dateAdded << endl;
                needsUpdate = true;
            } else {
                dateAdded = song->getDateAdded();
            }
        }
        if (bpm.compare(song->getBpm())  && (!boost::regex_match(bpm, match1, decimal) || !boost::regex_match(song->getBpm(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!bpm.empty()) {
                cout << "updating song " << id << " bpm from " << song->getBpm() << " to " << bpm << endl;
                needsUpdate = true;
            } else {
                bpm = song->getBpm();
            }
        }
        if (!equivalentSets<string>(tonicKeys, song->tonicKeys)) {
            if (!containsSet<string>(tonicKeys, song->tonicKeys)) {
                cout << "updating song " << id << " tonicKeys" << endl;
                needsUpdate = true;
            }
            tonicKeys.insert(song->tonicKeys.begin(), song->tonicKeys.end());
        }
        if (tonicKey.compare(song->getTonicKey())  && (!boost::regex_match(tonicKey, match1, decimal) || !boost::regex_match(song->getTonicKey(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!tonicKey.empty()) {
                cout << "updating song " << id << " tonicKey from " << song->getTonicKey() << " to " << tonicKey << endl;
                needsUpdate = true;
            } else {
                tonicKey = song->getTonicKey();
            }
        }
        if (energy != song->getEnergy()) {
            if (energy) {
                cout << "updating song " << id << " energy from " << song->getEnergy() << " to " << energy << endl;
                needsUpdate = true;
            } else {
                energy = song->getEnergy();
            }
        }
        if (comments.compare(song->getComments())  && (!boost::regex_match(comments, match1, decimal) || !boost::regex_match(song->getComments(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!comments.empty()) {
                cout << "updating song " << id << " comments from " << song->getComments() << " to " << comments << endl;
                needsUpdate = true;
            } else {
                comments = song->getComments();
            }
        }
        if (trashed != song->getTrashed()) {
            if (trashed) {
                cout << "updating song " << id << " trashed from " << song->getTrashed() << " to " << trashed << endl;
                needsUpdate = true;
            } else {
                trashed = song->getTrashed();
            }
        }
        if (lowQuality != song->getLowQuality()) {
            if (lowQuality) {
                cout << "updating song " << id << " lowQuality from " << song->getLowQuality() << " to " << lowQuality << endl;
                needsUpdate = true;
            } else {
                lowQuality = song->getLowQuality();
            }
        }
        if (googleSongId.compare(song->getGoogleSongId())  && (!boost::regex_match(googleSongId, match1, decimal) || !boost::regex_match(song->getGoogleSongId(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!googleSongId.empty()) {
                cout << "updating song " << id << " googleSongId from " << song->getGoogleSongId() << " to " << googleSongId << endl;
                needsUpdate = true;
            } else {
                googleSongId = song->getGoogleSongId();
            }
        }
        if (durationInMs != song->getDurationInMs()) {
            if (durationInMs) {
                cout << "updating song " << id << " durationInMs from " << song->getDurationInMs() << " to " << durationInMs << endl;
                needsUpdate = true;
            } else {
                durationInMs = song->getDurationInMs();
            }
        }
        if (curator.compare(song->getCurator())  && (!boost::regex_match(curator, match1, decimal) || !boost::regex_match(song->getCurator(), match2, decimal) || match1[1].str().compare(match2[1].str()))) {
            if (!curator.empty()) {
                cout << "updating song " << id << " curator from " << song->getCurator() << " to " << curator << endl;
                needsUpdate = true;
            } else {
                curator = song->getCurator();
            }
        }
        if (reSongId != song->getRESongId()) {
            if (reSongId) {
                cout << "updating song " << id << " reSongId from " << song->getRESongId() << " to " << reSongId << endl;
                needsUpdate = true;
            } else {
                reSongId = song->getRESongId();
            }
        }
        if (reSong) needsUpdate |= reSong->sync();
        if (albumId != song->getAlbumId()) {
            if (albumId) {
                cout << "updating song " << id << " albumId from " << song->getAlbumId() << " to " << albumId << endl;
                needsUpdate = true;
            } else {
                albumId = song->getAlbumId();
            }
        }
        if (album) needsUpdate |= album->sync();
        if (albumPartId != song->getAlbumPartId()) {
            if (albumPartId) {
                cout << "updating song " << id << " albumPartId from " << song->getAlbumPartId() << " to " << albumPartId << endl;
                needsUpdate = true;
            } else {
                albumPartId = song->getAlbumPartId();
            }
        }
        if (albumPart) needsUpdate |= albumPart->sync();
        if (!equivalentVectors<int>(styleIds, song->getStyleIds())) {
            if (!containsVector<int>(styleIds, song->getStyleIds())) {
                cout << "updating song " << id << " styleIds" << endl;
                needsUpdate = true;
            }
            appendUniqueVector<int>(song->getStyleIds(), &styleIds);
        }
        return needsUpdate;
    }


# pragma mark accessors

    const int Song::getId() const { return id; }
    void Song::setId(const int id) { this->id = id; }

    const string& Song::getArtist() const { return artist; }
    void Song::setArtist(const string& artist) { this->artist = artist; }

    const string& Song::getTrack() const { return track; }
    void Song::setTrack(const string& track) { this->track = track; }

    const string& Song::getTitle() const { return title; }
    void Song::setTitle(const string& title) { this->title = title; }

    const string& Song::getRemixer() const { return remixer; }
    void Song::setRemixer(const string& remixer) { this->remixer = remixer; }

    const string& Song::getFeaturing() const { return featuring; }
    void Song::setFeaturing(const string& featuring) { this->featuring = featuring; }

    const string& Song::getFilepath() const { return filepath; }
    void Song::setFilepath(const string& filepath) { this->filepath = filepath; }

    const int Song::getRating() const { return rating; }
    void Song::setRating(const int rating) { this->rating = rating; }

    const time_t Song::getDateAdded() const { return dateAdded; }
    void Song::setDateAdded(const time_t dateAdded) { this->dateAdded = dateAdded; }

    const string& Song::getBpm() const { return bpm; }
    void Song::setBpm(const string& bpm) { this->bpm = bpm; }

    const set<string>& Song::getTonicKeys() const {
        return tonicKeys;
    }
    void Song::setTonicKeys(const set<string>& tonicKeys) {
        this->tonicKeys = tonicKeys;
    }
    void Song::addTonicKey(const string& tonicKey) {
        this->tonicKeys.insert(tonicKey);
    }
    void Song::removeTonicKey(const string& tonicKey) {
        this->tonicKeys.erase(tonicKey);
    }

    const string& Song::getTonicKey() const { return tonicKey; }
    void Song::setTonicKey(const string& tonicKey) { this->tonicKey = tonicKey; }

    const int Song::getEnergy() const { return energy; }
    void Song::setEnergy(const int energy) { this->energy = energy; }

    const string& Song::getComments() const { return comments; }
    void Song::setComments(const string& comments) { this->comments = comments; }

    const bool Song::getTrashed() const { return trashed; }
    void Song::setTrashed(const bool trashed) { this->trashed = trashed; }

    const bool Song::getLowQuality() const { return lowQuality; }
    void Song::setLowQuality(const bool lowQuality) { this->lowQuality = lowQuality; }

    const string& Song::getGoogleSongId() const { return googleSongId; }
    void Song::setGoogleSongId(const string& googleSongId) { this->googleSongId = googleSongId; }

    const int Song::getDurationInMs() const { return durationInMs; }
    void Song::setDurationInMs(const int durationInMs) { this->durationInMs = durationInMs; }

    const string& Song::getCurator() const { return curator; }
    void Song::setCurator(const string& curator) { this->curator = curator; }

    const int Song::getRESongId() const { 
        return (!reSongId && reSong) ? reSong->getId() : reSongId;
    }
    void Song::setRESongId(const int reSongId) {
        this->reSongId = reSongId;
        delete reSong;
        reSong = NULL;
    }

    RESong* Song::getRESong() {
        if (!reSong && reSongId) {
            reSong = RESong::findById(reSongId);
        }
        return reSong;
    }
    RESong* Song::getRESongOnce() const {
        return (!reSong && reSongId) ? RESong::findById(reSongId) : reSong;
    }
    void Song::setRESong(const RESong& reSong) {
        this->reSongId = reSong.getId();
        delete this->reSong;
        this->reSong = new RESong(reSong);
    }
    void Song::setRESong(RESong* reSong) {
        this->reSongId = reSong->getId();
        delete this->reSong;
        this->reSong = reSong;
    }

    const int Song::getAlbumId() const { 
        return (!albumId && album) ? album->getId() : albumId;
    }
    void Song::setAlbumId(const int albumId) {
        this->albumId = albumId;
        delete album;
        album = NULL;
    }

    Album* Song::getAlbum() {
        if (!album && albumId) {
            album = Album::findById(albumId);
        }
        return album;
    }
    Album* Song::getAlbumOnce() const {
        return (!album && albumId) ? Album::findById(albumId) : album;
    }
    void Song::setAlbum(const Album& album) {
        this->albumId = album.getId();
        delete this->album;
        this->album = new Album(album);
    }
    void Song::setAlbum(Album* album) {
        this->albumId = album->getId();
        delete this->album;
        this->album = album;
    }

    const int Song::getAlbumPartId() const { 
        return (!albumPartId && albumPart) ? albumPart->getId() : albumPartId;
    }
    void Song::setAlbumPartId(const int albumPartId) {
        this->albumPartId = albumPartId;
        delete albumPart;
        albumPart = NULL;
    }

    AlbumPart* Song::getAlbumPart() {
        if (!albumPart && albumPartId) {
            albumPart = AlbumPart::findById(albumPartId);
        }
        return albumPart;
    }
    AlbumPart* Song::getAlbumPartOnce() const {
        return (!albumPart && albumPartId) ? AlbumPart::findById(albumPartId) : albumPart;
    }
    void Song::setAlbumPart(const AlbumPart& albumPart) {
        this->albumPartId = albumPart.getId();
        delete this->albumPart;
        this->albumPart = new AlbumPart(albumPart);
    }
    void Song::setAlbumPart(AlbumPart* albumPart) {
        this->albumPartId = albumPart->getId();
        delete this->albumPart;
        this->albumPart = albumPart;
    }

    const vector<int>& Song::getStyleIds() const { return styleIds; }
    void Song::setStyleIds(const vector<int>& styleIds) {
        while (!styles.empty()) delete styles.back(), styles.pop_back();
        this->styleIds.clear();
        this->styleIds = styleIds;
    }

    const vector<Style*>& Song::getStyles() {
        if (styles.empty() && !styleIds.empty()) {
            for (vector<int>::const_iterator it = styleIds.begin(); it != styleIds.end(); ++it) {
                styles.push_back(Style::findById(*it));
            }
        }
        return styles;
    }
    void Song::setStyles(const vector<Style*>& styles) {
        deleteVectorPointers<Style*>(&this->styles);
        this->styles = styles;
        this->styleIds.clear();
        for (vector<Style*>::const_iterator it = styles.begin(); it != styles.end(); ++it) {
            this->styleIds.push_back((*it)->getId());
        }
    }

}
}
