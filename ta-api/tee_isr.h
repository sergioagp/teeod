#ifndef TEE_ISR_H
#define TEE_ISR_H

#define TEE_IRQn           0


#define TEE_INT_Msk       (1UL << ((TEE_IRQn) & 0x1FUL))

#define WR_DATA(ADDRESS, DATA)  *(uint32_t *) ADDRESS = DATA
#define RD_DATA(ADDRESS)        *(uint32_t *) ADDRESS

#define TEE_ARGS_BASE           0xA0020000
#define TEE_OP_ARGS            (TEE_ARGS_BASE+0x00)
#define TEE_SESSIONID_ARGS     (TEE_ARGS_BASE+0x04)
#define TEE_PARAMTYPE_ARGS     (TEE_ARGS_BASE+0x08)
#define TEE_PARAM0_0_ARGS      (TEE_ARGS_BASE+0x0C)
#define TEE_PARAM0_1_ARGS      (TEE_ARGS_BASE+0x10)
#define TEE_PARAM1_0_ARGS      (TEE_ARGS_BASE+0x14)
#define TEE_PARAM1_1_ARGS      (TEE_ARGS_BASE+0x18)
#define TEE_PARAM2_0_ARGS      (TEE_ARGS_BASE+0x1C)
#define TEE_PARAM2_1_ARGS      (TEE_ARGS_BASE+0x20)
#define TEE_PARAM3_0_ARGS      (TEE_ARGS_BASE+0x24)
#define TEE_PARAM3_1_ARGS      (TEE_ARGS_BASE+0x28)
#define TEE_CMDID_ARGS         (TEE_ARGS_BASE+0x2C)

#define TEE_RETURN_ARGS        (TEE_ARGS_BASE+0x00)
#endif /* TEE_ISR_H */