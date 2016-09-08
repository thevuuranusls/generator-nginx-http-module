#ifndef DDEBUG
#define DDEBUG 0
#endif
#include "ddebug.h"

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

#include "<%= name %>.h"

<% if (ctx.preconfiguration) { -%>
static ngx_int_t
<%= name %>_pre_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.postconfiguration) { -%>
static ngx_int_t
<%= name %>_post_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.create_main_configuration) { -%>
static void *
<%= name %>_create_main_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.init_main_configuration) { -%>
static char *
<%= name %>_init_main_conf(ngx_conf_t *cf, void *conf);
<% } -%>
<% if (ctx.create_server_configuration) { -%>
static void *
<%= name %>_create_server_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.merge_server_configuration) { -%>
static char *
<%= name %>_merge_server_conf(ngx_conf_t *cf, void *prev, void *conf);
<% } -%>
<% if (ctx.create_location_configuration) { -%>
static void *
<%= name %>_create_loc_conf(ngx_conf_t *cf);
<% } -%>
<% if (ctx.mrege_location_configuration) { -%>
static char *
<%= name %>_merge_loc_conf(ngx_conf_t *cf, void *prev, void *conf);
<% } -%>
<% if (ctx.postconfiguration) { -%>
static ngx_int_t
ngx_http_<%= name %>_handler(ngx_http_request_t *r);
<% } -%>
static char *
ngx_http_placeholder(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);


static ngx_command_t <%= name %>_commands[] = [
    {
        ngx_string("placeholder"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
        |NGX_CONF_TAKE1,
        ngx_http_placeholder,
        NGX_HTTP_LOC_CONF_OFFSET,
        0,
        NULL
    },
    ngx_null_command
];


static ngx_http_module_t  <%= name %>_ctx = {
    <% if (ctx.preconfiguration) { -%>
        <%= name %>_pre_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.postconfiguration) { -%>
        <%= name %>_post_conf,
    <% } else { -%>
        NULL,
    <% } -%>

    <% if (ctx.create_main_configuration) { -%>
        <%= name %>_create_main_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.init_main_configuration) { -%>
        <%= name %>_init_main_conf,
    <% } else { -%>
        NULL,
    <% } -%>

    <% if (ctx.create_server_configuration) { -%>
        <%= name %>_create_server_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.merge_server_configuration) { -%>
        <%= name %>_merge_server_conf,
    <% } else { -%>
        NULL,
    <% } -%>

    <% if (ctx.create_location_configuration) { -%>
        <%= name %>_create_loc_conf,
    <% } else { -%>
        NULL,
    <% } -%>
    <% if (ctx.mrege_location_configuration) { -%>
        <%= name %>_merge_loc_conf,
    <% } else { -%>
        NULL,
    <% } -%>
};


ngx_module_t ngx_http_<%= name %>_module = {
    NGX_MODULE_V1,
    &ngx_http_<%= name %>_ctx,             /* module context */
    ngx_http_<%= name %>_commands,         /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static char *
ngx_http_placeholder(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_str_t                  *value;
    ngx_http_<%= name %>_loc_conf_t <%= name[0] %>lcf;
    ngx_http_<%= name %>_srv_conf_t <%= name[0] %>scf;
    ngx_http_<%= name %>_main_conf_t <%= name[0] %>mcf;


    <%= name[0] %>lcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_<%= name %>_module);
    <%= name[0] %>scf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_<%= name %>_module);
    <%= name[0] %>mcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_<%= name %>_module);

    value = cf->args->elts;

    return NGX_CONF_OK;
}


<% if (ctx.preconfiguration) { -%>
static ngx_int_t
<%= name %>_pre_conf(ngx_conf_t *cf)
{

}
<% } -%>

<% if (ctx.postconfiguration) { -%>
static ngx_int_t
<%= name %>_post_conf(ngx_conf_t *cf)
{
    ngx_http_handler_pt        *h;
    ngx_http_core_main_conf_t  *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);
    h = ngx_array_push(&cmcf->phases[<%= phase %>].handlers);
    if (h == NULL) {
        return NGX_ERROR;
    }
    *h = ngx_http_<%= name %>_handler;

    return NGX_OK;
}
<% } -%>

<% if (ctx.create_main_configuration) { -%>
static void *
<%= name %>_create_main_conf(ngx_conf_t *cf)
{

}
<% } -%>

<% if (ctx.init_main_configuration) { -%>
static char *
<%= name %>_init_main_conf(ngx_conf_t *cf, void *conf)
{

}
<% } -%>

<% if (ctx.create_server_configuration) { -%>
static void *
<%= name %>_create_server_conf(ngx_conf_t *cf)
{

}
<% } -%>

<% if (ctx.merge_server_configuration) { -%>
static char *
<%= name %>_merge_server_conf(ngx_conf_t *cf, void *prev, void *conf)
{

}
<% } -%>

<% if (ctx.create_location_configuration) { -%>
static void *
<%= name %>_create_loc_conf(ngx_conf_t *cf)
{

}
<% } -%>

<% if (ctx.mrege_location_configuration) { -%>
static char *
<%= name %>_merge_loc_conf(ngx_conf_t *cf, void *prev, void *conf)
{

}
<% } -%>

<% if (ctx.postconfiguration) { -%>
static ngx_int_t
ngx_http_<%= name %>_handler(ngx_http_request_t *r)
{

}
<% } -%>
