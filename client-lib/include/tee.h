#ifndef __TEE_H
#define __TEE_H

#include <stdint.h>
#include <tee_defines.h>
/*
 * Defines the number of available memory references in an open session or
 * invoke command operation payload.
 */
#define TEEC_CONFIG_PAYLOAD_REF_COUNT 4

#define trigger_command(X) WR_DATA(TEE_OP_ARGS, X);

struct tee_param {
	uint32_t	a;
	uint32_t	b;
};

struct tee_open_session_arg {
	uint32_t session_id;
	uint32_t paramTypes;
	struct tee_param params[TEEC_CONFIG_PAYLOAD_REF_COUNT];
};

struct tee_invoke_arg {
	uint32_t session_id;
	uint32_t paramTypes;
	struct tee_param params[TEEC_CONFIG_PAYLOAD_REF_COUNT];
	uint32_t cmd_id;
};

/**
 * struct tee_ioctl_close_session_arg - Closes an open session
 * @session:	[in] Session id
 */
struct tee_close_session_arg {
	uint32_t session_id;
};

#endif /*__TEE_H*/
