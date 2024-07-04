#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

/***************/
#include <util\delay.h>
/******************/

#include "USART_interface.h"
#include "USART_cfg.h"
#include "USART_prv.h"
#include "USART_reg.h"

void USART_voidInit(void)
{
	uint8 Local_u8UCSRCValue =0u ;

	/*Receiver and transmitter enable*/
	SET_BIT(UCSRB, UCSRB_RXEN);
	SET_BIT(UCSRB, UCSRB_TXEN);

	/*Character size: 8bits*/
	CLR_BIT(UCSRB, 2);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);

	/*Set register select bit to select UCSRC*/
	SET_BIT(Local_u8UCSRCValue, UCSRC_URSEL);

	/*Write the UCSRC register with bit 7 set*/
	UCSRC = Local_u8UCSRCValue;

	/*Set baud rate to 9600bps with 16MHz oscillator frequency*/
	UBRRL = 103;
}

void USART_voidTransmit(uint8 Copy_u8Data)
{
	/*wait for data register empty flag*/
	while(GET_BIT(UCSRA, UCSRA_UDRE)==0);

	/*Send the data*/
	UDR = Copy_u8Data;
}

uint8 USART_voidTransmitString(const char* Copy_pchString)
{
	uint8 Local_u8ErrorState = OK;
	if(Copy_pchString != NULL)
	{
		uint8 Local_u8Iterator=0u;
		while(Copy_pchString[Local_u8Iterator] != '\0')
		{
			USART_voidTransmit(Copy_pchString[Local_u8Iterator]);
			Local_u8Iterator++;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 USART_u8Receive(void)
{
	/*wait for receiving data*/
	while((GET_BIT(UCSRA, UCSRA_RXC))==0);

	/*read the data*/
	return UDR;
}
