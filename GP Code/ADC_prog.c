#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"

#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"

static uint16* ADC_pu16Result = NULL;
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;

static ADC_Chain_t* ADC_pChainData = NULL;

static uint8 ADC_u8BusyFlag = IDLE;

static uint8 ADC_u8ISRSource;

void ADC_voidInit(void)
{
	/*Set AVCC as a reference voltage*/
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	/*Select left adjust or right adjust according to resolution configurations*/
#if ADC_u8Resolution == EIGHT_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_u8Resolution == TEN_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
#error Wrong ADC_u8Resolution configuration option
#endif


	/*Disable Auto trigger mode*/
	CLR_BIT(ADCSRA, ADCSRA_ADATE);

	/*Disable interrupt*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/*Enable ADC*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

	/*Configure the prescaler division factor*/
	ADCSRA &= PRESCALER_BIT_MASK;										/*Clear the prescaler bits*/
	ADCSRA |= ADC_u8PRESCALER_DIVISION_FACTOR << PRESCALER_BIT_POS;
}

uint8 ADC_u8StartSingleConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result)
{
	uint8 Local_u8ErrorState = OK;
	uint32 Local_u32Counter = 0u;

	if(Copy_pu16Result != NULL)
	{
		/*Check if ADC is IDLE*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Set the input channel*/
			ADMUX &= CHANNEL_BIT_MASK; 											/*Clear the channel selections bits*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Polling (with blocking) on the conversion complete on condition that timeout is not passed yet*/
			while(((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0u) && (Local_u32Counter < ADC_u32TIMEOUT))
			{
				Local_u32Counter++;
			}

			if(Local_u32Counter == ADC_u32TIMEOUT)
			{
				/*Timeout has passed without the flag being raised*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else
			{
				/*Flag is raised before Timeout*/
				/*Clear the conversion complete flag*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);

				/*Get the conversion result*/
#if ADC_u8Resolution == EIGHT_BITS
				*Copy_pu16Result = ADCH;
#elif ADC_u8Resolution == TEN_BITS
				*Copy_pu16Result = ADC;
#endif
			}

			/*ADC is now IDLE*/
			ADC_u8BusyFlag = IDLE;
		}
		else
		{
			/*ADC is busy, update error state*/
			Local_u8ErrorState = BUSY_ERR;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result, void(*Copy_pvNotificationFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		/*Check if ADC is IDLE*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Convert the local ADC result into global*/
			ADC_pu16Result = Copy_pu16Result;

			/*Convert the local ADC call back into global*/
			ADC_pvCallBackNotificationFunc = Copy_pvNotificationFunc;

			/*Set the input channel*/
			ADMUX &= CHANNEL_BIT_MASK; 											/*Clear the channel selections bits*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);

			/*ISR Source is Single Conversion Asynch*/
			ADC_u8ISRSource = SINGLE_ASYNCH;
		}
		else
		{
			/*ADC is busy, update error state*/
			Local_u8ErrorState = BUSY_ERR;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

uint8 ADC_u8StartChainConversionAsynch(const ADC_Chain_t* Copy_object)
{
	uint8 Local_u8ErrorState = OK;

	if((Copy_object != NULL) && (Copy_object->ChannelArr != NULL) && (Copy_object->ResultArr != NULL) && (Copy_object->NotificationFunc != NULL))
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			/*ADC is now busy*/
			ADC_u8BusyFlag = BUSY;

			/*Define the input chain data globally*/
			ADC_pChainData = Copy_object;

			/*Set the input channel*/
			ADMUX &= CHANNEL_BIT_MASK; 											/*Clear the channel selections bits*/
			ADMUX |= ADC_pChainData->ChannelArr[0];

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Enable ADC conversion complete interrupt*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);

			/*ISR Source is Chain Conversion Asynch*/
			ADC_u8ISRSource = CHAIN_ASYNCH;

		}
		else
		{
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

static void voidHandleSingleConvAsynch(void)
{
	/*ISR comes to complete the work of Start Single Conversion Asynch Function*/
	/*Read the result*/
#if ADC_u8Resolution == EIGHT_BITS
	*ADC_pu16Result = ADCH;
#elif ADC_u8Resolution == TEN_BITS
	*ADC_pu16Result = ADC;
#endif

	/*Disable ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

	/*ADC is now IDLE*/
	ADC_u8BusyFlag = IDLE;

	/*Invoke the call back notification function*/
	if(ADC_pvCallBackNotificationFunc != NULL)
	{
		ADC_pvCallBackNotificationFunc();
	}
	else
	{
		/*Do nothing*/
	}
}

static void voidHandleChainConvAsynch(void)
{
	volatile static uint8 Local_u8ChannelIndex = 0u;

	/*ISR comes to complete the work of Start Chain Conversion Asynch Function*/
#if ADC_u8Resolution == EIGHT_BITS
	ADC_pChainData->ResultArr[Local_u8ChannelIndex] = ADCH;
#elif ADC_u8Resolution == TEN_BITS
	ADC_pChainData->ResultArr[Local_u8ChannelIndex] = ADC;
#endif

	/*Increment the Channel Counter*/
	Local_u8ChannelIndex++;

	if(Local_u8ChannelIndex == ADC_pChainData->ChainSize)
	{
		/*Chain is completed*/

		/*Reset the Channel Index to be prepared for next conversion*/
		Local_u8ChannelIndex = 0;

		/*Disable ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA, ADCSRA_ADIE);

		/*ADC is now IDLE*/
		ADC_u8BusyFlag = IDLE;

		/*Invoke the call back notification function*/
		if(ADC_pChainData->NotificationFunc != NULL)
		{
			ADC_pChainData->NotificationFunc();
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Chain is not finished yet, start the next conversion*/
		/*Set the input channel*/
		ADMUX &= CHANNEL_BIT_MASK; 											/*Clear the channel selections bits*/
		ADMUX |= ADC_pChainData->ChannelArr[Local_u8ChannelIndex];

		/*Start conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);
	}
}

/*ADC conversion complete ISR*/
__attribute__((signal)) void __vector_16 (void);
void __vector_16 (void)
{
	if(ADC_u8ISRSource == SINGLE_ASYNCH)
	{
		voidHandleSingleConvAsynch();
	}

	else if(ADC_u8ISRSource == CHAIN_ASYNCH)
	{
		voidHandleChainConvAsynch();
	}
}
