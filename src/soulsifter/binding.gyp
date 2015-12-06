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
          "AlbumPart_wrap.cpp",
          "BasicGenre.cpp",
          "BasicGenre_wrap.cpp",
          "BasicGenreHelper.cpp",
          "Mix.cpp",
          "Mix_wrap.cpp",
          "MixHelper.cpp",
          "MusicVideo.cpp",
          "MusicVideo_wrap.cpp",
          "Playlist.cpp",
          "Playlist_wrap.cpp",
          "PlaylistEntry.cpp",
          "PlaylistEntry_wrap.cpp",
          "REAlbumCover.cpp",
          "RESetting.cpp",
          "RESettingHelper.cpp",
          "RESong.cpp",
          "Song.cpp",
          "Song_wrap.cpp",
          "SongHelper.cpp",
          "Style.cpp",
          "Style_wrap.cpp",
          "StyleHelper.cpp",
          # detection
          "AudioAnalyzer.cpp",
          "AudioAnalyzer_wrap.cpp",
          "bstdfile.c",
          "madlld.cpp",
          "MiniBpm.cpp",
          # organization
          "FilesToAdd.cpp",
          "MusicManager.cpp",
          "MusicVideoService.cpp",
          "MusicVideoService_wrap.cpp",
          "NewSongManager.cpp",
          "NewSongManager_wrap.cpp",
          "SearchUtil.cpp",
          "SearchUtil_wrap.cpp",
          "SoulSifterSettings.cpp",
          "SoulSifterSettings_wrap.cpp",
          "TagService.cpp",
          "TagService_wrap.cpp",
          # persistence
          "MysqlAccess.h",
          "MysqlAccess.cpp",
          "ResultSetIterator.h",
          # util
          "DTVectorUtil.h",
          "DTQueueUtil.h",
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
          "/usr/local/lib/libmad.0.2.1.dylib",
          "/usr/local/lib/libmysqlclient.18.dylib",
          "/usr/local/lib/libmysqlcppconn.7.dylib",
          "/usr/local/lib/libtag.1.14.0.dylib",
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
        "<!(node -e \"require('nan')\")",
        "/usr/local/include",
      ],
    }
  ]
}
