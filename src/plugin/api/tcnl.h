#include <linux/rtnetlink.h>
#include "plugin/context.h"

#define TCA_BUF_MAX	(64*1024)
#define MAX_MSG 16384 // for tcmsg
#define NLMSG_TAIL(nmsg) \
	((struct rtattr *) (((void *) (nmsg)) + NLMSG_ALIGN((nmsg)->nlmsg_len)))

struct nl_request {
    struct nlmsghdr nlh;
    struct tcmsg tcm;
    char buf[TCA_BUF_MAX];
};

unsigned int djb2_hash(const char *str);
int tcnl_modify_ingress_qdisc_shared_block(onm_tc_nl_ctx_t* nl_ctx, int if_idx, uint32_t tca_block_id);
int tcnl_tc_block_exists(unsigned int block_index);