#include "printf.h"
#include "utils.h"
#include "mini_uart.h"

void init_kernel()
{
	uart_init();
	init_printf(0, putc);
}

void el_print()
{
	int el = get_el();
	printf("Exception level: %d \r\n", el);
}

void kernel_main(void)
{
	el_print();

	while (1) {
		uart_send(uart_recv());
	}
}
