module.exports = function(grunt) {

  grunt.initConfig({
    nodewebkit: {
      options: {
        version: '0.12.0', // Version of node-webkit
        buildDir: './build', // Where the build version of my node-webkit app is saved
        credits: './src/credits.html', // Mac credits
        macIcns: './DVDRipper.icns', // Path to the Mac icon file
        platforms: ['osx'] // These are the platforms that we want to build
      },
      src: [
          './src/**/*', // Your node-webkit app
          './components/**/*',
          './fonts/**/*',
          './node_modules/playmusic/**/*'
      ]
    },
    shell: {
      nwgypclean: {
        command: 'nw-gyp clean',
        options: {
          execOptions: {
            cwd: 'src/soulsifter',
          },
        },
      },
      nwgypconfigure: {
        command: 'nw-gyp configure --arch=x64 --target=0.12.0',
        options: {
          execOptions: {
            cwd: 'src/soulsifter',
          },
        },
      },
      nwgypbuild: {
        command: 'nw-gyp build',
        options: {
          execOptions: {
            cwd: 'src/soulsifter',
          },
        },
      },
      updateviews: {
        command: 'cp src/views/*.html build/soulsifter/osx64/soulsifter.app/Contents/Resources/app.nw/views/',
      },
      updatecomponents: {
        command: 'cp -r src/components/soul-sifter build/soulsifter/osx64/soulsifter.app/Contents/Resources/app.nw/components/',
      },
    },
    replace: {
      rtti: {
        src: 'src/soulsifter/build/soulsifter.target.mk',
        overwrite: true,
        replacements: [{
          from: /\t*-fno-rtti \\\n/g,
          to: ''
        }]
      }
    },
    copy: {
      ffmpegsumo: {
        files: [
          {
            src: 'libraries/ffmpegsumo.so',
            dest: 'build/soulsifter/osx64/soulsifter.app/Contents/Frameworks/nwjs Framework.framework/Libraries/ffmpegsumo.so',
            flatten: true
          },
        ]
      }
    },
    spawn: {
      run: {
        command: './build/soulsifter/osx/soulsifter.app/Contents/MacOS/node-webkit build/soulsifter/osx/soulsifter.app/Contents/Resources/app.nw',
      },
      ulimit: {
        command: 'ulimit -n 10240',
      },
    },
  });

  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-node-webkit-builder');
  grunt.loadNpmTasks('grunt-shell');
  grunt.loadNpmTasks('grunt-spawn');
  grunt.loadNpmTasks('grunt-text-replace');

  grunt.registerTask('default', ['nodewebkit', 'copy:ffmpegsumo']);
  grunt.registerTask('nw-gyp', ['shell:nwgypclean', 'shell:nwgypconfigure', 'replace:rtti', 'shell:nwgypbuild']);
  grunt.registerTask('up', ['shell:updateviews', 'shell:updatecomponents']);
  grunt.registerTask('all', ['nw-gyp', 'nodewebkit', 'copy:ffmpegsumo']);
};
