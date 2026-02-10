#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN PB5

void gpio_init(void)
{
  DDRB |= (1<<LED_PIN);
}
void timer1_init(void)
{
  TCCR1A = 0; //As WGM bits are split across A and B, we need to clear all for CTC mode
  TCCR1B = 0;
  TCNT1  = 0;
  TCCR1B |= (1<<WGM12); //CTC Mode 
  TCCR1B |= (1<<CS12); //Prescaler = 256
  OCR1A = 31249; //tick count for 500ms - 16us tick duration
  TIMSK1 |= (1<<OCIE1A);
  sei();
}
ISR(TIMER1_COMPA_vect)
{
    PORTB ^= (1 << LED_PIN);
}
void setup()
{
  gpio_init();
  timer1_init();
}
void loop()
{}
