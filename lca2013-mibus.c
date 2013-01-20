// Needed for PORTB and friends
#include <avr/io.h>

// Needed for sei() etc.
#include <avr/interrupt.h>

int setup_timer (void) {
	// CLear Interrupts
	// Clears the Global Interrupt Enable flag from SREG
	// ATmega328 datasheet, 7.3.1, pg 11.
	// This function is actually a helper macro in avr/interrupt.h
	// cli();

	// TCCR1A: ATmega328 datasheet, 16.11.1, pg 136
	// "Normal" waveform generation, and no output/comparison modes
	TCCR1A = 0;

	// TCCR1B: ATmega328 datasheet, 16.11.2, pg 138
	// No waveform options, clock prescaler of 64
	TCCR1B = (1<<CS11) | (1<<CS10);

	// TCCR1C: ATmega328 datasheet, 16.11.3, pg 139
	// Set no options.
	TCCR1C = 0;

	// TIMSK1: ATmega328 datasheet, 16.11.8, pg 141
	// Enable interrupt on overflow
	TIMSK1 = (1<<TOIE1);

	// SEt Interrupts
	// Sets the Global Interrupt Enable flag from SREG
	// ATmega328 datasheet, 7.3.1, pg 11.
	// This function is actually a helper macro in avr/interrupt.h
	// equivalent to: SREG |= (1<<7);
	sei();
}

// Register a function to handle the TIMER1_OVF interrupt
// ATmega328 datasheet, 12.4, pg 67
ISR(TIMER1_OVF_vect)
{
	// Toggle the output of pin PB1 in PORTB
	PORTB ^= (1<<PB1);
}

// Entry point
int main (void)
{
	// Set up Data Direction Register for PORT B
	// ATmega328 datasheet, 14.2.1, pg 78.
	// These are pins 15 & 16, aka PB1 & PB2, according
	// to the layout at the very start of the datasheet
	DDRB = (1<<DDB1) | (1<<DDB2);

	// Wipe all output of pins on PORT B
	PORTB = 0;

	// Call a function to enable the timer
	setup_timer();

	// Enter an infinite loop
	while (1) {
	}
}
