#ifndef ADC_REG_H
#define ADC_REG_H

#define ADMUX				*((volatile uint8*)0x27)
#define ADMUX_REFS1			7u
#define ADMUX_REFS0 		6u
#define ADMUX_ADLAR			5u


#define ADCSRA				*((volatile uint8*)0x26)
#define ADCSRA_ADEN			7u
#define ADCSRA_ADSC			6u
#define ADCSRA_ADATE		5u
#define ADCSRA_ADIF			4u
#define ADCSRA_ADIE			3u

#define ADCH				*((volatile uint8*)0x25)
#define ADCL				*((volatile uint8*)0x24)
#define ADC					*((volatile uint16*)0x24)

#endif