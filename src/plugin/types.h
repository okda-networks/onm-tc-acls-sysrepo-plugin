#ifndef ONM_TC_PLUGIN_TYPES_H
#define ONM_TC_PLUGIN_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <uthash.h>
#include <sysrepo.h>
// typedefs
typedef struct onm_tc_eth onm_tc_eth_t;
typedef struct onm_tc_ipv4 onm_tc_ipv4_t;
typedef struct onm_tc_ipv6 onm_tc_ipv6_t;
typedef struct onm_tc_tcp onm_tc_tcp_t;
typedef struct onm_tc_source_port onm_tc_source_port_t;
typedef struct onm_tc_destination_port onm_tc_destination_port_t;
typedef struct onm_tc_udp onm_tc_udp_t;
typedef struct onm_tc_icmp onm_tc_icmp_t;
typedef struct onm_tc_matches onm_tc_matches_t;
typedef struct onm_tc_ace onm_tc_ace_t;
typedef struct onm_tc_ace_element onm_tc_ace_element_t;
typedef struct onm_tc_aces onm_tc_aces_t;
typedef struct onm_tc_acl onm_tc_acl_t;
typedef struct onm_tc_acl_element onm_tc_acl_element_t;
//typedef struct onm_tc_acls onm_tc_acls_t;

typedef struct onm_tc_aps_ingress onm_tc_aps_ingress_t;
typedef struct onm_tc_aps_egress onm_tc_aps_egress_t;
typedef struct onm_tc_aps_acl_sets onm_tc_aps_acl_sets_t;
typedef struct onm_tc_aps_acl_set onm_tc_aps_acl_set_t;
typedef struct onm_tc_aps_acl_set_element onm_tc_aps_acl_set_element_t;
typedef struct onm_tc_aps_interface onm_tc_aps_interface_t;
typedef struct onm_tc_aps_interface_element onm_tc_aps_interface_element_t;
typedef struct onm_tc_aps onm_tc_aps_t;

typedef struct ietf_interface ietf_interface_t;
typedef enum forwarding_action forwarding_action_t;
typedef enum logging_action logging_action_t;
typedef enum port_operation port_operation_t;

typedef struct onm_tc_port_attributes onm_tc_port_attributes_t;
typedef enum onm_tc_port_attr_direction onm_tc_port_attr_direction_t;
typedef enum onm_tc_port_attr_proto onm_tc_port_attr_proto_t;

typedef struct onm_tc_actions onm_tc_actions_t;
typedef enum onm_tc_acl_type onm_tc_acl_type_t;

typedef struct onm_tc_acl_hash_element onm_tc_acl_hash_element_t;
typedef struct onm_tc_aps_interface_hash_element onm_tc_aps_interface_hash_element_t;


//TODO Add more details to interface definition
struct ietf_interface {
    char * name;
};

enum forwarding_action{
    FORWARD_NOOP,
    FORWARD_ACCEPT,
    FORWARD_DROP,
    FORWARD_REJECT
};

enum logging_action{
    LOG_SYSLOG,
    LOG_NONE
};

enum port_operation{
    PORT_NOOP,
    PORT_EQUAL,
    PORT_LTE,
    PORT_GTE,
    PORT_NOT_EQUAL,
    PORT_RANGE
};

struct onm_tc_actions {
    forwarding_action_t forwarding;
    forwarding_action_t logging;
};

enum onm_tc_port_attr_proto{
    PROT_ATTR_NOPROTO,
    PORT_ATTR_PROTO_TCP,
    PORT_ATTR_PROTO_UDP
};

enum onm_tc_port_attr_direction{
    PROT_ATTR_NODIRECTION,
    PORT_ATTR_SRC,
    PORT_ATTR_DST
};

struct onm_tc_port_attributes{
    onm_tc_port_attr_proto_t proto;
    onm_tc_port_attr_direction_t direction;
    port_operation_t port_operation;
    uint16_t port;
    uint16_t lower_port;
    uint16_t upper_port;
};



struct onm_tc_eth {
    char * destination_mac_address;
    char * destination_mac_address_mask;
    char * source_mac_address;
    char * source_mac_address_mask;
    uint16_t ethertype;
    uint8_t _is_set;
    sr_change_oper_t src_mac_change_op;
    sr_change_oper_t src_mac_mask_change_op;
    sr_change_oper_t dst_mac_change_op;
    sr_change_oper_t dst_mac_mask_change_op;
    sr_change_oper_t ethertype_change_op;
};

struct onm_tc_ipv4 {
    uint8_t dscp;
    uint8_t ecn;
    uint16_t length;
    uint8_t ttl;
    uint8_t protocol;
    uint8_t ihl;
    uint64_t flags;
    uint16_t offset;
    uint16_t identification;
    char * destination_ipv4_network;
    char * source_ipv4_network;
    uint8_t _is_set;
    sr_change_oper_t src_ipv4_change_op;
    sr_change_oper_t dst_ipv4_change_op;
};

struct onm_tc_ipv6 {
    uint8_t dscp;
    uint8_t ecn;
    uint16_t length;
    uint8_t ttl;
    uint8_t protocol;
    char * destination_ipv6_network;
    char * source_ipv6_network;
    uint32_t flow_label;
    uint8_t _is_set;
    sr_change_oper_t src_ipv6_change_op;
    sr_change_oper_t dst_ipv6_change_op;
};

struct onm_tc_source_port {
    uint16_t lower_port;
    uint16_t upper_port;
    uint16_t port;
    port_operation_t port_operation;
    sr_change_oper_t src_port_value_change_op;
};

struct onm_tc_destination_port {
    uint16_t lower_port;
    uint16_t upper_port;
    uint16_t port;
    port_operation_t port_operation;
    sr_change_oper_t dst_port_value_change_op;
    sr_change_oper_t dst_port_operation_change_op;
};

struct onm_tc_tcp {
    uint32_t sequence_number;
    uint32_t acknowledgement_number;
    uint8_t data_offset;
    uint8_t reserved;
    uint64_t flags;
    uint16_t window_size;
    uint16_t urgent_pointer;
    void * options;
    onm_tc_source_port_t source_port;
    onm_tc_destination_port_t destination_port;
    uint8_t _is_set;
};


struct onm_tc_udp {
    uint16_t length;
    onm_tc_source_port_t source_port;
    onm_tc_destination_port_t destination_port;
    uint8_t _is_set;
};

struct onm_tc_icmp {
    uint8_t type;
    uint8_t code;
    void * rest_of_header;
    uint8_t _is_set;
    sr_change_oper_t icmp_type_change_op;
    sr_change_oper_t icmp_code_change_op;
};

struct onm_tc_matches {
    onm_tc_eth_t eth;
    onm_tc_ipv4_t ipv4;
    onm_tc_ipv6_t ipv6;
    onm_tc_tcp_t tcp;
    onm_tc_udp_t udp;
    onm_tc_icmp_t icmp;
    ietf_interface_t egress_interface;
    ietf_interface_t ingress_interface;
};

struct onm_tc_aces {
    onm_tc_ace_element_t* ace;
};

struct onm_tc_ace {
    char * name;
    onm_tc_matches_t matches;
    onm_tc_actions_t actions;
    sr_change_oper_t ace_name_change_op;
};

struct onm_tc_ace_element {
    onm_tc_ace_element_t* next;
    onm_tc_ace_t ace;
};


enum onm_tc_acl_type{
    ACL_BASE,
    IPV4_ACL_TYPE,
    IPV6_ACL_TYPE,
    ETH_ACL_TYPE,
    MIXED_ETH_IPV4_ACL_TYPE,
    MIXED_ETH_IPV6_ACL_TYPE,
    MIXED_ETH_IPV4_IPV6_ACL_TYPE
};


struct onm_tc_acl {
    char * name;
    onm_tc_acl_type_t type;
    onm_tc_aces_t aces;
    sr_change_oper_t acl_name_change_op;
    sr_change_oper_t acl_type_change_op;
};

struct onm_tc_acl_element {
    onm_tc_acl_t acl;
    onm_tc_acl_element_t* next;
};

struct onm_tc_aps_acl_set {
    char * name;
};

struct onm_tc_aps_acl_sets {
    onm_tc_aps_acl_set_element_t* acl_set;
};

struct onm_tc_aps_ingress {
    onm_tc_aps_acl_sets_t acl_sets;
};

struct onm_tc_aps_acl_set_element {
    onm_tc_aps_acl_set_t acl_set;
    onm_tc_aps_acl_set_element_t* next;
};



struct onm_tc_aps_egress {
    onm_tc_aps_acl_sets_t acl_sets;
};

struct onm_tc_aps_interface {
    //TODO review interface_id type (referes to interface name)
    char * interface_id;
    onm_tc_aps_ingress_t ingress;
    onm_tc_aps_egress_t egress;
};

struct onm_tc_aps_interface_element {
    onm_tc_aps_interface_t interface;
    onm_tc_aps_interface_element_t* next;
};

struct onm_tc_aps {
    onm_tc_aps_interface_element_t* interface;
};

/*
struct onm_tc_acls {
    onm_tc_acl_element_t* acl;
    onm_tc_aps_t attachment_points;
};
*/
struct onm_tc_acl_hash_element {
    onm_tc_acl_t acl;
    UT_hash_handle hh;
};

struct onm_tc_aps_interface_hash_element {
    onm_tc_aps_interface_t interface;
    UT_hash_handle hh;
};

#endif // ONM_TC_PLUGIN_TYPES_H