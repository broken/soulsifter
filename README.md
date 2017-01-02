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
* install npm modules
  * global: grunt-cli, nw-gyp, bower
  * locally with npm install: grunt plugins
* install bower components
* custom build of nwjs (for drag & drop & mp3 play support)
* required libs (brew install): mysql-connector-c++, libtag, mad, boost, youtube-dl (for music videos)

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
Following for nw19 compilation:
- http://buildbot-master.nwjs.io:8010/builders/nw19_sdk_mac64
- http://docs.nwjs.io/en/latest/For%20Developers/Building%20NW.js/
- https://github.com/butterproject/butter-desktop/issues/339
sudo xcode-select -s /Applications/Xcode7.3.1.app/Contents/Developer/
mkdir nwjs19_sdk_xcode7.3.1
cd nwjs19_sdk_xcode7.3.1
export MAIN=nw19
gclient config --name=src https://github.com/nwjs/chromium.src.git@origin/nw19
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
git checkout $MAIN
cd ../../..
git clone https://github.com/nwjs/node src/third_party/node
cd src/third_party/node
git checkout $MAIN
cd ../../..
git clone https://github.com/nwjs/v8 src/v8
cd src/v8
git checkout $MAIN
cd ../..
gclient sync --with_branch_heads
# takes awhile to run & must use python 2.7+
gn gen src/out/nw '--args=is_debug=false is_component_ffmpeg=true target_cpu="x64" enable_nacl=false is_official_build=true nwjs_sdk=true ffmpeg_branding="Chrome" proprietary_codecs=true' --root=src
export GYP_DEFINES=target_arch=x64 nwjs_sdk=1 mac_breakpad=1 buildtype=Official
export GYP_CHROMIUM_NO_ACTION=0
python src/build/gyp_chromium -I src/third_party/node/common.gypi src/third_party/node/node.gyp
unset GYP_DEFINES
unset GYP_CHROMIUM_NO_ACTION
# maybe skip these and edit file first, but leaving in jic that is the trick
ninja -C src/out/nw nwjs
ninja -C src/out/Release node
vim src/content/browser/web_contents/web_drag_source_mac.mm
# edit extensis lines for osx drag&drop
# https://github.com/broken/node-webkit-dragout/blob/master/src/content/browser/web_contents/web_drag_source_mac.mm
ninja -C src/out/nw nwjs
ninja -C src/out/Release node
ninja -C src/out/nw copy_node
ninja -C src/out/nw dist
sudo xcode-select -s /Applications/Xcode.app/Contents/Developer/

-- printenv
TERM_PROGRAM=iTerm.app
TERM=xterm-256color
SHELL=/bin/bash
TMPDIR=/var/folders/6s/m1bcbsvx1479p63tc_t1nw500000gn/T/
Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.EoZYiWgZSu/Render
TERM_PROGRAM_VERSION=3.0.12
OLDPWD=/Users/dogatech/dev/open.src/nwjs19_sdk_xcode7.3.1/src
TERM_SESSION_ID=w4t0p0:22170E84-A423-4EE4-AF1F-FC96E807799D
USER=dogatech
nwjs_sdk=1
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.ShzTDDk7W9/Listeners
__CF_USER_TEXT_ENCODING=0x1F5:0x0:0x0
PATH=/Users/dogatech/dev/open.src/depot_tools:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
MAIN=nw19
PWD=/Users/dogatech/dev/open.src/nwjs19_sdk_xcode7.3.1
LANG=en_US.UTF-8
ITERM_PROFILE=Dogatech
XPC_FLAGS=0x0
XPC_SERVICE_NAME=0
SHLVL=1
HOME=/Users/dogatech
COLORFGBG=15;0
ITERM_SESSION_ID=w4t0p0:22170E84-A423-4EE4-AF1F-FC96E807799D
LOGNAME=dogatech
buildtype=Official
mac_breakpad=1
_=/usr/bin/printenv
```
