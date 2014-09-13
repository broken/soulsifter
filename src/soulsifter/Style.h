//
//  Style.h
//  soul-sifter
//
//  Created by Robby Neale
//  Generated by generate_model.rb
//

#ifndef __soul_sifter__Style__
#define __soul_sifter__Style__

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

    class Style {
    public:
        Style();
        explicit Style(const Style& style);
        ~Style();
        void clear();

        static Style* findById(int id);
        static Style* findByREId(int reId);
        static ResultSetIterator<Style>* findAll();

        bool sync();
        int update();
        int save();

        bool operator<(const Style& style) const;
        bool operator>(const Style& style) const;

        static ResultSetIterator<Style>* findAllParents();
        static void findAllSortedByName(vector<Style*>** stylesPtr);
        static void findAllSortedByREId(vector<Style*>** stylesPtr);

        const int getId() const;
        void setId(int id);
        const string& getName() const;
        void setName(const string& name);
        const int getREId() const;
        void setREId(int reId);
        const string& getRELabel() const;
        void setRELabel(const string& reLabel);
        const vector<Style*>& getChildren();
        void setChildren(const vector<Style*>& children);
        void addChildById(int childId);
        void removeChildById(int childId);
        const vector<Style*>& getParents();
        void setParents(const vector<Style*>& parents);
        void addParentById(int parentId);
        void removeParentById(int parentId);

        friend ResultSetIterator<Style>;

    private:
        int id;
        string name;
        int reId;
        string reLabel;
        vector<Style*> children;
        vector<int> childrenIds;
        vector<Style*> parents;
        vector<int> parentsIds;

        static void populateFields(const sql::ResultSet* rs, Style* style);
        static void populateChildrenIds(Style* style);
        static void populateParentsIds(Style* style);

        void operator=(const Style& style);
    };

}
}

#endif /* defined(__soul_sifter__Style__) */
