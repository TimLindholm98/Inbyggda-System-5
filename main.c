#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "SWseriale.h" // SWseriale library

#include "adc.h"
#include "gpio.h"
#include "serial.h"
#include "timer.h"
#include "enum.h"

static volatile char uart_rx_command = 'T';
volatile bool new_uart_data = false;

static struct message_struct{
	char receive_buffer[7] = {0};
	int angle = 0;
	uint8_t strenght = 0;
	uint8_t state = 0;
} message_data;


static struct servo_struct{
	uint8_t speed = 127;
	uint8_t stearing = 127;
} servo_values;

// mac 98:D3:81:FD:68:2F

void main (void) {

	uart_init();
	sei();
	SWseriale_begin(); // Initialize INT1, Timer2, Pin 3 (Input, Pull-up) and Pin 4 (Output)

	SWseriale_write("HI\r\n",2);

    while (1){

			if(SWseriale_available()){
				uint8_t receive_buffer[indexing] = SWseriale_read();
				indexing++

				if(indexing <= 7){
					process_joystick_data(&receive_buffer,&angle, &strenght,&state);
					//constrain_and_map_data(&angle,&strenght,&state,&speed,&stearing);
					printf("%d%d%d",255,0,);
					printf("%d%d%d",255,1,speed);
					indexing = 0;
				}

				/*if(isdigit(uart_rx_command)){
					SWseriale_write(&uart_rx_command, 1);
					printf("%d%d%d",255,0,uart_rx_command);
				}*/

				/*if(uart_rx_command == 'w'){
					PORTB ^= (1<<PB5);
					SWseriale_write(&uart_rx_command, 1);		// Send one character using SWseriale
				}
				else if(uart_rx_command == 's'){
					PORTB ^= (1<<PB5);
					SWseriale_write(&uart_rx_command, 1);
				}
				else if(uart_rx_command == 'a'){
					PORTB ^= (1<<PB5);
					SWseriale_write(&uart_rx_command, 1);
				}
				else if(uart_rx_command == 'd'){
					PORTB ^= (1<<PB5);
					SWseriale_write(&uart_rx_command, 1);
				}*/
    	}

    _delay_ms(10); // Wait 10 ms, optional
    }
}

/*printf_P(PSTR("TESTING\r\n"));
_delay_ms(500);
if(new_uart_data){
	printf_P(PSTR("new_uart_data\r\n"));
	if(uart_rx_command == FORWARD){
		//printf_P(PSTR("FORWARD\r\n"));
		new_uart_data = false;
	}
	else if(uart_rx_command == BACKWARD){
		//printf_P(PSTR("BACKWARD\r\n"));
		new_uart_data = false;
	}
	else if(uart_rx_command == LEFT){
		//printf_P(PSTR("LEFT\r\n"));
		new_uart_data = false;
	}
	else if(uart_rx_command == RIGHT){
		//printf_P(PSTR("RIGHT\r\n"));
		new_uart_data = false;
	}
}*/
