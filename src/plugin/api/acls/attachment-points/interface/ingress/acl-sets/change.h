#ifndef ONM_TC_PLUGIN_API_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_CHANGE_H
#define ONM_TC_PLUGIN_API_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_CHANGE_H

#include <utarray.h>
#include <srpc.h>

int acls_attachment_points_interface_ingress_acl_sets_change_acl_set_init(void *priv);
int acls_attachment_points_interface_ingress_acl_sets_change_acl_set(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
void acls_attachment_points_interface_ingress_acl_sets_change_acl_set_free(void *priv);

#endif // ONM_TC_PLUGIN_API_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_CHANGE_H