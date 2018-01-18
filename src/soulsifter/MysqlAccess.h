//
//  MysqlAccess.h
//  soul-sifter
//
//  Created by Robby Neale on 11/11/12.
//
//  TODO make this derived from a generic version

#ifndef __soul_sifter__MysqlAccess__
#define __soul_sifter__MysqlAccess__

#include <chrono>
#include <map>
#include <string>
#include <thread>

#include <boost/thread/tss.hpp>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class Connection;
class Driver;

namespace dogatech {
namespace soulsifter {
    
    // public helper methods for working with times & a db
    time_t timeFromString(const std::string& str);
    std::string stringFromTime(const time_t time);

class MysqlAccess {
public:
    ~MysqlAccess();
    
    static MysqlAccess& getInstance() {
      // instantiated on first use per thread
      static boost::thread_specific_ptr<MysqlAccess> instance;
      if (!instance.get()) {
        instance.reset(new MysqlAccess());
      }
      return *instance;
    }

    template<typename F>
    static void* execute(F f) {
        for (int i = 0; i < 3; ++i) {
            try {
                return f();
            } catch (sql::SQLException &e) {
                std::cout << "ERROR: SQLException in " << __FILE__;
                std::cout << " (" << __func__<< ") on line " << __LINE__ << std::endl;
                std::cout << "ERROR: " << e.what();
                std::cout << " (MySQL error code: " << e.getErrorCode();
                std::cout << ", SQLState: " << e.getSQLState() << ")" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        return 0;
    }

    sql::Connection *getConnection() {
        return connection;
    }
    
    sql::PreparedStatement* getPreparedStatement(std::string query);
    
    const int getLastInsertId();
    
private:
    MysqlAccess();
    MysqlAccess(MysqlAccess const&);
    void operator=(MysqlAccess const&);
    
    bool connect();
    bool disconnect();
    sql::Driver *driver;
    sql::Connection *connection;
    std::map<std::string, sql::PreparedStatement*> preparedStatements;
};
  
}
}

#endif /* defined(__soul_sifter__MysqlAccess__) */
