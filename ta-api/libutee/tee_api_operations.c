#include <tee_api.h>
#include <stdlib.h>
#include <string.h>

/* Cryptographic Operations API - Random Number Generation Functions */

void TEE_GenerateRandom(void *randomBuffer, uint32_t randomBufferLen)
{
	memset(randomBuffer,0xDE, randomBufferLen);
}


/* Cryptographic Operations API - Generic Operation Functions */

TEE_Result TEE_AllocateOperation(TEE_OperationHandle *operation,
				 uint32_t algorithm, uint32_t mode,
				 uint32_t maxKeySize)
{

    return TEE_SUCCESS;
}

TEE_Result TEE_SetOperationKey(TEE_OperationHandle operation,
			       TEE_ObjectHandle key)
{

    return TEE_SUCCESS;
}


void TEE_FreeOperation(TEE_OperationHandle operation)
{

}
