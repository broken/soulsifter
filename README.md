Soul Sifter
===========

DJ/Organization Music app.

This is created by me for me.

Would be awesome if others found use, but I'm focused on features I want versus making it available for others. However, hopefully the code samples or build steps will help somebody else.

The mentions of RE are from where I previously housed my music - Rapid Evolution. It's a sweet music app, but ultimately I found I wanted more control. In the beginning there was a lot of syncing back & forth between its db and mine. However, I've completely moved off of RE now, so that code is deprecated & dusty, and will be removed when I find the need for code cleanup.

OSX Build Instructions
======================
Presteps:
* create mysql db
* install npm modules
* custom build of nwjs (for drag & drop & mp3 play support)
* copy ffmpegsumo.so from Chrom into libraries/ directory (for mp3 play support)
* required libs: mysql-connector-c++, libtag, mad, boost

```
grunt all
./build/soulsifter/osx64/soulsifter.app/Contents/MacOS/nwjs build/soulsifter/osx/soulsifter.app/Contents/Resources/app.nw
```

Win / Linux Differences
=======================
I run this on OSX 10.7 & 10.10 x64. While most things should work on the other systems, edits would need to happen. (these are just off the top of my head atm)
* update package.json files
* update Gruntfile.js
* the custom build of nwjs would need to edit a separate place for drag&drop support

Music Database
==============
The music database is stored in mysql. I chose this because of simplicity. Writing scripts & functions against mysql in multiple languages is well documented and straight forward. I can easily install it on any OS and manipulate the data easily. I also like the visualization provided by the mysql workbench and being able to generate the schemas from it.

Model Generation
================
When I first started, I found myself doing much of the same work for the model objects. Rather than creating a hard to follow template, I created a ruby script to generate the model objects for me. This has proved to make model edits easy and safe.

On the same token, the wrappers for nwjs is also generated. However, this code utilizes antlr and created in a separate project. I did just enough to get what I needed, but again it makes edits quick, safe, and painless. That project: https://github.com/broken/node-webkit-cpp-wrapper

NW.JS Build Directions
======================
There are two reasons I need to manually build nwjs:
* drag & drop to external native apps
* audio decoding using proprietary codecs

There is a massive thread on nwjs's project discussions, but this is what I needed to do:

```
Following: https://github.com/nwjs/nw.js/wiki/Building-nw.js
mkdir nw.js
cd nw.js
vim .gclient
-- fill with info from above site

gclient sync --no-history --nohooks
-- takes awhile to run & must use python 2.7+

-- edit extensis lines for osx drag&drop
-- https://github.com/broken/node-webkit-dragout/blob/master/src/content/browser/web_contents/web_drag_source_mac.mm
vim content/browser/web_contents/web_drag_source_mac.mm

-- edit for ffmpeg
-- these ffmpeg steps are obsolete since I copied from whatever was in Chrome, but I'm keeping here in case that one day they may work with a little effort
cd src/third_party/ffmpeg
vim ./chromium/scripts/build_ffmpeg.py
./chromium/scripts/build_ffmpeg.py mac ia32
./chromium/scripts/build_ffmpeg.py mac x64
./chromium/scripts/copy_config.sh
./chromium/scripts/generate_gyp.py
gclient runhooks

-- edit ffmpeg branding gyp
-- https://github.com/nwjs/nw.js/issues/1461
vim ffmpeg.gyp

-- edit common_media_types
-- note: proprietary types must have at least one object for this to build
cd ../..
vim src/net/base/mime_util.cc

-- back to building
export GYP_GENERATORS=ninja
./build/gyp_chromium -Dproprietary_codecs=1 content/content.gyp --no-circular-check
ninja -C out/Release -j4 ffmpegsumo
ninja -C out/Release nw -j4
```
