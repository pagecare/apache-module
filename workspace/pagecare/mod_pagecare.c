#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int pagecare_handler(request_rec *r)
{
    if (strcmp(r->handler, "pagecare")) {
        return DECLINED;
    }

    r->content_type = "text/html";

    if (!r->header_only) {
        ap_rputs("<html><head><title>PageCare module</title></head><body>\n", r);
        ap_rputs("<h1>Intercepted!</h1>", r);
        ap_rputs("</body></html>\n", r);
    }
    return OK;
}

static void pagecare_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(pagecare_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA pagecare_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    pagecare_register_hooks  /* register hooks                      */
};
