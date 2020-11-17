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


struct servo_struct servo_values;

void main (void) {
	uint8_t indexing = 0;

	servo_values.speed = 0;
	servo_values.stearing_angle = 0;

	//Initate uart and send byte to servo controller for baudrate auto-detection.
	uart_init();
	putchar(0xAA);
	Set_Target_Mini_SSC(0,servo_values.stearing_angle);
	Set_Target_Mini_SSC(1,servo_values.speed);

	sei();
	SWseriale_begin(); // Initialize INT1, Timer2, Pin 3 (Input, Pull-up) and Pin 4 (Output)

	while (1){
		if(SWseriale_available()){
			servo_values.receive_buffer[indexing] = SWseriale_read();
			indexing++;

			if(indexing >= 6){
				cli();	//Disable interrupts from software serial otherwise
				process_joystick_data();
				convert_processed_joystick_data();

				Set_Target_Mini_SSC(0,servo_values.stearing_angle);
				Set_Target_Mini_SSC(1,servo_values.speed);

				indexing = 0;
				sei();		//Done activate sofware serial interrupts again.
			}
		}
	}
}
