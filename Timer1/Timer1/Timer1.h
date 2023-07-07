#ifndef TIMER1_H
#define	TIMER1_H
#include <xc.h>
#include <avr/interrupt.h>


// -------------- Номера режимов ---------------- //


#define TIMER1_NORMAL_MODE         0
#define TIMER1_PWM_PC_8_MODE       1
#define TIMER1_PWM_PC_9_MODE       2
#define TIMER1_PWM_PC_10_MODE      3
#define TIMER1_CTC_OCR1A_MODE      4
#define TIMER1_FAST_PWM_8_MODE     5
#define TIMER1_FAST_PWM_9_MODE     6
#define TIMER1_FAST_PWM_10_MODE    7
#define TIMER1_PWM_PFC_ICR1_MODE   8
#define TIMER1_PWM_PFC_OCR1A_MODE  9
#define TIMER1_PWM_PC_ICR1_MODE    10
#define TIMER1_PWM_PC_OCR1A_MODE   11
#define TIMER1_CTC_ICR1_MODE       12
#define TIMER1_FAST_PWM_ICR1_MODE  14
#define TIMER1_FAST_PWM_OCR1A_MODE 15


// ---------------------------------------------- //


// Предделитель
#define TIMER1_PRESCALER 1

// Режим таймера
#define TIMER1_MODE    TIMER1_NORMAL_MODE

// COM
#define TCCR1A_COM1A  ( 0b00 << COM1A1 ) // None
#define TCCR1A_COM1B  ( 0b10 << COM1B1 ) // Non-Inverse

// Interrupts

// Input Capture
#define TIMSK1_ICIE1        0
// Output Compare B
#define TIMSK1_OCIE1B       0
// Output Compare A
#define TIMSK1_OCIE1A       0
// Overflow
#define TIMSK1_TOIE1        1


// ---------------------------------------------- //


#define TCCR1B_PRESC_OFF 0b000
#if TIMER1_PRESCALER == 1
#define TCCR1B_PRESC 0b001
#elif TIMER1_PRESCALER == 8
#define TCCR1B_PRESC 0b010
#elif TIMER1_PRESCALER == 64
#define TCCR1B_PRESC 0b011
#elif TIMER1_PRESCALER == 256
#define TCCR1B_PRESC 0b100
#elif TIMER1_PRESCALER == 1024
#define TCCR1B_PRESC 0b101
#else
#error "BAD TIMER1 PRESCALER"
#endif


// Normal //
#if TIMER1_MODE == TIMER1_NORMAL_MODE          // 0
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b00 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_8_MODE      // 1
	#define TCCR1A_WGM1 0b01
	#define TCCR1B_WGM2 ( 0b00 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_8_MODE      // 2
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b00 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_10_MODE     // 3
	#define TCCR1A_WGM1 0b11
	#define TCCR1B_WGM2( 0b00 << 3 )
// CTC //
#elif TIMER1_MODE == TIMER1_CTC_OCR1A_MODE     // 4
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b01 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_8_MODE    // 5
	#define TCCR1A_WGM1 0b01
	#define TCCR1B_WGM2 ( 0b01 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_9_MODE    // 6
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b01 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_10_MODE   // 7
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b01 << 3 )
// Phase Correct //
#elif TIMER1_MODE == TIMER1_PWM_PFC_ICR1_MODE  // 8
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b10 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PFC_OCR1A_MODE // 9
	#define TCCR1A_WGM1 0b01
	#define TCCR1B_WGM2 ( 0b10 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_ICR1_MODE   // 10
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b10 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_OCR1A_MODE  // 11
	#define TCCR1A_WGM1 0b11
	#define TCCR1B_WGM2 ( 0b10 << 3 )
// Fast PWM //
#elif TIMER1_MODE == TIMER1_CTC_ICR1_MODE      // 12
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b11 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE // 14
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b11 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE // 15
	#define TCCR1A_WGM1 0b11
	#define TCCR1B_WGM2 ( 0b11 << 3 )
#else
	#error "BAD TIMER1 MODE"
#endif


// Проверка прерываний


#if TIMSK1_ICIE1  == 1
	#if (TIMER1_MODE == 0)
		#error "MODE TIMER1_NORMAL_MODE HAS NO INTERRUPT TIMER1_CAPT_vect"
	#endif
#else
	#undef TIMER1_CAPT_vect
#endif

#if TIMSK1_OCIE1B == 1
	#if (TIMER1_MODE == 0)
		#error "MODE TIMER1_NORMAL_MODE HAS NO INTERRUPT TIMER1_COMPB_vect"
	#endif
#else
	#undef TIMER1_COMPB_vect
#endif

#if TIMSK1_OCIE1A == 1
	#if (TIMER1_MODE == 0)
		#error "MODE TIMER1_NORMAL_MODE HAS NO INTERRUPT TIMER1_COMPA_vect"
	#endif
#else
	#undef TIMER1_COMPA_vect
#endif

#if (TIMSK1_TOIE1  == 0)
	#undef TIMER1_OVF_vect
#endif

// ---------------------------------------------- //


// Result
#define TCCR1A_start      TCCR1A_COM1A | TCCR1A_COM1B | TCCR1A_WGM1;
#define TCCR1B_start_ON   TCCR1B_WGM2  | TCCR1B_PRESC;
#define TCCR1B_start_OFF  TCCR1B_WGM2  | TCCR1B_PRESC_OFF;

#define TIMSK1_start      ( TIMSK1_ICIE1 << ICIE1 ) | ( TIMSK1_OCIE1B << OCIE1B ) | ( TIMSK1_OCIE1A << OCIE1A) | ( TIMSK1_TOIE1 << TOIE1)


// ---------------------------------------------- //


void TIMER1_clear();
void TIMER1_set();
void TIMER1_start();


// ---------------------------------------------- //


#endif