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
  * SELECT @@GLOBAL.sql_mode; SET GLOBAL sql_mode=(SELECT REPLACE(@@sql_mode,'ONLY_FULL_GROUP_BY',''));
  * update /etc/mysql/my.cnf to with the new sql-mode= under [mysqld]
    * example: [mysqld]
      secure_file_priv=/Users/dogatech/Music/db
      sql-mode="STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION"
* install npm modules
  * global: grunt-cli, nw-gyp, bower
  * locally with npm install: grunt plugins
* install bower components
* custom build of nwjs (for drag & drop & mp3 play support)
* required libs (brew install): mysql-connector-c++, libtag, mad, boost, youtube-dl (for music videos), ffmpeg (for youtube audio), g3log

```
grunt all
./build/soulsifter/osx64/soulsifter.app/Contents/MacOS/nwjs build/soulsifter/osx/soulsifter.app/Contents/Resources/app.nw
```
note: may want to setup a shortlink to the version working on: ln -s build/soulsifter\ -\ v0.7.0/ build/soulsifter

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

```
Following for nw23 compilation (xcode 8.3.3 w/ 10.12 sdk):
# depot tools installation: https://www.chromium.org/developers/how-tos/install-depot-tools
# Use thier buildbot for confirmation of steps: http://buildbot-master.nwjs.io:8010/waterfall
# Instructions: http://docs.nwjs.io/en/latest/For%20Developers/Building%20NW.js/
# Hints on building ffmpeg which should be included below: https://github.com/butterproject/butter-desktop/issues/339

export NWV=nw23
export XCV=8.3.3
# sudo xcode-select -s /Applications/Xcode$XCV.app/Contents/Developer/
xcode-select -p
mkdir $(printf "%s_sdk_xcode%s" $NWV $XCV)
cd $(printf "%s_sdk_xcode%s" $NWV $XCV)
gclient config --name=src https://github.com/nwjs/chromium.src.git@origin/$NWV
vim .gclient
# update custom_deps of .gclient with:
      "src/third_party/WebKit/LayoutTests": None,
      "src/chrome_frame/tools/test/reference_build/chrome": None,
      "src/chrome_frame/tools/test/reference_build/chrome_win": None,
      "src/chrome/tools/test/reference_build/chrome": None,
      "src/chrome/tools/test/reference_build/chrome_linux": None,
      "src/chrome/tools/test/reference_build/chrome_mac": None,
      "src/chrome/tools/test/reference_build/chrome_win": None,
--
git clone https://github.com/nwjs/nw.js.git src/content/nw 
cd src/content/nw
git checkout $NWV
cd ../../..
git clone https://github.com/nwjs/node src/third_party/node-nw
cd src/third_party/node-nw
git checkout $NWV
cd ../../..
git clone https://github.com/nwjs/v8 src/v8
cd src/v8
git checkout $NWV
cd ../..
# gclient takes awhile (>1 hr) to run & must use python 2.7+
gclient sync -v --with_branch_heads --disable-syntax-validation
export GYP_DEFINES=target_arch=x64 nwjs_sdk=1 mac_breakpad=1 buildtype=Official disable_nacl=0
export GYP_CHROMIUM_NO_ACTION=0
gn gen src/out/nw '--args=is_debug=false is_component_ffmpeg=true target_cpu="x64" enable_nacl=true is_official_build=true nwjs_sdk=true ffmpeg_branding="Chrome" proprietary_codecs=true enable_stripping=true enable_dsyms=true' --root=src
python src/build/gyp_chromium -I src/third_party/node-nw/common.gypi src/third_party/node-nw/node.gyp
unset GYP_DEFINES
unset GYP_CHROMIUM_NO_ACTION
vim src/content/browser/web_contents/web_drag_source_mac.mm
# edit extensis lines for osx drag&drop
# https://github.com/broken/node-webkit-dragout/blob/master/src/content/browser/web_contents/web_drag_source_mac.mm
# Building nwjs will take all f*@#ing day and all the cpu
ninja -C src/out/nw nwjs
ninja -C src/out/Release node
ninja -C src/out/nw copy_node
ninja -C src/out/nw dump
ninja -C src/out/nw dist
sudo xcode-select -s /Applications/Xcode.app/Contents/Developer/
```
