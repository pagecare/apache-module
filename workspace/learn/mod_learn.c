/*
**  mod_learn.c -- Apache sample learn module
**  [Autogenerated via ``apxs -n learn -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory
**  by running:
**
**    $ apxs -c -i mod_learn.c
**
**  Then activate it in Apache's apache2.conf file for instance
**  for the URL /learn in as follows:
**
**    #   apache2.conf
**    LoadModule learn_module modules/mod_learn.so
**    <Location /learn>
**    SetHandler learn
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /learn and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/learn
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**
**    The sample page from mod_learn.c
*/

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_string(const char *name, char *value, request_rec *r) {
    ap_rputs("<dt>", r);
    ap_rputs(name, r);
    ap_rputs("</dt>\n", r);
    ap_rputs("<dd>", r);
    if (value == NULL) {
        ap_rputs("null", r);
    } else {
        ap_rputs(value, r);
    }
    ap_rputs("</dd>\n", r);
}

static void print_pool(request_rec *r) {
    print_string("r->pool", "TODO", r);
}

static void print_connection(request_rec *r) {
    print_string("r->connection", "TODO", r);
}

static void print_server(request_rec *r) {
    print_string("r->server", "TODO", r);
}

static void print_next(request_rec *r) {
    print_string("r->next", "TODO", r);
}

static void print_prev(request_rec *r) {
    print_string("r->prev", "TODO", r);
}

static void print_main(request_rec *r) {
    print_string("r->main", "TODO", r);
}

static char * my_itoa(int value) {
    int LENGTH = (CHAR_BIT * sizeof(int) - 1) / 3 + 2;
    char result[LENGTH];
    snprintf(result, 10, "%d", value);
    return &result;
}

static void print_int(char *name, int value, request_rec *r) {
    ap_rputs("<dt>", r);
    ap_rputs(name, r);
    ap_rputs("</dt><dd>", r);
    ap_rputs(my_itoa(value), r);
    ap_rputs("</dd>\n", r);
}

static void print_request_time(request_rec *r) {
    print_string("r->request_time", "TODO", r);
}

static int learn_handler(request_rec *r)
{
    if (strcmp(r->handler, "learn")) {
        return DECLINED;
    }

    r->content_type = "text/html";

    if (!r->header_only) {
        ap_rputs("<html><head><title>Learn module</title></head><body>\n", r);
        ap_rputs("<h1>Hello, world!</h1>", r);
        ap_rputs("<dl>\n", r);
        print_pool(r);
        print_connection(r);
        print_server(r);
        print_next(r);
        print_prev(r);
        print_main(r);
        print_string("r->the_request", r->the_request, r);
        //print_int("r->assbackwards", r->assbackwards, r);
        //print_int("r->proxyreq", r->proxyreq, r);
        //print_int("r->header_only", r->header_only, r);
        //print_int("r->proto_num", r->proto_num, r);
        print_string("r->handler", r->handler, r);
        print_string("r->protocol", r->protocol, r);
        print_string("r->hostname", r->hostname, r);
        print_request_time(r);
        print_string("r->status_line", r->status_line, r);
        //print_string("r->status", r->status, r);
        //print_int("r->method_number", r->method_number, r);
        print_string("r->method", r->method, r);
        //
        print_string("r->range", r->range, r);
        print_string("r->content_type", r->content_type, r);
        print_string("r->content_encoding", r->content_encoding, r);
        print_string("r->vlist_validator", r->vlist_validator, r);
        print_string("r->user", r->user, r);
        print_string("r->ap_auth_type", r->ap_auth_type, r);
        print_string("r->unparsed_uri", r->unparsed_uri, r);
        print_string("r->uri", r->uri, r);
        print_string("r->filename", r->filename, r);
        print_string("r->canonical_filename", r->canonical_filename, r);
        print_string("r->path_info", r->path_info, r);
        print_string("r->args", r->args, r);
        print_string("r->log_id", r->log_id, r);
        print_string("r->useragent_ip", r->useragent_ip, r);
        ap_rputs("</dl></body></html>\n", r);
    }
    return OK;
}

static void learn_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(learn_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA learn_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    learn_register_hooks  /* register hooks                      */
};
