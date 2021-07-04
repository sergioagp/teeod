// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2014, STMicroelectronics International N.V.
 */
#include <stdlib.h>
#include <string.h>
#include <tee_api.h>


void *TEE_Malloc(uint32_t len, uint32_t hint)
{
	if (hint == TEE_MALLOC_FILL_ZERO)
		return calloc(1, len);
	else if (hint == TEE_USER_MEM_HINT_NO_FILL_ZERO)
		return malloc(len);

	//EMSG("Invalid hint %#" PRIx32, hint);

	return NULL;
}

void *TEE_Realloc(void *buffer, uint32_t newSize)
{
	return realloc(buffer, newSize);
}

void TEE_Free(void *buffer)
{
	free(buffer);
}

void *TEE_MemMove(void *dest, const void *src, uint32_t size)
{
	return memmove(dest, src, size);
}