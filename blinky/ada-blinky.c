// this is the header file that tells the compiler what pins and ports, etc.
// are available on this chip.
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>

// define what pins the LEDs are connected to.
// in reality, PD6 is really just '6'
#define LED PD6

// Some macros that make the code more readable
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

// this is just a program that 'kills time' in a calibrated method
void delay_ms(uint8_t ms) {
  uint16_t delay_count = F_CPU / 17500;
  volatile uint16_t i;

  while (ms != 0) {
    for (i=0; i != delay_count; i++);
    ms--;
  }
}

volatile int i = 0;
volatile int up = 1;

ISR(SIG_INTERRUPT0) {
    output_high(PORTD, LED);
    if (up) {
        if (i < 230) i += 10;
        else up = 0;
    }
    else {
        if (i > 20) i -= 10;
        else up = 1;
    }
    output_low(PORTD, LED);
}

int main(void) {
  // initialize the direction of PORTD #6 to be an output
  set_output(DDRD, LED);  
  set_input(DDRB, 5);
  set_input(DDRD, 2);
    DDRB  = 0b11111111;   // All outputs
    DDRD  = 0b11111011;   // set PD2 to input
    PORTD = 0b00000100;   // set PD2 to high

    EIMSK |= _BV(INT0);  //Enable INT0
    EICRA |= _BV(ISC01); //Trigger on falling edge of INT0


  sei();
  //power_timer0_enable();

  while (1) {
    // turn on the LED for 200ms
    output_high(PORTD, LED);
    delay_ms(20 + i);
    // now turn off the LED for another 200ms
    output_low(PORTD, LED);
    delay_ms(230 - i);
    // now start over
  }
}
