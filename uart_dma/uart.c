#include "stm32f4xx.h"

#define BUF_SIZE 32
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
	//USART2->CR1 |= USART_CR1_UE + USART_CR1_RE + USART_CR1_TE + USART_CR1_RXNEIE;
	USART2->CR1 |= USART_CR1_UE + USART_CR1_RE + USART_CR1_TE;
	// enable dma 
	USART2->CR3 |= USART_CR3_DMAR + USART_CR3_DMAT;
	NVIC_EnableIRQ(USART2_IRQn);
	/* set boderate
	 * USARTDIV = 40e6/9600/16 = 260.42
	 * FRACT = 7
	 * MANT = 260
	 */
	 USART2->BRR = 0x1047;
	 	 	 
	 // dma1config  for uart
	 // stream5 - RX
	 // stream6 - TX
	 RCC->AHB1ENR |= 1<<21;		// DMA1 clock enable
	 
	 // disable streams for config ability
	 DMA1_Stream5->CR &= ~DMA_SxCR_EN;
	 while(DMA1_Stream5->CR & DMA_SxCR_EN){};
	 
	 DMA1_Stream6->CR &= ~DMA_SxCR_EN;
	 while(DMA1_Stream6->CR & DMA_SxCR_EN){};
	 
	 // stream is ready to be configured
	 DMA1->HISR = 0;		// clear the flags
	 
	 //Set the peripheral port register address
	 DMA1_Stream5->PAR = (uint32_t)&(USART2->DR);
	 DMA1_Stream6->PAR = (uint32_t)&(USART2->DR);
	 
	 // Set the memory address
	 DMA1_Stream5->M0AR = (uint32_t)rx_buf;
	 DMA1_Stream6->M0AR = (uint32_t)tx_buf;
	 
	 // Configure the total number of data items to be transferred
	 DMA1_Stream5->NDTR = BUF_SIZE;
	 DMA1_Stream6->NDTR = 0;
	 
	 // Select the DMA channel 4 (request)
	 DMA1_Stream5->CR |= (4<<25) + DMA_SxCR_MINC + DMA_SxCR_CIRC;
	 DMA1_Stream6->CR |= (4<<25) + DMA_SxCR_MINC + (1<<6);
	 
	 // enable rx dma
	 DMA1_Stream5->CR |= DMA_SxCR_EN;
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
	
	// stop dma
	DMA1_Stream6->CR &= ~DMA_SxCR_EN;
	while(DMA1_Stream6->CR & DMA_SxCR_EN){};
	
	// how mach remain bytes
	int nrm = DMA1_Stream6->NDTR;
	uint8_t *pt = &tx_buf[nrm];
	
	// copy new data in the tx buffer
	for( i = 0; (i < nb) && (i < BUF_SIZE); i++ ){
		*pt++ = *pb++;
		nrm++;
	}		
	
	DMA1_Stream6->NDTR = nrm;
	DMA1_Stream6->CR |= DMA_SxCR_EN;
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
	
	rx_idx = BUF_SIZE - DMA1_Stream5->NDTR;
	
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
