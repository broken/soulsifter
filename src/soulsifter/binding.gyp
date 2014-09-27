{
  "targets": [
    {
      "target_name": "soulsifter",
      "sources": [
          # module
          "soulsifter.cc",
          # model
          "Album.cpp",
          "Album_wrap.cpp",
          "AlbumHelper.cpp",
          "AlbumPart.cpp",
          "BasicGenre.cpp",
          #"BasicGenre_wrap.cpp",
          "BasicGenreHelper.cpp",
          "Mix.cpp",
          "MixHelper.cpp",
          "REAlbumCover.cpp",
          "RESetting.cpp",
          "RESettingHelper.cpp",
          "SearchUtil.cpp",
          "SearchUtil_wrap.cpp",
          "Song.cpp",
          "Song_wrap.cpp",
          "SongHelper.cpp",
          "Style.cpp",
          "Style_wrap.cpp",
          "StyleHelper.cpp",
          # detection
          "AudioAnalyzer.cpp",
          "bstdfile.c",
          "madlld.cpp",
          "MiniBpm.cpp",
          # organization
          "MusicManager.cpp",
          #"MusicManager_wrap.cpp",
          "SoulSifterSettings.h",
          #"TagWriter.cpp",
          # persistence
          "MysqlAccess.h",
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
          "/usr/local/lib/libmysqlcppconn.7.1.1.3.dylib",
          "/usr/local/lib/libtag.1.14.0.dylib",
          "/opt/local/lib/libmad.dylib",
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