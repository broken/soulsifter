#include "SoulSifterSettings.h"

#include <cstdlib>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost;
using namespace std;

namespace dogatech {
namespace soulsifter {

  SoulSifterSettings::SoulSifterSettings() {
    // TODO settings file stored in other OS place
    filename.append(getenv("HOME"));
    filename.append("/Library/Application Support/Soul Sifter");
    if (!filesystem::exists(filename)) {
      if (!filesystem::create_directory(filename)) {
        cerr << "Unable to create settings directory " << filename << endl;
      }
    }
    filename.append("/settings.json");
    if (filesystem::exists(filename)) {
      // Load the JSON file into the property tree. If reading fails
      // (cannot open file, parse error), an exception is thrown.
      read_json(filename, ptree);
    } else {
      // defaults
      ptree.put("db.url", "localhost");
      ptree.put("db.user", "ss");
      ptree.put("db.name", "music");
      ptree.put("songList.limit", 128);
    }
  }
  
  void SoulSifterSettings::save() {
    write_json(filename, ptree);
  }

  template <typename T>
  const T SoulSifterSettings::get(const string& label) const {
    return ptree.get<T>(label);
  }
  template<> const int SoulSifterSettings::get<int>(const std::string& label) const {
    return ptree.get(label, 0);
  }
  template<> const string SoulSifterSettings::get<string>(const std::string& label) const {
    return ptree.get(label, "");
  }

  template <typename T>
  void SoulSifterSettings::put(const string& label, const T& value) {
    ptree.put(label, value);
  }
  template void SoulSifterSettings::put<int>(const string& label, const int& value);
  template void SoulSifterSettings::put<string>(const string& label, const string& value);

}  // namespace soulsifter
}  // namespace dogatech