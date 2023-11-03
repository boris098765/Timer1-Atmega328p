// TODO: Проверки setFrequency

#ifndef TIMER1_H
#define	TIMER1_H

#include <stdbool.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

extern volatile uint16_t TIMER1_PRESC;
extern volatile uint16_t TIMER1_COMPA;
extern volatile uint16_t TIMER1_COMPB;


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


// Режим таймера
#define TIMER1_MODE    9

// COM
#define TCCR1A_COM1A  ( 0b10 << COM1A0 )
#define TCCR1A_COM1B  ( 0b10 << COM1B0 )

// Interrupts
// Input Capture
#define TIMSK1_ICIE1        0
// Output Compare B
#define TIMSK1_OCIE1B       0
// Output Compare A
#define TIMSK1_OCIE1A       0
// Overflow
#define TIMSK1_TOIE1        0


// ---------------------------------------------- //


#define TCCR1B_PRESC_OFF   0b000
#define TCCR1B_PRESC_1     0b001
#define TCCR1B_PRESC_8     0b010
#define TCCR1B_PRESC_64    0b011
#define TCCR1B_PRESC_256   0b100
#define TCCR1B_PRESC_1024  0b101

#if TIMER1_MODE == TIMER1_NORMAL_MODE           // 0
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b00 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_8_MODE       // 1
	#define TCCR1A_WGM1 0b01
	#define TCCR1B_WGM2 ( 0b00 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_9_MODE       // 2
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b00 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_10_MODE      // 3
	#define TCCR1A_WGM1 0b11
	#define TCCR1B_WGM2 ( 0b00 << 3 )
#elif TIMER1_MODE == TIMER1_CTC_OCR1A_MODE      // 4
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b01 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_8_MODE     // 5
	#define TCCR1A_WGM1 0b01
	#define TCCR1B_WGM2 ( 0b01 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_9_MODE     // 6
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b01 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_10_MODE    // 7
	#define TCCR1A_WGM1 0b11
	#define TCCR1B_WGM2 ( 0b01 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PFC_ICR1_MODE   // 8
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b10 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PFC_OCR1A_MODE  // 9
	#define TCCR1A_WGM1 0b01
	#define TCCR1B_WGM2 ( 0b10 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_ICR1_MODE    // 10
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b10 << 3 )
#elif TIMER1_MODE == TIMER1_PWM_PC_OCR1A_MODE   // 11
	#define TCCR1A_WGM1 0b11
	#define TCCR1B_WGM2 ( 0b10 << 3 )
#elif TIMER1_MODE == TIMER1_CTC_ICR1_MODE       // 12
	#define TCCR1A_WGM1 0b00
	#define TCCR1B_WGM2 ( 0b11 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE  // 14
	#define TCCR1A_WGM1 0b10
	#define TCCR1B_WGM2 ( 0b11 << 3 )
#elif TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE // 15
	#define TCCR1A_WGM1 0b11
	#define TCCR1B_WGM2 ( 0b11 << 3 )
#else
	#error "BAD TIMER1 MODE"
#endif


// ---------------------------------------------- //


// Проверка прерываний (сделал до 9-го)

#if TIMSK1_ICIE1 == 1
	#if (TIMER1_MODE == 0)
		#error "MODE TIMER1_NORMAL_MODE HAS NO INTERRUPT TIMER1_CAPT_vect"
	#endif
	#if (TIMER1_MODE == 1)
		#error "MODE TIMER1_PWM_PC_8_MODE HAS NO INTERRUPT TIMER1_CAPT_vect"
	#endif
	#if (TIMER1_MODE == 2)
		#error "MODE TIMER1_PWM_PC_9_MODE HAS NO INTERRUPT TIMER1_CAPT_vect"
	#endif
	#if (TIMER1_MODE == 3)
		#error "MODE TIMER1_PWM_PC_10_MODE HAS NO INTERRUPT TIMER1_CAPT_vect"
	#endif
	#if (TIMER1_MODE == 4)
		#error "MODE TIMER1_CTC_OCR1A_MODE HAS NO INTERRUPT TIMER1_CAPT_vect"
	#endif
	#else
		#undef TIMER1_CAPT_vect
#endif
#if TIMSK1_OCIE1B == 1
	#if (TIMER1_MODE == 0)
		#error "MODE TIMER1_NORMAL_MODE HAS NO INTERRUPT TIMER1_COMPB_vect"
	#endif
	#if (TIMER1_MODE == 4)
		#error "MODE TIMER1_CTC_OCR1A_MODE HAS NO INTERRUPT TIMER1_COMPB_vect"
	#endif
	#if (TIMER1_MODE == 9)
		#error "MODE TIMER1_PWM_PFC_OCR1A_MODE HAS NO INTERRUPT TIMER1_COMPB_vect"
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
#if TIMSK1_TOIE1 == 1
	#if (TIMER1_MODE == 4)
		#error "MODE TIMER1_CTC_OCR1A_MODE HAS NO INTERRUPT TIMER1_OVF_vect"
	#endif
	#if (TIMER1_MODE == 5)
		#error "MODE TIMER1_FAST_PWM_8_MODE HAS NO INTERRUPT TIMER1_OVF_vect"
	#endif
	#if (TIMER1_MODE == 6)
		#error "MODE TIMER1_FAST_PWM_9_MODE HAS NO INTERRUPT TIMER1_OVF_vect"
	#endif
	#if (TIMER1_MODE == 7)
		#error "MODE TIMER1_FAST_PWM_10_MODE HAS NO INTERRUPT TIMER1_OVF_vect"
	#endif
	#else
		#undef TIMER1_OVF_vect
#endif


#define TIMSK1_start  ( TIMSK1_ICIE1 << ICIE1 ) | ( TIMSK1_OCIE1B << OCIE1B ) | ( TIMSK1_OCIE1A << OCIE1A) | ( TIMSK1_TOIE1 << TOIE1)

#define TIMER1_startInterrupts() TIMSK1 = TIMSK1_start
#define TIMER1_stopInterrupts()  TIMSK1 = 0


// ---------------------------------------------- //


// Result
#define TCCR1A_start      TCCR1A_COM1A | TCCR1A_COM1B | TCCR1A_WGM1
#define TCCR1B_start_OFF  TCCR1B_WGM2  | TCCR1B_PRESC_OFF


// ---------------------------------------------- //


void TIMER1_clear();
void TIMER1_init();

void TIMER1_start();
void TIMER1_stop();

#if TIMER1_MODE == 0 || TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 5 || TIMER1_MODE == 6 || TIMER1_MODE == 7
bool TIMER1_setPrescaler(uint16_t presc);
#endif

#if TIMER1_MODE == 4 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 | TIMER1_MODE == 11 || TIMER1_MODE == 12 || TIMER1_MODE == 14 || TIMER1_MODE == 15
bool TIMER1_setFrequency( uint32_t f );
#endif

float TIMER1_getFrequency();

#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 5 || TIMER1_MODE == 6 || TIMER1_MODE == 7 || TIMER1_MODE == 8 || TIMER1_MODE == 10 || TIMER1_MODE == 14
void TIMER1_setDutyA( uint8_t duty );
void TIMER1_setWidthA( uint16_t width );
#endif

#if TIMER1_MODE == 1 || TIMER1_MODE == 2 || TIMER1_MODE == 3 || TIMER1_MODE == 5 || TIMER1_MODE == 6 || TIMER1_MODE == 7 || TIMER1_MODE == 8 || TIMER1_MODE == 9 || TIMER1_MODE == 10 || TIMER1_MODE == 11 || TIMER1_MODE == 14 || TIMER1_MODE == 15
void TIMER1_setDutyB( uint8_t duty );
void TIMER1_setWidthB( uint16_t width );
#endif

// ---------------------------------------------- //


#endif