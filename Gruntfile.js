module.exports = function(grunt) {

  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    builtAppDir: 'build/<%= pkg.name %> - v<%= pkg.version %>/osx64/<%= pkg.name %>.app',
    nwjs: {
      options: {
        version: '0.37.4', // Version of node-webkit (http://dl.nwjs.io)
        buildDir: './build', // Where the build version of my node-webkit app is saved
        credits: './src/credits.html', // Mac credits
        macIcns: './DVDRipper.icns', // Path to the Mac icon file
        platforms: ['osx64'], // These are the platforms that we want to build
        buildType: 'versioned' // Append version to name
      },
      src: [
          './src/**/*', // Your node-webkit app
          './components/**/*',
          './fonts/**/*',
          './node_modules/async/**/*',
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
        command: 'nw-gyp configure --arch=x64 --target=0.37.4',
        options: {
          execOptions: {
            cwd: 'src/soulsifter',
          },
        },
      },
      nwgypbuild: {
        command: 'nw-gyp build --target=0.37.4',
        options: {
          execOptions: {
            cwd: 'src/soulsifter',
          },
        },
      },
      updateviews: {
        command: 'cp src/views/*.html "<%= builtAppDir %>/Contents/Resources/app.nw/views/"',
      },
      updatecomponents: {
        command: 'cp -r src/components/soul-sifter "<%= builtAppDir %>/Contents/Resources/app.nw/components/"',
      },
      updateworkers: {
        command: 'cp -r src/workers/*.js "<%= builtAppDir %>/Contents/Resources/app.nw/workers/"',
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
      },
      less: {
        src: '<%= builtAppDir %>/Contents/Resources/app.nw/components/soul-sifter/theme.html',
        overwrite: true,
        replacements: [{
          from: /\/\*</g,
          to: '<',
        },
        {
          from: />\*\//g,
          to: '>',
        }],
      }
    },
    copy: {
      ffmpeg: {
        files: [
          {
            src: 'cache/libffmpeg.dylib',
            dest: '<%= builtAppDir %>/Contents/Versions/55.0.2883.65/nwjs Framework.framework/libffmpeg.dylib',
            flatten: true
          },
        ]
      }
    },
    spawn: {
      run: {
        command: './<%= builtAppDir %>/Contents/MacOS/nwjs',
        commandArgs: ['<%= builtAppDir %>/Contents/Resources/app.nw'],
        directory: '.',
      },
      ulimit: {
        command: 'ulimit',
        commandArgs: ['-n', '10240'],
        directory: '.',
      },
    },
    bump: {  // grunt bump:patch/minor/major
      options: {
        files: ['version.json', 'package.json', 'src/package.json', 'bower.json'],
        updateConfigs: [],
        commit: false,
        commitMessage: 'Release v%VERSION%',
        commitFiles: [],
        createTag: false,
        tagName: 'v%VERSION%',
        tagMessage: 'Version %VERSION%',
        push: false,
        pushTo: 'origin',
        gitDescribeOptions: '--tags --always --abbrev=1 --dirty=-d',
        globalReplace: false,
        prereleaseName: false,
        regExp: false
      }
    },
    buildnumber: {
      files: [ 'version.json' ]
    },
    less: {
      development: {
        options: {
          ieCompat: false,
        },
        files: {
          '<%= builtAppDir %>/Contents/Resources/app.nw/components/soul-sifter/theme.html': 'src/components/soul-sifter/theme-scratchlive.html',
        },
      },
    },
  });

  grunt.loadNpmTasks('grunt-build-number');
  grunt.loadNpmTasks('grunt-bump');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-contrib-less');
  grunt.loadNpmTasks('grunt-nw-builder');
  grunt.loadNpmTasks('grunt-shell');
  grunt.loadNpmTasks('grunt-spawn');
  grunt.loadNpmTasks('grunt-text-replace');

  grunt.registerTask('run', ['spawn:run']);
  grunt.registerTask('css-hack', ['less:development', 'replace:less']);
  grunt.registerTask('default', ['nwjs', 'css-hack', 'buildnumber', 'run']);
  grunt.registerTask('nw-gyp', ['shell:nwgypclean', 'shell:nwgypconfigure', 'replace:rtti', 'shell:nwgypbuild']);
  grunt.registerTask('up', ['shell:updateviews', 'shell:updatecomponents', 'shell:updateworkers', 'css-hack', 'buildnumber']);
  grunt.registerTask('all', ['nw-gyp', 'default']);
};
