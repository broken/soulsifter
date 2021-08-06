#include "MusicService.h"

#include <string>

#include "MusicManager.h"

namespace dogatech {
namespace soulsifter {

std::string cleanDirName(const std::string& name) { return MusicManager::cleanDirName(name); }

}  // namespace soulsifter
}  // namespace dogatech
