#include <avr/io.h>
#include <util/delay.h>

#define UBRR_VALUE 103   // 9600 baud @ 16 MHz

void uart_init(void)
{
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8); //shifts no. 8 bits right, leaving only high bits
    UBRR0L = (uint8_t)(UBRR_VALUE);

    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(char data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_send_string(const char *str)
{
    while (*str)
    {
        uart_transmit(*str++);
    }
}

void setup(void)
{
    uart_init();
}

void loop(void)
{
    uart_send_string("Hello from UART\r\n");
    _delay_ms(1000);
}
