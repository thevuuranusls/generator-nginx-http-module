'use strict';
var yeoman = require('yeoman-generator');
var chalk = require('chalk');
var yosay = require('yosay');

var ctx_hooks = [
  'preconfiguration',
  'postconfiguration',
  'create_main_configuration',
  'init_main_configuration',
  'create_server_configuration',
  'merge_server_configuration',
  'create_location_configuration',
  'merge_location_configuration',
];
var module_hooks = [
  'init_master',
  'init_module',
  'init_process',
  'init_thread',
  'exit_thread',
  'exit_process',
  'exit_master',
]

module.exports = yeoman.Base.extend({
  prompting: function () {
    // Have Yeoman greet the user.
    this.log(yosay(
      'Welcome to the stupendous ' + chalk.red('generator-nginx-http-module') + ' generator!'
    ));

    var prompts = [
      {
        type: 'input',
        name: 'name',
        message: 'what\'s your module name (ngx_http_xx_module)',
      },
      {
        type: 'checkbox',
        name: 'module',
        message: 'what module hook do you want',
        choices: module_hooks,
        default: ''
      },
      {
        type: 'list',
        name: 'phase',
        message: 'which phase is your module working on',
        choices: ['NGX_HTTP_POST_READ_PHASE',
                  'NGX_HTTP_SERVER_REWRITE_PHASE',
                  'NGX_HTTP_REWRITE_PHASE',
                  'NGX_HTTP_PREACCESS_PHASE',
                  'NGX_HTTP_ACCESS_PHASE',
                  'NGX_HTTP_CONTENT_PHASE',
                  'NGX_HTTP_LOG_PHASE'],
        default: 'NGX_HTTP_CONTENT_PHASE',
      },
      {
        type: 'checkbox',
        name: 'ctx',
        message: 'which hook do you need on module ctx',
        choices: ctx_hooks,
        default: 'create_location_configuration'
      }
    ];

    return this.prompt(prompts).then(function (props) {
      // To access props later use this.props.someAnswer;

      var ctx = {};
      for (var i = 0; i < ctx_hooks.length; i++) {
        var hook = ctx_hooks[i];
        if (props.ctx.indexOf(hook) !== -1) {
          ctx[hook] = true;
        }
      }
      var module = {};
      for (var i = 0; i < module_hooks.length; i++) {
        var hook = module_hooks[i];
        if (props.module.indexOf(hook) !== -1) {
          module[hook] = true;
        }
      }

      props.ctx = ctx;
      props.module = module;
      this.props = props;
    }.bind(this));
  },

  writing: function () {
    this.fs.copy(
      this.templatePath('src/ddebug.h'),
      this.destinationPath(`src/ddebug.h`)
    );
    this.fs.copy(
      this.templatePath('Makefile'),
      this.destinationPath(`Makefile`)
    );
    this.fs.copy(
      this.templatePath('editorconfig'),
      this.destinationPath(`.editorconfig`)
    );
    this.fs.copy(
      this.templatePath('gitignore'),
      this.destinationPath(`.gitignore`)
    );
    this.fs.copy(
      this.templatePath('gitattributes'),
      this.destinationPath(`.gitattributes`)
    );
    this.fs.copyTpl(
      this.templatePath('config'),
      this.destinationPath(`config`),
      this.props
    );
    this.fs.copyTpl(
      this.templatePath('src/ngx_http_module.c'),
      this.destinationPath(`src/ngx_http_${this.props.name}_module.c`),
      this.props
    );
    this.fs.copyTpl(
      this.templatePath('src/ngx_http_module.c'),
      this.destinationPath(`src/ngx_http_${this.props.name}_module.c`),
      this.props
    );
    this.fs.copyTpl(
      this.templatePath('src/ngx_http_module.h'),
      this.destinationPath(`src/ngx_http_${this.props.name}_module.h`),
      this.props
    );
    this.fs.copy(
      this.templatePath('t/000.t'),
      this.destinationPath(`t/000.t`)
    );
  },

  install: function () {
  }
});
