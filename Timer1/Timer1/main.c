#include <xc.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer1.h"

int main(void)
{
	DDRB = 0b11111111;
	
	sei();
	
	TIMER1_clear();
    TIMER1_set();
	
	OCR1A = 1999;
	OCR1B = 50;
	
	TIMER1_start();
	
	while (1) {}
}