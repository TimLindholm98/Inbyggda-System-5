#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "math_functions.h"
#include "serial.h"



static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char)(UBRR);
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C |= (3 << UCSZ00);
	//UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve complete interrupt

	stdout = &uart_stdout;
}

int uart_putchar(char chr, FILE *stream) {
	if (chr == '\n') {
		uart_putchar('\r', NULL);
	}
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = chr;
	return 0;
}

char uart_getchar(void) {
	while (!(UCSR0A & (1 << RXC0)))
		;
	return UDR0;
}

void process_joystick_data(){
	char temp_angle[4] = {0};
	char temp_strenght[4] = {0};

	strncpy(temp_angle, servo_values.receive_buffer, 3);
	strncpy(temp_strenght, servo_values.receive_buffer+3, 3);


	servo_values.direction = atoi(temp_angle);
	servo_values.strenght = atoi(temp_strenght);
	servo_values.state = atoi(servo_values.receive_buffer[6]);

}

void convert_processed_joystick_data(){
	bool forward = false;

	if((servo_values.direction < 360) && (servo_values.direction > 179)){
		servo_values.stearing_angle = map(servo_values.direction,180,359,0,255);			//The high number eqauls the right on the joystick
		forward = false;
	}

	if((servo_values.direction < 179) && (servo_values.direction > 0)){
		servo_values.stearing_angle = map(servo_values.direction,178,0,0,255);
		forward = true;
	}

	if(forward){
		servo_values.speed = map(servo_values.strenght,0,100,122,244);
	}
	else{
		servo_values.speed = map(servo_values.strenght,0,100,122,0);
	}
}

void Set_Target_Mini_SSC(uint8_t channel_address, uint8_t target){
	putchar(0xFF);
	putchar(channel_address);
	putchar(target);

}

/*void constrain_and_remap_data(message_struct *servo_values, servo_struct *servo_values){
	servo_values


	servo_values.speed = map();
	servo_values.stearing_angle();
}*/
