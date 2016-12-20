#ifndef soul_sifter_GoogleMusicManager_h
#define soul_sifter_GoogleMusicManager_h

namespace GMusicApi {
class Mobileclient;
}

namespace dogatech {
namespace soulsifter {

class GoogleMusicManager {
public:
  GoogleMusicManager();
  ~GoogleMusicManager();

  bool login();
  bool logout();
private:
  GMusicApi::Mobileclient* mc;

  // cannot be copied
  GoogleMusicManager(GoogleMusicManager const&);
  void operator=(GoogleMusicManager const&);
};
    
}  // namespace soulsifter
}  // namespace dogatech

#endif
