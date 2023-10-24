#include <xc.h>
#include <stdint.h>
#include <avr/io.h>

#include "Timer1.h"

int main(void)
{
	DDRB = 0b11111111;
	
	sei();
	
	TIMER1_clear();
	TIMER1_init();
	
	TIMER1_setFrequency(2000);
	OCR1B = 50;
	
	TIMER1_start();
	
	while (1) {}
}