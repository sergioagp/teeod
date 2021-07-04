#ifndef PERIPH_H
#define PERIPH_H


#define UART_BASE                   0x40100000

#define UART_RX_FIFO_OFFSET		    0	/* receive FIFO, read only */
#define UART_TX_FIFO_OFFSET		    4	/* transmit FIFO, write only */
#define UART_STATUS_REG_OFFSET		8	/* status register, read only */
#define UART_CONTROL_REG_OFFSET		12	/* control reg, write only */

#define UART_RX_FIFO_ADDR		    (UART_BASE+UART_RX_FIFO_OFFSET)     	/* receive FIFO, read only */
#define UART_TX_FIFO_ADDR		    (UART_BASE+UART_TX_FIFO_OFFSET)     	/* transmit FIFO, write only */
#define UART_STATUS_REG_ADDR		(UART_BASE+UART_STATUS_REG_OFFSET)      /* status register, read only */
#define UART_CONTROL_REG_ADDR		(UART_BASE+UART_CONTROL_REG_OFFSET)     /* control reg, write only */


/* Control Register bit positions */

#define UART_CR_ENABLE_INTR		    0x10	/* enable interrupt */
#define UART_CR_FIFO_RX_RESET		0x02	/* reset receive FIFO */
#define UART_CR_FIFO_TX_RESET		0x01	/* reset transmit FIFO */

/* Status Register bit positions */

#define UART_SR_PARITY_ERROR		0x80
#define UART_SR_FRAMING_ERROR		0x40
#define UART_SR_OVERRUN_ERROR		0x20
#define UART_SR_INTR_ENABLED		0x10	/* interrupt enabled */
#define UART_SR_TX_FIFO_FULL		0x08	/* transmit FIFO full */
#define UART_SR_TX_FIFO_EMPTY		0x04	/* transmit FIFO empty */
#define UART_SR_RX_FIFO_FULL		0x02	/* receive FIFO full */
#define UART_SR_RX_FIFO_VALID_DATA	0x01	/* data in receive FIFO */


#define WriteReg(BaseAddress, Data) \
	*((uint32_t *) BaseAddress) = (uint32_t) (Data)

#define ReadReg(BaseAddress, RegOffset) \
	*((uint32_t *) (BaseAddress + RegOffset))

#define UART_GetStatusReg \
		ReadReg(UART_BASE, UART_STATUS_REG_OFFSET)

#define UART_IsTransmitFull \
	((UART_GetStatusReg & UART_SR_TX_FIFO_FULL) == \
	  UART_SR_TX_FIFO_FULL)

void Uart_SendByte(uint8_t Data);
void print_uart(char *str);

#endif /*PERIPH_H*/