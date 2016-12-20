#include "GoogleMusicManager.h"

#include <iostream>
#include <string>

#include "gmusicapi/Module.h"
#include "gmusicapi/Mobileclient.h"

#include "SoulSifterSettings.h"

namespace dogatech {
namespace soulsifter {

GoogleMusicManager::GoogleMusicManager() {
  GMusicApi::Module module;
  mc = new GMusicApi::Mobileclient(module);
}

GoogleMusicManager::~GoogleMusicManager() {
  delete mc;
}

bool GoogleMusicManager::login() {
  return mc->login(SoulSifterSettings::getInstance().get<std::string>("google.email"), SoulSifterSettings::getInstance().get<std::string>("google.appKey"));
}

bool GoogleMusicManager::logout() {
  return mc->logout();
}

}  // namespace soulsifter
}  // namespace dogatech