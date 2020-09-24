

#include "gpio_driver.h"



//Write all the APIs here

/*********************************************************************
 * @fn      				  - GPIO_Init
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_Init( GPIO_Handle_t *pGPIOHandle )													//Configure its mode, its speed, its output type, pull-up pull-down resistor configuration, alternate functionality and various other things
{

	// Enabling Clock of GPIO Peripheral
	GPIO_PeriClockControl ( pGPIOHandle->pGPIOx, ENABLE );


//Configuring Mode, remember application member will fill all the macros ie all possible value in application layer, thats why we are not taking direct macros. eg we are not using macro GPIO_MODE_ANALOG (ie 11 (value 3)), instead we are using pGPIOHandle->GPIO_PinConfig.GPIO_PinMode , this variable will have all the macros ie macro for 1, macro for 2, macro for 3.
	uint32_t temp = 0;		//temporary register
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG )									//non interrupt mode, GPIO_MODE_ANALOG = 4
	{
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;		//where 00 or 01 or 10 or 11 will be placed will be decided by pin number, ie. 2 times the pin number
		pGPIOHandle->pGPIOx->MODER &= ~ ( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );							//clearing required bits before setting
		pGPIOHandle->pGPIOx->MODER |= temp;
	}
	else
	{
		//interrupt mode
		//note: first of all for interrupt funtionality we need to use NVIC processor support, and we know as per ST design for GPIO peripheral NVIC is not directly attached, NVIC is connected with the help of EXTI block, so first EXTI registers address we should know, therefore we need to structure EXTI registers first
		if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT )
		{
				//configuring FTSR
				EXTI_RegDef_t * pEXTI = EXTI	;
				pEXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ;
				//clearing RTSR for safety
				pEXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ;
		}
		else if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT )
		{
				//configuring RTSR
				EXTI_RegDef_t * pEXTI = EXTI  ;
				pEXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ;
				//clearing FTSR for safety
			  pEXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ;
		}
		else if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT )
		{
				//configuring FTSR and RTSR
				EXTI_RegDef_t * pEXTI = EXTI	;
				pEXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber )  ;
				pEXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber )  ;
		}
		//configuring SYSCFG_EXTICR GPIO port for selectiion

		uint32_t pcode = getportcode ( pGPIOHandle->pGPIOx ) ;
		uint8_t index = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4 ;				//for 0 - 4 this is not required, but for pins more than 4, we have to map them into range of 0 -4, otherwise index will go out of range

		SYSCFG_PCLK_EN();																												//before using any peripheral, we have to enable clock of that peripheral.

		if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 3 )
		{

				SYSCFG->EXTI_CR1 |= pcode << ( 4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ;

		}
		else if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber >= 4 && pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7 )
		{

				SYSCFG->EXTI_CR2 |= pcode << ( 4 * index ) ;

		}
		else if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber >= 8 && pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 11 )
		{

				SYSCFG->EXTI_CR3 |= pcode << ( 4 * index ) ;

		}
		else if ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber >= 12 && pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 15 )
		{

				SYSCFG->EXTI_CR4 |= pcode << ( 4 * index ) ;

		}

		//enabling the EXTI interrupt delivery
		EXTI->IMR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ;

	}
//Configuring Speed
	  temp = 0;
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) ;
		pGPIOHandle->pGPIOx->OSPEEDR &= ~ ( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );							//clearing required bits before setting
	  pGPIOHandle->pGPIOx->OSPEEDR |= temp;																																					//or is used because we dont want to change other bits, ie we dont want to reinitialise the entire register

//Configuring Output type setting
		temp = 0;
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ;
		pGPIOHandle->pGPIOx->OTYPER &= ~ ( 0x1 << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );							//clearing required bits before setting
	  pGPIOHandle->pGPIOx->OTYPER |= temp;

//Configuring PUPD setting
		temp = 0;
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
		pGPIOHandle->pGPIOx->PUPDR &= ~ ( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );							//clearing required bits before setting
	  pGPIOHandle->pGPIOx->PUPDR |= temp;

//Configuring Alternate Functionality setting
		temp = 0;
		if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN )
		{
				if(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber < 8 )
				{
						temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
						pGPIOHandle->pGPIOx->AFLRL &= ~ ( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );							//clearing required bits before setting
					  pGPIOHandle->pGPIOx->AFLRL |= temp;
				}
				else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber >= 8 )
				{
						temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8 );			// % 8 because for pin number >= 8 we want to map it into 0 to 7 because register can handle only 7 Alt fxn.
						pGPIOHandle->pGPIOx->AFLRH &= ~ ( 0xF << ( 4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );							//clearing required bits before setting
					  pGPIOHandle->pGPIOx->AFLRH |= temp;
				}
		}
}


/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_DeInit( GPIO_RegDef_t *pGPIOx )
{
		if( pGPIOx == GPIOA )
		{
				GPIOA_REG_RESET();																																				//we have already defined RCC in mcu specific header file, thats why we dont need to define RCC structure pointer
		}
		else if( pGPIOx == GPIOB )
		{
				GPIOB_REG_RESET();
		}
		else if( pGPIOx == GPIOC )
		{
				GPIOC_REG_RESET();
		}
		else if( pGPIOx == GPIOD )
		{
				GPIOD_REG_RESET();
		}
		else if( pGPIOx == GPIOE )
		{
				GPIOE_REG_RESET();
		}
		else if( pGPIOx == GPIOF )
		{
				GPIOF_REG_RESET();
		}
		else if( pGPIOx == GPIOG )
		{
				GPIOG_REG_RESET();
		}
		else if( pGPIOx == GPIOH )
		{
				GPIOH_REG_RESET();
		}
}


/*********************************************************************
 * @fn      		 			- GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */

void GPIO_PeriClockControl( GPIO_RegDef_t * pGPIOx, uint8_t ENorDI)
{
	if( ENorDI == ENABLE )
	{
		if( pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN() ;
		}
		else if( pGPIOx == GPIOB)
		{
			GPIOB_PLCK_EN() ;
		}
		else if( pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN() ;
		}
		else if( pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN() ;
		}
		else if( pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN() ;
		}
		else if( pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN() ;
		}
		else if( pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN() ;
		}
		else if( pGPIOx == GPIOA)
		{
			GPIOH_PCLK_EN() ;
		}
	}
	else if( ENorDI == DISABLE )
	{
		if( pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI() ;
		}
		else if( pGPIOx == GPIOB)
		{
			GPIOB_PLCK_DI() ;
		}
		else if( pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI() ;
		}
		else if( pGPIOx == GPIOD)
		{
			GPIOD_PLCK_DI() ;
		}
		else if( pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI() ;
		}
		else if( pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI() ;
		}
		else if( pGPIOx == GPIOG)
		{
			GPIOG_PLCK_DI() ;
		}
		else if( pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI() ;
		}
	}
}




/*********************************************************************
 * @fn      		 			- GPIO_ReadFromInputPort
 *
 * @brief             - Reads value of a GPIOx Port.
 *
 * @param[in]         - Base address of required GPIO.
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  16 bit Input Data Register Value
 *
 * @Note              -
 */

uint16_t  GPIO_ReadFromInputPort( GPIO_RegDef_t * pGPIOx )
{
		uint16_t value = pGPIOx->IDR ;																			//uint16_t not uint32_t because IDR is 16 bit long
		return value;
}


/*********************************************************************
 * @fn      		 			- GPIO_ReadFromInputPin
 *
 * @brief             - Reads specified pin of a GPIOx Port.
 *
 * @param[in]         - Base address of required GPIO.
 * @param[in]         - Required Pin number
 * @param[in]         -
 *
 * @return            -  0 or 1
 *
 * @Note              -
 */

uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber )
{
		uint8_t value = (uint8_t )(pGPIOx->IDR >> PinNumber  & 0x00000001);
		return value;
}


/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_WriteToOutputPort( GPIO_RegDef_t * pGPIOx, uint16_t value )
{
		pGPIOx->ODR = value;
}


/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_WriteToOutputPin( GPIO_RegDef_t * pGPIOx, uint8_t PinNumber, uint8_t  value )
{
		if( value == GPIO_PIN_SET )
		{
			pGPIOx->ODR |= ( 1 << PinNumber );
		}
		else if( value == GPIO_PIN_RESET )
		{
			pGPIOx->ODR  &= ~( 1 << PinNumber );
		}
}


/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_ToggleOutputPin( GPIO_RegDef_t * pGPIOx, uint8_t PinNumber )
{
		pGPIOx->ODR ^= (1 << PinNumber );
}


/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_InterruptConfig( uint32_t IRQNumber, uint8_t EnorDi )						//used to configure IRQ number like enabling it, disabling, changing priority
{
		//configuring NVIC related registers, or configuring processor registers
		if( EnorDi == ENABLE )
		{
			if ( IRQNumber <= 31 )
			{
					//program ISER0 register
					*NVIC_ISER0 |= ( 1 << IRQNumber ) ;
			}
			else if ( IRQNumber >= 32 && IRQNumber <= 63 )
			{
					//program ISER1 register
				  *NVIC_ISER1 |= ( 1 << IRQNumber%32 ) ;									// %32 is make 32 - 63 in the range of 0 - 31
			}
			else if ( IRQNumber >= 64 && IRQNumber <= 95 )
			{
					//program ISER2 register
			  	*NVIC_ISER2 |= ( 1 << IRQNumber%64 ) ;									// %64 is make 64 - 95 in the range of 0 - 31
			}
		}
		else if( EnorDi == DISABLE )
		{
			if ( IRQNumber <= 31 )
			{
					//program ISER0 register
					*NVIC_ICER0 |= ( 1 << IRQNumber ) ;
			}
			else if ( IRQNumber >= 32 && IRQNumber <= 63 )
			{
					//program ISER1 register
				  *NVIC_ICER1 |= ( 1 << IRQNumber%32 ) ;									// %32 is make 32 - 63 in the range of 0 - 31
			}
			else if ( IRQNumber >= 64 && IRQNumber <= 95 )
			{
					//program ISER2 register
			  	*NVIC_ICER2 |= ( 1 << IRQNumber%64 ) ;									// %64 is make 64 - 95 in the range of 0 - 31
			}
		}
}

/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_IRQHandling( uint8_t PinNumber )					//means whenever interrupt occurs, user application should call this function in order to process that interrupt.
{
		if ( EXTI->PR && ( 1 << PinNumber )	)						//check if Interrupt is pending or not
		{
				//if pending then clear pending register and do whatever work you want to do
				EXTI->PR |= ( 1 << PinNumber ) ;									//in refernce manual it is given writing 1, clears the PR
		}
}

/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

void GPIO_IRQPriorityConfig( uint8_t IRQNumber, uint32_t IRQPriority )
{
		uint8_t reg_number = IRQPriority / 4 ;																	// it tells in which NVIC Priority register we have to use
		uint8_t reg_section = IRQPriority % 4 ; 																// it tells which in bit of a NVIC Priority register we have to use

		uint8_t shifting_amount = 8 * reg_section + ( 8 - NO_PR_BITS_IMPLEMENTED ) ;
		*( NVIC_IPR_BASEADDR + reg_number ) |= ( IRQPriority << shifting_amount ) ;					//lower 4 bits are not implemented in each and every field of this register, therefore we have shift by additional 4 amount
																																												//note: above
}

/*********************************************************************
 * @fn      		 			-
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -
 */

uint8_t getportcode( GPIO_RegDef_t *pGPIOx )
{
		if ( pGPIOx == GPIOA )
			return 0;
		else if ( pGPIOx == GPIOB )
			return 1;
		else if ( pGPIOx == GPIOC )
			return 2;
		else if ( pGPIOx == GPIOD )
			return 3;
		else if ( pGPIOx == GPIOE )
			return 4;
		else if ( pGPIOx == GPIOF )
			return 5;
		else if ( pGPIOx == GPIOG )
			return 6;
		else if ( pGPIOx == GPIOH )
			return 7;
		else
			return 0;
}


