#ifndef ONM_TC_PLUGIN_API_ACLS_CHANGE_H
#define ONM_TC_PLUGIN_API_ACLS_CHANGE_H

#include <utarray.h>
#include <srpc.h>

int change_acl_init(void *priv);
void change_acl_free(void *priv);
int acl_change_iterator(void *priv, sr_session_ctx_t *session, const char *xpath);
#endif // ONM_TC_PLUGIN_API_ACLS_CHANGE_H