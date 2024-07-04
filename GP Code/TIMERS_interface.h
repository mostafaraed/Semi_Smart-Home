#ifndef TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H

typedef enum
{
	FALLING_EDGE, RISING_EDGE
}SenseCtrl_t;

void Timer0_voidInit(void);
void Timer0_voidSetPerloadValue(uint8 Copy_u8PreloadVal);
void Timer0_voidCompareMatchValue(uint8 Copy_u8CompMatchVal);
void Timer0_voidDisableOverflowInterrupt(void);
void Timer0_voidDisableCompareMatchInterrupt(void);
void Timer0_voidChangeMode(uint8 Copy_u8Mode);

void Timer1_voidInit(void);
uint16 Timer1_u16GetTimervalue(void);
uint16 Timer1_u16GetICR1value(void);
void Timer1_voidSetvalue(uint16 Copy_u16Value);
void Timer1_voidSetCompvalue(uint16 Copy_u16Value);
void Timer1_voidChangeMode(uint8 Copy_u8Mode);
uint8 Timer1_ICU_u8SetSenseCtrl(SenseCtrl_t Copy_SenseCtrl);

void Timer2_voidInit(void);
void Timer2_voidCompareMatchValue(uint8 Copy_u8CompMatchVal);
void Timer2_voidDisableOverflowInterrupt(void);

uint8 Timer_u8SetCallBack(uint8 Copu_u8IntSourse, void(*Copy_pvCallBackFunc)(void));


#define TIMER0_OVF_INT       		0u
#define TIMER0_OC_INT        		1u
#define TIMER1_ICU_INT 		 		2u
#define TIMER2_OVF_INT       		3u

#define TIMER0_NORMAL_MODE			0u
#define TIMER0_FastPWM_MODE			1u

#define TIMER1_FastPWM14_MODE		0u
#define TIMER1_ICU_MODE				1u

#endif
