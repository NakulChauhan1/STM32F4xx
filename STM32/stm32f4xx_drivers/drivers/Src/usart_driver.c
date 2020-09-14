
#include "usart_driver.h"

/*********************************************************************
 * @fn      		  		- USART_Init
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

void USART_Init (	USART_Handle_t *pUSARTHandle	)
{
		uint32_t temp = 0;

	/******************************** Configuration of CR1******************************************/

		// USART Clock enable
		USART_PeriClockControl ( pUSARTHandle->pUSARTx, ENABLE );

		//USART Mode
		if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX_ONLY )
		{
				temp |= ( 1 << USART_CR1_TE );
		}
		else if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_RX_ONLY )
		{
				temp |= ( 1 << USART_CR1_RE );
		}
		else if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX_ONLY )
		{
				temp |= ( 1 << USART_CR1_RE ) | ( 1 << USART_CR1_TE );
		}

		//USART Word Length
		if ( pUSARTHandle->USART_Config.USART_WorldLength == USART_WORDLEN_8BITS )
		{
				temp &= ~( 1 << USART_CR1_M );
		}
		else if ( pUSARTHandle->USART_Config.USART_WorldLength == USART_WORDLEN_9BITS )
		{
				temp |= ( 1 << USART_CR1_M );
		}

		//USART Parity Control
		temp |= ( 1 << USART_CR1_PCE );									//Parity Enable
		temp |= ( pUSARTHandle->USART_Config.USART_ParityControl << USART_CR1_PS );


		//Programming CR1 register
		pUSARTHandle->pUSARTx->CR1 |= temp;

		/******************************** Configuration of CR2******************************************/

		temp = 0;

		//configuring the number of stop bits inserted during USART frame transmission
		temp |= ( pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP ) ;

		//Programming the CR2 register
		pUSARTHandle->pUSARTx->CR2 |= temp;

		/******************************** Configuration of CR3******************************************/

		temp = 0;

		if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS )
		{
				temp |= ( 1 << USART_CR3_RTSE );
		}
		else if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS )
		{
				temp |= ( 1 << USART_CR3_CTSE );
		}
		else if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS )
		{
				temp |= ( 1 << USART_CR3_CTSE );
				temp |= ( 1 << USART_CR3_RTSE );
		}

		//Programming the CR3 register
		pUSARTHandle->pUSARTx->CR3 |= temp;

	/******************************** Configuration of BRR(Baudrate register)******************************************/
	USART_SetBaudRate();
}


/*********************************************************************
 * @fn      		  		- USART_DeInit
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

void USART_DeInit ( USART_RegDef_t * pUSARTx )
{
		if ( EnorDi == ENABLE )
		{
				if ( pUSARTx == USART1 )
				{
						RCC->APB2ENR |= ( 1 << 4 );
				}
				else if ( pUSARTx == USART2 )
				{
						RCC->APB1ENR |= ( 1 << 17 );
				}
				else if ( pUSARTx == USART3 )
				{
						RCC->APB1ENR |= ( 1 << 18 );
				}
						else if ( pUSARTx == UART4 )
				{
						RCC->APB1ENR |= ( 1 << 19 );
				}
				else if ( pUSARTx == UART5 )
				{
						RCC->APB1ENR |= ( 1 << 20 );
				}
				else if ( pUSARTx == USART6 )
				{
						RCC->APB2ENR |= ( 1 << 5 );
				}
		}
		else
		{
				if ( pUSARTx == USART1 )
				{
						USART1_PCLK_DI();
				}
				else if ( pUSARTx == USART2 )
				{
						USART2_PCLK_DI();
				}
				else if ( pUSARTx == USART3 )
				{
						USART3_PCLK_DI();
				}
						else if ( pUSARTx == UART4 )
				{
						UART4_PCLK_DI();
				}
				else if ( pUSARTx == UART5 )
				{
						UART5_PCLK_DI();
				}
				else if ( pUSARTx == USART6 )
				{
						USART6_PCLK_DI();
				}
		}
}


/*********************************************************************
 * @fn      		  		- USART_PeriClockControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *SZZZZ
 * @Note              -

 */

void USART_PeriClockControl ( USART_RegDef_t * pUSARTx, uint8_t EnorDi )
{
		if ( pUSARTx == USART1 )
		{
				RCC->APB2RSTR |= ( 1 << 4 );
				RCC->APB2RSTR &= ~( 1 << 4 );
		}
		else if ( pUSARTx == USART2 )
		{
				RCC->APB1RSTR |= ( 1 << 17 );
   			RCC->APB1RSTR &= ~( 1 << 17 );
		}
		else if ( pUSARTx == USART3 )
		{
				RCC->APB1RSTR |= ( 1 << 18 );
				RCC->APB1RSTR &= ~( 1 << 18 );
		}
		else if ( pUSARTx == UART4 )
		{
				RCC->APB1RSTR |= ( 1 << 19 );
				RCC->APB1RSTR &= ~( 1 << 19 );
		}
		else if ( pUSARTx == UART5 )
		{
				RCC->APB1RSTR |= ( 1 << 20 );
				RCC->APB1RSTR &= ~( 1 << 20 );
		}
		else if ( pUSARTx == USART6 )
		{
				RCC->APB2RSTR |= ( 1 << 5 );
			  RCC->APB2RSTR &= ~( 1 << 5 );
		}
}

/*********************************************************************
 * @fn      		  		- USART_Init
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


