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
	TIMER1_start();
	
	// PORTB |= ( 1 << PINB2 );
	
	while (1) {}
}

// TOP
ISR(OVF_vect) {
	PORTB ^= ( 1 << PINB2 );
}