#ifndef ONM_TC_PLUGIN_STARTUP_STORE_H
#define ONM_TC_PLUGIN_STARTUP_STORE_H

#include "plugin/context.h"

int onm_tc_store(onm_tc_ctx_t *ctx, sr_session_ctx_t *session, bool store_acls, bool store_aps, bool run_api);
#endif // ONM_TC_PLUGIN_STARTUP_STORE_H