/*
 * sensorControl.c
 * Control for an Arduino alarm system.
 * Included here will be:
 * - State machine for the states of the program
 * - Reading of IR-signal
 * - Reading the signal from ultrasonic sensor
 * - The buzzer
 * - Remote controls
 * - Communications with the Arduino Mega that will control the LCD to show the alarm system states.
 * Created: 9.3.2023 7.06.06
 * Author : lassi
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"

#define COM_CONNECT 0
#define MOVEMENT_DETECT 1
#define PASSW_NOTGIVEN 2
#define PASSW_GIVEN 3
#define INCORRECT_PASSW 4

volatile int8_t g_STATE = 0;


void pulse()
{
	PORTB |= (1 << PB1);
	_delay_us(10);
	PORTB &= ~(1 << PB1);
}

int16_t distanceCalc()
{
	while (!(PIND & (1 << PD4)));
	
	TCNT1 = 0;
	
	while(PIND & (1 << PD4));
	
	int16_t pulseWidth = TCNT1;
	int16_t duration = pulseWidth * (1.0 / F_CPU);
	
	int16_t distance = (duration * 343) / 2;
	return distance;
}


int main(void)
{
	DDRB |= (1 << PB1); // ultrasonic trigger
	DDRB |= (1 << PB0); // passive buzzer
	DDRD &= ~(1 << PD5); // IR-receiver
	DDRD &= ~(1 << PD4); // ultrasonic echo
	
	// declare values for the inputs for trigger and IR-receiver
    //int8_t g_IR_receiver = 0;
	//int8_t g_us_echo = 0;
	int16_t distance = 0;
    while (1) //TODO: signal goes through, voice works.
    {
		pulse();
		distance = distanceCalc();
		if (distance < 2000)
		{
			PORTB |= (1 << PB0);
		}
		else
		{
			PORTB &= ~(1 << PB0);
		}
		
		switch (g_STATE) {
			case COM_CONNECT:
				
			break;
			case MOVEMENT_DETECT:
				
			break;
			case PASSW_NOTGIVEN:
			
			break;
			case PASSW_GIVEN:
				
			break;
			case INCORRECT_PASSW:
			
			break;
		}
			
    }
	
}

