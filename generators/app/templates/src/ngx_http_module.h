#ifndef __<%= name.toUpperCase() %>__H_INCLUDED_
#define __<%= name.toUpperCase() %>__H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef struct {
} ngx_http_<%= name %>_loc_conf_t;

typedef struct {
} ngx_http_<%= name %>_main_conf_t;

typedef struct {
} ngx_http_<%= name %>_srv_conf_t;

#endif
