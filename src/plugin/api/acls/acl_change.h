#ifndef ONM_TC_PLUGIN_API_ACLS_CHANGE_H
#define ONM_TC_PLUGIN_API_ACLS_CHANGE_H

#include <utarray.h>
#include <srpc.h>

int onm_tc_change_acl_init(void *priv);
int onm_tc_change_acl(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
void onm_tc_change_acl_free(void *priv);

#endif // ONM_TC_PLUGIN_API_ACLS_CHANGE_H