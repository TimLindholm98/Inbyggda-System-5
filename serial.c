#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "serial.h"

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char)(UBRR);
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C |= (3 << UCSZ00);

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

/*int extract_stearing(char *receive_buffer){
	int i;
	char temp_array[3];
	for (i = 0; i <= 3; i++) {
		if(receive_buffer[i] == ','){
			break;
		}
		temp_array[i] = receive_buffer[i];
	}
	if(isdigit(temp_array)){
		return atoi(temp_array);
	}
	else{
		return 127;
	}
}*/

/*int extract_speed(char *receive_buffer){
	int i;
	char temp_array[3];
	for (i = 0; i <= 3; i++) {
		if(receive_buffer[i] == ','){
			break;
		}
		temp_array[i] = receive_buffer[i];
	}
	if(isdigit(temp_array)){
		return atoi(temp_array);
	}
	else{
		return 127;
	}

}*/

void process_joystick_data(char *receive_buffer, int *angle, int *strenght, int *state){
	char temp_angle[3] = {0};
	char temp_strenght[3] = {0};
	char temp_state = 0;

	for(int i = 0; i < 6; i++){
		if(i <= 2){
			char temp_angle[i];
		}
		else if(i >= 2 && i <= 5){
			char temp_strenght[i];
		}
		else if(i < 5){
			char temp_state = 0;
		}
	}

	*angle = atoi(temp_angle);
	*strenght = atoi(temp_strenght);
	*state = atoi(temp_state);

	}
}
