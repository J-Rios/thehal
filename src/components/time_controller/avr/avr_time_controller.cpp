
/**
 * @file    avr_time_controller.cpp
 * @author  Jose Miguel Rios Rubio <jrios.github@gmail.com>
 * @date    08-12-2020
 * @version 1.0.0
 *
 * @section DESCRIPTION
 *
 * Time related functionalities Controller for AVR devices.
 *
 * @section LICENSE
 *
 * Copyright (c) 2020 Jose Miguel Rios Rubio. All right reserved.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*****************************************************************************/

/* Build Guard */

#if defined(__AVR__) and !defined(ARDUINO)

/*****************************************************************************/

/* Libraries */

#include "avr_time_controller.h"

/*****************************************************************************/

/* Constants */

// Prescaler set to get timer0 ticks every 64 clock cycles
// Overflow handler is called every 256 ticks
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// Number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

// Fractional number of milliseconds per timer0 overflow
// Shift right by three to fit these numbers into a byte
// For 8 and 16 MHz clock speeds, this doesn't lose precision
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

/*****************************************************************************/

/* System Tick Timer ISR */

volatile uint32_t timer0_overflow_count = 0;
volatile uint32_t timer0_millis = 0;
static uint8_t timer0_fract = 0;


#if defined(TIM0_OVF_vect)
ISR(TIM0_OVF_vect)
#else
ISR(TIMER0_OVF_vect)
#endif
{
    // copy these to local variables so they can be stored in registers
    // (volatile variables must be read from memory on every access)
    uint32_t m = timer0_millis;
    uint8_t f = timer0_fract;

    m = m + MILLIS_INC;
    f = f + FRACT_INC;
    if (f >= FRACT_MAX)
    {
        f = f - FRACT_MAX;
        m = m + 1;
    }

    timer0_fract = f;
    timer0_millis = m;
    timer0_overflow_count++;
}

/*****************************************************************************/

/* Constructor & Destructor */

/* Time constructor */
Time::Time()
{
    this->initialized = false;
}

/* Time destructor */
Time::~Time()
{}

/*****************************************************************************/

/* Public Methods */

/**
  * @brief  Setup and initialize timers for system tick control.
  */
void Time::setup(void)
{
    // Ignore if already initialized
    if(this->initialized)
        return;
    this->initialized = true;

    // General enable interrupts
    sei();
    
    // on the ATmega168, timer 0 is also used for fast hardware pwm (using
    // phase-correct PWM would mean that timer 0 overflowed half as often
    // resulting in different millis() behavior on the ATmega8 and ATmega168)
    #if defined(TCCR0A) && defined(WGM01)
        sbi(TCCR0A, WGM01);
        sbi(TCCR0A, WGM00);
    #endif

    // set timer 0 prescale factor to 64
    #if defined(__AVR_ATmega128__)
        // CPU specific: different values for the ATmega128
        sbi(TCCR0, CS02);
    #elif defined(TCCR0) && defined(CS01) && defined(CS00)
        // this combination is for the standard atmega8
        sbi(TCCR0, CS01);
        sbi(TCCR0, CS00);
    #elif defined(TCCR0B) && defined(CS01) && defined(CS00)
        // this combination is for the standard 168/328/1280/2560
        sbi(TCCR0B, CS01);
        sbi(TCCR0B, CS00);
    #elif defined(TCCR0A) && defined(CS01) && defined(CS00)
        // this combination is for the __AVR_ATmega645__ series
        sbi(TCCR0A, CS01);
        sbi(TCCR0A, CS00);
    #else
        #error Timer 0 prescale factor 64 not set correctly
    #endif

    // enable timer 0 overflow interrupt
    #if defined(TIMSK) && defined(TOIE0)
        sbi(TIMSK, TOIE0);
    #elif defined(TIMSK0) && defined(TOIE0)
        sbi(TIMSK0, TOIE0);
    #else
        #error Timer 0 overflow interrupt not set correctly
    #endif

    // timers 1 and 2 are used for phase-correct hardware pwm
    // this is better for motors as it ensures an even waveform
    // note, however, that fast pwm mode can achieve a frequency of up
    // 8 MHz (with a 16 MHz clock) at 50% duty cycle
    #if defined(TCCR1B) && defined(CS11) && defined(CS10)
        // set timer 1 prescale factor to 64
        TCCR1B = 0;
        sbi(TCCR1B, CS11);
        #if F_CPU >= 8000000L
            sbi(TCCR1B, CS10);
        #endif
    #elif defined(TCCR1) && defined(CS11) && defined(CS10)
        sbi(TCCR1, CS11);
        #if F_CPU >= 8000000L
            sbi(TCCR1, CS10);
        #endif
    #endif

    // put timer 1 in 8-bit phase correct pwm mode
    #if defined(TCCR1A) && defined(WGM10)
        sbi(TCCR1A, WGM10);
    #endif

    // set timer 2 prescale factor to 64
    #if defined(TCCR2) && defined(CS22)
        sbi(TCCR2, CS22);
    #elif defined(TCCR2B) && defined(CS22)
        sbi(TCCR2B, CS22);
    #endif

    // configure timer 2 for phase correct pwm (8-bit)
    #if defined(TCCR2) && defined(WGM20)
        sbi(TCCR2, WGM20);
    #elif defined(TCCR2A) && defined(WGM20)
        sbi(TCCR2A, WGM20);
    #endif

    #if defined(TCCR3B) && defined(CS31) && defined(WGM30)
        sbi(TCCR3B, CS31); // set timer 3 prescale factor to 64
        sbi(TCCR3B, CS30);
        sbi(TCCR3A, WGM30); // put timer 3 in 8-bit phase correct pwm mode
    #endif

    /* beginning of timer4 block for 32U4 and similar */
    #if defined(TCCR4A) && defined(TCCR4B) && defined(TCCR4D)
        sbi(TCCR4B, CS42); // set timer4 prescale factor to 64
        sbi(TCCR4B, CS41);
        sbi(TCCR4B, CS40);
        sbi(TCCR4D, WGM40); // put timer 4 in phase and freq correct PWM mode
        sbi(TCCR4A, PWM4A); // enable PWM mode for comparator OCR4A
        sbi(TCCR4C, PWM4D); // enable PWM mode for comparator OCR4D
    #else /* beginning of timer4 block for ATMEGA1280 and ATMEGA2560 */
        #if defined(TCCR4B) && defined(CS41) && defined(WGM40)
            sbi(TCCR4B, CS41); // set timer 4 prescale factor to 64
            sbi(TCCR4B, CS40);
            sbi(TCCR4A, WGM40); // put timer 4 in 8-bit phase correct pwm mode
        #endif
    #endif /* end timer4 block for ATMEGA1280/2560 and similar */	

    #if defined(TCCR5B) && defined(CS51) && defined(WGM50)
        sbi(TCCR5B, CS51); // set timer 5 prescale factor to 64
        sbi(TCCR5B, CS50);
        sbi(TCCR5A, WGM50); // put timer 5 in 8-bit phase correct pwm mode
    #endif

    #if defined(ADCSRA)
        // set a2d prescaler so we are inside the desired 50-200 KHz range
        #if F_CPU >= 16000000 // 16 MHz / 128 = 125 KHz
            sbi(ADCSRA, ADPS2);
            sbi(ADCSRA, ADPS1);
            sbi(ADCSRA, ADPS0);
        #elif F_CPU >= 8000000 // 8 MHz / 64 = 125 KHz
            sbi(ADCSRA, ADPS2);
            sbi(ADCSRA, ADPS1);
            cbi(ADCSRA, ADPS0);
        #elif F_CPU >= 4000000 // 4 MHz / 32 = 125 KHz
            sbi(ADCSRA, ADPS2);
            cbi(ADCSRA, ADPS1);
            sbi(ADCSRA, ADPS0);
        #elif F_CPU >= 2000000 // 2 MHz / 16 = 125 KHz
            sbi(ADCSRA, ADPS2);
            cbi(ADCSRA, ADPS1);
            cbi(ADCSRA, ADPS0);
        #elif F_CPU >= 1000000 // 1 MHz / 8 = 125 KHz
            cbi(ADCSRA, ADPS2);
            sbi(ADCSRA, ADPS1);
            sbi(ADCSRA, ADPS0);
        #else // 128/2 = 64KHz - The closest you can get, the prescaler is 2
            cbi(ADCSRA, ADPS2);
            cbi(ADCSRA, ADPS1);
            sbi(ADCSRA, ADPS0);
        #endif
        // enable a2d conversions
        sbi(ADCSRA, ADEN);
    #endif

    // the bootloader connects pins 0 and 1 to the USART; disconnect them
    // here so they can be used as normal digital i/o; they will be
    // reconnected in Serial.begin()
    #if defined(UCSRB)
        UCSRB = 0;
    #elif defined(UCSR0B)
        UCSR0B = 0;
    #endif
}

/**
  * @brief  Get current system tick in microseconds.
  * @return How many microseconds has passed after system tick initialization.
  */
uint32_t Time::micros(void)
{
    unsigned long m;
    uint8_t oldSREG = SREG, t;
    
    cli();
    m = timer0_overflow_count;
    #if defined(TCNT0)
        t = TCNT0;
    #elif defined(TCNT0L)
        t = TCNT0L;
    #else
        #error TIMER 0 not defined
    #endif

    #ifdef TIFR0
        if ((TIFR0 & _BV(TOV0)) && (t < 255))
            m++;
    #else
        if ((TIFR & _BV(TOV0)) && (t < 255))
            m++;
    #endif

    SREG = oldSREG;
    
    return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}

/**
  * @brief  Get current system tick in milliseconds.
  * @return How many milliseconds has passed after system tick initialization.
  */
uint32_t Time::millis(void)
{
    uint32_t ms;
    uint8_t oldSREG = SREG;

    cli();
    ms = ::timer0_millis;
    SREG = oldSREG;

    return ms;
}

/**
  * @brief  Delay execution for some microseconds.
  * @param  t_delay_us Number of microseconds to delay.
  */
void Time::delay_us(const uint32_t t_delay_us)
{
    // call = 4 cycles + 2 to 4 cycles to init us
    // (2 for constant delay, 4 for variable)

    // calling avrlib's delay_us() function with low values (e.g. 1 or
    // 2 microseconds) gives delays longer than desired.
    #if F_CPU >= 24000000L
        // for the 24 MHz clock for the aventurous ones, trying to overclock

        // zero delay fix
        if (!us) return; //  = 3 cycles, (4 when true)

        // the following loop takes a 1/6 of a microsecond (4 cycles)
        // per iteration, so execute it six times for each microsecond of
        // delay requested.
        us *= 6; // x6 us, = 7 cycles

        // account for the time taken in the preceeding commands.
        // we just burned 22 (24) cycles above, remove 5, (5*4=20)
        // us is at least 6 so we can substract 5
        us -= 5; //=2 cycles
    #elif F_CPU >= 20000000L
        // for the 20 MHz clock on rare Arduino boards

        // for a one-microsecond delay, simply return.  the overhead
        // of the function call takes 18 (20) cycles, which is 1us
        __asm__ __volatile__ (
            "nop" "\n\t"
            "nop" "\n\t"
            "nop" "\n\t"
            "nop"); //just waiting 4 cycles
        if (us <= 1) return; //  = 3 cycles, (4 when true)

        // the following loop takes a 1/5 of a microsecond (4 cycles)
        // per iteration, so execute it five times for each microsecond of
        // delay requested.
        us = (us << 2) + us; // x5 us, = 7 cycles

        // account for the time taken in the preceeding commands.
        // we just burned 26 (28) cycles above, remove 7, (7*4=28)
        // us is at least 10 so we can substract 7
        us -= 7; // 2 cycles
    #elif F_CPU >= 16000000L
        // for the 16 MHz clock on most Arduino boards

        // for a one-microsecond delay, simply return.  the overhead
        // of the function call takes 14 (16) cycles, which is 1us
        if (us <= 1) return; //  = 3 cycles, (4 when true)

        // the following loop takes 1/4 of a microsecond (4 cycles)
        // per iteration, so execute it four times for each microsecond of
        // delay requested.
        us <<= 2; // x4 us, = 4 cycles

        // account for the time taken in the preceeding commands.
        // we just burned 19 (21) cycles above, remove 5, (5*4=20)
        // us is at least 8 so we can substract 5
        us -= 5; // = 2 cycles,
    #elif F_CPU >= 12000000L
        // for the 12 MHz clock if somebody is working with USB

        // for a 1 microsecond delay, simply return.  the overhead
        // of the function call takes 14 (16) cycles, which is 1.5us
        if (us <= 1) return; //  = 3 cycles, (4 when true)

        // the following loop takes 1/3 of a microsecond (4 cycles)
        // per iteration, so execute it three times for each microsecond of
        // delay requested.
        us = (us << 1) + us; // x3 us, = 5 cycles

        // account for the time taken in the preceeding commands.
        // we just burned 20 (22) cycles above, remove 5, (5*4=20)
        // us is at least 6 so we can substract 5
        us -= 5; // 2 cycles
    #elif F_CPU >= 8000000L
        // for the 8 MHz internal clock

        // for a 1 and 2 microsecond delay, simply return.  the overhead
        // of the function call takes 14 (16) cycles, which is 2us
        if (us <= 2) return; // = 3 cycles, (4 when true)

        // the following loop takes 1/2 of a microsecond (4 cycles)
        // per iteration, so execute it twice for each microsecond of
        // delay requested.
        us <<= 1; //x2 us, = 2 cycles

        // account for the time taken in the preceeding commands.
        // we just burned 17 (19) cycles above, remove 4, (4*4=16)
        // us is at least 6 so we can substract 4
        us -= 4; // = 2 cycles
    #else
        // for the 1 MHz internal clock
        // (default settings for common Atmega microcontrollers)

        // the overhead of the function calls is 14 (16) cycles
        // 3 cycles, (4 when true)
        if (us <= 16) return;

        // 3 cycles, (4 when true)
        // (must be at least 25 if we want to substract 22)
        if (us <= 25) return; 

        // compensate for the time taken by the preceeding and next
        // commands (about 22 cycles)
        us -= 22; // = 2 cycles
        // the following loop takes 4 microseconds (4 cycles)
        // per iteration, so execute it us/4 times
        // us is at least 4, divided by 4 gives us 1 (no zero delay bug)
        us >>= 2; // us div 4, = 4 cycles
    #endif

    // busy wait
    __asm__ __volatile__ (
        "1: sbiw %0,1" "\n\t" // 2 cycles
        "brne 1b" : "=w" (us) : "0" (us) // 2 cycles
    );
    // return = 4 cycles
}

/**
  * @brief  Delay execution for some milliseconds.
  * @param  t_delay_ms Number of milliseconds to delay.
  */
void Time::delay_ms(const uint32_t t_delay_ms)
{
    uint32_t start = micros();

    while(ms > 0)
    {
        if((micros() - start) >= 1000)
        {
            ms = ms - 1;
            start = start + 1000;
        }
    }
}

/*****************************************************************************/

/* Private Methods */


/*****************************************************************************/

#endif /* defined(__AVR__) and !defined(ARDUINO) */

/*****************************************************************************/