{
  "targets": [
    {
      "target_name": "soulsifter",
      "sources": [ "soulsifter.cc", "Album.cpp", "AlbumHelper.cpp", "AlbumPart.cpp", "BasicGenre_wrap.cpp", "BasicGenre.cpp", "BasicGenreHelper.cpp", "DTVectorUtil.h", "Mix.cpp", "MixHelper.cpp", "MysqlAccess.cpp", "ResultSetIterator.h", "Song_wrap.cpp", "Song.cpp", "Style.cpp"],
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
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
    }
  ]
}