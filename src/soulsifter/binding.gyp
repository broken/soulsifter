{
  "targets": [
    {
      "target_name": "soulsifter",
      "sources": [ "soulsifter.cc", "BasicGenre_wrap.cpp", "BasicGenre.cpp", "MysqlAccess.cpp" ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "link_settings": {
        "libraries": [
          "/usr/local/lib/libboost_date_time-mt.dylib",
          "/usr/local/lib/libboost_filesystem-mt.dylib",
          "/usr/local/lib/libboost_regex-mt.dylib",
          "/usr/local/lib/libboost_system-mt.dylib",
          "/usr/local/lib/libboost_thread-mt.dylib",
          "/usr/local/lib/libmysqlclient.18.dylib",
          "/usr/local/lib/libmysqlcppconn.7.1.1.4.dylib",
        ],
      },
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ],
    }
  ]
}