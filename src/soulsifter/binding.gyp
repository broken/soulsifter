{
  "targets": [
    {
      "target_name": "soulsifter",
      "sources": [
          # module
          "soulsifter.cc",
          # model
          "Album.cpp",
          "AlbumHelper.cpp",
          "AlbumPart.cpp",
          "BasicGenre_wrap.cpp",
          "BasicGenre.cpp",
          "BasicGenreHelper.cpp",
          "Mix.cpp",
          "MixHelper.cpp",
          "REAlbumCover.cpp",
          "RESetting.cpp",
          "RESettingHelper.cpp",
          "Song_wrap.cpp",
          "Song.cpp",
          "SongHelper.cpp",
          "Style.cpp",
          "StyleHelper.cpp",
          # detection
          "AudioAnalyzer.cpp",
          "bstdfile.c",
          "madlld.cpp",
          "MiniBpm.cpp",
          # persistence
          "MysqlAccess.cpp",
          "ResultSetIterator.h",
          # util
          "DTVectorUtil.h",
      ],
      'cflags!': [
          '-fno-exceptions',
          '-std=c++11',
          '-stdlib=libc++',
      ],
      'cflags_cc!': [
          '-fno-exceptions',
          '-std=c++11',
          '-stdlib=libc++',
      ],
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
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_CFLAGS': [ '-stdlib=libc++', ],
            'OTHER_CPLUSPLUSFLAGS' : [ '-stdlib=libc++', '-std=c++11' ],
            'OTHER_LDFLAGS': [ '-stdlib=libc++', ],
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
          }
        }]
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
    }
  ]
}