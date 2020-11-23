# Embedded-Driver-Developmentt

This repository consists of drivers for STM32 based microcontroller for peripherals like GPIO, SPI, I2C, UART.

1. DRIVER folder - https://github.com/NakulChauhan1/STM32F4xx/tree/master/STM32/stm32f4xx_drivers/drivers
Consists of Inc and Src folder of drivers.
Src folder is having .c files of all the drivers and Inc folder consists of .h files of corresponding source files.

2. SRC folder - https://github.com/NakulChauhan1/STM32F4xx/tree/master/STM32/stm32f4xx_drivers/Src
Consists of small applications which are made using drivers, which are there in DRIVER folder for testing purpose.

3. Startup folder - https://github.com/NakulChauhan1/STM32F4xx/tree/master/STM32/stm32f4xx_drivers/Startup
Consists of startup file which consists of all initializations required before writing anyhting in main() function.



/******************************************************************************************
 *								APIs supported by GPIO driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
 
/*
* Init and De-init
*/

- void GPIO_Init( GPIO_Handle_t *pGPIOHandle );																																						
- void GPIO_DeInit( GPIO_RegDef_t *pGPIOx );


/*
* Peripheral Clock setup
*/

- void GPIO_PeriClockControl( GPIO_RegDef_t * pGPIOx, uint8_t ENorDI);																								



/*
* Data read and write
*/

- uint16_t  GPIO_ReadFromInputPort( GPIO_RegDef_t *pGPIOx );																
- uint8_t  GPIO_ReadFromInputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
- void GPIO_WriteToOutputPort( GPIO_RegDef_t *pGPIOx, uint16_t Value);
- void GPIO_WriteToOutputPin( GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
- void GPIO_ToggleOutputPin( GPIO_RegDef_t * pGPIOx, uint8_t PinNumber );


/*
* IRQ Configuration and ISR handling
*/

- void GPIO_InterruptConfig( uint32_t IRQNumber, uint8_t EnorDi );																		
- void GPIO_IRQPriorityConfig( uint8_t IRQNumber, uint32_t IRQPriority );
- void GPIO_IRQHandling( uint8_t PinNumber );




/******************************************************************************************
 *								APIs supported by SPI driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/

/*
 * Peripheral Clock setup
 */

 - void SPI_PeriClockControl ( SPI_RegDef_t * pSPIx, uint8_t EnorDi );


/*
 * Init or Deinit
 */
 - void SPI_Init ( SPI_Handle_t *pSPIHandle );
 - void SPI_DeInit ( SPI_RegDef_t * pSPIx );


/*
 * Data Receive and
 */
 - void SPI_SendData ( SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len );
 - void SPI_ReceiveData ( SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len );
 - uint8_t SPI_SendDataIT ( SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len );
 - uint8_t SPI_ReceiveDataIT ( SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len );
 - uint8_t SPI_GetFlagStatus ( SPI_RegDef_t *pSPIx , uint32_t FlagName );
 - void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
 - void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle);
 - void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Other peripheral Control APIs
 *
 */
  - void SPI_PeripheralControl ( SPI_RegDef_t * pSPIx, uint8_t ENorDi  ) ;
  - void SPI_SSIConfig ( SPI_RegDef_t * pSPIx, uint8_t ENorDi );
  - void SPI_SSOEConfig ( SPI_RegDef_t * pSPIx, uint8_t ENorDi );


 /*
 * IRQ Configuration and ISR handling
 */

  - void SPI_InterruptConfig( uint32_t IRQNumber, uint8_t EnorDi );
  - void SPI_IRQPriorityConfig( uint8_t IRQNumber, uint32_t IRQPriority );
  - void SPI_IRQHandling(SPI_Handle_t *pHandle);

 /*
  * Application callback
  */

  -  - void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv);
 
 
 /******************************************************************************************
 *								APIs supported by I2C driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/

/*
 * Peripheral Clock setup
 */

 -  void I2C_PeriClockControl ( I2C_RegDef_t * pI2Cx, uint8_t ENorDi );

/*
 * Init or Deinit
 */

  - void I2C_Init ( I2C_Handle_t * pI2Cx );
  -  void I2C_Deinit ( I2C_RegDef_t * pI2Cx );

/*
 * Data Send and Receive
 */

  - void I2C_MasterSendData ( I2C_RegDef_t * pI2Cx, uint8_t * pTxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr );
  -  - void I2C_MasterReceiveData ( I2C_RegDef_t * pI2Cx, uint8_t * pRxbuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr);


/*
 * Other Peripheral Control APIs
 */

  - void I2C_PeripheralControl ( I2C_RegDef_t * pI2Cx, uint8_t EnorDi );
  - void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

  - uint32_t RCC_GetPCLK1Value ( void ) ;
 
 
 
 /******************************************************************************************
 *								APIs supported by USART driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/

/*
 * Peripheral Clock setup
 */

 - void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/*
 * Init and De-init
 */

 - void USART_Init(USART_Handle_t *pUSARTHandle);
 - void USART_DeInit(USART_RegDef_t *pUSARTx);


/*
 * Data Send and Receive
 */

 - void USART_SendData(USART_Handle_t *pUSARTx,uint8_t *pTxBuffer, uint32_t Len);
 - void USART_ReceiveData(USART_Handle_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len);
 - uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);
 - uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */

 - void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
 - void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
 - void USART_IRQHandling(USART_Handle_t *pHandle);

/*
 * Other Peripheral Control APIs
 */

 - void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
 - uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx , uint32_t FlagName);
 -  - void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);

/*
 * Application callback
 */

 - void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv);
