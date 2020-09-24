

#include "i2c_driver.h"


 static void I2C_GenerateStartCondition ( I2C_RegDef_t * pI2Cx );											//helper function private to driver
 static void I2C_ExecuteAddressPhaseWrite ( I2C_RegDef_t * I2Cx, uint8_t SlaveAddr );
 static void I2C_ExecuteAddressPhaseRead ( I2C_RegDef_t * pI2Cx, uint8_t SlaveAddr );
 static void I2C_ClearADDRFlag ( I2C_RegDef_t * pI2Cx );
 static void I2C_GenerateStopCondition ( I2C_RegDef_t * pI2Cx );


 /*********************************************************************
  * @fn      				  - I2C_GenerateStartCondition
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

 static void I2C_GenerateStartCondition ( I2C_RegDef_t * pI2Cx )
 {
		pI2Cx->CR1 |= ( 1 << I2C_CR1_START );
 }

 /*********************************************************************
  * @fn      				  - I2C_ExecuteAddressPhaseWrite
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

 static void I2C_ExecuteAddressPhaseWrite ( I2C_RegDef_t * pI2Cx, uint8_t SlaveAddr )
 {
		//SlaveAddr contains 7 bit slave address
		SlaveAddr = ( SlaveAddr << 1 );										//SlaveAddr is of 8 bits size and shifting SlaveAddr by 1 will shift all 7 bits by 1 and space for R/nW will be created in 8th bit place.
		SlaveAddr &= ~ (1);																//LSB ie 8th bit is R/nW bit which must be set to 0 in order to write.
		// Now SlaveAddr is ( SlaveAddress + R/nW ).

		pI2Cx->DR = SlaveAddr;														//this clears the SB bit, and slave address is sent by the master
		// Note: With writing Slave Address to Data Register, not only SB is cleared but also Address Phase is completed.
		// So, SB is cleared and Address phase is completed with only single line.

	 //pI2Cx->OAR1 |= ( pI2Cx->I2C_Config.I2C_DeviceAddress << 1 );				//this line was thought by me
 }

 /*********************************************************************
  * @fn      				  - I2C_ExecuteAddressPhaseRead
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

 static void I2C_ExecuteAddressPhaseRead ( I2C_RegDef_t * pI2Cx, uint8_t SlaveAddr )
  {
 		//SlaveAddr contains 7 bit slave address
 		SlaveAddr = ( SlaveAddr << 1 );										//SlaveAddr is of 8 bits size and shifting SlaveAddr by 1 will shift all 7 bits by 1 and space for R/nW will be created in 8th bit place.
 	  SlaveAddr |= (1);																	//LSB ie 8th bit is R/nW bit which must be set to 1 in order to Read.

 		// Now SlaveAddr is ( SlaveAddress + R/nW ).
 	  pI2Cx->DR = SlaveAddr;
  }


 /*********************************************************************
  * @fn      				  - I2C_ClearADDRFlag
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

 static void I2C_ClearADDRFlag ( I2C_RegDef_t * pI2Cx )
 {
		//acc. to RTM ADDR is cleared by reading SR1 and SR2.
		uint32_t dummyRead = pI2Cx->SR1;
	  dummyRead = pI2Cx->SR2;
		(void)dummyRead;										//to avoid unused variable error
 }

 /*********************************************************************
  * @fn      				  - I2C_GenerateStopCondition
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

 static void I2C_GenerateStopCondition ( I2C_RegDef_t * pI2Cx )
 {
		pI2Cx->CR1 |= ( 1 << I2C_CR1_STOP );
 }



/*********************************************************************
 * @fn      				  - I2C_PeriClockControl
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

 void I2C_PeriClockControl ( I2C_RegDef_t * pI2Cx, uint8_t EnorDi )
 {
		if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}else if (pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}else if (pI2Cx == I2C3)
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DI();
		}else if (pI2Cx == I2C2)
		{
			I2C2_PCLK_DI();
		}else if (pI2Cx == I2C3)
		{
			I2C3_PCLK_DI();
		}
	}
 }



 	 /*********************************************************************
 * @fn      				  - I2C_Init
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

 void I2C_Init ( I2C_Handle_t * pI2Cxx )
 {
		//Enabling the clock of I2Cxx peripheral
		I2C_PeriClockControl ( pI2Cxx->pI2Cx, ENABLE );

		//1. Configuring ACK
		uint32_t temp = 0 ;
	  temp |= pI2Cxx->I2C_Config.I2C_ACKControl << I2C_CR1_ACK ;
		pI2Cxx->pI2Cx->CR1 |= temp ;

		//2. Configuring FREQ field
		//now for freq field the freq bits must be configured with the APB clock frequency value. So, we have to calculate value of APB1 bus clock frequency.
		temp = 0 ;
		uint32_t pclk1 = RCC_GetPCLK1Value ();
		temp |=  ( pclk1 )/1000000U ;				//divind by 1M bcz we want only value not exponentials, values like 16, 8 etc
		pI2Cxx->pI2Cx->CR2 |= temp ;

		//3. now setting Slave Address
		temp = 0 ;
		uint8_t addMode = 0 ;															//this bit tells wheather slave address is 7 bit or 10 bit, by default its zero. (its incomplete)

		if ( addMode == 1 )														//10 bit slave address
		{
			temp |= ( 1 << I2C_OAR1_ADDMODE ) ;
			temp |= ( pI2Cxx->I2C_Config.I2C_DeviceAddress & 0x01 ) ;									//first bit of 10 bit slave address
			temp |= ( ( pI2Cxx->I2C_Config.I2C_DeviceAddress >> 1 ) << 1 ) ;					//saving rest of the 9 bits of Slave Address.
			temp |= ( 1 << 14 ) ;																											//according to RTM 14th bit should be set
		}
		else																				//7 bit slave address
		{
			 temp &= ~( 1 << I2C_OAR1_ADDMODE ) ;
		   temp |= ( pI2Cxx->I2C_Config.I2C_DeviceAddress << 1 ) ;
			 temp |= ( 1 << 14 ) ;																										//according to RTM 14th bit should be set
		}
		pI2Cxx->pI2Cx->OAR1 |= temp ;

		//4. Configuring I2C Clock control register (I2C_CCR)
		temp = 0 ;
	  uint16_t ccr_value = 0 ;
		if ( pI2Cxx->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM  )
		{
				temp &= ~( 1 << I2C_CCR_FS );
				ccr_value = RCC_GetPCLK1Value () / ( 2 * pI2Cxx->I2C_Config.I2C_SCLSpeed ) ;
				temp |= ( ccr_value & 0xFFFF ) ;									//ccr_value is of 16 bits but we want only 12 bits
		}
		else
		{
				temp |= ( 1 << I2C_CCR_FS );
				temp |= ( pI2Cxx->I2C_Config.I2C_FMDutyCycle << I2C_CCR_DUTY ) ;
				if ( pI2Cxx->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2 )
				{
						ccr_value = RCC_GetPCLK1Value() / ( 3 * pI2Cxx->I2C_Config.I2C_SCLSpeed );
				}
				else
				{
						ccr_value = RCC_GetPCLK1Value() / ( 25 * pI2Cxx->I2C_Config.I2C_SCLSpeed ) ;
				}
				temp |= ( ccr_value & 0xFFF ) ;
		}
		pI2Cxx->pI2Cx->CCR |= temp ;



		//Configuring Clock Frequency
	  pI2Cxx->pI2Cx->CR2 |= ( pI2Cxx->I2C_Config.I2C_SCLSpeed << 5 ) ;
 }


 /*********************************************************************
 * @fn      				  - I2C1_Deinit
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

  void I2C1_Deinit ( I2C_RegDef_t * pI2Cx )
	{
			if ( pI2Cx == I2C1 )
		{
				RCC->APB1RSTR |= ( 1 << 21 );
				RCC->APB1RSTR &= ~( 1 << 21 );
		}
		else if ( pI2Cx == I2C2 )
		{
				RCC->APB1RSTR |= ( 1 << 22 );
				RCC->APB1RSTR &= ~( 1 << 22 );
		}
		else if ( pI2Cx == I2C3 )
		{
				RCC->APB1RSTR |= ( 1 << 23 );
				RCC->APB1RSTR &= ~( 1 << 23 );
		}
	}


	 /*********************************************************************
 * @fn      				  - I2C_PeripheralControl
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

	void I2C_PeripheralControl ( I2C_RegDef_t * pI2Cx, uint8_t EnorDi )
	{
			if ( EnorDi == ENABLE )
			{
					pI2Cx->CR1 |= ( 1 << I2C_CR1_PE );
			}
			else
			{
					pI2Cx->CR1 &= ~( 1 << I2C_CR1_PE );
			}
	}







  /*********************************************************************
 * @fn      				  - I2C_GetFlagStatus
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

 uint8_t I2C_GetFlagStatus ( I2C_RegDef_t * pI2Cx, uint32_t flagName )								//Flagname is the masking detail of that particular flag, eg. ( 1 << 1 ) for TX flag
 {
	 if ( pI2Cx->SR1 & flagName )																		//if this is true then it means that, that particular flag is set.
	 {

			return FLAG_SET;
	 }
		return FLAG_RESET;
 }

  /*********************************************************************
 * @fn      				  - I2C_MasterSendData
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

 void I2C_MasterSendData ( I2C_RegDef_t * pI2Cxx, uint8_t * Txbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr )
 {
		// 1. Generate Start Condition
		I2C_GenerateStartCondition ( pI2Cxx  );

		// 2. Confirm that start generation is completed by checking the SB flag in the SR1. This has to be done because SB takes some time to be 1.
		// Note: if we will not check the SB bit for 1, then data can be lost because SCL is pulled to 0 untill SB=1, thats why checking SB bit and halting execution until SB = 1 is important.
		//Note: Until SB is cleared SCL will be stretched (ie pulled to LOW)

	  while ( !I2C_GetFlagStatus ( pI2Cxx, I2C_SB_FLAG ) );					//execution will be stoped here until fxn returns 1, ie SB is generated successfully.
		//Note: for clearing the SB bit we have read SR1 and will write to DR in Address Phase, so SB bit will be cleared

	  // 3. Send the address of the slave with R/nW bit set to w(0) ( total 8 bits ), this will be send by writing Address to Data Register.
		I2C_ExecuteAddressPhaseWrite ( pI2Cxx, SlaveAddr );										//Address Phase is all about sending Slave Address or Writing Slave Address to Data Register.

		// 4. Confirm that address phase is completed by checking the ADDR Flag in SR1, if not completed then wait for it to complete.
		while ( !I2C_GetFlagStatus ( pI2Cxx, I2C_ADDR_FLAG ) );

		// 5. Clear the ADDR flag according to its software sequence
		// Note: Until ADDR is not cleared SCL will be stretched ( pull to low ) thats why checking ADDR and halting execution until SB=1 is important.
		I2C_ClearADDRFlag ( pI2Cxx );

		// 6. Send Data until length becomes zero
	 while ( Len > 0 )
	 {
			while ( !I2C_GetFlagStatus ( pI2Cxx, I2C_TxE_FLAG ) );				//checking wheather Data Register is empty or not.
			pI2Cxx->DR = * Txbuffer;
			Txbuffer ++;
			Len --;
	 }

	 // 7. When Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition.
	 // Note: TxE=1, BTF=1, means that both SR and DR are empty and next transmission should begin
	 // when BTF=1, SCL will be stretched (pulled to LOW)
	 while ( !I2C_GetFlagStatus ( pI2Cxx, I2C_TxE_FLAG ) );
	 while ( I2C_GetFlagStatus ( pI2Cxx, I2C_BTF_FLAG ) );


	 //	8. Generate STOP condition and master need not to wait for the completion of stop condition.
	 // Note: generating STOP, automatically clears the BTF

	 if ( Sr == I2C_DISABLE_SR )
	 {
		 I2C_GenerateStopCondition(pI2Cxx);
	 }

 }


  /*********************************************************************
 * @fn      				  - I2C_MasterReceiveData
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

 void I2C_MasterReceiveData ( I2C_RegDef_t * pI2Cx, uint8_t * pRxbuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr)
 {
		//1. Generating the Start Condition
		 I2C_GenerateStartCondition ( pI2Cx );

	  //2. Confirming that start condition is generated.
		// Note: Until SB is not cleared, SCL will be stretched (pulled to low).
	   while ( !I2C_GetFlagStatus ( pI2Cx, I2C_SB_FLAG ) );

		//3. Send the address of the slave with R/nW bit set to R(1), (total 8 bits).
		 I2C_ExecuteAddressPhaseRead ( pI2Cx, SlaveAddr );

		//4. Wait until Slave Address is not matched or Address Phase is not completed.
		 while ( !I2C_GetFlagStatus ( pI2Cx, I2C_ADDR_FLAG ) );

		//procedure to read only 1 byte from slave
		if ( Len == 1 )
		{
				//Disabling ACKing
				I2C_ManageAcking ( pI2Cx, I2C_ACK_DISABLE );

				//Clearing the ADDR flag
				I2C_ClearADDRFlag ( pI2Cx );

				//waiting for Data Register (Receive DR) to be empty,
				// ie waiting for RxNE to become 1
				while ( !I2C_GetFlagStatus ( pI2Cx, I2C_RxNE_FLAG ) );

				//generating STOP condition
				if ( Sr == I2C_DISABLE_SR )
				{
						I2C_GenerateStopCondition ( pI2Cx );
				}
				//read data in to buffer
				*pRxbuffer = pI2Cx->DR;

				//re-enabling of ACK
				I2C_ManageAcking ( pI2Cx, I2C_ACK_ENABLE );
				return;
		}
		else
		{
				//clearing the ADDR Flag
				I2C_ClearADDRFlag ( pI2Cx );

				//reading the data utnil Len becomes zero
				while ( Len > 0 )
				{
						//waiting for Data Register (Receive DR) to be empty,
						// ie waiting for RxNE to become 1
						while ( !I2C_GetFlagStatus ( pI2Cx, I2C_RxNE_FLAG ) );

						if ( Len == 2 )
						{
								//clearing the ACK bit
								I2C_ManageAcking ( pI2Cx, I2C_ACK_DISABLE );

								//generating the STOP condition.
								if ( Sr == I2C_DISABLE_SR )
								{
									I2C_GenerateStopCondition ( pI2Cx );
								}
						}
						//reading the data from data register into buffer
						*pRxbuffer = pI2Cx->DR;

						//incrementing the buffer address
						pRxbuffer ++;
						Len--;
				}
		}
		//re-enable ACKing
		I2C_ManageAcking ( pI2Cx, I2C_ACK_ENABLE );

 }

 /*********************************************************************
* @fn      				  - I2C_MasterReceiveData
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


 void I2C_ManageAcking ( I2C_RegDef_t * pI2Cx, uint8_t ENorDi )
  {
 		if ( ENorDi == I2C_ACK_ENABLE )
 		{
 			pI2Cx->CR1 |= ( 1 << I2C_CR1_ACK );
 		}
 		else
 		{
 				pI2Cx->CR1 &= ~( 1 << I2C_CR1_ACK );
 		}
  }


