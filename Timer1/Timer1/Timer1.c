#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Timer1.h"

volatile uint16_t TIMER1_PRESC = 0;
volatile uint16_t TIMER1_COMPA = 0;
volatile uint16_t TIMER1_COMPB = 0;

volatile uint16_t TCCR1B_start_ON = TCCR1B_WGM2;


uint16_t TIMER1_Prescalers[]    = { 1, 8, 64, 256, 1024 };
uint16_t TIMER1_PrescalerVals[] = {
	TCCR1B_PRESC_1,
	TCCR1B_PRESC_8,
	TCCR1B_PRESC_64,
	TCCR1B_PRESC_256,
	TCCR1B_PRESC_1024
};


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

void TIMER1_start() { TCCR1B = TCCR1B_start_ON;  }
void TIMER1_stop()  { TCCR1B = TCCR1B_start_OFF; }
	
#if TIMER1_MODE == 0 || TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 5 || TIMER1_MODE == 6 || TIMER1_MODE == 7
bool TIMER1_setPrescaler(uint16_t presc) {
	switch ( presc ) {
		case 0:
			TIMER1_PRESC = 0;
			TCCR1B_start_ON = TCCR1B_WGM2 | TCCR1B_PRESC_OFF;
		break;
		case 1:
			TIMER1_PRESC = 1;
			TCCR1B_start_ON = TCCR1B_WGM2 | TCCR1B_PRESC_1;
		break;
		case 8:
			TIMER1_PRESC = 8;
			TCCR1B_start_ON = TCCR1B_WGM2 | TCCR1B_PRESC_8;
		break;
		case 64:
			TIMER1_PRESC = 64;
			TCCR1B_start_ON = TCCR1B_WGM2 | TCCR1B_PRESC_64;
		break;
		case 256:
			TIMER1_PRESC = 256;
			TCCR1B_start_ON = TCCR1B_WGM2 | TCCR1B_PRESC_256;
		break;
		case 1024:
			TIMER1_PRESC = 1024;
			TCCR1B_start_ON = TCCR1B_WGM2 | TCCR1B_PRESC_1024;
		break;
		default:
			return false;
	}
	return true;
}
#endif

#if TIMER1_MODE == 4 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 | TIMER1_MODE == 11 || TIMER1_MODE == 12 || TIMER1_MODE == 14 || TIMER1_MODE == 15
bool TIMER1_setFrequency( uint32_t f ) {
	if (f == 0) return false;
	
	#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 || TIMER1_MODE == 11
	uint32_t neededTicks = F_CPU / (4 * f);
	#else
	uint32_t neededTicks = F_CPU / (2 * f);
	#endif
	
	for (uint8_t i = 0; i < sizeof(TIMER1_Prescalers) / sizeof(TIMER1_Prescalers[0]); i++) {
		TIMER1_PRESC = TIMER1_Prescalers[i];
		if ( neededTicks / TIMER1_PRESC <= 0xFFFF ) {
			TCCR1B_start_ON = TCCR1B_WGM2 | TIMER1_PrescalerVals[i];
			
			uint16_t TOP = neededTicks / TIMER1_PRESC;
			
			#if TIMER1_MODE == 8 || TIMER1_MODE == 10 || TIMER1_MODE == 12 || TIMER1_MODE == 14
			ICR1  = TOP;
			#else
			OCR1A = TOP;
			#endif
			
			return true;
		}
	}
	
	return false;
}
#endif

float TIMER1_getFrequency() {
	uint32_t TOP;
	uint32_t ticks;
	
	#if TIMER1_MODE == 0
	TOP = 0xFFFF;
	#elif TIMER1_MODE == 1 || TIMER1_MODE == 5
	TOP = 0x00FF;
	#elif TIMER1_MODE == 2 || TIMER1_MODE == 6
	TOP = 0x01FF;
	#elif TIMER1_MODE == 3 || TIMER1_MODE == 7
	TOP = 0x03FF;
	#elif TIMER1_MODE == 8 || TIMER1_MODE == 10 || TIMER1_MODE == 12 || TIMER1_MODE == 14
	TOP = ICR1;
	#else
	TOP = OCR1A;
	#endif
	
	ticks = ( TOP + 1 ) * TIMER1_PRESC;
	
	#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 || TIMER1_MODE == 11
	return F_CPU / ( 4.0 * ticks );
	#else
	return F_CPU / ( 2.0 * ticks );
	#endif
}

#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 5 || TIMER1_MODE == 6 || TIMER1_MODE == 7 || TIMER1_MODE == 8 || TIMER1_MODE == 10 || TIMER1_MODE == 14
void TIMER1_setDutyA( uint8_t duty ) {
	uint16_t TOP;
	
	#if TIMER1_MODE == 1 || TIMER1_MODE == 5
	TOP = 0x00FF;
	#elif TIMER1_MODE == 2 || TIMER1_MODE == 6
	TOP = 0x01FF;
	#elif TIMER1_MODE == 3 || TIMER1_MODE == 7
	TOP = 0x03FF;
	#elif TIMER1_MODE == 8 || TIMER1_MODE == 10 || TIMER1_MODE == 12 || TIMER1_MODE == 14
	TOP = ICR1;
	#else
	TOP = OCR1B;
	#endif
	
	OCR1A = (uint16_t)(duty / 100.0 * TOP);
}

void TIMER1_setWidthA( uint16_t width ) {
	uint32_t val = ( ( F_CPU / 2000000UL ) * width ) / TIMER1_PRESC;
	
	#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 || TIMER1_MODE == 11
	val /= 2;
	#endif
	
	OCR1A = val;
}
#endif

#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 5 || TIMER1_MODE == 6 || TIMER1_MODE == 7 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 || TIMER1_MODE == 11 || TIMER1_MODE == 14 || TIMER1_MODE == 15
void TIMER1_setDutyB(uint8_t duty) {
	uint16_t TOP;
	
	#if TIMER1_MODE == 1 || TIMER1_MODE == 5
	TOP = 0x00FF;
	#elif TIMER1_MODE == 2 || TIMER1_MODE == 6
	TOP = 0x01FF;
	#elif TIMER1_MODE == 3 || TIMER1_MODE == 7
	TOP = 0x03FF;
	#elif TIMER1_MODE == 8 || TIMER1_MODE == 10 || TIMER1_MODE == 14
	TOP = ICR1;
	#else
	TOP = OCR1A;
	#endif
	
	OCR1B = (uint16_t)(duty / 100.0 * TOP);
}

void TIMER1_setWidthB( uint16_t width ) {
	uint32_t val = ( ( F_CPU / 2000000UL ) * width ) / TIMER1_PRESC;
	
	#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 || TIMER1_MODE == 11
	val /= 2;
	#endif
	
	OCR1B = val;
}
#endif