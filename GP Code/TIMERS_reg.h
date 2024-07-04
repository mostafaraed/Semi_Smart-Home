#ifndef TIMERS_REG_H
#define TIMERS_REG_H
/************************TIMER0 Registers*********************************/
#define TCCR0 			*((volatile uint8*)0x53)   
#define TCCR0_WGM00     6u   /*Waveform Generation Mode*/
#define TCCR0_WGM01     3u

#define TCCR0_CS02      2u    /*Clock Select*/
#define TCCR0_CS01      1u
#define TCCR0_CS00      0u

#define TCCR0_COM01      5u   /*set compare out mode*/
#define TCCR0_COM00      4u


#define TCNT0 			*((volatile uint8*)0x52)

#define OCR0 			*((volatile uint8*)0x5C)


#define TIMSK 			*((volatile uint8*)0x59)
#define TIMSK_TOIE0     0u   /*Timer/Counter0 Overflow Interrupt Enable*/
#define TIMSK_OCIE0     1u
#define TIMSK_TICIE1 	5u
#define TIMSK_TOIE2		6u
#define TIMSK_OCIE2		7u

/************************TIMER1 Registers*********************************/
#define TCCR1A 					*((volatile uint8*)0x4F)
#define TCCR1A_WGM10 			0u
#define TCCR1A_WGM11  			1u
#define TCCR1A_COM1B0 			4u
#define TCCR1A_COM1B1 			5u
#define TCCR1A_COM1A0 			6u
#define TCCR1A_COM1A1 			7u

#define TCCR1B 					*((volatile uint8*)0x4E)
#define TCCR1B_CS10 			0u
#define TCCR1B_CS11 			1u
#define TCCR1B_CS12 			2u
#define TCCR1B_WGM12 			3u
#define TCCR1B_WGM13 			4u
#define TCCR1B_ICES1 			6u
#define TCCR1B_ICNC1 			7u

#define TCNT1L					*((volatile uint8*)0x4C)
#define TCNT1H					*((volatile uint8*)0x4D)
#define TCNT1					*((volatile uint16*)0x4C)

#define OCR1AL					*((volatile uint8*)0x4A)
#define OCR1AH					*((volatile uint8*)0x4B)
#define OCR1A					*((volatile uint16*)0x4A)

#define OCR1BL					*((volatile uint8*)0x48)
#define OCR1BH					*((volatile uint8*)0x49)
#define OCR1B					*((volatile uint16*)0x48)

#define ICR1L					*((volatile uint8*)0x46)
#define ICR1H					*((volatile uint8*)0x47)
#define ICR1					*((volatile uint16*)0x46)

/************************TIMER2 Registers*********************************/
#define TCCR2					*((volatile uint8*)0x45)
#define TCCR2_CS20				0u
#define TCCR2_CS21				1u
#define TCCR2_CS22				2u
#define TCCR2_WGM21				3u
#define TCCR2_COM20				4u
#define TCCR2_COM21				5u
#define TCCR2_WGM20				6u

#define OCR2					*((volatile uint8*)0x43)


#endif
