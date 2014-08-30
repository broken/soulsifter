ulimit -n 10240

cd src/soulsifter && nw-gyp clean && nw-gyp configure --target=0.8.6 && nw-gyp build && cd ../.. && grunt && build/soulsifter/osx/soulsifter.app/Contents/MacOS/node-webkit
