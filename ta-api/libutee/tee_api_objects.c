#include <tee_api.h>
#include <stdlib.h>
#include <string.h>



/* Data and Key Storage API  - Transient Object Functions */

TEE_Result TEE_AllocateTransientObject(TEE_ObjectType objectType,
				       uint32_t maxKeySize,
				       TEE_ObjectHandle *object)
{
	return TEE_SUCCESS;
}

void TEE_CloseObject(TEE_ObjectHandle object)
{

}
