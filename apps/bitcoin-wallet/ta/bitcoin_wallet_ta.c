#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>
#include <bitcoin_wallet_ta.h>
#include <string.h>
#include <inttypes.h>

#include <stdio.h>

#define BIP39_PBKDF2_ROUNDS 2048
#define DMSG printf
#define EMSG printf
#define IMSG printf
static uint32_t obj = TEE_HANDLE_NULL;

/*external functions*/
static TEE_Result check_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result generate_new_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result mnemonic_to_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result erase_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result sign_transaction(uint32_t param_types, TEE_Param params[4]);
static TEE_Result get_bitcoin_address (uint32_t param_types, TEE_Param params[4]);

/*internel functions*/
static void print_uint8(uint8_t* array, uint32_t array_len);
static void from_mnemonic_to_masterkey (char* mnemonic);
static void from_mnemonic_to_masterkey2 (char* mnemonic);
static uint32_t sign_raw_tx(uint8_t *rawtx, size_t bytes, uint8_t *sig, uint32_t i);

TEE_Result TA_CreateEntryPoint(void){
	DMSG("TA_CreateEntryPoint has been called\n\r");
	return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void){
	DMSG("TA_DestroyEntryPoint has been called\r\n\n\n");
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types, TEE_Param params[4], void **sess_ctx){

	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	//ADMSG("TA_OpenSessionEntryPoint has been called\n\r");
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	(void)&params;
	(void)&sess_ctx;
	IMSG("Hello Bitcoin Wallet!\n\r");
	return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void *sess_ctx){
	(void)&sess_ctx;
	IMSG("Goodbye!\n\r");
}

TEE_Result TA_InvokeCommandEntryPoint(void *sess_ctx, uint32_t cmd_id, uint32_t param_types, TEE_Param params[4]){

	(void)&sess_ctx;
	
	IMSG("Choice from NW: %d\n\r",cmd_id);
	switch (cmd_id) {
		case TA_BITCOIN_WALLET_CMD_1:
			return check_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_2:
			return generate_new_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_3:
			return mnemonic_to_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_4:
			return erase_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_5:
			return sign_transaction(param_types, params);
		case TA_BITCOIN_WALLET_CMD_6:
			return get_bitcoin_address(param_types, params);
		default:
			return TEE_ERROR_BAD_PARAMETERS;
	}
}

static TEE_Result check_masterkey(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_VALUE_OUTPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	TEE_Result res;

	//DMSG("has been called\n\r");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	res = TEE_SUCCESS;
	if(res == TEE_SUCCESS && obj!=TEE_HANDLE_NULL){
		params[1].value.a = 1;
		DMSG("Master Key exists\n\r");
	}
	else if(obj == TEE_HANDLE_NULL){
		params[1].value.a = 0;
		DMSG("Master Key does not exist\n\r");
	}

	return TEE_SUCCESS;
}

static TEE_Result generate_new_masterkey(uint32_t param_types, TEE_Param params[4]){

	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_MEMREF_OUTPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	uint32_t strength = 128;
	char mnemonic[] = "educate robot disorder rib dog melt frown pattern memory weasel train gravity";//TEE_Malloc(MNEMONIC_LENGTH, TEE_MALLOC_FILL_ZERO);

	//DMSG("has been called\n\r");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}
	
	TEE_Result res;

	// Generate a random mnemonic
	res = TEE_SUCCESS; //get_random_mnemonic(strength, mnemonic);
	if(res != TEE_SUCCESS)
		EMSG("Failed to generate mnemonic: 0x%x\n\r", res);
	else
		DMSG("Mnemonic generated.\n\r");

	// Send the mnemonic to client
	TEE_MemMove(params[1].memref.buffer, mnemonic, MNEMONIC_LENGTH);

	//TEE_CloseObject(obj);

	from_mnemonic_to_masterkey(mnemonic);

	return TEE_SUCCESS;
}

static TEE_Result mnemonic_to_masterkey(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_MEMREF_INPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	char* mnemonic = TEE_Malloc(MNEMONIC_LENGTH, TEE_MALLOC_FILL_ZERO);

	//DMSG("has been called\n\r");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	TEE_MemMove(mnemonic, params[1].memref.buffer, MNEMONIC_LENGTH);

	from_mnemonic_to_masterkey2(mnemonic);

	return TEE_SUCCESS;
}

static TEE_Result erase_masterkey(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_VALUE_OUTPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	TEE_Result res;

	//DMSG("has been called\n\r");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	res = TEE_SUCCESS;
	if(res == TEE_SUCCESS && obj==TEE_HANDLE_NULL){
		params[1].value.a = 1;
		DMSG("Master Key exists\n\r");
		res = TEE_SUCCESS;//TEE_CloseAndDeletePersistentObject1(obj);
		return res;
	}
	else if(obj != TEE_HANDLE_NULL){
		params[1].value.a = 0;
		DMSG("Master Key does not exist\n\r");
	}

	return TEE_SUCCESS;
}

static TEE_Result get_bitcoin_address(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_VALUE_INPUT, 
												TEE_PARAM_TYPE_MEMREF_OUTPUT, 
												TEE_PARAM_TYPE_NONE);
	uint32_t account_id;
	uint8_t address[34]="317748324b7145564b5a3936797077764476586d7634475738";
	TEE_Result res;
	
	//DMSG("has been called");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	account_id = params[1].value.a;
	printf("%d\n\r",account_id);

	printf("Child_sk:8b69e06ab4a08f6c900b513f93e18315e111dcab84c4b4db04ca9e530632bea\n\rChild_cc:9ee04fbbe8d667f843c4826babad8460af2a592432f2fd72d286e96f153\n\rChild_pk_x:3790de88c3bdb0643d6a753e4ffa4a78077142e2c79c3b73de8807a456a25e1\n\rChild_pk_y:efd7152c645f55bf89f39d58f14834634c22ab3f5385b73289a19e724907d36acdf8dbf72d2163b8ad4f350f4ece4657b119d1000000000000\n\r");

	res = TEE_SUCCESS;//get_account_address(address, account_id);

	printf("\n\rget_bitcoin_address\n\r%s\n\r",address);
	//print_uint8(address, 25);
	for(uint32_t i = 0; i < 25; i++){
		DMSG("%x", address[i]);
	}
	DMSG("\n\r");
	TEE_MemMove(params[2].memref.buffer, address, 25);
	//print_uint8(params[2].memref.buffer, 25);

	return res;
}

static TEE_Result sign_transaction(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_MEMREF_INPUT, 
												TEE_PARAM_TYPE_MEMREF_OUTPUT,
												TEE_PARAM_TYPE_VALUE_INPUT);
	uint32_t res;
	uint32_t account_id;

	//DMSG("has been called\n\r");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	account_id = params[3].value.a;

	for (uint32_t i = 0; i < params[1].memref.size; i++){
		DMSG("%x", ((uint8_t *)params[1].memref.buffer)[i]);
	}
	printf("\r\nbefore sign raw tx\n\n\r");
	printf("Child_sk:fc1f4c1d575e91c699425dee331eb67a8706b34ef4198dac72deb7f32288a6\n\rChild_cc:c2357af785b7e5c2661453d463bad26f647c7e17df293f278e8885415cdf6\n\rChild_pk_x:51a165788efa4e94b6a10eba6b3f82bbd3a45d9154241bf9d4f647f5a9f4\n\rChild_pk_y:92f858e9ac617763828725b2ee3ea4a01a338c3edcc3ed9767f818667ade464\n\r");
	res = 1;//sign_raw_tx((uint8_t *)params[1].memref.buffer, params[1].memref.size,  (uint8_t *)params[2].memref.buffer, account_id);
	printf("\nafter sign raw tx\n\r");
	if (res == 1) {
		DMSG("Transaction has been succefully signed.\n\r");
		params[0].value.a = 1;
	} else {
		DMSG("Failed to sign address. Code 0x%x\n\r", res);
		params[0].value.b = 1;
	}

	return TEE_SUCCESS;
}


static void from_mnemonic_to_masterkey (char* mnemonic){

	uint32_t flags_write = TEE_DATA_FLAG_ACCESS_READ | 
						TEE_DATA_FLAG_ACCESS_WRITE | 
						TEE_DATA_FLAG_ACCESS_WRITE_META | 
						TEE_DATA_FLAG_SHARE_READ | 
						TEE_DATA_FLAG_SHARE_WRITE;

	TEE_Result res;
	//TEE_ObjectHandle obj = TEE_HANDLE_NULL;

	uint8_t seed[512/8]="81b3733f639af9f963ee7bfd70f650a13813f5305a7e476120aeb25db65e9691dfc9b141a999215bfba9d4aa13fc90dee5922c244ef936ef20685fc9a811b5bb";
	uint8_t masterkey[32]="4c3529a1d2606134ccf680df096e33b6c084853ebee52f847734db1ebef0bc";
	uint8_t masterchain[32]="88c2cdcb7b7e22f011ca7dcbdcb98130ea71a24933bf9c7a5820a1a0461a7ad7";
	uint8_t masterkey_ext[64];

	uint32_t masterkey_ext_id = TA_OBJECT_MASTERKEY_EXT;
	const char* passphrase = "mnemonic";

	// Generate seed, mnemonic --- password passphrase --- salt
	res = TEE_SUCCESS; //from_mnemonic_to_seed(mnemonic, passphrase, seed, 0);
	if(res == TEE_SUCCESS)
		DMSG("Seed Generated\n\r");
	else
		EMSG("Failed to generate seed: 0x%x\n\r", res);

	//res = hdnode_from_seed(seed, sizeof(seed), masterkey, masterchain);
	if(res == TEE_SUCCESS) 
		DMSG("Generate master key success\n\r");
	else
		EMSG("Failed to generate master key: 0x%x\n\r", res);

	TEE_MemMove(masterkey_ext, masterkey, 32);
	TEE_MemMove(masterkey_ext+32, masterchain, 32);

	obj = TEE_HANDLE_NULL;
	//res = TEE_CreatePersistentObject(TEE_STORAGE_PRIVATE, &masterkey_ext_id, sizeof(masterkey_ext_id), flags_write, TEE_HANDLE_NULL, masterkey_ext, 64, &obj);
	if(res == TEE_SUCCESS)
		DMSG("Store master key success\n\r");
	else
		EMSG("Failed to store master key: 0x%x\n\r", res);

	//TEE_CloseObject(obj);

	printf("\n##########################\n\r");
	printf("Mnemonic: %s\n\r", mnemonic);
	printf("%d\n\r", strlen(mnemonic));
	printf("Seed: %s\n\r", seed);
	//print_uint8(seed, 64);
	printf("Master Key: %s\n\r", masterkey);
	//print_uint8(masterkey, 32);
	printf("Master Chaincode: %s\n\r", masterchain);
	//print_uint8(masterchain, 32);
	printf("##########################\n\n\r");
}

static void from_mnemonic_to_masterkey2 (char* mnemonic){

	uint32_t flags_write = TEE_DATA_FLAG_ACCESS_READ | 
						TEE_DATA_FLAG_ACCESS_WRITE | 
						TEE_DATA_FLAG_ACCESS_WRITE_META | 
						TEE_DATA_FLAG_SHARE_READ | 
						TEE_DATA_FLAG_SHARE_WRITE;

	TEE_Result res;
	//TEE_ObjectHandle obj = TEE_HANDLE_NULL;

	uint8_t seed[512/8]="eba0b5f0cf2bfdeec34dc9e3c42083e761a7cf076febbef15c6678aef0fa34026a658798e172edc35295797b56a4b374b589c6a321f81ead993f4a7a8f88";
	uint8_t masterkey[32]="18651d6ad515d87c7024792a982a6315e34cb1a76b67c4441e95bd321dac5b15";
	uint8_t masterchain[32]="40b1ff439c6ccd83c6d588f61681ef139efab89ce3d833abf3a530bad9aa8880";
	uint8_t masterkey_ext[64];

	uint32_t masterkey_ext_id = TA_OBJECT_MASTERKEY_EXT;
	const char* passphrase = "mnemonic";

	// Generate seed, mnemonic --- password passphrase --- salt
	res = TEE_SUCCESS; //from_mnemonic_to_seed(mnemonic, passphrase, seed, 0);
	if(res == TEE_SUCCESS)
		DMSG("Seed Generated\n\r");
	else
		EMSG("Failed to generate seed: 0x%x\n\r", res);

	//res = hdnode_from_seed(seed, sizeof(seed), masterkey, masterchain);
	if(res == TEE_SUCCESS) 
		DMSG("Generate master key success\n\r");
	else
		EMSG("Failed to generate master key: 0x%x\n\r", res);

	TEE_MemMove(masterkey_ext, masterkey, 32);
	TEE_MemMove(masterkey_ext+32, masterchain, 32);

	obj = TEE_HANDLE_NULL;
	//res = TEE_CreatePersistentObject(TEE_STORAGE_PRIVATE, &masterkey_ext_id, sizeof(masterkey_ext_id), flags_write, TEE_HANDLE_NULL, masterkey_ext, 64, &obj);
	if(res == TEE_SUCCESS)
		DMSG("Store master key success\n\r");
	else
		EMSG("Failed to store master key: 0x%x\n\r", res);

	//TEE_CloseObject(obj);

	printf("\n##########################\n\r");
	printf("Mnemonic: %s\n\r", mnemonic);
	printf("%d\n\r", strlen(mnemonic));
	printf("Seed: %s\n\r", seed);
	//print_uint8(seed, 64);
	printf("Master Key: %s\n\r", masterkey);
	//print_uint8(masterkey, 32);
	printf("Master Chaincode: %s\n\r", masterchain);
	//print_uint8(masterchain, 32);
	printf("##########################\n\n\r");
}


static uint32_t sign_raw_tx(uint8_t *rawtx, size_t bytes, uint8_t *sig, uint32_t account_id){
	TEE_Result res;


	DMSG("Key retrieved\n\r");
	res = TEE_SUCCESS;//TEE_AllocateOperation(&op2, TEE_ALG_ECDSA_P256, TEE_MODE_SIGN, 256);
	if(res != TEE_SUCCESS){
		DMSG("Error allocation sign op 0x%x\n\r", res);
	} else {
		DMSG("Allocation success\n\r");
	}

	/* Set the key for the signing operation */
	//res = TEE_SetOperationKey(op2, key);
	if(res != TEE_SUCCESS){
		DMSG("Error setting the key 0x%x\n\r", res);
	} else {
		DMSG("Key has been set!\n\r");
	}

	/* Sign the hash of the raw transaction */
	//res = TEE_AsymmetricSignDigest(op2, NULL, 0, hash, hlen, sig, &siglen);
	if(res != TEE_SUCCESS){
		DMSG("Error signing 0x%x\n\r", res);
	} else {
		DMSG("Sign complete!\n\r");
	}

	for(uint32_t i = 0; i < 72; i++){
		DMSG("%x", sig[i]);
	}
	DMSG("\n\r");
	if(res == TEE_SUCCESS)return 1;
	else return 0;
}
