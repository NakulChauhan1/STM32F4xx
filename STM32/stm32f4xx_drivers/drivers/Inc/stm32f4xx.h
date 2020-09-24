

/* Note: This has only information about uC. ie addresses of various peripherals
and things associated with a peripheral, APIs (their prototypes) will be in driver.h file.
Also it has only macro, struct, enum in it. It doesnot have even a single function (APIS), it has only information in it,
There is no coding in it.*/


#ifndef __STM32F446xx_H
#define __STM32F446xx_H



#include<stdint.h>																//for	uint32_t

#define __IO volatile


/**********************************START:Processor Specific Details **********************************/
/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */

#define NVIC_ISER0_BASEADDR 		0xE000E100U													//addresses are always unsigned but default complier takes number as signed therefore typecasting is reguired
#define NVIC_ISER1_BASEADDR 		( NVIC_ISER0_BASEADDR + 0x04 )
#define NVIC_ISER2_BASEADDR 		( NVIC_ISER1_BASEADDR + 0x04 )
#define NVIC_ISER3_BASEADDR 		( NVIC_ISER2_BASEADDR + 0x04 )
#define NVIC_ISER4_BASEADDR 		( NVIC_ISER3_BASEADDR + 0x04 )
#define NVIC_ISER5_BASEADDR 		( NVIC_ISER4_BASEADDR + 0x04 )
#define NVIC_ISER6_BASEADDR 		( NVIC_ISER5_BASEADDR + 0x04 )
#define NVIC_ISER7_BASEADDR 		( NVIC_ISER6_BASEADDR + 0x04 )

/*
 * ARM Cortex Mx Processor NVIC ISERx register definition
 */

#define NVIC_ISER0							(__IO uint32_t *)NVIC_ISER0_BASEADDR
#define NVIC_ISER1							(__IO uint32_t *)NVIC_ISER1_BASEADDR
#define NVIC_ISER2							(__IO uint32_t *)NVIC_ISER2_BASEADDR
#define NVIC_ISER3							(__IO uint32_t *)NVIC_ISER3_BASEADDR
#define NVIC_ISER4							(__IO uint32_t *)NVIC_ISER4_BASEADDR
#define NVIC_ISER5							(__IO uint32_t *)NVIC_ISER5_BASEADDR
#define NVIC_ISER6							(__IO uint32_t *)NVIC_ISER6_BASEADDR
#define NVIC_ISER7							(__IO uint32_t *)NVIC_ISER7_BASEADDR




/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses and definiton
 */
#define NVIC_ICER0 			((__IO uint32_t*)0XE000E180)
#define NVIC_ICER1			((__IO uint32_t*)0XE000E184)
#define NVIC_ICER2  		((__IO uint32_t*)0XE000E188)
#define NVIC_ICER3			((__IO uint32_t*)0XE000E18C)



/*
 * ARM Cortex Mx Processor NVIC IPRx register Addresses and definiton
 */
#define NVIC_IPR_BASEADDR 			((__IO uint32_t *)0XE000E400)													//only one is sufficient, we can traverse to other from here only


#define	NO_PR_BITS_IMPLEMENTED		4								//although NVIC_IPR register is of 8 bit, but only upper 4 bits are implemented by ST in our microcontroller


/* Base Addresses of FLASH and SRAM Memories*/
#define FLASH_BASEADDR            0x08000000U
#define SRAM1_BASEADDR            0x20000000U
#define SRAM2_BASEADDR            0x2001C000U
#define SRAM2_BASEADDR            0x2001C000U
#define SRAM_BASEADDR							SRAM1_BASE
#define ROM                       0x1FFF0000U


/* AHBx and APBx Bus Peripheral Base Adresses*/
#define PERIPH_BASEADDR               0x40000000U
#define APB1PERIPH_BASEADDR           PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR           (PERIPH_BASEADDR + 0x00010000U)
#define AHB1PERIPH_BASEADDR           (PERIPH_BASEADDR + 0x00020000U)
#define AHB2PERIPH_BASEADDR           (PERIPH_BASEADDR + 0x10000000U)


/* Perpheral Base Addresses*/


/*!< Base addresses of Peripherals which are hanging onto AHB1 Bus */
#define GPIOA_BASEADDR            (AHB1PERIPH_BASEADDR + 0x0000UL)
#define GPIOB_BASEADDR            (AHB1PERIPH_BASEADDR + 0x0400UL)
#define GPIOC_BASEADDR		        (AHB1PERIPH_BASEADDR + 0x0800UL)
#define GPIOD_BASEADDR            (AHB1PERIPH_BASEADDR + 0x0C00UL)
#define GPIOE_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1000UL)
#define GPIOF_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1400UL)
#define GPIOG_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1800UL)
#define GPIOH_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1C00UL)
#define RCC_BASEADDR              (AHB1PERIPH_BASEADDR + 0x3800UL)


/*!< Base addresses of Peripherals which are hanging onto APB1 Bus */
#define I2C1_BASEADDR             (APB1PERIPH_BASEADDR + 0x5400UL)
#define I2C2_BASEADDR             (APB1PERIPH_BASEADDR + 0x5800UL)
#define I2C3_BASEADDR             (APB1PERIPH_BASEADDR + 0x5C00UL)
#define SPI2_BASEADDR             (APB1PERIPH_BASEADDR + 0x3800UL)
#define SPI3_BASEADDR             (APB1PERIPH_BASEADDR + 0x3C00UL)
#define USART2_BASEADDR           (APB1PERIPH_BASEADDR + 0x4400UL)
#define USART3_BASEADDR           (APB1PERIPH_BASEADDR + 0x4800UL)
#define UART4_BASEADDR            (APB1PERIPH_BASEADDR + 0x4C00UL)
#define UART5_BASEADDR            (APB1PERIPH_BASEADDR + 0x5000UL)



/*!< Base addresses of Peripherals which are hanging onto APB2 Bus */
#define EXTI_BASEADDR             		(APB2PERIPH_BASEADDR + 0x3C00UL)
#define SPI1_BASEADDR           	  	(APB2PERIPH_BASEADDR + 0x3000UL)
#define SPI4_BASEADDR           	  	(APB2PERIPH_BASEADDR + 0x3400UL)
#define SYSCFG_BASEADDR          			(APB2PERIPH_BASEADDR + 0x3800UL)
#define USART1_BASEADDR 	    	      (APB2PERIPH_BASEADDR + 0x1000UL)
#define USART6_BASEADDR   		        (APB2PERIPH_BASEADDR + 0x1400UL)


/* Now it is time for writing addresses of registers of each peripheral*/
/* Addresses of Peripheral Register */

typedef struct
{
		__IO uint32_t IMR;
		__IO uint32_t EMR;
		__IO uint32_t RTSR;
		__IO uint32_t FTSR;
		__IO uint32_t SWIER;
		__IO uint32_t PR;
}EXTI_RegDef_t;

typedef struct
{
		__IO	uint32_t MODER;
		__IO	uint32_t OTYPER;
		__IO	uint32_t OSPEEDR;
		__IO	uint32_t PUPDR;
		__IO	uint32_t IDR;
		__IO	uint32_t ODR;
		__IO	uint32_t BSRR;
		__IO	uint32_t LCKR;
		__IO	uint32_t AFLRL;
		__IO	uint32_t AFLRH;
}GPIO_RegDef_t;



typedef struct
{
		__IO uint32_t CR;
		__IO uint32_t PLLCFGR;
  	__IO uint32_t CFGR;
 	 	__IO uint32_t CIR;
 	  __IO uint32_t AHB1RSTR;
	  __IO uint32_t AHB2RSTR;
		__IO uint32_t AHB3RSTR;
				 uint32_t RESERVED0;
		__IO uint32_t APB1RSTR;
		__IO uint32_t APB2RSTR;
				 uint32_t RESERVED1[2];
		__IO uint32_t AHB1ENR;
		__IO uint32_t AHB2ENR;
		__IO uint32_t AHB3ENR;
				 uint32_t RESERVED2;
		__IO uint32_t APB1ENR;
		__IO uint32_t APB2ENR;
				 uint32_t RESERVED3[2];
		__IO uint32_t AHB1LPENR;
		__IO uint32_t AHB2LPENR;
		__IO uint32_t AHB3LPENR;
				 uint32_t RESERVED4;
		__IO uint32_t APB1LPENR;
		__IO uint32_t APB2LPENR;
				 uint32_t RESERVED5[2];
		__IO uint32_t BDCR;
		__IO uint32_t CSR;
				 uint32_t RESERVED6[2];
		__IO uint32_t SSCGR;
		__IO uint32_t PLLI2SCFGR;
		__IO uint32_t PLLSAICFGR;
		__IO uint32_t DCKCFGR;
		__IO uint32_t CKGATENR;
		__IO uint32_t DCKCFGR2;
}RCC_RegDef_t;


typedef struct
{
		__IO	uint32_t CR1;
		__IO	uint32_t CR2;
		__IO	uint32_t OAR1;
		__IO	uint32_t OAR2;
		__IO	uint32_t DR;
		__IO	uint32_t SR1;
		__IO	uint32_t SR2;
		__IO	uint32_t CCR;
		__IO	uint32_t TRISE;
	  __IO	uint32_t FLTR;
}I2C_RegDef_t;



typedef struct
{
		uint32_t MEMRMP;
	  uint32_t PMC;
		uint32_t EXTI_CR1;
		uint32_t EXTI_CR2;
		uint32_t EXTI_CR3;
		uint32_t EXTI_CR4;
		uint32_t reserved1[2];
		uint32_t CMPCR;
		uint32_t reserved2[2];
		uint32_t CFGR;
}SYSCFG_RegDef_t;



typedef struct
{
		uint32_t CR1;
		uint32_t CR2;
		uint32_t SR;
		uint32_t DR;
		uint32_t CRCPR;
		uint32_t RXCRCR;
		uint32_t TXCRCR;
		uint32_t I2SCFGR;
		uint32_t I2SPR;
}SPI_RegDef_t;



typedef struct
{
		uint32_t SR;
		uint32_t DR;
		uint32_t BRR;
		uint32_t CR1;
		uint32_t CR2;
		uint32_t CR3;
		uint32_t GTPR;
}USART_RegDef_t;


/* Peripheral Definition (Peripheral base address typecasted to GPIOx_RegDef_t) */

#define 	EXTI		((EXTI_RegDef_t *)EXTI_BASEADDR)																														//these all are pointers
#define		GPIOA		((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define		GPIOB		((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define   GPIOC		((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define   GPIOD		((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define   GPIOE		((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define   GPIOF		((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define   GPIOG		((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define   GPIOH		((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define 	I2C1		((I2C_RegDef_t *)I2C1_BASEADDR)
#define		I2C2		((I2C_RegDef_t *)I2C2_BASEADDR)
#define		I2C3		((I2C_RegDef_t *)I2C3_BASEADDR)
#define 	RCC			((RCC_RegDef_t *)RCC_BASEADDR)
#define 	SPI1		((SPI_RegDef_t *)SPI1_BASEADDR)
#define 	SPI2		((SPI_RegDef_t *)SPI2_BASEADDR)
#define	 	SPI3		((SPI_RegDef_t *)SPI3_BASEADDR)
#define 	SPI4		((SPI_RegDef_t *)SPI4_BASEADDR)
#define   SYSCFG	((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)
#define		USART1	((USART_RegDef_t *)USART1_BASEADDR)
#define		USART2	((USART_RegDef_t *)USART2_BASEADDR)
#define		USART3	((USART_RegDef_t *)USART3_BASEADDR)
#define		UART4		((USART_RegDef_t *)UART4_BASEADDR)
#define		UART5		((USART_RegDef_t *)UART5_BASEADDR)
#define		USART6	((USART_RegDef_t *)USART6_BASEADDR)

// for enabling/disabling clock we need RCC section, so we need to have access to base addresse of RCC registers,
// therefore we need to structure RCC peripherals (ie its registers) first.

/****************************clock enable*******************************/

//AHB1 for clock enable
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= ( 1<<0 ))
#define GPIOB_PLCK_EN()		(RCC->AHB1ENR |= ( 1<<1 ))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= ( 1<<2 ))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= ( 1<<2 ))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= ( 1<<3 ))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= ( 1<<4 ))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= ( 1<<5 ))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= ( 1<<6 ))
//no clock definition for RCC

//APB1 clock enable
#define I2C1_PCLK_EN()		(RCC->APB1ENR |= ( 1<<21 ))
#define I2C2_PCLK_EN()		(RCC->APB2ENR |= ( 1<<22 ))
#define I2C3_PCLK_EN() 	  (RCC->APB2ENR |= ( 1<<23 ))
#define	SPI2_PCLK_EN()		(RCC->APB1ENR |= ( 1<<14 ))
#define	SPI3_PCLK_EN()		(RCC->APB1ENR |= ( 1<<15 ))
#define	USART2_PCLK_EN()	(RCC->APB1ENR |= ( 1<<17 ))
#define	USART3_PCLK_EN()	(RCC->APB1ENR |= ( 1<<18 ))
#define	UART4_PCLK_EN()		(RCC->APB1ENR |= ( 1<<19 ))
#define	UART5_PCLK_EN()		(RCC->APB1ENR |= ( 1<<20 ))

//APB2 clock enable
#define SPI1_PLCK_EN()		(RCC->APB2ENR |= ( 1<<12 ))
#define SPI4_PLCK_EN()		(RCC->APB2ENR |= ( 1<<13 ))
#define	SYSCFG_PCLK_EN()	(RCC->APB2ENR |= ( 1<<14 ))
#define	USART1_PCLK_EN()	(RCC->APB2ENR |= ( 1<<4 ))
#define	USART6_PCLK_EN()	(RCC->APB2ENR |= ( 1<<5 ))

/****************************clock disable*******************************/

//AHB1 clock disable
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~( 1<<0 ))
#define GPIOB_PLCK_DI()		(RCC->AHB1ENR &= ~( 1<<1 ))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~( 1<<2 ))
#define GPIOD_PLCK_DI()		(RCC->AHB1ENR &= ~( 1<<3 ))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~( 1<<4 ))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR &= ~( 1<<5 ))
#define GPIOG_PLCK_DI()		(RCC->AHB1ENR &= ~( 1<<6 ))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~( 1<<7 ))


//APB1 clock disable
#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~( 1<<21 ))
#define I2C2_PCLK_DI()		(RCC->APB2ENR &= ~( 1<<22 ))
#define I2C3_PCLK_DI() 	  (RCC->APB2ENR &= ~( 1<<23 ))
#define	SPI2_PCLK_DI()		(RCC->APB1ENR &= ~( 1<<14 ))
#define	SPI3_PCLK_DI()		(RCC->APB1ENR &= ~( 1<<15 ))
#define	USART2_PCLK_DI()	(RCC->APB1ENR &= ~( 1<<17 ))
#define	USART3_PCLK_DI()	(RCC->APB1ENR &= ~( 1<<18 ))
#define	UART4_PCLK_DI()		(RCC->APB1ENR &= ~( 1<<19 ))
#define	UART5_PCLK_DI()		(RCC->APB1ENR &= ~( 1<<20 ))


//APB2 clock disable
#define SPI1_PLCK_DI()		(RCC->APB2ENR &= ~( 1<<12 ))
#define SPI4_PLCK_DI()		(RCC->APB2ENR &= ~( 1<<12 ))
#define	SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~( 1<<14 ))
#define	USART1_PCLK_DI()	(RCC->APB2ENR &= ~( 1<<4 ))
#define	USART6_PCLK_DI()	(RCC->APB2ENR &= ~( 1<<5 ))





/*
*	Reset Macros for GPIOx peipheral
*/
#define GPIOA_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 0 ); RCC->AHB1RSTR &= ~( 1 << 0 );}while(0)							//no semicolon because we give one ; when we will use this macro
#define GPIOB_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 1 ); RCC->AHB1RSTR &= ~( 1 << 1 );}while(0)							//note: when we reset a gpio then that gpio will be in reset state until we disable that bit, thats why we have to first set it and then reset it.
#define GPIOC_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 2 ); RCC->AHB1RSTR &= ~( 1 << 2 );}while(0)
#define GPIOD_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 3 ); RCC->AHB1RSTR &= ~( 1 << 3 );}while(0)
#define GPIOE_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 4 ); RCC->AHB1RSTR &= ~( 1 << 4 );}while(0)
#define GPIOF_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 5 ); RCC->AHB1RSTR &= ~( 1 << 5 );}while(0)
#define GPIOG_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 6 ); RCC->AHB1RSTR &= ~( 1 << 6 );}while(0)
#define GPIOH_REG_RESET()					do {RCC->AHB1RSTR |= ( 1 << 7 ); RCC->AHB1RSTR &= ~( 1 << 7 );}while(0)



/*****************Some generic Macros*****************************/
#define ENABLE 										1
#define DISABLE 									0
#define SET			 									1
#define RESET   									0
#define GPIO_PIN_SET   						1
#define GPIO_PIN_RESET   					0
#define FLAG_SET			 						1
#define FLAG_RESET   							0






/*
 * IRQ(Interrupt Request) Numbers of STM32F407x MCU
 */

#define IRQ_NO_EXTI0 				6
#define IRQ_NO_EXTI1 				7
#define IRQ_NO_EXTI2 				8
#define IRQ_NO_EXTI3 				9
#define IRQ_NO_EXTI4 				10
#define IRQ_NO_EXTI9_5 			23
#define IRQ_NO_EXTI15_10 		40









/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */

#define SPI_CR1_CPHA     					 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     					 2
#define SPI_CR1_BR   							 3
#define SPI_CR1_SPE     				 	 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     					 8
#define SPI_CR1_SSM      					 9
#define SPI_CR1_RXONLY      		 	10
#define SPI_CR1_DFF     				 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   				 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE     			15



/*
 * Bit position definitions SPI_CR2
 */

#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE					 	2
#define SPI_CR2_FRF							4
#define SPI_CR2_ERRIE						5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE						7


/*
 * Bit position definitions SPI_SR
 */

#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8






/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/


/*
 * Bit position definitions I2C_CR1
 */

#define I2C_CR1_PE								0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 						8
#define I2C_CR1_STOP  					 	9
#define I2C_CR1_ACK 				 			10
#define I2C_CR1_SWRST  				 		15

/*
 * Bit position definitions I2C_CR2
 */

#define I2C_CR2_FREQ				 			0
#define I2C_CR2_ITERREN				 		8
#define I2C_CR2_ITEVTEN				 		9
#define I2C_CR2_ITBUFEN 			 	  10

/*
 * Bit position definitions I2C_OAR1
 */

#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 				3
#define I2C_SR1_STOPF 				4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 			14

/*
 * Bit position definitions I2C_SR2
 */

#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 			4
#define I2C_SR2_DUALF 				7

/*
 * Bit position definitions I2C_CCR
 */

#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  		 	  	 1


/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK						0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 						3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  			5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 						9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 						12
#define USART_CR1_UE 					  13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP  				12
#define USART_CR2_LINEN   			14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   			3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   			10
#define USART_CR3_ONEBIT   			11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9


#include "gpio_driver.h"
#include "spi_driver.h"
#include "i2c_driver.h"
#include "usart_driver.h"
#include "rcc_driver.h"

#endif /* __STM32F446xx_H */





/*************************************************************************************************************************************************
Note the order:
1. Base Addresses of Memory
2. Base Addresses of Buses
3. Base Addresses of Peripherals
4. Addresses of Register (for that used structure)
5. Peripheral Definition (ie pointer type casting of base address of a peripheral to pointer of struct typedef)
6. Peripheral Clock Enable/Disable Macros
************************************************************************************************************************************************/

