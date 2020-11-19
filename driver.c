#include "driver.h"
#include <stdint.h>
#include <stdio.h>

uint8_t motor_speed;
extern uint8_t adjustments[10];
extern uint8_t alarms[10];
int a_index = 0; // index to vary values over time

void driver_send_input(uint8_t inp_byte){
  motor_speed = (inp_byte >> 4) & 0xf;
  printf("Driver: inp_byte is %d\n", inp_byte);
  printf("Driver: Motor Speed set to %d\n", motor_speed);
  // This is one way to print a variable string:
  printf("Driver: LED1 is "); if (inp_byte & LED1_ON){printf("ON\n");} else {printf("OFF\n");}
  printf("Driver: LED2 is "); if (inp_byte & LED2_ON){printf("ON\n");} else {printf("OFF\n");}
  printf("Driver: LED3 is "); if (inp_byte & LED3_ON){printf("ON\n");} else {printf("OFF\n");}
  printf("Driver: BUZZ is "); if (inp_byte & BUZZ_ON){printf("ON\n");} else {printf("OFF\n");}
}

uint8_t driver_get_byte(){
  uint8_t x = motor_speed + adjustments[a_index % 10];
  printf("Driver: Motor Speed is %d\n", x);
  x <<= 4;
  x |= alarms[a_index];
  x |= MOTOR_ON;
  a_index += 1;
  return x;
}
