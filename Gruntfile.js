module.exports = function(grunt) {

  grunt.initConfig({
    nodewebkit: {
      options: {
        version: 'latest', // Version of node-webkit
        buildDir: './build', // Where the build version of my node-webkit app is saved
        credits: './app/Credits.html', // Mac credits
        macIcns: './icon.icns', // Path to the Mac icon file
        platforms: ['osx'] // These are the platforms that we want to build
      },
      src: './app/**/*' // Your node-webkit app
    },
  });

  grunt.loadNpmTasks('grunt-node-webkit-builder');
  grunt.registerTask('default', ['nodewebkit']);

};