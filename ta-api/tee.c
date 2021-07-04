#include "tee_internal_api.h"
#include "tee_isr.h"

#include <stdio.h>

void _ta_create(void)
{
	//printf("#  ISR called\r\n");
	TA_CreateEntryPoint();
}

void _open_session(void)
{
	//printf("\r\n#  open	 called\r\n");
	uint32_t param_types = RD_DATA(TEE_PARAMTYPE_ARGS);
	TEE_Param *params=(TEE_Param *) TEE_PARAM0_0_ARGS;
	
	void **sess_ctx;
	
	TA_OpenSessionEntryPoint(param_types,params,sess_ctx);
}

void _close_session(void)
{
	//printf("\r\n#  close called\r\n");
	void **sess_ctx;
    TA_CloseSessionEntryPoint(sess_ctx);
	TA_DestroyEntryPoint();
}


void _invoke_command(void)
{
	//printf("\r\n#  invoke called\r\n");
	uint32_t param_types = RD_DATA(TEE_PARAMTYPE_ARGS);
	TEE_Param *params=(TEE_Param *) TEE_PARAM0_0_ARGS;
	uint32_t cmd_id = RD_DATA(TEE_CMDID_ARGS);
	void **sess_ctx;
    TA_InvokeCommandEntryPoint(sess_ctx, cmd_id, param_types, params);
}
