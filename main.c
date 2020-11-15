#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include <ctype.h>

#include "adc.h"
#include "gpio.h"
#include "serial.h"
#include "timer.h"
#include "enum.h"

static volatile char uart_rx_command = 0;
volatile bool new_uart_data = false;


void main (void) {

	uart_init();
	sei();

	while(1){
		/*printf_P(PSTR("TESTING\r\n"));
		_delay_ms(500);*/
		if(new_uart_data){
			printf_P(PSTR("new_uart_data\r\n"));
			if(uart_rx_command == FORWARD){
				printf_P(PSTR("FORWARD\r\n"));
				new_uart_data = false;
			}
			else if(uart_rx_command == BACKWARD){
				printf_P(PSTR("BACKWARD\r\n"));
				new_uart_data = false;
			}
			else if(uart_rx_command == LEFT){
				printf_P(PSTR("LEFT\r\n"));
				new_uart_data = false;
			}
			else if(uart_rx_command == RIGHT){
				printf_P(PSTR("RIGHT\r\n"));
				new_uart_data = false;
			}
		}
	}
}

ISR(USART_RX_vect){
	while (!(UCSR0A & (1 << RXC0)));
	uart_rx_command = UDR0;
	if(uart_rx_command == iscntrl(uart_rx_command)){
		new_uart_data = true;
	}
}
