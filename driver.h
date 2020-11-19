#include <stdint.h>

#define LED1_ON 8
#define LED2_ON 4
#define LED3_ON 2
#define BUZZ_ON 1
#define MOTOR_ON 8
#define ALARM_1 4
#define ALARM_2 2
#define ALARM_3 1

void driver_send_input(uint8_t inp_byte);
uint8_t driver_get_byte();
