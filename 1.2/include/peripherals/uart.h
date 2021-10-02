#ifndef	_P_UART_H
#define	_P_UART_H

#include "peripherals/base.h"

#define UART_BASE (PBASE+0x00201000)

#define U_DATA_REG (UART_BASE+0x00)
#define U_FLAG_REG (UART_BASE+0x18)
#define U_IBRD_REG (UART_BASE+0x24)
#define U_FBRD_REG (UART_BASE+0x28)
#define U_LCRH_REG (UART_BASE+0x2C)
#define U_CTRL_REG (UART_BASE+0x30)

#define U_ART_CLK 48000000
#define BAUD_RATE 115200
#define BAUD_RATE_DIV (((double) U_ART_CLK)/(16*BAUD_RATE))
#define BAUD_RATE_INT (unsigned int) (BAUD_RATE_DIV)
#define BAUD_RATE_FRAC (unsigned int) ((BAUD_RATE_DIV-BAUD_RATE_INT)*64 + 0.5)

#endif  /*_P_UART_H */