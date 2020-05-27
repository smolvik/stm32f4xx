extern unsigned long _data_flash;
extern unsigned long _data_begin;
extern unsigned long _data_end;
extern unsigned long _bss_begin;
extern unsigned long _bss_end;
extern unsigned long _stack_end;

extern int main(void);
/* Vector Table */

void Reset_Handler(void) __attribute__ ((weak,  alias ("handler_reset")));
void NMI_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void HardFault_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void MemManage_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void BusFault_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void UsageFault_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void SVC_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void DebugMon_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void PendSV_Handler(void) __attribute__ ((weak,  alias ("default_handler")));
void SysTick_Handler(void) __attribute__ ((weak,  alias ("default_handler")));

/* External Interrupts */
void	WWDG_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* Window WatchDog              */                                        
void	PVD_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                    /* PVD through EXTI Line detection */                        
void	TAMP_STAMP_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));             /* Tamper and TimeStamps through the EXTI line */            
void	RTC_WKUP_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* RTC Wakeup through the EXTI line */                      
void	FLASH_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* FLASH                        */                                          
void	RCC_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                    /* RCC                          */                                            
void	EXTI0_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* EXTI Line0                   */                        
void	EXTI1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* EXTI Line1                   */                          
void	EXTI2_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* EXTI Line2                   */                          
void	EXTI3_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* EXTI Line3                   */                          
void	EXTI4_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* EXTI Line4                   */                          
void	DMA1_Stream0_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream 0                */                  
void	DMA1_Stream1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream 1                */                   
void	DMA1_Stream2_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream 2                */                   
void	DMA1_Stream3_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream 3                */                   
void	DMA1_Stream4_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream 4                */                   
void	DMA1_Stream5_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream 5                */                   
void	DMA1_Stream6_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream 6                */                   
void	ADC_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                    /* ADC1, ADC2 and ADC3s         */                   
void	CAN1_TX_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* CAN1 TX                      */                         
void	CAN1_RX0_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));              /* CAN1 RX0                     */                          
void	CAN1_RX1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));              /* CAN1 RX1                     */                          
void	CAN1_SCE_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* CAN1 SCE                     */                          
void	EXTI9_5_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* External Line[9:5]s          */                          
void	TIM1_BRK_TIM9_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));          /* TIM1 Break and TIM9          */         
void	TIM1_UP_TIM10_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));          /* TIM1 Update and TIM10        */         
void	TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));     /* TIM1 Trigger and Commutation and TIM11 */
void	TIM1_CC_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* TIM1 Capture Compare         */                          
void	TIM2_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* TIM2                         */                   
void	TIM3_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* TIM3                         */                   
void	TIM4_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* TIM4                         */                   
void	I2C1_EV_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* I2C1 Event                   */                          
void	I2C1_ER_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* I2C1 Error                   */                          
void	I2C2_EV_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* I2C2 Event                   */                          
void	I2C2_ER_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* I2C2 Error                   */                            
void	SPI1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* SPI1                         */                   
void	SPI2_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* SPI2                         */                   
void	USART1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                 /* USART1                       */                   
void	USART2_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                 /* USART2                       */                   
void	USART3_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* USART3                       */                   
void	EXTI15_10_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));              /* External Line[15:10]s        */                          
void	RTC_Alarm_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));              /* RTC Alarm (A and B) through EXTI Line */                 
void	OTG_FS_WKUP_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));            /* USB OTG FS Wakeup through EXTI line */                       
void	TIM8_BRK_TIM12_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));         /* TIM8 Break and TIM12         */         
void	TIM8_UP_TIM13_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));          /* TIM8 Update and TIM13        */         
void	TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));     /* TIM8 Trigger and Commutation and TIM14 */
void	TIM8_CC_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* TIM8 Capture Compare         */                          
void	DMA1_Stream7_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA1 Stream7                 */                          
void	FSMC_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* FSMC                         */                   
void	SDIO_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* SDIO                         */                   
void	TIM5_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* TIM5                         */                   
void	SPI3_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* SPI3                         */                   
void	UART4_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* UART4                        */                   
void	UART5_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                  /* UART5                        */                   
void	TIM6_DAC_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* TIM6 and DAC1&2 underrun errors */                   
void	TIM7_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* TIM7                         */
void	DMA2_Stream0_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 0                */                   
void	DMA2_Stream1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 1                */                   
void	DMA2_Stream2_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 2                */                   
void	DMA2_Stream3_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 3                */                   
void	DMA2_Stream4_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 4                */                   
void	ETH_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                    /* Ethernet                     */                   
void	ETH_WKUP_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* Ethernet Wakeup through EXTI line */                     
void	CAN2_TX_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* CAN2 TX                      */                          
void	CAN2_RX0_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* CAN2 RX0                     */                          
void	CAN2_RX1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* CAN2 RX1                     */                          
void	CAN2_SCE_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* CAN2 SCE                     */                          
void	OTG_FS_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                 /* USB OTG FS                   */                   
void	DMA2_Stream5_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 5                */                   
void	DMA2_Stream6_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 6                */                   
void	DMA2_Stream7_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));           /* DMA2 Stream 7                */                   
void	USART6_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                 /* USART6                       */                    
void	I2C3_EV_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* I2C3 event                   */                          
void	I2C3_ER_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                /* I2C3 error                   */                          
void	OTG_HS_EP1_OUT_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));         /* USB OTG HS End Point 1 Out   */                   
void	OTG_HS_EP1_IN_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));          /* USB OTG HS End Point 1 In    */                   
void	OTG_HS_WKUP_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));            /* USB OTG HS Wakeup through EXTI */                         
void	OTG_HS_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                 /* USB OTG HS                   */                   
void	DCMI_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* DCMI                         */                   
void	CRYP_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                   /* CRYP crypto                  */                   
void	HASH_RNG_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));               /* Hash and Rng                 */
void	FPU_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));                    /* FPU                          */  


void handler_reset(void)
{
	unsigned long *source;
	unsigned long *destination;
	// Copying data from Flash to RAM
	source = &_data_flash;
	for (destination = &_data_begin; destination < &_data_end;)
	{
	*(destination++) = *(source++);
	}
	// default zero to undefined variables
	for (destination = &_bss_begin; destination < &_bss_end;)
	{
	*(destination++) = 0;
	}
	
	// starting main program
	main();
}

void default_handler(void)
{
	while (1)
	{
	//loop
	}
}

__attribute__ ((section(".interrupt_vector")))

void (* const table_interrupt_vector[])(void) = 
{
	(void *) &_stack_end,
	Reset_Handler,              // Reset Handler
	NMI_Handler,                // NMI Handler
	HardFault_Handler,          // Hard Fault Handler
	MemManage_Handler,          // MPU Fault Handler
	BusFault_Handler,           // Bus Fault Handler
	UsageFault_Handler,         // Usage Fault Handler
	0,                          // Reserved
	0,                          // Reserved
	0,                          // Reserved
	0,                          // Reserved
	SVC_Handler,                // SVCall Handler
	DebugMon_Handler,           // Debug Monitor Handler
	0,                          // Reserved
	PendSV_Handler,             // PendSV Handler
	SysTick_Handler,            // SysTick Handler

	// External Interrupts
  WWDG_IRQHandler,                   /* Window WatchDog              */                                        
  PVD_IRQHandler,                    /* PVD through EXTI Line detection */                        
  TAMP_STAMP_IRQHandler,            /* Tamper and TimeStamps through the EXTI line */            
  RTC_WKUP_IRQHandler,               /* RTC Wakeup through the EXTI line */                      
  FLASH_IRQHandler,                  /* FLASH                        */                                          
  RCC_IRQHandler,                    /* RCC                          */                                            
  EXTI0_IRQHandler,                  /* EXTI Line0                   */                        
  EXTI1_IRQHandler,                  /* EXTI Line1                   */                          
  EXTI2_IRQHandler,                  /* EXTI Line2                   */                          
  EXTI3_IRQHandler,                  /* EXTI Line3                   */                          
  EXTI4_IRQHandler,                  /* EXTI Line4                   */                          
  DMA1_Stream0_IRQHandler,           /* DMA1 Stream 0                */                  
  DMA1_Stream1_IRQHandler,           /* DMA1 Stream 1                */                   
  DMA1_Stream2_IRQHandler,           /* DMA1 Stream 2                */                   
  DMA1_Stream3_IRQHandler,           /* DMA1 Stream 3                */                   
  DMA1_Stream4_IRQHandler,           /* DMA1 Stream 4                */                   
  DMA1_Stream5_IRQHandler,           /* DMA1 Stream 5                */                   
  DMA1_Stream6_IRQHandler,           /* DMA1 Stream 6                */                   
  ADC_IRQHandler,                    /* ADC1, ADC2 and ADC3s         */                   
  CAN1_TX_IRQHandler,                /* CAN1 TX                      */                         
  CAN1_RX0_IRQHandler,               /* CAN1 RX0                     */                          
  CAN1_RX1_IRQHandler,               /* CAN1 RX1                     */                          
  CAN1_SCE_IRQHandler,               /* CAN1 SCE                     */                          
  EXTI9_5_IRQHandler,                /* External Line[9:5]s          */                          
  TIM1_BRK_TIM9_IRQHandler,          /* TIM1 Break and TIM9          */         
  TIM1_UP_TIM10_IRQHandler,          /* TIM1 Update and TIM10        */         
  TIM1_TRG_COM_TIM11_IRQHandler,     /* TIM1 Trigger and Commutation and TIM11 */
  TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */                          
  TIM2_IRQHandler,                   /* TIM2                         */                   
  TIM3_IRQHandler,                   /* TIM3                         */                   
  TIM4_IRQHandler,                   /* TIM4                         */                   
  I2C1_EV_IRQHandler,                /* I2C1 Event                   */                          
  I2C1_ER_IRQHandler,                /* I2C1 Error                   */                          
  I2C2_EV_IRQHandler,                /* I2C2 Event                   */                          
  I2C2_ER_IRQHandler,                /* I2C2 Error                   */                            
  SPI1_IRQHandler,                   /* SPI1                         */                   
  SPI2_IRQHandler,                   /* SPI2                         */                   
  USART1_IRQHandler,                 /* USART1                       */                   
  USART2_IRQHandler,                 /* USART2                       */                   
  USART3_IRQHandler,                 /* USART3                       */                   
  EXTI15_10_IRQHandler,              /* External Line[15:10]s        */                          
  RTC_Alarm_IRQHandler,              /* RTC Alarm (A and B) through EXTI Line */                 
  OTG_FS_WKUP_IRQHandler,            /* USB OTG FS Wakeup through EXTI line */                       
  TIM8_BRK_TIM12_IRQHandler,         /* TIM8 Break and TIM12         */         
  TIM8_UP_TIM13_IRQHandler,          /* TIM8 Update and TIM13        */         
  TIM8_TRG_COM_TIM14_IRQHandler,     /* TIM8 Trigger and Commutation and TIM14 */
  TIM8_CC_IRQHandler,                /* TIM8 Capture Compare         */                          
  DMA1_Stream7_IRQHandler,           /* DMA1 Stream7                 */                          
  FSMC_IRQHandler,                   /* FSMC                         */                   
  SDIO_IRQHandler,                   /* SDIO                         */                   
  TIM5_IRQHandler,                   /* TIM5                         */                   
  SPI3_IRQHandler,                   /* SPI3                         */                   
  UART4_IRQHandler,                  /* UART4                        */                   
  UART5_IRQHandler,                  /* UART5                        */                   
  TIM6_DAC_IRQHandler,               /* TIM6 and DAC1&2 underrun errors */                   
  TIM7_IRQHandler,                   /* TIM7                         */
  DMA2_Stream0_IRQHandler,           /* DMA2 Stream 0                */                   
  DMA2_Stream1_IRQHandler,           /* DMA2 Stream 1                */                   
  DMA2_Stream2_IRQHandler,           /* DMA2 Stream 2                */                   
  DMA2_Stream3_IRQHandler,           /* DMA2 Stream 3                */                   
  DMA2_Stream4_IRQHandler,           /* DMA2 Stream 4                */                   
  ETH_IRQHandler,                    /* Ethernet                     */                   
  ETH_WKUP_IRQHandler,               /* Ethernet Wakeup through EXTI line */                     
  CAN2_TX_IRQHandler,                /* CAN2 TX                      */                          
  CAN2_RX0_IRQHandler,               /* CAN2 RX0                     */                          
  CAN2_RX1_IRQHandler,               /* CAN2 RX1                     */                          
  CAN2_SCE_IRQHandler,               /* CAN2 SCE                     */                          
  OTG_FS_IRQHandler,                 /* USB OTG FS                   */                   
  DMA2_Stream5_IRQHandler,           /* DMA2 Stream 5                */                   
  DMA2_Stream6_IRQHandler,           /* DMA2 Stream 6                */                   
  DMA2_Stream7_IRQHandler,           /* DMA2 Stream 7                */                   
  USART6_IRQHandler,                 /* USART6                       */                    
  I2C3_EV_IRQHandler,                /* I2C3 event                   */                          
  I2C3_ER_IRQHandler,                /* I2C3 error                   */                          
  OTG_HS_EP1_OUT_IRQHandler,         /* USB OTG HS End Point 1 Out   */                   
  OTG_HS_EP1_IN_IRQHandler,          /* USB OTG HS End Point 1 In    */                   
  OTG_HS_WKUP_IRQHandler,            /* USB OTG HS Wakeup through EXTI */                         
  OTG_HS_IRQHandler,                 /* USB OTG HS                   */                   
  DCMI_IRQHandler,                   /* DCMI                         */                   
  CRYP_IRQHandler,                   /* CRYP crypto                  */                   
  HASH_RNG_IRQHandler,               /* Hash and Rng                 */
  FPU_IRQHandler                    /* FPU                          */
};
