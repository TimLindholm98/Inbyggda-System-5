#ifndef SERIAL_H_
#define SERIAL_H_

#define BAUDRATE 9600
#define UBRR (F_CPU/16/BAUDRATE-1)

void uart_init(void);

int uart_putchar(char chr, FILE *stream);

char uart_getchar(void);

void process_joystick_data(void);

void convert_processed_joystick_data();

void Set_Target_Mini_SSC(uint8_t channel_address, uint8_t target);

#endif
