#include "plugin/types.h"
#include <srpc.h>
#include "plugin/context.h"

#define VALIDATE_AND_UPDATE_EVENT_PORT_OR_RANGE(ACL_NAME, ACE_ITER, PROTO, PORT_FIELD, LOG_MSG, PORT_ATTR_DIR, PORT_ATTR_PROTO) \
    do { \
        if ((ACE_ITER)->ace.matches.PROTO.PORT_FIELD.lower_port == 0 && (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.upper_port == 0 ) { \
            if ((ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port_operator == PORT_NOOP && (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port == 0) { \
                (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.lower_port = running_ace->ace.matches.PROTO.PORT_FIELD.lower_port;\
                (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.upper_port = running_ace->ace.matches.PROTO.PORT_FIELD.upper_port;\
                (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port_operator = running_ace->ace.matches.PROTO.PORT_FIELD.port_operator; \
                (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port = running_ace->ace.matches.PROTO.PORT_FIELD.port; \
                (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.single_port_change_op = DEFAULT_CHANGE_OPERATION; \
                (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.range_port_change_op = DEFAULT_CHANGE_OPERATION; \
                (ACE_ITER)->ace.matches.PROTO._is_set = running_ace->ace.matches.PROTO._is_set; \
            } \
        } \
        if ((ACE_ITER)->ace.matches.PROTO.PORT_FIELD.lower_port == 0 && (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.upper_port != 0) { \
            SRPLG_LOG_DBG(PLUGIN_NAME, LOG_MSG, ACL_NAME, (ACE_ITER)->ace.name); \
            (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.lower_port = running_ace->ace.matches.PROTO.PORT_FIELD.lower_port; \
            (ACE_ITER)->ace.matches.PROTO._is_set = running_ace->ace.matches.PROTO._is_set; \
        } \
        if ((ACE_ITER)->ace.matches.PROTO.PORT_FIELD.upper_port == 0 && (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.lower_port != 0) { \
            SRPLG_LOG_DBG(PLUGIN_NAME, LOG_MSG, ACL_NAME, (ACE_ITER)->ace.name); \
            (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.upper_port = running_ace->ace.matches.PROTO.PORT_FIELD.upper_port;\
            (ACE_ITER)->ace.matches.PROTO._is_set = running_ace->ace.matches.PROTO._is_set; \
        } \
        if ((ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port != 0 && (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port_operator == PORT_NOOP) { \
            SRPLG_LOG_DBG(PLUGIN_NAME, LOG_MSG, ACL_NAME, (ACE_ITER)->ace.name); \
            (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port_operator = running_ace->ace.matches.PROTO.PORT_FIELD.port_operator; \
            (ACE_ITER)->ace.matches.PROTO._is_set = running_ace->ace.matches.PROTO._is_set; \
        } \
        if ((ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port_operator != PORT_NOOP && (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port == 0) { \
            SRPLG_LOG_DBG(PLUGIN_NAME, LOG_MSG, ACL_NAME, (ACE_ITER)->ace.name); \
            (ACE_ITER)->ace.matches.PROTO.PORT_FIELD.port = running_ace->ace.matches.PROTO.PORT_FIELD.port;\
            (ACE_ITER)->ace.matches.PROTO._is_set = running_ace->ace.matches.PROTO._is_set; \
        } \
    } while (0)

int onm_tc_acls_list_from_ly(onm_tc_acl_hash_element_t** if_hash, const struct lyd_node* acl_list_node);
onm_tc_acl_hash_element_t* onm_tc_acl_hash_element_new(void);
onm_tc_acl_hash_element_t* onm_tc_acl_hash_new(void);

void onm_tc_acl_element_hash_free(onm_tc_acl_hash_element_t** el);
void onm_tc_acls_list_hash_free(onm_tc_acl_hash_element_t** hash);

void onm_tc_acls_list_print_debug(const onm_tc_acl_hash_element_t* acl_hash);

unsigned int acl_name2id(const char *str);
int onm_tc_acl_hash_element_set_name(onm_tc_acl_hash_element_t** el, const char* name,sr_change_oper_t change_operation);
int onm_tc_acl_hash_element_set_type(onm_tc_acl_hash_element_t** el, const char* type,sr_change_oper_t change_operation);
int onm_tc_acl_hash_element_set_operation(onm_tc_acl_hash_element_t** el,sr_change_oper_t operation);




onm_tc_acl_hash_element_t* onm_tc_acl_hash_get_element(onm_tc_acl_hash_element_t** hash, const char* name);
int onm_tc_acls_hash_add_acl_element(onm_tc_acl_hash_element_t** hash, onm_tc_acl_hash_element_t* new_element);
int onm_tc_events_acls_hash_add_acl_element(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);

int events_acl_init(void *priv);
void events_acl_free(void *priv);

int validate_and_update_events_acls_hash(onm_tc_ctx_t * ctx);