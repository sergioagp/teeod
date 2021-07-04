
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "platform.h"

// ----------------------------------------------------------------------------
int _close(int file) {
// ----------------------------------------------------------------------------

	return -1;
}

// ----------------------------------------------------------------------------
int _fstat(int file, struct stat *st) {
// ----------------------------------------------------------------------------

	st->st_mode = S_IFCHR;
	return 0;
}

// // ----------------------------------------------------------------------------
// void * _sbrk(int incr) {
// // ----------------------------------------------------------------------------

// 	extern char __end__[];
// 	extern char __HeapLimit[];
// 	static char *_heap_ptr = __end__;

// 	if ((_heap_ptr + incr < __end__) || (_heap_ptr + incr > __HeapLimit))
// 		return  (void *) -1;

// 	_heap_ptr += incr;
// 	return _heap_ptr - incr;
// }

// ----------------------------------------------------------------------------
int _isatty(int file) {
// ----------------------------------------------------------------------------

	return (file == STDIN_FILENO || file == STDOUT_FILENO || file == STDERR_FILENO) ? 1 : 0;

}

// ----------------------------------------------------------------------------
int _lseek(int file, off_t ptr, int dir) {
// ----------------------------------------------------------------------------

	return 0;
}

// ----------------------------------------------------------------------------
int _open(const char* name, int flags, int mode) {
// ----------------------------------------------------------------------------
    return 0;
}

// ----------------------------------------------------------------------------
int _read(int file, char *ptr, size_t len) {
// ----------------------------------------------------------------------------
	// if (isatty(file)) {

	// 	ssize_t count = 0;
	// 	int rxfifo = -1;

	// 	while( count<len && ((rxfifo = USART3_REG(USART_RDR)) >0) ){
	// 		*ptr++ = (char)rxfifo;
	// 		count++;
	// 	}

	// 	return count;
	// }
	// return -1;
}

// ----------------------------------------------------------------------------
size_t _write(int file, const void *ptr, size_t len) {
// ----------------------------------------------------------------------------

	if (isatty(file)) {

		const uint8_t * buff = (uint8_t *)ptr;

		for (size_t i = 0; i < len; i++) {
			while (UART_IsTransmitFull);
	        WriteReg(UART_TX_FIFO_ADDR, (char) buff[i]);
		}

		return len;
	}

	return -1;
}