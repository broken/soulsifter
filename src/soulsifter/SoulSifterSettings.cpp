#include "SoulSifterSettings.h"

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost;
using namespace std;

namespace dogatech {
namespace soulsifter {

  SoulSifterSettings::SoulSifterSettings() {
    if (filesystem::exists(filename)) {
      // Load the JSON file into the property tree. If reading fails
      // (cannot open file, parse error), an exception is thrown.
      read_json(filename, ptree);
    } else {
      // TODO set defaults
      ptree.put("something", "relax");
    }
  }
  
  void SoulSifterSettings::save() {
    write_json(filename, ptree);
  }

  template <typename T>
  const T SoulSifterSettings::get(const string& label) const {
    return ptree.get<T>(label);
  }
  template const int SoulSifterSettings::get<int>(const std::string& label) const;
  template const string SoulSifterSettings::get<string>(const std::string& label) const;

  template <typename T>
  void SoulSifterSettings::put(const string& label, const T& value) {
    ptree.put(label, value);
  }
  template void SoulSifterSettings::put<int>(const string& label, const int& value);
  template void SoulSifterSettings::put<string>(const string& label, const string& value);

}  // namespace soulsifter
}  // namespace dogatech