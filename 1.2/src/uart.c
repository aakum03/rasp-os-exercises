#include "utils.h"
#include "peripherals/uart.h"
#include "peripherals/gpio.h"

void uart_send ( char c )
{
	while(1) {
		if(!(get32(U_FLAG_REG)&(1<<5))) 
			break;
	}
	put32(U_DATA_REG,c);
}

char uart_recv ( void )
{
	while(1) {
		if(!(get32(U_FLAG_REG)&(1<<4))) 
			break;
	}
	return(get32(U_DATA_REG)&0xFF);
}

void uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_send((char)str[i]);
	}
}

void uart_init ( void )
{
	unsigned int selector;

	selector = get32(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 4<<12;                      // set alt1 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 4<<15;                      // set alt1 for gpio15
	put32(GPFSEL1,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	put32(GPPUDCLK0,0);

	put32(U_CTRL_REG, 0);					// Disable Control Register
	put32(U_IBRD_REG, BAUD_RATE_INT);		// Set Integer part of the Baud Rate
	put32(U_FBRD_REG, BAUD_RATE_FRAC);		// Set Fractional part of the Baud Rate
	// Set to-8 bit mode and enable FIFO using the Line Control Register
	// (UARTLCR_H set bits 5:6 and 4 respectively)
	put32(U_LCRH_REG, (7<<4));
	// Enable Transmit, Receive and UART (Set UARTCR bits 8, 9 and 0 respectively)			
	put32(U_CTRL_REG, (1<<0) | (3<<8));
}
