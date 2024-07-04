#include "STD_TYPES.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "TIMERS_interface.h"
#include "TIMERS_reg.h"
#include "TIMERS_cfg.h"
#include "TIMERS_prv.h"

static void (*Timer_pvCallBackFunc[8])(void)= {NULL};

void Timer0_voidInit(void)
{
	/*Set Normal mode*/
	CLR_BIT(TCCR0, TCCR0_WGM00);
	CLR_BIT(TCCR0, TCCR0_WGM01);

	/*Set compare out mode, Normal*/
	CLR_BIT(TCCR0, TCCR0_COM00);
	CLR_BIT(TCCR0, TCCR0_COM01);

	/*Clear Prescaler bits*/
	TCCR0 &=0b11111000;

	/*Set Prescelar divide by 1024*/
	TCCR0 |=0b101;

	/*Enable overflow interrupt*/
	SET_BIT(TIMSK, TIMSK_TOIE0);
}

void Timer1_voidInit(void)
{
	/*Set Fast PWM  mode 14*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*set compare match event Clear OC1A/OC1B on compare match, set OC1A/OC1B at TOP*/
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);

	/*set top value*/
	ICR1 = 40000u ;

	/*CLR prescaler bits*/
	TCCR1B &= 0b11111000;

	/*Set prescaler div factor 8*/
	TCCR1B |= 0b10;
}

void Timer2_voidInit(void)
{
	/*Set Normal mode*/
	CLR_BIT(TCCR2,TCCR2_WGM20);
	CLR_BIT(TCCR2,TCCR2_WGM21);

	/*Set Compare output mode, Normal*/
	CLR_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);

	/*CLR prescaler bits*/
	TCCR2 &= 0b11111000;

	/*Set Prescelar divide by 32*/
	TCCR2 |= 0b11;

	/*Enable overflow interrupt*/
	SET_BIT(TIMSK, TIMSK_TOIE2);
}

void Timer0_voidSetPerloadValue(uint8 Copy_u8PreloadVal)
{
	TCNT0=Copy_u8PreloadVal;
}

void Timer0_voidCompareMatchValue(uint8 Copy_u8CompMatchVal)
{
	OCR0=Copy_u8CompMatchVal;
}

void Timer0_voidDisableOverflowInterrupt(void)
{
	/*Disable overflow interrupt*/
	CLR_BIT(TIMSK, TIMSK_TOIE0);
}

void Timer0_voidDisableCompareMatchInterrupt(void)
{
	/*Disable Compare Match interrupt*/
	CLR_BIT(TIMSK, TIMSK_OCIE0);
}

void Timer0_voidChangeMode(uint8 Copy_u8Mode)
{
	switch(Copy_u8Mode)
	{
	case(TIMER0_NORMAL_MODE):
			{
		/*Set Normal mode*/
		CLR_BIT(TCCR0, TCCR0_WGM00);
		CLR_BIT(TCCR0, TCCR0_WGM01);

		/*Set compare out mode, Normal*/
		CLR_BIT(TCCR0, TCCR0_COM00);
		CLR_BIT(TCCR0, TCCR0_COM01);

		/*Clear Prescaler bits*/
		TCCR0 &=0b11111000;

		/*Set Prescelar divide by 1024*/
		TCCR0 |=0b101;

		/*Enable overflow interrupt*/
		SET_BIT(TIMSK, TIMSK_TOIE0);

		break;
			}
	case(TIMER0_FastPWM_MODE):
			{
		/*Set Fast PWM mode*/
		SET_BIT(TCCR0, TCCR0_WGM00);
		SET_BIT(TCCR0, TCCR0_WGM01);

		/*Set compare out mode, Set on TOP & Clear on Compare*/
		CLR_BIT(TCCR0, TCCR0_COM00);
		SET_BIT(TCCR0, TCCR0_COM01);

		/*Clear Prescaler bits*/
		TCCR0 &=0b11111000;

		/*Set Prescelar divide by 64*/
		TCCR0 |=0b11;

		/*Enable Compare Match interrupt*/
		SET_BIT(TIMSK, TIMSK_OCIE0);

		break;
			}
	default:	break;
	}
}

uint16 Timer1_u16GetTimervalue(void)
{
	return TCNT1;
}

uint16 Timer1_u16GetICR1value(void)
{
	return ICR1;
}

void Timer1_voidSetvalue(uint16 Copy_u16Value)
{
	TCNT1= Copy_u16Value;
}

void Timer1_voidSetCompvalue(uint16 Copy_u16Value)
{
	OCR1A= Copy_u16Value;
	OCR1B= Copy_u16Value;
}

uint8 Timer1_ICU_u8SetSenseCtrl(SenseCtrl_t Copy_SenseCtrl)
{
	uint8 Local_u8ErrorState = OK;

	switch(Copy_SenseCtrl)
	{
	case FALLING_EDGE: CLR_BIT(TCCR1B, TCCR1B_ICES1); break;
	case RISING_EDGE:  SET_BIT(TCCR1B, TCCR1B_ICES1); break;
	default:		   Local_u8ErrorState = NOK; break;
	}

	return Local_u8ErrorState;
}

void Timer1_voidChangeMode(uint8 Copy_u8Mode)
{
	switch(Copy_u8Mode)
	{
	case(TIMER1_FastPWM14_MODE):
			{
		/*Set Fast PWM  mode 14*/
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);

		/*set compare match event Clear OC1A/OC1B on compare match, set OC1A/OC1B at TOP*/
		CLR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLR_BIT(TCCR1A,TCCR1A_COM1B0);
		SET_BIT(TCCR1A,TCCR1A_COM1A1);
		SET_BIT(TCCR1A,TCCR1A_COM1B1);

		/*set top value*/
		ICR1 = 40000u ;

		/*CLR prescaler bits*/
		TCCR1B &= 0b11111000;

		/*Set prescaler div factor 8*/
		TCCR1B |= 0b10;

		break;
			}
	case(TIMER1_ICU_MODE):
			{
		/*Set Normal mode*/
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);

		/*set compare match mode, Normal*/
		CLR_BIT(TCCR1A,TCCR1A_COM1A0);
		CLR_BIT(TCCR1A,TCCR1A_COM1B0);
		CLR_BIT(TCCR1A,TCCR1A_COM1A1);
		CLR_BIT(TCCR1A,TCCR1A_COM1B1);

		/*Set Input Capture Noise Canceler*/
		SET_BIT(TCCR1B,TCCR1B_ICNC1);

		/*Set the Input Capture Edge, Rising Edge*/
		SET_BIT(TCCR1B,TCCR1B_ICES1);

		/*CLR prescaler bits*/
		TCCR1B &= 0b11111000;

		/*Set Prescelar = 1*/
		TCCR1B |= 0b11;

		/*Enable Input Capture Interrupt*/
		SET_BIT(TIMSK,TIMSK_TICIE1);

		break;
			}
	default:	break;
	}
}

void Timer2_voidCompareMatchValue(uint8 Copy_u8CompMatchVal)
{
	OCR2 = Copy_u8CompMatchVal;
}

void Timer2_voidDisableOverflowInterrupt(void)
{
	/*Disable overflow interrupt*/
	CLR_BIT(TIMSK, TIMSK_TOIE2);
}

uint8 Timer_u8SetCallBack(uint8 Copu_u8IntSourse, void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_pvCallBackFunc!=NULL)
	{
		Timer_pvCallBackFunc[Copu_u8IntSourse]=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


/*Timer0 overflow ISR*/
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if(Timer_pvCallBackFunc[TIMER0_OVF_INT]!=NULL)
	{
		Timer_pvCallBackFunc[TIMER0_OVF_INT]();
	}
}

/*Timer0 Compare match ISR*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(Timer_pvCallBackFunc[TIMER0_OC_INT]!=NULL)
	{
		Timer_pvCallBackFunc[TIMER0_OC_INT]();
	}
}

/*Timer1 ICU ISR*/
void __vector_6(void) __attribute__((signal));

void __vector_6(void)
{
	if(Timer_pvCallBackFunc[TIMER1_ICU_INT]!=NULL)
	{
		Timer_pvCallBackFunc[TIMER1_ICU_INT]();
	}
}

/*Timer2 overflow ISR*/
void __vector_5(void) __attribute__((signal));

void __vector_5(void)
{
	if(Timer_pvCallBackFunc[TIMER2_OVF_INT]!=NULL)
	{
		Timer_pvCallBackFunc[TIMER2_OVF_INT]();
	}
}
