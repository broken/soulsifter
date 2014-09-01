ulimit -n 10240

cd src/soulsifter && nw-gyp clean && nw-gyp configure --target=0.10.2 && nw-gyp build && cd ../.. && grunt && build/soulsifter/osx/soulsifter.app/Contents/MacOS/node-webkit
