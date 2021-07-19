#ifndef TEE_OBJ_H
#define TEE_OBJ_H

#include <tee_api_types.h>


#define TEE_USAGE_DEFAULT   0xffffffff

struct tee_obj {
    void * po;
    size_t  po_len;
}; 

#endif
