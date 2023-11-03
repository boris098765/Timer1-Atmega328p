#include <xc.h>
#include <stdint.h>
#include <avr/io.h>

#include "Timer1.h"

#define F_CPU 16000000UL
#include <util/delay.h>

float f;

int main(void)
{
	DDRB = 0b11111111;
	
	sei();
	
	TIMER1_clear();
	TIMER1_init();
	
	TIMER1_setFrequency(10);
	TIMER1_setWidthB(50);
	TIMER1_start();
	
	
	while (1) {}
}