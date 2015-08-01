//
//  REXml.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__REXml__
#define __soul_sifter__REXml__

#include <set>
#include <string>
#include <vector>

#include "ResultSetIterator.h"

namespace sql {
    class ResultSet;
}

using namespace std;

namespace dogatech {
namespace soulsifter {


    class REXml {
    public:
        REXml();
        explicit REXml(const REXml& reXml);
        ~REXml();
        void clear();

        static REXml* findById(int id);
        static REXml* findByName(const string& name);
        static ResultSetIterator<REXml>* findAll();

        int update();
        int save();
        // sync with db & return true if object needs saving or updating
        bool sync();

        string& getXmlRef();

        const int getId() const;
        void setId(int id);
        const string& getName() const;
        void setName(const string& name);
        const string& getXml() const;
        void setXml(const string& xml);

        friend ResultSetIterator<REXml>;

    private:
        int id;
        string name;
        string xml;

        static void populateFields(const sql::ResultSet* rs, REXml* reXml);

        void operator=(const REXml& reXml);
    };

}
}

#endif /* defined(__soul_sifter__REXml__) */
