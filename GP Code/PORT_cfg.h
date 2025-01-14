#ifndef PORT_CFG_H
#define PORT_CFG_H

/*Configure the MCU Pins direction, options :  1- INPUT
											   2- OUTPUT		*/
#define PORTA_PIN0_DIR    			INPUT					//LDR Pin
#define PORTA_PIN1_DIR    			INPUT
#define PORTA_PIN2_DIR    			INPUT
#define PORTA_PIN3_DIR    			INPUT
#define PORTA_PIN4_DIR    			INPUT
#define PORTA_PIN5_DIR    			INPUT
#define PORTA_PIN6_DIR    			INPUT
#define PORTA_PIN7_DIR    			INPUT					//LM35 Pin

#define PORTB_PIN0_DIR    			INPUT
#define PORTB_PIN1_DIR    			INPUT
#define PORTB_PIN2_DIR    			INPUT
#define PORTB_PIN3_DIR    			OUTPUT					//DC Motor Pin
#define PORTB_PIN4_DIR    			INPUT
#define PORTB_PIN5_DIR    			INPUT
#define PORTB_PIN6_DIR    			INPUT
#define PORTB_PIN7_DIR    			INPUT

#define PORTC_PIN0_DIR    			OUTPUT					//Red LED Pin
#define PORTC_PIN1_DIR    			OUTPUT					//Green LED Pin
#define PORTC_PIN2_DIR    			OUTPUT					//Blue LED Pin
#define PORTC_PIN3_DIR    			INPUT
#define PORTC_PIN4_DIR    			INPUT
#define PORTC_PIN5_DIR    			OUTPUT					//Buzzer Pin
#define PORTC_PIN6_DIR    			INPUT
#define PORTC_PIN7_DIR    			INPUT

#define PORTD_PIN0_DIR    			INPUT					//RX Pin
#define PORTD_PIN1_DIR    			OUTPUT					//TX Pin
#define PORTD_PIN2_DIR    			OUTPUT					//Trigger Pin for Ultrasonic
#define PORTD_PIN3_DIR    			INPUT
#define PORTD_PIN4_DIR    			OUTPUT					//Servomotor Pin
#define PORTD_PIN5_DIR    			INPUT
#define PORTD_PIN6_DIR    			INPUT					//Echo Pin for Ultrasonic
#define PORTD_PIN7_DIR    			INPUT


/*Configure the MCU pins intitial value, in case of input direction, options:   1- FLOATING
																			    2- PULLED_UP
																				
										, in case of output direction, options: 1- LOW
																				2- HIGH  */
#define PORTA_PIN0_INIT_VAL    			FLOATING
#define PORTA_PIN1_INIT_VAL    			FLOATING
#define PORTA_PIN2_INIT_VAL    			FLOATING
#define PORTA_PIN3_INIT_VAL    			FLOATING
#define PORTA_PIN4_INIT_VAL    			FLOATING
#define PORTA_PIN5_INIT_VAL    			FLOATING
#define PORTA_PIN6_INIT_VAL    			FLOATING
#define PORTA_PIN7_INIT_VAL    			FLOATING

#define PORTB_PIN0_INIT_VAL    			FLOATING
#define PORTB_PIN1_INIT_VAL    			FLOATING
#define PORTB_PIN2_INIT_VAL    			FLOATING
#define PORTB_PIN3_INIT_VAL    			FLOATING
#define PORTB_PIN4_INIT_VAL    			FLOATING
#define PORTB_PIN5_INIT_VAL    			FLOATING
#define PORTB_PIN6_INIT_VAL    			FLOATING
#define PORTB_PIN7_INIT_VAL    			FLOATING

#define PORTC_PIN0_INIT_VAL    			FLOATING
#define PORTC_PIN1_INIT_VAL    			FLOATING
#define PORTC_PIN2_INIT_VAL    			FLOATING
#define PORTC_PIN3_INIT_VAL    			FLOATING
#define PORTC_PIN4_INIT_VAL    			FLOATING
#define PORTC_PIN5_INIT_VAL    			FLOATING
#define PORTC_PIN6_INIT_VAL    			FLOATING
#define PORTC_PIN7_INIT_VAL    			FLOATING

#define PORTD_PIN0_INIT_VAL    			FLOATING
#define PORTD_PIN1_INIT_VAL    			FLOATING
#define PORTD_PIN2_INIT_VAL    			FLOATING
#define PORTD_PIN3_INIT_VAL    			FLOATING
#define PORTD_PIN4_INIT_VAL    			FLOATING
#define PORTD_PIN5_INIT_VAL    			FLOATING
#define PORTD_PIN6_INIT_VAL    			FLOATING
#define PORTD_PIN7_INIT_VAL    			FLOATING

#endif
