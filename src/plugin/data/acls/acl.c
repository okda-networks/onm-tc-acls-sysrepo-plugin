/*
 * okda-networks / onm-tc-acls
 *
 * This program is made available under the terms of the
 * BSD 3-Clause license which is available at
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * SPDX-FileCopyrightText: 2023 Okda Networks
 * SPDX-FileContributor: Sartura Ltd, Deutsche Telekom AG.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "libyang/log.h"
#include "libyang/tree_data.h"
#include "plugin/common.h"
#include "plugin/ly_tree.h"
#include "plugin/types.h"
#include "srpc/ly_tree.h"
#include "sysrepo.h"
#include "uthash.h"
#include "utils/memory.h"
#include "utlist.h"
#include "memory.h"
// other data API
#include "acl.h"
#include "acl/aces.h"
#include "acl/linked_list.h"

#include <assert.h>
#include <srpc.h>
#include <stdio.h>
#include <stdlib.h>

#include "plugin/api/tcnl.h"

/*
    Libyang and srpc conversion functions.
*/

onm_tc_acl_hash_element_t* onm_tc_acl_hash_new(void)
{
    return NULL;
}

onm_tc_acl_hash_element_t* onm_tc_acl_hash_element_new(void)
{
    onm_tc_acl_hash_element_t* new_element = NULL;

    new_element = xmalloc(sizeof(onm_tc_acl_hash_element_t));
    if (!new_element)
        return NULL;

    // NULL all fields
    new_element->acl = (onm_tc_acl_t) { 0 };
    return new_element;
}

int onm_tc_acl_hash_element_set_name(onm_tc_acl_hash_element_t** el, const char* name, sr_change_oper_t change_operation)
{
    if ((*el)->acl.name) {
        FREE_SAFE((*el)->acl.name);
    }
    if (name) {
        (*el)->acl.name = xstrdup(name);
        (*el)->acl.acl_name_change_op = change_operation;
        return (*el)->acl.name == NULL;
    }

    return 0;
}

int onm_tc_acl_hash_element_set_type(onm_tc_acl_hash_element_t** el, const char* type,sr_change_oper_t change_operation)
{
    //TODO fix data type
    if ((*el)->acl.type) {
    //    FREE_SAFE((*el)->acl.type);
    }
    if (type) {
    //    (*el)->acl.type = xstrdup(type);
    //    return (*el)->acl.type == NULL;
    }
    return 0;
}

int onm_tc_acls_hash_add_acl_element(onm_tc_acl_hash_element_t** hash, onm_tc_acl_hash_element_t* new_element)
{
    onm_tc_acl_hash_element_t* found_element = NULL;

    if (new_element->acl.name)
        HASH_FIND_STR(*hash, new_element->acl.name, found_element);
    else
    {
        // element key is NULL
        return -2;
    }
    // element already exists
    if (found_element != NULL) {
        return -1;
    }

    // element not found - add new element to the hash
    HASH_ADD_KEYPTR(hh, *hash, new_element->acl.name, strlen(new_element->acl.name), new_element);

    return 0;
}

onm_tc_acl_hash_element_t* onm_tc_acl_hash_get_element(onm_tc_acl_hash_element_t** hash, const char* name)
{
    onm_tc_acl_hash_element_t* found_element = NULL;

    HASH_FIND_STR(*hash, name, found_element);

    return found_element;
}

//TODO compelete freeing elements
void onm_tc_acl_element_hash_free(onm_tc_acl_hash_element_t** el)
{
    if (*el) {
        // name
        if ((*el)->acl.name) {
            free((*el)->acl.name);
        }

        // type
        //TODO fix data type
        if ((*el)->acl.type) {
            //free((*el)->acl.type);
        }

        //attachment points TODO handeld on a seperate function

        // ace list
        // TODO add all ACE entries
        // TODO fix data type
        if ((*el)->acl.aces.ace) {
            ONM_TC_ACL_LIST_FREE((*el)->acl.aces.ace);
        }
        // element data
        free(*el);
        *el = NULL;
    }
}

void onm_tc_acls_list_hash_free(onm_tc_acl_hash_element_t** hash)
{
    onm_tc_acl_hash_element_t *tmp = NULL, *element = NULL;
    HASH_ITER(hh, *hash, element, tmp)
    {   
        HASH_DEL(*hash, element);
        onm_tc_acl_element_hash_free(&element);
    }

    *hash = NULL;
}

int onm_tc_events_acls_hash_add_acl_element(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx)
{
	const char *node_name = LYD_NAME(change_ctx->node);
	const char *parent_node_name = LYD_NAME(&change_ctx->node->parent->node);
	const char *node_value = lyd_get_value(change_ctx->node);
    onm_tc_ctx_t *ctx = (onm_tc_ctx_t *) priv;
	printf("ADD ACL DATA:\n\tNode Name: %s\n\tNode Value: %s\n\tParent Node Name: %s\n\tOperation: %d\n",node_name,node_value,parent_node_name,change_ctx->operation);
	onm_tc_acl_hash_element_t* event_acl_hash = NULL;
    event_acl_hash = onm_tc_acl_hash_element_new();

	int error = 0;
	if (strcmp(node_name,"name")==0)
	{
		SRPLG_LOG_INF(PLUGIN_NAME, "Processing new ACL change, ACL Name: %s, Change operation: %d.",node_value,change_ctx->operation);
		SRPC_SAFE_CALL_ERR(error, onm_tc_acl_hash_element_set_name(&event_acl_hash, node_value,change_ctx->operation), error_out);

        //init aces list inside temp change acl hash element
        ONM_TC_ACL_LIST_NEW(event_acl_hash->acl.aces.ace);

        // add acl element to acls_list
        onm_tc_acls_hash_add_acl_element(&ctx->events_acls_list, event_acl_hash);
        printf("added acl element %s change acl list\n",event_acl_hash->acl.name);
	}
	goto out;

error_out:
	return error;

out:
	return error;
}

int events_acl_init(void *priv)
{
	int error = 0;
	return error;
}

void events_acl_free(void *priv)
{
}


int onm_tc_acls_list_from_ly(onm_tc_acl_hash_element_t** acl_hash, const struct lyd_node* acl_list_node)
{
    int error = 0;
    int default_change_operation = -1;
    // make sure the hash is empty at the start
    assert(*acl_hash == NULL);

    // libyang
    struct lyd_node *acl_iter = (struct lyd_node*)acl_list_node;
    struct lyd_node *acl_name_node = NULL, *acl_type_node = NULL;
    struct lyd_node *aces_container_node = NULL;
    struct lyd_node *ace_list_node = NULL;
    struct lyd_node *ace_name_node = NULL;
    struct lyd_node *matches_container_node = NULL, *actions_container_node = NULL;

    struct lyd_node *match_eth_container_node = NULL, *match_ipv4_container_node = NULL, *match_ipv6_container_node = NULL, *match_tcp_container_node = NULL, *match_udp_container_node = NULL, *match_icmp_container_node = NULL;
    struct lyd_node *eth_dst_mac_addr_node = NULL, *eth_dst_mac_addr_mask_node = NULL, *eth_src_mac_addr_node = NULL, *eth_src_mac_addr_mask_node = NULL, *eth_ethtype_node = NULL;
    struct lyd_node *ipv4_src_network_node = NULL, *ipv4_dst_network_node = NULL;
    struct lyd_node *ipv6_src_network_node = NULL, *ipv6_dst_network_node = NULL;
    //tcp
    struct lyd_node *tcp_src_port_container_node = NULL, *tcp_dst_port_container_node = NULL;
    struct lyd_node *tcp_src_port_node = NULL, *tcp_dst_port_node = NULL,*tcp_src_range_lower_port_node = NULL,*tcp_dst_range_lower_port_node = NULL, *tcp_src_range_upper_port_node = NULL, *tcp_dst_range_upper_port_node = NULL;
    //udp
    struct lyd_node *udp_src_port_container_node = NULL, *udp_dst_port_container_node = NULL;
    struct lyd_node *udp_src_port_node = NULL, *udp_dst_port_node = NULL,*udp_src_range_lower_port_node = NULL,*udp_dst_range_lower_port_node = NULL, *udp_src_range_upper_port_node = NULL, *udp_dst_range_upper_port_node = NULL;
    // tcp or udp
    struct lyd_node *src_port_operator_node = NULL, *dst_port_operator_node = NULL;
    struct lyd_node *icmp_code_node = NULL;
    struct lyd_node *action_forwarding_node = NULL, *action_logging_node = NULL;


    // internal DS
    onm_tc_acl_hash_element_t* new_element = NULL;
    onm_tc_ace_element_t* new_ace_element = NULL;

    while (acl_iter) {
        // create new element
        new_element = onm_tc_acl_hash_element_new();

        // get existing nodes
        SRPC_SAFE_CALL_PTR(acl_name_node, srpc_ly_tree_get_child_leaf(acl_iter, "name"), error_out);
        acl_type_node = srpc_ly_tree_get_child_leaf(acl_iter, "type");
        aces_container_node = srpc_ly_tree_get_child_container(acl_iter, "aces");

        //set data
        if (acl_name_node){
            SRPC_SAFE_CALL_ERR(error, onm_tc_acl_hash_element_set_name(&new_element, lyd_get_value(acl_name_node),default_change_operation), error_out);  
        }
        if (acl_type_node){
            SRPC_SAFE_CALL_ERR(error, onm_tc_acl_hash_element_set_type(&new_element, lyd_get_value(acl_type_node),default_change_operation), error_out);
        }

        if (aces_container_node){
            ace_list_node = srpc_ly_tree_get_child_list(aces_container_node, "ace");

            // init ace list
            ONM_TC_ACL_LIST_NEW(new_element->acl.aces.ace);

            while(ace_list_node){
                // add new ace element
                new_ace_element = onm_tc_ace_hash_element_new();

                // fetch ace nodes
                SRPC_SAFE_CALL_PTR(ace_name_node, srpc_ly_tree_get_child_leaf(ace_list_node, "name"), error_out);
                matches_container_node = srpc_ly_tree_get_child_container(ace_list_node, "matches");
                actions_container_node = srpc_ly_tree_get_child_container(ace_list_node, "actions");

                //parse ace data
                if (ace_name_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_ace_name(&new_ace_element, lyd_get_value(ace_name_node),default_change_operation), error_out);
                    ace_name_node = NULL;
                }

                if (matches_container_node){
                    match_eth_container_node = srpc_ly_tree_get_child_container(matches_container_node, "eth");
                    match_ipv4_container_node = srpc_ly_tree_get_child_container(matches_container_node, "ipv4");
                    match_ipv6_container_node = srpc_ly_tree_get_child_container(matches_container_node, "ipv6");
                    match_tcp_container_node = srpc_ly_tree_get_child_container(matches_container_node, "tcp");
                    match_udp_container_node = srpc_ly_tree_get_child_container(matches_container_node, "udp");
                    match_icmp_container_node = srpc_ly_tree_get_child_container(matches_container_node, "icmp");
                    matches_container_node = NULL;
                    if (match_eth_container_node){
                        eth_src_mac_addr_node = srpc_ly_tree_get_child_leaf(match_eth_container_node, "source-mac-address");
                        eth_src_mac_addr_mask_node = srpc_ly_tree_get_child_leaf(match_eth_container_node, "source-mac-address-mask");
                        eth_dst_mac_addr_node = srpc_ly_tree_get_child_leaf(match_eth_container_node, "destination-mac-address");
                        eth_dst_mac_addr_mask_node = srpc_ly_tree_get_child_leaf(match_eth_container_node, "destination-mac-address-mask");
                        eth_ethtype_node = srpc_ly_tree_get_child_leaf(match_eth_container_node, "ethertype");
                        match_eth_container_node = NULL;
                    }

                    if (match_ipv4_container_node){
                        ipv4_src_network_node = srpc_ly_tree_get_child_leaf(match_ipv4_container_node, "source-ipv4-network");
                        ipv4_dst_network_node = srpc_ly_tree_get_child_leaf(match_ipv4_container_node, "destination-ipv4-network");
                        match_ipv4_container_node = NULL;
                    }

                    if (match_ipv6_container_node){
                        ipv6_src_network_node = srpc_ly_tree_get_child_leaf(match_ipv6_container_node, "source-ipv6-network");
                        ipv6_dst_network_node = srpc_ly_tree_get_child_leaf(match_ipv6_container_node, "destination-ipv6-network");
                        match_ipv6_container_node = NULL;
                    }

                    if (match_tcp_container_node){
                        tcp_src_port_container_node = srpc_ly_tree_get_child_container(match_tcp_container_node, "source-port");
                        tcp_dst_port_container_node = srpc_ly_tree_get_child_container(match_tcp_container_node, "destination-port");
                        match_tcp_container_node = NULL;
                        if (tcp_src_port_container_node){
                            tcp_src_port_node = srpc_ly_tree_get_child_leaf(tcp_src_port_container_node, "port");
                            tcp_src_range_lower_port_node = srpc_ly_tree_get_child_leaf(tcp_src_port_container_node, "lower-port");
                            tcp_src_range_upper_port_node = srpc_ly_tree_get_child_leaf(tcp_src_port_container_node, "upper-port");
                            src_port_operator_node = srpc_ly_tree_get_child_leaf(tcp_src_port_container_node, "operator");
                            tcp_src_port_container_node = NULL;
                        }
                        if (tcp_dst_port_container_node){
                            tcp_dst_port_node = srpc_ly_tree_get_child_leaf(tcp_dst_port_container_node, "port");
                            tcp_dst_range_lower_port_node = srpc_ly_tree_get_child_leaf(tcp_dst_port_container_node, "lower-port");
                            tcp_dst_range_upper_port_node = srpc_ly_tree_get_child_leaf(tcp_dst_port_container_node, "upper-port");
                            dst_port_operator_node = srpc_ly_tree_get_child_leaf(tcp_dst_port_container_node, "operator");
                            tcp_dst_port_container_node = NULL;
                        }
                    }

                    if (match_udp_container_node){
                        udp_src_port_container_node = srpc_ly_tree_get_child_container(match_udp_container_node, "source-port");
                        udp_dst_port_container_node = srpc_ly_tree_get_child_container(match_udp_container_node, "destination-port");
                        match_udp_container_node = NULL;
                        if (udp_src_port_container_node){
                            udp_src_port_node = srpc_ly_tree_get_child_leaf(udp_src_port_container_node, "port");
                            udp_src_range_lower_port_node = srpc_ly_tree_get_child_leaf(udp_src_port_container_node, "lower-port");
                            udp_src_range_upper_port_node = srpc_ly_tree_get_child_leaf(udp_src_port_container_node, "upper-port");
                            src_port_operator_node = srpc_ly_tree_get_child_leaf(udp_src_port_container_node, "operator");
                            udp_src_port_container_node = NULL;
                        }
                        if (udp_dst_port_container_node){
                            udp_dst_port_node = srpc_ly_tree_get_child_leaf(udp_dst_port_container_node, "port");
                            udp_dst_range_lower_port_node = srpc_ly_tree_get_child_leaf(udp_dst_port_container_node, "lower-port");
                            udp_dst_range_upper_port_node = srpc_ly_tree_get_child_leaf(udp_dst_port_container_node, "upper-port");
                            dst_port_operator_node = srpc_ly_tree_get_child_leaf(udp_dst_port_container_node, "operator");
                            udp_dst_port_container_node = NULL;
                        }
                    }

                    if (match_icmp_container_node){
                        icmp_code_node = srpc_ly_tree_get_child_leaf(match_icmp_container_node, "code");
                        match_icmp_container_node = NULL;
                    }
                }

                if (actions_container_node){
                    SRPC_SAFE_CALL_PTR(action_forwarding_node, srpc_ly_tree_get_child_leaf(actions_container_node, "forwarding"), error_out);
                    SRPC_SAFE_CALL_PTR(action_logging_node, srpc_ly_tree_get_child_leaf(actions_container_node, "logging"), error_out);
                    actions_container_node = NULL;
                }

                // set match data
                if(eth_src_mac_addr_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_src_mac_addr(&new_ace_element, lyd_get_value(eth_src_mac_addr_node),default_change_operation), error_out);
                    eth_src_mac_addr_node = NULL;
                }
                if(eth_src_mac_addr_mask_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_src_mac_addr_mask(&new_ace_element, lyd_get_value(eth_src_mac_addr_mask_node),default_change_operation), error_out);
                    eth_src_mac_addr_mask_node = NULL;
                }
                if(eth_dst_mac_addr_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_dst_mac_addr(&new_ace_element, lyd_get_value(eth_dst_mac_addr_node),default_change_operation), error_out);
                    eth_dst_mac_addr_node = NULL;
                }
                if(eth_dst_mac_addr_mask_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_dst_mac_addr_mask(&new_ace_element, lyd_get_value(eth_dst_mac_addr_mask_node),default_change_operation), error_out);
                    eth_dst_mac_addr_mask_node = NULL;
                }
                if(eth_ethtype_node){
                    const char* ethertype_str = NULL;
                    SRPC_SAFE_CALL_PTR(ethertype_str, lyd_get_value(eth_ethtype_node), error_out);
                    uint16_t ether_type;
                    if (ll_proto_a2n(&ether_type, ethertype_str))
                    {
                        // TODO revise: currently this failure will set ethertype to ALL
                        SRPLG_LOG_ERR(PLUGIN_NAME, "ACE %s Failed to set specified EtherType for L2 match",new_ace_element->ace.name);
                        error = -1;
                    }
                    else
                        SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_eth_ethertype(&new_ace_element, ether_type,default_change_operation), error_out);
                    eth_ethtype_node = NULL;
                }
                if(ipv4_src_network_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_ipv4_src_network(&new_ace_element, lyd_get_value(ipv4_src_network_node),default_change_operation), error_out);
                    ipv4_src_network_node = NULL;
                }
                if(ipv4_dst_network_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_ipv4_dst_network(&new_ace_element, lyd_get_value(ipv4_dst_network_node),default_change_operation), error_out);
                    ipv4_dst_network_node = NULL;
                }
                if(ipv6_src_network_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_ipv6_src_network(&new_ace_element, lyd_get_value(ipv6_src_network_node),default_change_operation), error_out);
                    ipv6_src_network_node = NULL;
                }
                if(ipv6_dst_network_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_ipv6_dst_network(&new_ace_element, lyd_get_value(ipv6_dst_network_node),default_change_operation), error_out);
                    ipv6_dst_network_node = NULL;
                }

                if(tcp_src_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str, *port_str = NULL;
                    SRPC_SAFE_CALL_PTR(port_oper_str, lyd_get_value(src_port_operator_node), error_out);
                    SRPC_SAFE_CALL_PTR(port_str, lyd_get_value(tcp_src_port_node), error_out);
                    
                    error = port_str_to_port_attr(port_attr,port_str,NULL,port_oper_str,PORT_ATTR_SRC,PORT_ATTR_PROTO_TCP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);

                    tcp_src_port_node = NULL;
                    free(port_attr);
                }
                if(tcp_dst_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str, *port_str = NULL;
                    SRPC_SAFE_CALL_PTR(port_oper_str, lyd_get_value(dst_port_operator_node), error_out);
                    SRPC_SAFE_CALL_PTR(port_str, lyd_get_value(tcp_dst_port_node), error_out);

                    error = port_str_to_port_attr(port_attr,port_str,NULL,port_oper_str,PORT_ATTR_DST,PORT_ATTR_PROTO_TCP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);
                    tcp_dst_port_node = NULL;
                    free(port_attr);
                }
                if(udp_src_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str, *port_str = NULL;
                    SRPC_SAFE_CALL_PTR(port_oper_str, lyd_get_value(src_port_operator_node), error_out);
                    SRPC_SAFE_CALL_PTR(port_str, lyd_get_value(udp_src_port_node), error_out);

                    error = port_str_to_port_attr(port_attr,port_str,NULL,port_oper_str,PORT_ATTR_SRC,PORT_ATTR_PROTO_UDP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);

                    udp_src_port_node = NULL;
                    free(port_attr);
                }
                if(udp_dst_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str, *port_str = NULL;
                    SRPC_SAFE_CALL_PTR(port_oper_str, lyd_get_value(dst_port_operator_node), error_out);
                    SRPC_SAFE_CALL_PTR(port_str, lyd_get_value(udp_dst_port_node), error_out);

                    error = port_str_to_port_attr(port_attr,port_str,NULL,port_oper_str,PORT_ATTR_DST,PORT_ATTR_PROTO_UDP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);

                    udp_dst_port_node = NULL;
                    free(port_attr);
                }
                if(tcp_src_range_lower_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str =NULL, * lower_str = NULL, *upper_str = NULL;
                    port_oper_str = "range";
                    SRPC_SAFE_CALL_PTR(lower_str, lyd_get_value(tcp_src_range_lower_port_node), error_out);
                    SRPC_SAFE_CALL_PTR(upper_str, lyd_get_value(tcp_src_range_upper_port_node), error_out);

                    port_str_to_port_attr(port_attr, lower_str, upper_str,port_oper_str,PORT_ATTR_SRC,PORT_ATTR_PROTO_TCP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);

                    tcp_src_range_lower_port_node = NULL;
                    tcp_src_range_upper_port_node = NULL;
                    free(port_attr);
                }
                if(tcp_dst_range_lower_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str =NULL, * lower_str = NULL, *upper_str = NULL;
                    port_oper_str = "range";
                    SRPC_SAFE_CALL_PTR(lower_str, lyd_get_value(tcp_dst_range_lower_port_node), error_out);
                    SRPC_SAFE_CALL_PTR(upper_str, lyd_get_value(tcp_dst_range_upper_port_node), error_out);

                    port_str_to_port_attr(port_attr, lower_str, upper_str,port_oper_str,PORT_ATTR_DST,PORT_ATTR_PROTO_TCP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);

                    tcp_dst_range_lower_port_node = NULL;
                    tcp_dst_range_upper_port_node = NULL;
                    free(port_attr);
                }
                if(udp_src_range_lower_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str =NULL, * lower_str = NULL, *upper_str = NULL;
                    port_oper_str = "range";
                    SRPC_SAFE_CALL_PTR(lower_str, lyd_get_value(udp_src_range_lower_port_node), error_out);
                    SRPC_SAFE_CALL_PTR(upper_str, lyd_get_value(udp_src_range_upper_port_node), error_out);

                    port_str_to_port_attr(port_attr, lower_str, upper_str,port_oper_str,PORT_ATTR_SRC,PORT_ATTR_PROTO_UDP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);

                    udp_src_range_lower_port_node = NULL;
                    udp_src_range_upper_port_node = NULL;
                    free(port_attr);
                }
                if(udp_dst_range_lower_port_node){
                    onm_tc_port_attributes_t *port_attr = malloc(sizeof(onm_tc_port_attributes_t));
                    const char* port_oper_str =NULL, * lower_str = NULL, *upper_str = NULL;
                    port_oper_str = "range";
                    SRPC_SAFE_CALL_PTR(lower_str, lyd_get_value(udp_dst_range_lower_port_node), error_out);
                    SRPC_SAFE_CALL_PTR(upper_str, lyd_get_value(udp_dst_range_upper_port_node), error_out);

                    port_str_to_port_attr(port_attr, lower_str, upper_str,port_oper_str,PORT_ATTR_DST,PORT_ATTR_PROTO_UDP);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port(&new_ace_element, port_attr,default_change_operation), error_out);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_port_operator(&new_ace_element, port_attr,default_change_operation), error_out);

                    udp_dst_range_lower_port_node = NULL;
                    udp_dst_range_upper_port_node = NULL;
                    free(port_attr);
                }

                if(icmp_code_node){
                    const char* icmp_code_str = NULL;
                    SRPC_SAFE_CALL_PTR(icmp_code_str, lyd_get_value(icmp_code_node), error_out);
                    const uint8_t icmp_code = (uint8_t)atoi(icmp_code_str);
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_match_icmp_code(&new_ace_element, icmp_code,default_change_operation), error_out);
                    icmp_code_node = NULL;
                }
                // set actions data
                if(action_forwarding_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_action_forwarding(&new_ace_element, lyd_get_value(action_forwarding_node),default_change_operation), error_out);
                    action_forwarding_node = NULL;
                }
                if(action_logging_node){
                    SRPC_SAFE_CALL_ERR(error, onm_tc_ace_hash_element_set_action_logging(&new_ace_element, lyd_get_value(action_logging_node),default_change_operation), error_out);
                    action_logging_node = NULL;
                }


                // add ace list to main acl list
                ONM_TC_ACL_LIST_ADD_ELEMENT(new_element->acl.aces.ace, new_ace_element);
                
                // null new ace element
                new_ace_element = NULL;

                //move to next ace
                ace_list_node = srpc_ly_tree_get_list_next(ace_list_node);
            }
        }

        // add acl element to acls list
        error = onm_tc_acls_hash_add_acl_element(acl_hash, new_element);

        // set to NULL
        new_element = NULL;

        // move to next acl entry
        acl_iter = srpc_ly_tree_get_list_next(acl_iter);
    }

    goto out;
error_out:
    error = -1;

out:
    if (new_element) {
        //TODO fix this function not cause a memeory leak, not all data are freed now
        onm_tc_acl_element_hash_free(&new_element);
    }

    return error;
}

void onm_tc_acls_list_print_debug(const onm_tc_acl_hash_element_t* acl_hash)
{
    const onm_tc_acl_hash_element_t *iter = NULL, *tmp = NULL;
    onm_tc_ace_element_t* ace_iter = NULL;
    SRPLG_LOG_INF(PLUGIN_NAME, "+ ACLs: ");
    HASH_ITER(hh, acl_hash, iter, tmp)
    {
        SRPLG_LOG_INF(PLUGIN_NAME, "| \t+ ACL %s:", iter->acl.name);
        SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\tName = %s (change operation %d)", iter->acl.name,iter->acl.acl_name_change_op);
        //SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\tName Change Operation = %d", iter->acl.acl_name_change_op);
        if(iter->acl.type){
            SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\tType = %s (change operation %d)", iter->acl.type,iter->acl.acl_type_change_op);
            //SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\tType Change Operation = %d", iter->acl.acl_type_change_op);
        }
        
        SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\tACEs:");
        LL_FOREACH(iter->acl.aces.ace, ace_iter)
        {
            SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t+ ACE %s", ace_iter->ace.name);
            SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     ACE Name = %s (change operation %d)", ace_iter->ace.name,ace_iter->ace.ace_name_change_op);
            SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     + Matches:");
            if(ace_iter->ace.matches.eth.source_mac_address){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Source mac address = %s (change operation %d)",
                ace_iter->ace.matches.eth.source_mac_address,
                ace_iter->ace.matches.eth.src_mac_change_op);
            }
            if(ace_iter->ace.matches.eth.source_mac_address_mask){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Source mac address mask = %s (change operation %d)",
                ace_iter->ace.matches.eth.source_mac_address_mask,
                ace_iter->ace.matches.eth.src_mac_mask_change_op);
            }
            if(ace_iter->ace.matches.eth.destination_mac_address){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Destination mac address = %s (change operation %d)",
                ace_iter->ace.matches.eth.destination_mac_address,
                ace_iter->ace.matches.eth.dst_mac_change_op);
            }
            if(ace_iter->ace.matches.eth.destination_mac_address_mask){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Destination mac address mask = %s (change operation %d)",
                ace_iter->ace.matches.eth.destination_mac_address_mask,
                ace_iter->ace.matches.eth.dst_mac_mask_change_op);
            }
            if(ace_iter->ace.matches.eth.ethertype != 0){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- EtherType = %d (change operation %d)",
                ace_iter->ace.matches.eth.ethertype,
                ace_iter->ace.matches.eth.ethertype_change_op);
            }
            if(ace_iter->ace.matches.ipv4.source_ipv4_network){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Source IPv4 Network = %s (change operation %d)",
                ace_iter->ace.matches.ipv4.source_ipv4_network,
                ace_iter->ace.matches.ipv4.src_ipv4_change_op);
            }
            if(ace_iter->ace.matches.ipv4.destination_ipv4_network){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Destination IPv4 Network = %s (change operation %d)",
                ace_iter->ace.matches.ipv4.destination_ipv4_network,
                ace_iter->ace.matches.ipv4.dst_ipv4_change_op);
            }
            if(ace_iter->ace.matches.ipv6.source_ipv6_network){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Source IPv6 Network = %s (change operation %d)",
                ace_iter->ace.matches.ipv6.source_ipv6_network,
                ace_iter->ace.matches.ipv6.src_ipv6_change_op);
            }
            if(ace_iter->ace.matches.ipv6.destination_ipv6_network){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Destination IPv6 Network = %s (change operation %d)",
                ace_iter->ace.matches.ipv6.destination_ipv6_network,ace_iter->ace.matches.ipv6.dst_ipv6_change_op);
            }
            // TCP Source Port
            if (ace_iter->ace.matches.tcp.source_port.port != 0 ||
                (ace_iter->ace.matches.tcp.source_port.port_operator != PORT_NOOP &&
                ace_iter->ace.matches.tcp.source_port.port_operator != PORT_RANGE)){
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- TCP Source Port = %d Operator = %d (change operation %d)",
                ace_iter->ace.matches.tcp.source_port.port, 
                ace_iter->ace.matches.tcp.source_port.port_operator,
                ace_iter->ace.matches.tcp.source_port.src_port_value_change_op);
            }
            // TCP Source Port Range
            if(ace_iter->ace.matches.tcp.source_port.lower_port != 0  || ace_iter->ace.matches.tcp.source_port.upper_port != 0)
            {
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- TCP Source Port Range = [%d-%d] Operator = %d (change operation %d)",
                ace_iter->ace.matches.tcp.source_port.lower_port, 
                ace_iter->ace.matches.tcp.source_port.upper_port,
                ace_iter->ace.matches.tcp.source_port.port_operator,
                ace_iter->ace.matches.tcp.source_port.src_port_value_change_op
                );
            }
            // UDP Source Port
            if (ace_iter->ace.matches.udp.source_port.port != 0 ||
                (ace_iter->ace.matches.udp.source_port.port_operator != PORT_NOOP &&
                ace_iter->ace.matches.udp.source_port.port_operator != PORT_RANGE)) {
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- UDP Source Port = %d Operator = %d (change operation %d)",
                ace_iter->ace.matches.udp.source_port.port,
                ace_iter->ace.matches.udp.source_port.port_operator,
                ace_iter->ace.matches.udp.source_port.src_port_value_change_op);
            }
            // UDP Source Port Range
            if (ace_iter->ace.matches.udp.source_port.lower_port != 0 || ace_iter->ace.matches.udp.source_port.upper_port != 0) {
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- UDP Source Port Range = [%d-%d] Operator = %d (change operation %d)",
                ace_iter->ace.matches.udp.source_port.lower_port,
                ace_iter->ace.matches.udp.source_port.upper_port,
                ace_iter->ace.matches.udp.source_port.port_operator,
                ace_iter->ace.matches.udp.source_port.src_port_value_change_op);
            }
            // TCP Destination Port
            if (ace_iter->ace.matches.tcp.destination_port.port != 0 ||
            (ace_iter->ace.matches.tcp.destination_port.port_operator != PORT_NOOP &&
            ace_iter->ace.matches.tcp.destination_port.port_operator != PORT_RANGE )) {
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- TCP Destination Port = %d Operator = %d (change operation %d)",
                ace_iter->ace.matches.tcp.destination_port.port,
                ace_iter->ace.matches.tcp.destination_port.port_operator,
                ace_iter->ace.matches.tcp.destination_port.dst_port_value_change_op);
            }
            // TCP Destination Port Range
            if (ace_iter->ace.matches.tcp.destination_port.lower_port != 0 || ace_iter->ace.matches.tcp.destination_port.upper_port != 0) {
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- TCP Destination Port Range = [%d-%d] Operator = %d (change operation %d)",
                ace_iter->ace.matches.tcp.destination_port.lower_port,
                ace_iter->ace.matches.tcp.destination_port.upper_port,
                ace_iter->ace.matches.tcp.destination_port.port_operator,
                ace_iter->ace.matches.tcp.destination_port.dst_port_value_change_op);
            }

            // UDP Destination Port
            if (ace_iter->ace.matches.udp.destination_port.port != 0 ||
                (ace_iter->ace.matches.udp.destination_port.port_operator != PORT_NOOP &&
                ace_iter->ace.matches.udp.destination_port.port_operator != PORT_RANGE)) {
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- UDP Destination Port = %d Operator = %d (change operation %d)",
                ace_iter->ace.matches.udp.destination_port.port,
                ace_iter->ace.matches.udp.destination_port.port_operator,
                ace_iter->ace.matches.udp.destination_port.dst_port_value_change_op);
            }

            // UDP Destination Port Range
            if (ace_iter->ace.matches.udp.destination_port.lower_port != 0 || ace_iter->ace.matches.udp.destination_port.upper_port != 0) {
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- UDP Destination Port Range = [%d-%d] Operator = %d (change operation %d)", 
                ace_iter->ace.matches.udp.destination_port.lower_port,
                ace_iter->ace.matches.udp.destination_port.upper_port,
                ace_iter->ace.matches.udp.destination_port.port_operator,
                ace_iter->ace.matches.udp.destination_port.dst_port_value_change_op);
            }
            SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     + Actions:");
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Action-Forwarding = %d (change operation %d)",
                ace_iter->ace.actions.forwarding,
                ace_iter->ace.actions.forwarding_change_op);
            if(ace_iter->ace.actions.logging != 0)
                SRPLG_LOG_INF(PLUGIN_NAME, "| \t|\t|     |---- Action-Logging = %d (change operation %d)", 
                ace_iter->ace.actions.logging,
                ace_iter->ace.actions.logging_change_op);
        }
    }
}
