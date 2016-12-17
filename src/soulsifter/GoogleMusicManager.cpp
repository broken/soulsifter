#include "GoogleMusicManager.h"

#include <iostream>
#include <string>

#include <Python.h>

#include "SoulSifterSettings.h"

namespace dogatech {
namespace soulsifter {

GoogleMusicManager::GoogleMusicManager() {
  Py_Initialize();
  gmusicapiModule = PyImport_ImportModule("gmusicapi");
  assert(gmusicapiModule != NULL);

  mobileclientClass = PyObject_GetAttrString(gmusicapiModule, "Mobileclient");
  assert(mobileclientClass != NULL);

  PyObject* argsObjectList = PyTuple_New(0);
  mobileclient =  PyObject_CallObject(mobileclientClass, argsObjectList);
  Py_DECREF(argsObjectList);
  assert(mobileclient != NULL);
}

GoogleMusicManager::~GoogleMusicManager() {
  Py_DECREF(mobileclient);
  Py_DECREF(mobileclientClass);
  Py_DECREF(gmusicapiModule);
  Py_Finalize();
}

bool GoogleMusicManager::login() {
  PyObject* func = PyObject_GetAttrString(mobileclient, "login");
  assert(PyCallable_Check(func));

  PyObject* argsObjectList = PyTuple_New(3);
  PyTuple_SetItem(argsObjectList, 0, Py_BuildValue("s", SoulSifterSettings::getInstance().get<std::string>("google.email").c_str()));
  PyTuple_SetItem(argsObjectList, 1, Py_BuildValue("s", SoulSifterSettings::getInstance().get<std::string>("google.appKey").c_str()));
  PyTuple_SetItem(argsObjectList, 2, Py_BuildValue("s", "1234567890abcdef"));

  PyObject* result = PyObject_CallObject(func, argsObjectList);
  Py_DECREF(argsObjectList);
  assert(result != NULL);
  assert(PyBool_Check(result));
  int isSuccess = PyObject_IsTrue(result);
  Py_DECREF(result);

  Py_DECREF(func);
  return isSuccess;
}

}  // namespace soulsifter
}  // namespace dogatech