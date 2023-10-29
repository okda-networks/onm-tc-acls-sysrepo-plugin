#ifndef ONM_TC_PLUGIN_API_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_CHANGE_H
#define ONM_TC_PLUGIN_API_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_CHANGE_H

#include <utarray.h>
#include <srpc.h>

int acls_acl_aces_ace_matches_udp_source_port_change_port_init(void *priv);
int acls_acl_aces_ace_matches_udp_source_port_change_port(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
void acls_acl_aces_ace_matches_udp_source_port_change_port_free(void *priv);
int acls_acl_aces_ace_matches_udp_source_port_change_operator_init(void *priv);
int acls_acl_aces_ace_matches_udp_source_port_change_operator(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
void acls_acl_aces_ace_matches_udp_source_port_change_operator_free(void *priv);
int acls_acl_aces_ace_matches_udp_source_port_change_upper_port_init(void *priv);
int acls_acl_aces_ace_matches_udp_source_port_change_upper_port(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
void acls_acl_aces_ace_matches_udp_source_port_change_upper_port_free(void *priv);
int acls_acl_aces_ace_matches_udp_source_port_change_lower_port_init(void *priv);
int acls_acl_aces_ace_matches_udp_source_port_change_lower_port(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
void acls_acl_aces_ace_matches_udp_source_port_change_lower_port_free(void *priv);

#endif // ONM_TC_PLUGIN_API_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_CHANGE_H