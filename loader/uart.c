#include "uart.h"
#include "t124.h"
#include "util.h"
#include "clock.h"
/* UART A, B, C, D and E. */
static const u16 _uart_base_offsets[5] = { 0, 0x40, 0x200, 0x300, 0x400 };

void uart_wait_xfer(u32 idx, u32 which)
{
	uart_t *uart = (uart_t *)(UART_BASE + (u32)_uart_base_offsets[idx]);
	if (UART_TX_IDLE & which)
	{
		while (!(uart->UART_LSR & UART_LSR_TMTY))
			;
	}
	if (UART_RX_RDYR & which)
	{
		while (uart->UART_LSR & UART_LSR_RDR)
			(void)uart->UART_THR_DLAB;
	}
}

void uart_send(u32 idx, const u8 *buf, u32 len)
{
	uart_t *uart = (uart_t *)(UART_BASE + (u32)_uart_base_offsets[idx]);

	for (u32 i = 0; i != len; i++)
	{
		while (!(uart->UART_LSR & UART_LSR_THRE))
			;
		uart->UART_THR_DLAB = buf[i];
	}
}
void uart_invert(u32 idx, u32 enable, u32 invert_mask)
{
	uart_t *uart = (uart_t *)(UART_BASE + (u32)_uart_base_offsets[idx]);

	if (enable)
		uart->UART_IRDA_CSR |= invert_mask;
	else
		uart->UART_IRDA_CSR &= ~invert_mask;
	(void)uart->UART_SPR;
}
void uart_init(u32 idx, u32 baud, u32 mode)
{
	uart_t *uart = (uart_t *)(UART_BASE + (u32)_uart_base_offsets[idx]);

	// Make sure no data is being sent.
	if (!(mode & (UART_MCR_CTS_EN | UART_MCR_DTR)))
		uart_wait_xfer(idx, UART_TX_IDLE);

	// Set clock. bool type
	u32 clk_type = clock_uart_use_src_div(idx, baud);

	// 2 STOP bits for rates > 1M. (Reduced efficiency but less errors on high baudrates).
	u32 uart_lcr_stop = baud > 1000000 ? UART_LCR_STOP : 0;

	// Misc settings.
	u32 div = clk_type ? ((8 * baud + 408000000) / (16 * baud)) : 1; // DIV_ROUND_CLOSEST.
	uart->UART_IER_DLAB = 0; // Disable interrupts.
	uart->UART_LCR      = UART_LCR_DLAB | UART_LCR_WORD_LENGTH_8; // Enable DLAB & set 8n1 mode.
	uart->UART_THR_DLAB = (u8)div;        // Divisor latch LSB.
	uart->UART_IER_DLAB = (u8)(div >> 8); // Divisor latch MSB.

	// Disable DLAB and set STOP bits setting if applicable.
	uart->UART_LCR = uart_lcr_stop | UART_LCR_WORD_LENGTH_8;
	(void)uart->UART_SPR;

	// Enable fifo.
	uart->UART_IIR_FCR = UART_IIR_FCR_EN_FIFO;
	(void)uart->UART_SPR;
	sleep(20);

	// Disable hardware flow control.
	uart->UART_MCR = 0;
	sleep(96);

	// Clear tx/rx fifos.
	uart->UART_IIR_FCR = UART_IIR_FCR_EN_FIFO | UART_IIR_FCR_TX_CLR | UART_IIR_FCR_RX_CLR;

	// Set hardware flow control.
	uart->UART_MCR = mode;

	// Wait 3 symbols for baudrate change.
	sleep(3 * ((baud + 999999) / baud));
	uart_wait_xfer(idx, UART_TX_IDLE | UART_RX_RDYR);
}