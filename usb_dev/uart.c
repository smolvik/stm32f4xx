#include "stm32f407xx.h"

#define BUF_SIZE 1024
#define DIV_MANT 22
#define DIV_FRACT 13

char tx_buf[BUF_SIZE];
int  tx_idx = 0;
int  tx_wr_idx = 0;

char rx_buf[BUF_SIZE];
int  rx_idx = 0;
int  rx_rd_idx = 0;

void USART2_Handler_RAM(void)
{
	if(USART2->SR & USART_SR_TXE)
	{
		if(tx_idx == tx_wr_idx)
		{
			// no data for transfer - interrupt disable
			USART2->CR1 &= ~USART_CR1_TXEIE; 
		}
		else
		{
			// transfer next byte from the buffer
			USART2->DR = tx_buf[tx_idx];
			tx_idx = (tx_idx+1)&(BUF_SIZE-1);	
		}
	}
	
	if(USART2->SR & USART_SR_RXNE)
	{
		rx_buf[rx_idx] = USART2->DR;
		rx_idx = (rx_idx+1)&(BUF_SIZE-1);	
	}
}

void uart_config()
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;	// enable clock at USART2
	// enable UART2 and Rx and Tx
	USART2->CR1 |= USART_CR1_UE + USART_CR1_RE + USART_CR1_TE + USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);
	/* set boderate
	 * USARTDIV = 40e6/9600/16 = 260.42
	 * FRACT = 7
	 * MANT = 260
	 */
	 USART2->BRR = 0x1047;

}

void uart_putch(unsigned char b)
{
	tx_buf[tx_wr_idx] = b;
	tx_wr_idx = (tx_wr_idx+1)&(BUF_SIZE-1);
	
	USART2->CR1 |= USART_CR1_TXEIE;  // Transmit data register empty interrupt enable	
}

int uart_send(char *pb, int nb)
{
	int i;
	
	for( i = 0; i < nb; i++ ){
		tx_buf[tx_wr_idx] = pb[i];
		tx_wr_idx = (tx_wr_idx+1)&(BUF_SIZE-1);
		if(tx_wr_idx == tx_idx) {
			i++;
			break;
		}
	}	
	
	USART2->CR1 |= USART_CR1_TXEIE;  // Transmit data register empty interrupt enable
	return i;	
}

int uart_send_str(char *pb)
{
	int i;
	int sz = BUF_SIZE;
	
	sz -= (tx_wr_idx - tx_idx)&(BUF_SIZE-1);
	
	for( i = 0; i < sz; i++ ){
		if(pb[i] == 0){
			i++;
			break;
		}
		tx_buf[tx_wr_idx] = pb[i];
		tx_wr_idx = (tx_wr_idx+1)&(BUF_SIZE-1);
	}	
	
	USART2->CR1 |= USART_CR1_TXEIE;  // Transmit data register empty interrupt enable
	return i;	
}

int uart_read(char *pb, int nb)
{
	int i;
	
	if(rx_rd_idx == rx_idx) return 0;
	
	for( i = 0; i < nb; i++ ){
		pb[i] = rx_buf[rx_rd_idx];
		rx_rd_idx = (rx_rd_idx+1)&(BUF_SIZE-1);
		if(rx_rd_idx == rx_idx) {
			i++;
			break;
		}
	}	
	return i;
}
