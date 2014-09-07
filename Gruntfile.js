module.exports = function(grunt) {

  grunt.initConfig({
    nodewebkit: {
      options: {
        version: '0.10.2', // Version of node-webkit
        buildDir: './build', // Where the build version of my node-webkit app is saved
        credits: './src/credits.html', // Mac credits
        macIcns: './DVDRipper.icns', // Path to the Mac icon file
        platforms: ['osx'] // These are the platforms that we want to build
      },
      src: [
          './src/**/*', // Your node-webkit app
          './components/**/*',
          './fonts/**/*'
      ]
    },
    shell: {
      run: {
        command: 'build/soulsifter/osx/soulsifter.app/Contents/MacOS/node-webkit',
      },
      ulimit: {
        command: 'ulimit -n 10240',
      },
      nwgypclean: {
        command: 'nw-gyp clean',
        options: {
          execOptions: {
            cwd: 'src/soulsifter',
          },
        },
      },
      nwgypconfigure: {
        command: 'nw-gyp configure --target=0.10.2',
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
        command: 'cp src/views/*.html build/soulsifter/osx/soulsifter.app/Contents/Resources/app.nw/views/',
      },
      updatecomponents: {
        command: 'cp -r src/components/soul-sifter build/soulsifter/osx/soulsifter.app/Contents/Resources/app.nw/components/',
      },
    },
  });

  grunt.loadNpmTasks('grunt-node-webkit-builder');
  grunt.loadNpmTasks('grunt-shell');
  grunt.registerTask('default', ['nodewebkit', 'shell:run']);
  grunt.registerTask('nw-gyp', ['shell:nwgypclean', 'shell:nwgypconfigure', 'shell:nwgypbuild']);
  grunt.registerTask('up', ['shell:updateviews', 'shell:updatecomponents']);
  grunt.registerTask('all', ['nw-gyp', 'nodewebkit', 'shell:run']);
};
