#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "USART_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include "TIMERS_interface.h"

#define START_INDEX			0u			//The start index for ID and Password; To get 4 digits
#define END_INDEX			4u			//The end index for ID and Password; To get 4 digits
#define PASS_TRIALS			4u			//The maximum trials for Password
#define ARR_SIZE			4u			//The array size for the ID and Password; To get 4 digits
#define SIZE_MINUS_ONE		3u			//To invert the ID Array

void voidReceiveFromOVINT(void);		//LDR
void voidReceiveFromOCINT(void); 		//LM35
void voidPIND2_TOGGLE(void);			//Ultrasonic
void ICR1_READ(void);					//Ultrasonic

uint8 u8ReceivedOption;
uint16 u16Reading1, u16Reading2;

void main(void)
{
	PORT_voidInit();
	USART_voidInit();
	ADC_voidInit();
	Timer1_voidInit();

	USART_voidTransmitString("WELCOME TO MY SMART HOME\n");

	/*ID Setup*/
	USART_voidTransmitString("Enter ID\n");
	uint8 Local_u8ReceivedID[ARR_SIZE] = {0};
	for(uint8 Local_u8IDCounter = START_INDEX; Local_u8IDCounter < END_INDEX; Local_u8IDCounter++)
	{
		Local_u8ReceivedID[Local_u8IDCounter] = USART_u8Receive();
	}


	/*Password Setup*/
	USART_voidTransmitString("Enter Password\n");
	uint8 Local_u8ReceivedPass[ARR_SIZE] = {0}, Local_u8PassTrials = 1u, Local_u8CorrectPassFlag = 0;
	while(Local_u8PassTrials < PASS_TRIALS)
	{
		for(uint8 Local_u8PassCounter = START_INDEX; Local_u8PassCounter < END_INDEX; Local_u8PassCounter++)
		{
			Local_u8ReceivedPass[Local_u8PassCounter] = USART_u8Receive();
		}

		for(uint8 Local_u8Counter = START_INDEX; Local_u8Counter < END_INDEX; Local_u8Counter++)
		{
			if(Local_u8ReceivedPass[Local_u8Counter] != Local_u8ReceivedID[(SIZE_MINUS_ONE - Local_u8Counter)])
			{
				USART_voidTransmitString("Wrong Password, Try again\n");
				Local_u8PassTrials++;
				Local_u8CorrectPassFlag = 0;
				break;
			}
			else
			{
				Local_u8CorrectPassFlag = 1;
			}
		}
		if(Local_u8CorrectPassFlag == 1)
		{
			break;
		}
	}
	if(Local_u8PassTrials == PASS_TRIALS)
	{
		USART_voidTransmitString("SYSTEM CLOSED\n");
		while(Local_u8PassTrials == PASS_TRIALS);
	}

	/*Sending the menu to choose an option*/
	USART_voidTransmitString("Please choose an option from the menu:\n0-Play music\n1-Turn on light\n2-Turn off light\n3-Open the door\n4-Close the door\n5-Open the fan\n6-Close the fan\n7-Control fan speed by temperature\n8-Control fan speed by hand\n9-Control Light Intensity\n");


	while(1)
	{
		u8ReceivedOption = USART_u8Receive();

		if(u8ReceivedOption == '0') //Play music
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(200);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(400);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(600);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(1000);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(1500);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(1000);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(800);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(500);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(200);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(50);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(20);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
			_delay_ms(5);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
			USART_voidTransmitString("Send another option\n");
		}
		else if(u8ReceivedOption == '1') //Turn on LEDs
		{
			USART_voidTransmitString("Lights are on\n");
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
			USART_voidTransmitString("Send another option\n");
		}
		else if(u8ReceivedOption == '2') //Turn off LEDs
		{
			USART_voidTransmitString("Lights are off\n");
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
			USART_voidTransmitString("Send another option\n");
		}
		else if(u8ReceivedOption == '3') //Turn on Servomotor
		{
			USART_voidTransmitString("Door is opened\n");
			Timer1_voidSetCompvalue(5300u);
			USART_voidTransmitString("Send another option\n");
		}
		else if(u8ReceivedOption == '4') //Turn off Servomotor
		{
			USART_voidTransmitString("Door is closed\n");
			Timer1_voidSetCompvalue(600u);
			USART_voidTransmitString("Send another option\n");
		}
		else if(u8ReceivedOption == '5') //Turn on DC Motor
		{
			USART_voidTransmitString("Fan is opened\n");
			DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_HIGH);
			USART_voidTransmitString("Send another option\n");
		}
		else if(u8ReceivedOption == '6') //Turn off DC Motor
		{
			USART_voidTransmitString("Fan is closed\n");
			DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN3,DIO_u8PIN_LOW);
			USART_voidTransmitString("Send another option\n");
		}


		uint8 Local_u8OnlyOneTimeFlag = 1u; //To make the instructions one time only inside the while loop

		while(u8ReceivedOption == '7') //Control DC motor speed by LM35
		{
			if(Local_u8OnlyOneTimeFlag == 1u)
			{
				USART_voidTransmitString("Fan Speed Temperature Control\n");
				Timer0_voidChangeMode(TIMER0_FastPWM_MODE);
				GIE_voidEnableGlobal();
				Timer_u8SetCallBack(TIMER0_OC_INT,&voidReceiveFromOCINT);
				Local_u8OnlyOneTimeFlag = 0u;
			}
			uint16 ADC_Result;
			ADC_u8StartSingleConversionSynch(7,&ADC_Result);
			uint32 Vout = ((uint32)(((uint32)(ADC_Result * 500UL)) / 256UL));
			Vout = Vout * 3u;
			Timer0_voidCompareMatchValue(Vout);
		}

		/*Disable the global interrupt*/
		GIE_voidDisableGlobal();

		while(u8ReceivedOption == '8') //Control DC motor speed by Ultrasonic
		{
			if(Local_u8OnlyOneTimeFlag == 1u)
			{
				USART_voidTransmitString("Fan Speed Ultrasonic Control\n");
				Timer0_voidChangeMode(TIMER0_FastPWM_MODE);
				Timer1_voidChangeMode(TIMER1_ICU_MODE);
				Timer_u8SetCallBack(TIMER1_ICU_INT,&ICR1_READ);
				Timer2_voidInit();
				Timer_u8SetCallBack(TIMER2_OVF_INT,&voidPIND2_TOGGLE);
				GIE_voidEnableGlobal();
				Local_u8OnlyOneTimeFlag = 0u;
			}
			uint16 Local_u16ReadingResult = u16Reading2 - u16Reading1;
			uint16 Local_u16DistanceResult = ((Local_u16ReadingResult * 119u) / 250u);
			Timer0_voidCompareMatchValue(Local_u16DistanceResult);
		}

		/*Disable the global interrupt*/
		GIE_voidDisableGlobal();

		while(u8ReceivedOption == '9') //LDR Control
		{
			if(Local_u8OnlyOneTimeFlag == 1u)
			{
				USART_voidTransmitString("LDR Control\n");
				Timer0_voidInit();
				GIE_voidEnableGlobal();
				Timer_u8SetCallBack(TIMER0_OVF_INT,&voidReceiveFromOVINT);
				Local_u8OnlyOneTimeFlag = 0u;
			}
			uint16 ADC_Result;
			ADC_u8StartSingleConversionSynch(0,&ADC_Result);
			uint16 Vout = ((uint16)(((uint32)ADC_Result * 5000UL) / 256UL));
			if(Vout < 45u)							//No Light detected, 3 LEDs are open
			{
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
			}
			else if((Vout > 70u) && (Vout < 110u))		//Low Light intensity detected, 2 LEDs only are open
			{
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
			}
			else if((Vout > 140u) && (Vout < 210u))	//High Light intensity detected, 1 LED only is open
			{
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
			}
			else if(Vout > 215u)						//Very high Light intensity detected, No LED is open
			{
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
			}
		}

		/*Disable the global interrupt*/
		GIE_voidDisableGlobal();
	}
}

void voidReceiveFromOVINT(void)
{
	volatile static uint16 Local_u16Counter = 0u;
	Local_u16Counter++;

	if(Local_u16Counter == 915u)  /*Count 15 seconds*/
	{
		USART_voidTransmitString("Send another option\n");
		///Timer0_voidChangeMode(TIMER0_NORMAL_MODE);
		Timer0_voidDisableOverflowInterrupt();
		u8ReceivedOption = 0u;
		Local_u16Counter = 0u;
	}
}

void voidReceiveFromOCINT(void)
{
	volatile static uint16 Local_u16Counter = 0u;
	Local_u16Counter++;

	if(Local_u16Counter == 20000u)
	{
		Timer0_voidDisableCompareMatchInterrupt();
		Timer0_voidChangeMode(TIMER0_NORMAL_MODE);
		USART_voidTransmitString("Send another option\n");
		u8ReceivedOption = 0u;
		Local_u16Counter = 0u;
	}

}

void voidPIND2_TOGGLE(void)
{
	volatile static uint8 Local_u8Counter1 = 0;
	volatile static uint16 Local_u8Counter2 = 0;
	Local_u8Counter1++;

	if(Local_u8Counter1 == 1)
	{
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_LOW);
	}
	else if(Local_u8Counter1 == 2)
	{
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_HIGH);
		Local_u8Counter1 = 0;
		Local_u8Counter2++;
	}

	if(Local_u8Counter2 == 10000u)
	{
		USART_voidTransmitString("Send another option\n");
		Timer0_voidChangeMode(TIMER0_NORMAL_MODE);
		Timer1_voidChangeMode(TIMER1_FastPWM14_MODE);
		Timer2_voidDisableOverflowInterrupt();
		u8ReceivedOption = 0u;
		Local_u8Counter2 = 0u;
	}
}

void ICR1_READ(void)
{
	volatile static uint8 Local_u8Counter = 0;
	Local_u8Counter++;

	if(Local_u8Counter == 1)
	{
		u16Reading1 = Timer1_u16GetICR1value();
		Timer1_ICU_u8SetSenseCtrl(FALLING_EDGE);
	}
	else
	{
		u16Reading2 = Timer1_u16GetICR1value();
		Timer1_ICU_u8SetSenseCtrl(RISING_EDGE);
		Local_u8Counter = 0;
	}
}
