#ifndef soul_sifter_GoogleMusicManager_h
#define soul_sifter_GoogleMusicManager_h

#include <Python.h>

namespace dogatech {
namespace soulsifter {

class GoogleMusicManager {
public:
  GoogleMusicManager();
  ~GoogleMusicManager();

  bool login();
  bool logout();
  bool isAuthenticated();
private:
  PyObject* gmusicapiModule;
  PyObject* mobileclientClass;
  PyObject* mobileclient;
  bool isLoggedIn;

  // cannot be copied
  GoogleMusicManager(GoogleMusicManager const&);
  void operator=(GoogleMusicManager const&);
};
    
}  // namespace soulsifter
}  // namespace dogatech

#endif
