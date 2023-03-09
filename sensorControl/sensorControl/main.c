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

#include <avr/io.h>
#include <util/delay.h>
#include <keypad.h>

#define COM_CONNECT 0
#define MOVEMENT_DETECT 1
#define PASSW_NOTGIVEN 2
#define PASSW_GIVEN 3
#define INCORRECT_PASSW 4

volatile int8_t g_STATE = 0;

int main(void)
{
	DDRB |= (1 << PB1); // ultrasonic echo
	DDRB |= (1 << PB0); // passive buzzer
	DDRD &= ~(1 << PD5); // IR-receiver
	DDRD &= ~(1 << PD4); // ultrasonic trigger
    
    while (1) 
    {
		
		switch (g_STATE) {
			case COM_CONNECT:
				
			case MOVEMENT_DETECT:
				
			case PASSW_NOTGIVEN:
			
			case PASSW_GIVEN:
			
			case INCORRECT_PASSW:
			
    }
}

