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

#include "main.h"
#include "adc.h"
#include "gpio.h"
#include "math_functions.h"
#include "serial.h"
#include "timer.h"

// mac 98:D3:81:FD:68:2F

struct servo_struct servo_values;


volatile bool proess_message = false;

void main (void) {
	uint8_t indexing = 0;
	uart_init();
	putchar(0xAA);
	sei();
	SWseriale_begin(); // Initialize INT1, Timer2, Pin 3 (Input, Pull-up) and Pin 4 (Output)

	while (1){
		if(SWseriale_available()){
			servo_values.receive_buffer[indexing] = SWseriale_read();
			indexing++;

			if(indexing >= 6){
				cli();
				process_joystick_data();
				convert_processed_joystick_data();
				Set_Target_Mini_SSC(0,servo_values.stearing_angle);
				printf("stearing_angle: %d speed: %d\n", servo_values.stearing_angle, servo_values.speed);

				//printf("%d%d%d",255,0,127);
				//_delay_ms(500);
				//printf("%d%d%d",255,0,100);
				//_delay_ms(500);
				//printf("%d%d%d",255,0,154);
				//_delay_ms(500);
				indexing = 0;
				sei();
			}
		}
	}
}


// TESTING
/*
if(SWseriale_available()){
	servo_values.receive_buffer[indexing] = SWseriale_read();
	indexing++;

	if(indexing >= 6){
		cli();
		printf("recv: %s\n", servo_values.receive_buffer);
		process_joystick_data();
		printf("serial: %d %d %d\n", servo_values.angle,servo_values.strenght,servo_values.state);
		indexing = 0;
		sei();
	}
}
*/
