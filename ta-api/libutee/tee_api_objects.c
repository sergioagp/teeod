#include <tee_api.h>
#include <stdlib.h>
#include <string.h>

static struct tee_obj list_objs[32] __attribute__((section ("secure_strg"))) ={0}; //change this to a link list

static const struct crypto_ecc_keypair_ops ecc_keypair_ops = {
	.generate = &_ltc_ecc_generate_keypair,
	.sign = &_ltc_ecc_sign,
	.shared_secret = &_ltc_ecc_shared_secret,
};

static void * _alloc_secure_storage(size_t size)
{
	uint32_t* ptr_addr = 0x10000000;
	uint32_t curr_ptr = * ptr_addr;
	if(*ptr_addr + size > 0x10010000)
		return NULL;

	*ptr_addr += size
	return curr_ptr;
}


/* Data and Key Storage API  - Transient Object Functions */

TEE_Result TEE_OpenPersistentObject(uint32_t storageID, const void *objectID,
				    uint32_t objectIDLen, uint32_t flags,
				    TEE_ObjectHandle *object)
{
	TEE_Result res=TEE_SUCCESS;
	uint32_t obj;

	if (!objectID) {
		res = TEE_ERROR_ITEM_NOT_FOUND;
		goto exit;
	}

	if(!list_objs[objectID])
	{
		res = TEE_ERROR_ITEM_NOT_FOUND;
		goto exit;
	}

	obj = &list_objs[objectID];

	if (res == TEE_SUCCESS)
		*object = (TEE_ObjectHandle)(uintptr_t)obj;

exit:
	if (res != TEE_SUCCESS)
		*object = TEE_HANDLE_NULL;

	return res;
}


TEE_Result TEE_CreatePersistentObject(uint32_t storageID, const void *objectID,
				      uint32_t objectIDLen, uint32_t flags,
				      TEE_ObjectHandle attributes,
				      const void *initialData,
				      uint32_t initialDataLen,
				      TEE_ObjectHandle *object)
{
	TEE_Result res=TEE_SUCCESS;
	uint32_t obj;

	if (!objectID) {
		res = TEE_ERROR_ITEM_NOT_FOUND;
		goto exit;
	}

	if(list_objs[objectID])
	{
		res = TEE_ERROR_ACCESS_CONFLICT;
		goto exit;
	}

	list_objs[objectID].po = _alloc_secure_storage(initialDataLen);
	if(!list_objs[objectID].po)
	{
		res = TEE_ERROR_OUT_OF_MEMORY;
		goto exit;
	}

	TEE_MemMove(list_objs[objectID].po, initialData, initialDataLen);
	
	list_objs[objectID].po_len= initialDataLen;
	
	obj = &list_objs[objectID];

	if (res == TEE_SUCCESS)
		*object = (TEE_ObjectHandle)(uintptr_t)obj;

exit:
	if (res != TEE_SUCCESS)
		*object = TEE_HANDLE_NULL;

	return res;
}

/* Data and Key Storage API  - Data Stream Access Functions */

TEE_Result TEE_ReadObjectData(TEE_ObjectHandle object, void *buffer,
			      uint32_t size, uint32_t *count)
{
	TEE_Result res=TEE_SUCCESS;
	uint32_t obj;

	if (!object) {
		res = TEE_ERROR_ITEM_NOT_FOUND;
		return res;
	}

	*count =(size<=list_objs[objectID].po_len)?size: list_objs[objectID].po_len;

	TEE_MemMove(buffer, list_objs[objectID].po, *count);

	return res;
}


TEE_Result TEE_AllocateTransientObject(TEE_ObjectType objectType,
				       uint32_t maxKeySize,
				       TEE_ObjectHandle *object)
{

	/* If we have a key structure, pre-allocate the bignums inside */
	switch (obj_type) {
	case TEE_TYPE_ECDSA_KEYPAIR:
		res = crypto_acipher_alloc_ecc_keypair(o->attr, obj_type,
						       max_key_size);
		o->attr->ops = &ecc_keypair_ops;
		break;
	default:
		if (obj_type != TEE_TYPE_DATA) {
			struct tee_cryp_obj_secret *key = o->attr;

			key->alloc_size = type_props->alloc_size -
					  sizeof(*key);
		}
		break;
	}

	return TEE_SUCCESS;
}

void TEE_CloseObject(TEE_ObjectHandle object)
{

}


void TEE_InitRefAttribute(TEE_Attribute *attr, uint32_t attributeID,
			  const void *buffer, uint32_t length)
{
	attr->attributeID = attributeID;
	attr->content.ref.buffer = (void *)buffer;
	attr->content.ref.length = length;
}

void TEE_InitValueAttribute(TEE_Attribute *attr, uint32_t attributeID,
			    uint32_t a, uint32_t b)
{
	attr->attributeID = attributeID;
	attr->content.value.a = a;
	attr->content.value.b = b;
}