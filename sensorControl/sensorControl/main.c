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
#include <avr/interrupt.h>
#include <util/delay.h>
#include "keypad.h"
#include <stdbool.h>

#define WAIT 0
#define MOVEMENT_DETECT 1
#define PASSW_NOTGIVEN 2
#define PASSW_GIVEN 3
#define INCORRECT_PASSW 4

volatile int8_t g_STATE = 0;
int16_t distance = 0;



ISR (TIMER1_COMPA_vect)
{
	TCNT1 = 0;
}


// calculate the top
int calculateTOP(int freq, int prescaler)
{
	long f_clkIO = F_CPU;
	return (f_clkIO) / (2*prescaler*freq);
}

// sounds the buzzer
void soundBuzzer()
{	
	sei();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	
	TCCR1A |= (1 << COM1A0);
	
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM13);
	
	TIMSK1 |= (1 << OCIE1A);
	
	OCR1A = calculateTOP(523, 1);
	
	//while(1)
	TCCR1B |= (1 << CS10);
	PORTB &= ~(1 << PB1);
}

// turns the buzzer of via register manipulation
void offBuzzer()
{
	TCCR1B = 0;
	TCCR1A &= ~(1 << COM1A0);
	PORTB &= ~(1 << PB1);
}

// Sends pulse from ultrasonic sensor and returns the distance
// the sound travels.
// Later on it will compared to the 50cm distance
// to check if something is in the vicinity of the sensor.
int16_t pulse()
{
	//int16_t pulseWidth;
	// Trigger pulse
	PORTB |= (1 << PB0);
	_delay_us(10);
	PORTB &= ~(1 << PB0);
	
	while (!(PIND & (1 << PD4)));
	//TCCR1B |= (1 << CS11);
	uint16_t duration = 0;
	while (PIND & (1 << PD4))
	{
		duration++;
		_delay_us(1);
	}
	//TCCR1B = 0;
	
	int16_t distance = ((duration * 0.0343) / 2);
	return distance;
	
}


int main(void)
{
	DDRB |= (1 << PB0); // ultrasonic trigger
	DDRB |= (1 << PB1); // passive buzzer
	DDRD &= ~(1 << PD5); // IR-receiver
	DDRD &= ~(1 << PD4); // ultrasonic echo
	DDRD |= (1 << PD2); // red led
	DDRD |= (1 << PD3); // green led
	
	sei();
	// declare values for the inputs for trigger and IR-receiver
    //int8_t g_IR_receiver = 0;
	//int8_t g_us_echo = 0;
    while (1) //TODO: signal goes through, voice works.
    {
		
		switch (g_STATE) {
			//case COM_CONNECT:
				
			//break;
			case WAIT:
				distance = pulse();
				if (distance < 50)
				{
					PORTD |= (1 << PD2);
					PORTD &= ~(1 << PD3);
					//PORTB |= (1 << PB1);
					soundBuzzer();
					_delay_ms(2);
				}
				else
				{
					PORTD |= (1 << PD3);
					PORTD &= ~(1 << PD2);
					//PORTB &= ~(1 << PB1);
					offBuzzer();
					_delay_ms(2);
				}
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

