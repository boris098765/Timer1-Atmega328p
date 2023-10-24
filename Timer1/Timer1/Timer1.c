#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer1.h"

void TIMER1_clear() {
	TCCR1A = 0; TCCR1B = 0;
	TCNT1  = 0; ICR1   = 0;
	OCR1A  = 0; OCR1B  = 0;
	TIMSK1 = 0;
}

void TIMER1_init() {
	TCCR1A = TCCR1A_start;
	TCCR1B = TCCR1B_start_OFF;
	TIMSK1 = TIMSK1_start;
}

void TIMER1_start() {
	TCCR1B = TCCR1B_start_ON;
}

void TIMER1_stop() {
	TCCR1B = TCCR1B_start_OFF;
}

bool TIMER1_setFrequency(uint16_t freq) {
	if (freq == 0) {
		return false;
	}
	
	uint16_t TOP = F_CPU / (freq * TIMER1_PRESCALER * 2) - 1;
	
	// Проверки
	
	OCR1A = TOP;
	return true;
}