#include "plugin/types.h"

onm_tc_ace_element_t* onm_tc_ace_element_new(void);
onm_tc_ace_element_t* onm_tc_ace_hash_element_new(void);
void onm_tc_ace_free (onm_tc_ace_element_t** ace);
int onm_tc_ace_hash_element_set_ace_name(onm_tc_ace_element_t** el, const char* name);
int onm_tc_ace_hash_element_set_match_src_mac_addr(onm_tc_ace_element_t** el, const char* src_mac_addr);
int onm_tc_ace_hash_element_set_match_src_mac_addr_mask(onm_tc_ace_element_t** el, const char* src_mac_mask);
int onm_tc_ace_hash_element_set_match_dst_mac_addr(onm_tc_ace_element_t** el, const char* dst_mac_addr);
int onm_tc_ace_hash_element_set_match_dst_mac_addr_mask(onm_tc_ace_element_t** el, const char* dst_mac_mask);
int onm_tc_ace_hash_element_set_match_eth_ethertype(onm_tc_ace_element_t** el, uint16_t ethertype);
int onm_tc_ace_hash_element_set_match_ipv4_src_network(onm_tc_ace_element_t** el, const char* ipv4_src_addr);
int onm_tc_ace_hash_element_set_match_ipv4_dst_network(onm_tc_ace_element_t** el, const char* ipv4_dst_addr);
int onm_tc_ace_hash_element_set_match_ipv6_src_network(onm_tc_ace_element_t** el, const char* ipv6_src_addr);
int onm_tc_ace_hash_element_set_match_ipv6_dst_network(onm_tc_ace_element_t** el, const char* ipv6_dst_addr);

int onm_tc_ace_hash_element_set_match_tcp_src_port(onm_tc_ace_element_t** el, const uint16_t tcp_src_port);
int onm_tc_ace_hash_element_set_match_tcp_dst_port(onm_tc_ace_element_t** el, const uint16_t tcp_dst_port);
int onm_tc_ace_hash_element_set_match_tcp_src_range(onm_tc_ace_element_t** el, uint16_t lower_port, uint16_t upper_port);
int onm_tc_ace_hash_element_set_match_tcp_dst_range(onm_tc_ace_element_t** el, uint16_t lower_port, uint16_t upper_port);

int onm_tc_ace_hash_element_set_match_udp_src_port(onm_tc_ace_element_t** el, const uint16_t udp_src_port);
int onm_tc_ace_hash_element_set_match_udp_dst_port(onm_tc_ace_element_t** el, const uint16_t udp_dst_port);
int onm_tc_ace_hash_element_set_match_udp_src_range(onm_tc_ace_element_t** el, uint16_t lower_port, uint16_t upper_port);
int onm_tc_ace_hash_element_set_match_udp_dst_range(onm_tc_ace_element_t** el, uint16_t lower_port, uint16_t upper_port);

int onm_tc_ace_hash_element_set_match_icmp_code(onm_tc_ace_element_t** el, const uint8_t icmp_code);
int onm_tc_ace_hash_element_set_action_forwarding(onm_tc_ace_element_t** el, const char* action);
int onm_tc_ace_hash_element_set_action_logging(onm_tc_ace_element_t** el, const char* action);