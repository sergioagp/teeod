#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <tee_client_api.h>
#include "tx.h"

/***************************************************************************//**
* Transaction & Serialisation Structs Definitions
*******************************************************************************/

struct intx_t {
	uint8_t *prvhash;
	uint8_t *prvindexl;
	uint8_t scrlen;
	uint8_t *scrsig;
	uint8_t *sequence;
};

struct outtx_t {
	uint8_t *value;
	uint8_t scrlen;
	uint8_t *scrpubkey;
};

struct tx_t {
	uint8_t *version;
	uint8_t incount;
	INTX inputtx;
	uint8_t outcount;
	OUTTX outputtx;
	uint8_t *lock;
};

struct serbuf_t {
    void *data;
    uint32_t next;
    size_t size;
};


/***************************************************************************//**
* Constructor methods: we don't want direct access to a struct's members.
* Opaque handles are used and access/init is gained through the appropriate
* methods. Typedefs are in the tx.h file.
*******************************************************************************/

/**
 * Initializes a new transaction input (INTX).
 *
 * @param prh
 * @param tmpscr
 */
INTX new_intx(const uint8_t *prh, const uint8_t *tmpscr)
{
	INTX intx = malloc(sizeof(struct intx_t));

	/* At the moment transactions with one input/output are supported */
	const uint8_t index[] = {0x01, 0x00, 0x00, 0x00};
	const uint8_t seq[] = {0xff, 0xff, 0xff, 0xff};

	if(intx == NULL)
		return NULL;

	intx->prvhash = malloc(32); /* 32 bytes length of previous tx hash */
	intx->prvindexl = malloc(4); /* 4 bytes index */
	intx->scrsig = malloc(25); /* initially the previous pubscript is used */
	intx->sequence = malloc(4);

	intx->scrlen = 0x19; /* initially the script length is 25 */
	memcpy(intx->prvhash, prh, 32);
	memcpy(intx->prvindexl, index, 4);
	memcpy(intx->scrsig, tmpscr, 25);
	memcpy(intx->sequence, seq, 4);

	return intx;
}


/**
 * Initializes a new transaction output (OUTTX).
 *
 * @param val The bitcoin value we want to redeem
 * @param tmpscr
 */
OUTTX new_outtx(const uint8_t *val, const uint8_t *tmpscr)
{
	OUTTX outtx = malloc(sizeof(struct outtx_t));
	if (outtx == NULL)
		return NULL;

	outtx->value = malloc(8);
	outtx->scrpubkey = malloc(25);

	outtx->scrlen = 0x19;
	memcpy(outtx->value, val, 8);
	memcpy(outtx->scrpubkey, tmpscr, 25);

	return outtx;
}


/**
 * Initializes a complete transaction (TX).
 *
 * @param intx The Input transaction
 * @param outtx The Output trsansaction
 */
TX new_tx(INTX intx, OUTTX outtx)
{
	TX tx = malloc(sizeof(struct tx_t));
	const uint8_t ver[] = {0x01, 0x00, 0x00, 0x00};
	const uint8_t lk[] = {0x00, 0x00, 0x00, 0x00};

	if (tx == NULL)
		return NULL;

	tx->version = malloc(4);
	tx->lock = malloc(4);

	memcpy(tx->version, ver, 4);
	tx->incount = 0x01;
	tx->inputtx = intx;
	tx->outcount = 0x01;
	tx->outputtx = outtx;
	memcpy(tx->lock, lk, 4);

	return tx;
}


/**
 * Initializes a new transaction buffer (TXBUF). Used to stored the serialized
 * byte data of a transaction struct. Its mainly used to store to byte string of
 * a transaction and passing it to the Secure World for hashing and signing.
 */
TXBUF new_txbuf(void)
{
    TXBUF buf = malloc(sizeof(struct serbuf_t));
	if (buf == NULL)
		return NULL;

    buf->data = malloc(TXBUF_INIT_SIZE);
    buf->size = TXBUF_INIT_SIZE;
    buf->next = 0;

    return buf;
}


/***************************************************************************//**
* Destroyer functions: Deallocate resources after we finish with the transaction.
*******************************************************************************/

/**
 * Frees an Input transaction (INTX)
 *
 * @param itx An initialized INTX Opaque handle.
 */
void free_intx(INTX itx)
{
	if (itx != NULL) {
		free(itx->prvhash);
		free(itx->prvindexl);
		free(itx->scrsig);
		free(itx->sequence);
		free(itx);
	}
}


/**
 * Frees an Output transaction (OUTTX)
 *
 * @param otx An initialized OUTTX Opaque handle.
 */
void free_outtx(OUTTX otx)
{
	if (otx != NULL) {
		free(otx->value);
		free(otx->scrpubkey);
		free(otx);
	}
}


/**
 * Frees an Transaction (TX)
 *
 * @param otx An initialized TX Opaque handle.
 */
void free_tx(TX tx)
{
	if (tx != NULL) {
		free_intx(tx->inputtx);
		free_outtx(tx->outputtx);
		free(tx->version);
		free(tx->lock);
		free(tx);
	}
}


void free_txbuf(TXBUF buf)
{
	if (buf != NULL) {
		free(buf->data);
		free(buf);
	}
}

/***************************************************************************//**
* Serialisation functions: Used for seralising the transaction structures
* before propagating them to the Secure World for signing.
*******************************************************************************/

void reserve_space(TXBUF b, size_t bytes) {
    if((b->next + bytes) > b->size) {
        /* double size to enforce O(lg N) reallocs */
        b->data = realloc(b->data, b->size * 2);
        b->size *= 2;
    }
}


void serialize_bytestr(uint8_t *x, size_t len, TXBUF b) {
    /* assume int == long; how can this be done better? */

    reserve_space(b, len);

    memcpy(((uint8_t *)b->data) + b->next, x, len);
    b->next += len;
}

void serialize_intx(INTX intx, TXBUF out)
{
	serialize_bytestr(intx->prvhash, 32, out);
	serialize_bytestr(intx->prvindexl, 4, out);
	serialize_bytestr(&intx->scrlen, 1, out);
	serialize_bytestr(intx->scrsig, 25, out);
	serialize_bytestr(intx->sequence, 4, out);
}

void serialize_outtx(OUTTX outtx, TXBUF out)
{
	serialize_bytestr(outtx->value, 8, out);
	serialize_bytestr(&outtx->scrlen, 1, out);
	serialize_bytestr(outtx->scrpubkey, 25, out);
}

void serialize_tx(TX tx, TXBUF out)
{
	serialize_bytestr(tx->version, 4, out);
	serialize_bytestr(&tx->incount, 1, out);
	serialize_intx(tx->inputtx, out);
	serialize_bytestr(&tx->outcount, 1, out);
	serialize_outtx(tx->outputtx, out);
	serialize_bytestr(tx->lock, 4, out);
}


void print_ser_bytes(TXBUF buf)
{
	for (size_t i = 0; i < buf->next; i++) {
		printf("%02x", ((uint8_t *)buf->data)[i]);
	}
	putchar('\n');
}

void *get_txbuf_data(TXBUF buf)
{
	return buf->data;
}

size_t get_txbuf_size(TXBUF buf)
{
	return buf->size;
}

uint32_t get_txbuf_next(TXBUF buf)
{
	return buf->next;
}


/***************************************************************************//**
* Debugging functions: Mainly used for printing and debugging transactions.
*******************************************************************************/
void print_intx(INTX intx)
{
	if (intx == NULL)
		return;

	for (uint32_t i = 1; i <= 5; i++) {

		switch(i) {
		case 1:
			for (uint32_t j = 0; j < 32; j++) { printf("%x ", intx->prvhash[j]); }
			putchar('\n');
			break;
		case 2:
			for (uint32_t j = 0; j < 4; j++) { printf("%x ", intx->prvindexl[j]); }
			putchar('\n');
			break;
		case 3:
			printf("%x ", intx->scrlen);
			putchar('\n');
			break;
		case 4:
			for (uint32_t j = 0; j < 25; j++) { printf("%x ", intx->scrsig[j]); }
			putchar('\n');
			break;
		case 5:
			for (uint32_t j = 0; j < 4; j++) { printf("%x ", intx->sequence[j]); }
			putchar('\n');
			break;
		}
	}
}


void print_outtx(OUTTX outtx)
{
	if (outtx == NULL)
		return;

	for (uint32_t i = 1; i <= 3; i++) {
		switch(i) {
		case 1:
			for (uint32_t j = 0; j < 8; j++) { printf("%x ", outtx->value[j]); }
			putchar('\n');
			break;
		case 2:
			printf("%x ", outtx->scrlen);
			putchar('\n');
			break;
		case 3:
			for (uint32_t j = 0; j < 25; j++) { printf("%x ", outtx->scrpubkey[j]); }
			putchar('\n');
			break;
		}
	}
}

void print_tx(TX tx)
{
	if (tx == NULL)
		return;

	for (uint32_t i = 1; i <= 6; i++) {
		switch(i) {
		case 1:
			for (uint32_t j = 0; j < 4; j++) { printf("%x ", tx->version[j]);}
			putchar('\n');
			break;
		case 2:
			printf("%x\n", tx->incount);
			break;
		case 3:
			print_intx(tx->inputtx);
			break;
		case 4:
			printf("%x\n", tx->outcount);
			break;
		case 5:
			print_outtx(tx->outputtx);
			break;
		case 6:
			for (uint32_t j = 0; j < 4; j++) {printf("%x ", tx->lock[i]);}
			putchar('\n');
			break;
		}
	}
}

void print_mem(void const *vp, size_t n)
{
    const uint8_t *p = vp;
    for (size_t i=0; i<n; i++)
        printf("%02x\n", p[i]);
    putchar('\n');
};

/*uint32_t create_unsigned_tx(INTX intx)
{
	intx = new_intx();
	return 1;
}*/
