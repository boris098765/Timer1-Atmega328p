#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer1.h"

extern void TIMER1_clear() {
	TCCR1A = 0; TCCR1B = 0;
	TCNT1  = 0; ICR1   = 0;
	OCR1A  = 0; OCR1B  = 0;
	TIMSK1 = 0;
}

extern void TIMER1_set() {
	TCCR1A = TCCR1A_start;
	TCCR1B = TCCR1B_start_OFF;
	TIMSK1 = TIMSK1_start;
}

extern void TIMER1_start() {
	TCCR1B = TCCR1B_start_ON;
}