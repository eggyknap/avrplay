#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>  

#define led0_on()  PORTD |= _BV(6)
#define led0_off()  PORTD &= ~_BV(6)

void sweep(void)
{
    PORTB = 0b10000000;
    for (int i=0;i<8;i++)
    {
        _delay_ms(100);
        PORTB >>= 1;
    }
}

ISR(SIG_INTERRUPT0)
{
    led0_on();
    _delay_ms(50);
    led0_off();
}

int main (void)
{
    DDRB  = 0b11111111;   // All outputs
    DDRC  = 0b01111111;   // All outputs (Although we will just use PC0 and PC1)
    DDRD  = 0b11111011;   // set PD2 to input
    PORTD = 0b00000100;   // set PD2 to high

    EIMSK |= _BV(INT0);  //Enable INT0
    EICRA |= _BV(ISC01); //Trigger on falling edge of INT0
    sei();

    while(1)
    {
        sweep();
    }
}
