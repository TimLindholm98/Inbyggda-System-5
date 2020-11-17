
struct servo_struct{	
  char receive_buffer[7];
	int direction;
	uint8_t strenght;
	uint8_t state;

  uint8_t speed;
	uint8_t stearing_angle;
};


extern struct servo_struct servo_values;
