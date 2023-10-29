#ifndef ONM_TC_PLUGIN_COMMON_H
#define ONM_TC_PLUGIN_COMMON_H

#define PLUGIN_NAME "ONM-TC-ACLs"

#define BASE_YANG_MODEL "ietf-access-control-list"

#define ONM_TC_ACLS_CONTAINER_YANG_PATH "/" BASE_YANG_MODEL ":acls"
#define ONM_TC_ACLS_LIST_YANG_PATH ONM_TC_ACLS_CONTAINER_YANG_PATH "/acl"

#define ONM_TC_ACLS_ACL_NAME_YANG_PATH ONM_TC_ACLS_ACL_YANG_PATH "/name"
#define ONM_TC_ACLS_ACL_TYPE_YANG_PATH ONM_TC_ACLS_ACL_YANG_PATH "/type"
#define ONM_TC_ACLS_ACL_ACES_ACE_NAME_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_YANG_PATH "/name"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_DESTINATION_MAC_ADDRESS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_YANG_PATH "/destination-mac-address"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_DESTINATION_MAC_ADDRESS_MASK_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_YANG_PATH "/destination-mac-address-mask"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_SOURCE_MAC_ADDRESS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_YANG_PATH "/source-mac-address"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_SOURCE_MAC_ADDRESS_MASK_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_YANG_PATH "/source-mac-address-mask"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_ETHERTYPE_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_YANG_PATH "/ethertype"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ETH_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/eth"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_DSCP_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/dscp"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_ECN_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/ecn"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_LENGTH_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/length"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_TTL_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/ttl"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_PROTOCOL_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/protocol"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_IHL_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/ihl"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_FLAGS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/flags"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_OFFSET_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/offset"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_IDENTIFICATION_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/identification"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_DESTINATION_IPV4_NETWORK_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/destination-ipv4-network"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_SOURCE_IPV4_NETWORK_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH "/source-ipv4-network"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV4_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/ipv4"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_DSCP_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/dscp"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_ECN_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/ecn"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_LENGTH_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/length"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_TTL_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/ttl"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_PROTOCOL_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/protocol"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_DESTINATION_IPV6_NETWORK_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/destination-ipv6-network"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_SOURCE_IPV6_NETWORK_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/source-ipv6-network"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_FLOW_LABEL_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH "/flow-label"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_IPV6_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/ipv6"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SEQUENCE_NUMBER_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/sequence-number"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_ACKNOWLEDGEMENT_NUMBER_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/acknowledgement-number"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DATA_OFFSET_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/data-offset"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_RESERVED_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/reserved"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_FLAGS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/flags"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_WINDOW_SIZE_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/window-size"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_URGENT_POINTER_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/urgent-pointer"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_OPTIONS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/options"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_LOWER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_YANG_PATH "/lower-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_UPPER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_YANG_PATH "/upper-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_OPERATOR_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_YANG_PATH "/operator"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_YANG_PATH "/port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_SOURCE_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/source-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_LOWER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_YANG_PATH "/lower-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_UPPER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_YANG_PATH "/upper-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_OPERATOR_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_YANG_PATH "/operator"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_YANG_PATH "/port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_DESTINATION_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH "/destination-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_TCP_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/tcp"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_LENGTH_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_YANG_PATH "/length"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_LOWER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_YANG_PATH "/lower-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_UPPER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_YANG_PATH "/upper-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_OPERATOR_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_YANG_PATH "/operator"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_YANG_PATH "/port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_SOURCE_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_YANG_PATH "/source-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_LOWER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_YANG_PATH "/lower-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_UPPER_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_YANG_PATH "/upper-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_OPERATOR_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_YANG_PATH "/operator"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_YANG_PATH "/port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_DESTINATION_PORT_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_YANG_PATH "/destination-port"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_UDP_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/udp"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ICMP_TYPE_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ICMP_YANG_PATH "/type"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ICMP_CODE_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ICMP_YANG_PATH "/code"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ICMP_REST_OF_HEADER_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ICMP_YANG_PATH "/rest-of-header"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_ICMP_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/icmp"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_EGRESS_INTERFACE_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/egress-interface"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_INGRESS_INTERFACE_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH "/ingress-interface"
#define ONM_TC_ACLS_ACL_ACES_ACE_MATCHES_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_YANG_PATH "/matches"
#define ONM_TC_ACLS_ACL_ACES_ACE_ACTIONS_FORWARDING_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_ACTIONS_YANG_PATH "/forwarding"
#define ONM_TC_ACLS_ACL_ACES_ACE_ACTIONS_LOGGING_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_ACTIONS_YANG_PATH "/logging"
#define ONM_TC_ACLS_ACL_ACES_ACE_ACTIONS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_YANG_PATH "/actions"
#define ONM_TC_ACLS_ACL_ACES_ACE_STATISTICS_MATCHED_PACKETS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_STATISTICS_YANG_PATH "/matched-packets"
#define ONM_TC_ACLS_ACL_ACES_ACE_STATISTICS_MATCHED_OCTETS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_STATISTICS_YANG_PATH "/matched-octets"
#define ONM_TC_ACLS_ACL_ACES_ACE_STATISTICS_YANG_PATH ONM_TC_ACLS_ACL_ACES_ACE_YANG_PATH "/statistics"
#define ONM_TC_ACLS_ACL_ACES_ACE_YANG_PATH ONM_TC_ACLS_ACL_ACES_YANG_PATH "/ace"
#define ONM_TC_ACLS_ACL_ACES_YANG_PATH ONM_TC_ACLS_ACL_YANG_PATH "/aces"
#define ONM_TC_ACLS_ACL_YANG_PATH ONM_TC_ACLS_YANG_PATH "/acl"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INTERFACE_ID_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_YANG_PATH "/interface-id"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_NAME_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_YANG_PATH "/name"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_NAME_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH "/name"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_MATCHED_PACKETS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH "/matched-packets"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_MATCHED_OCTETS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH "/matched-octets"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_YANG_PATH "/ace-statistics"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_ACL_SET_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_YANG_PATH "/acl-set"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_ACL_SETS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_YANG_PATH "/acl-sets"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_INGRESS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_YANG_PATH "/ingress"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_NAME_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_YANG_PATH "/name"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_NAME_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH "/name"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_MATCHED_PACKETS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH "/matched-packets"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_MATCHED_OCTETS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH "/matched-octets"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_ACE_STATISTICS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_YANG_PATH "/ace-statistics"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_ACL_SET_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_YANG_PATH "/acl-set"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_ACL_SETS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_YANG_PATH "/acl-sets"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_EGRESS_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_YANG_PATH "/egress"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_INTERFACE_YANG_PATH ONM_TC_ACLS_ATTACHMENT_POINTS_YANG_PATH "/interface"
#define ONM_TC_ACLS_ATTACHMENT_POINTS_YANG_PATH ONM_TC_ACLS_YANG_PATH "/attachment-points"
#define ONM_TC_ACLS_YANG_PATH "/ietf-access-control-list:acls"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#endif // ONM_TC_PLUGIN_COMMON_H