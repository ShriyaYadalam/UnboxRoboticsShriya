TASK 1 - 
Implementing a GPIO driver that configures a pin as output and toggles the onboard LED of Arduino Uno (pin 13) at 500ms in a continuous loop.

EXPLANATION - 
    • From Arduino UNO board documentation, it was observed that digital pin 13 on the board is wired to PB5.
      
    • From the ATmega328p datasheet, it can be observed that GPIO control is done through 3 registers – DDRx for direction, PORTx for output value and PINx for input. For this task, we modify DDRB and PORTB registers in order to toggle the onboard LED.
      
    • External clock = 16 MHz
    	Prescaler      = 256
	    Timer clock    = 16 MHz / 256 = 62,500 Hz
	    Tick duration  = 1 / 62,500 ≈ 16 µs
	    Ticks for 500 ms = 500 ms / 16 µs = 31,250
	    OCR1A = 31,249
	    Hence, the compare value is set as OCR1A = 31249

    • Since the WGM bits are split across TCCR1A and TCCR1B, both control registers are cleared to ensure that Timer1 runs in a deterministic CTC (Clear Timer on Compare match) configuration.
      
    • The toggling is performed inside the Timer1 Compare Match ISR.

TASK 2 -
To implement a UART driver that initializes UART for 9600 baud rate and 8N1 configuration & transmits a string periodically at an interval of 1000ms.

EXPLANATION - 
    • From the ATmega328p datasheet, it was observed that we can use USART Baud Rate Register(UBRR) to control UART communication speed, and UCSR0B & UCSR0C registers for transmission control and frame format
      
    • Baud Rate Calculation - 
      UBRR = (F_CPU / (16 × Baud Rate)) − 1
	    UBRR = (16,000,000 / (16 × 9600)) − 1
	    UBRR ≈ 103
	    This value is stored in UBRR0H and UBRR0L

    • UCSR0B – We enable the UART transmitter by setting the TXEN0 bit. 
      Once enabled, writing a value to the UDR0 register automatically initiates data transmission.
    • UCSR0C – 	UCSZ01 and UCSZ00 both need to be 1 for 8 bits transfer. Parity is disabled and one stop bit is used, resulting in an 8-N-1 configuration.
    • To prevent overwriting the transmit buffer before the previous byte is sent, we check UDRE0 which becomes 1 only when the UART transmit buffer is free.
