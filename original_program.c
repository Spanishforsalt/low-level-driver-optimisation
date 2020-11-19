#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "driver.h"

struct hw_state {
  char led1_on;
  char led2_on;
  char led3_on;
  char buzz_on;
  uint8_t motor_speed;
} state;

struct cmdls {
 int cmd_no;
 int cmd_arg;
 struct cmdls* next;
};

struct alarm_info {
 char alarm_1;
 char alarm_2;
 char alarm_3;
 struct alarm_info* next_alarm;
};

int main(int argc, char** argv){
 if (argc != 2){
   printf("Wrong number of arguments, expected 1, got %d\n", argc-1);
   return 1;
 }
 char* input_path = argv[1]; // first argument; 0 is name of executable
 struct alarm_info first_alarm_info;
 struct alarm_info* prev_alarm_info = &first_alarm_info;
 uint8_t inp_byte;
 uint8_t shifted_speed;
 uint8_t out_byte;
 uint8_t revs;
 float ratio; 
 struct cmdls first_cmd;
 struct cmdls* current = &first_cmd;
 struct cmdls* next;
 FILE* inp_fp = fopen(input_path, "r");
 
 while (fscanf(inp_fp, "%d %d\n", &current->cmd_no, &current->cmd_arg) != -1){
   printf("Read Command %d Arg %d\n", current->cmd_no, current->cmd_arg);
   next = calloc(1, sizeof(struct cmdls));
   current->next = next;
   current = next;
 }
 fclose(inp_fp);
 
 current = &first_cmd;
 
 while (current){
   switch (current->cmd_no){
     case 1:
       state.motor_speed = current->cmd_arg; 
       printf("Set Motor Speed to %d\n", current->cmd_arg);
       break;
     case 2:
       state.buzz_on = current->cmd_arg; 
       printf("Set Buzz to %d\n", current->cmd_arg);
       break;      
     case 3:
       state.led1_on = current->cmd_arg; 
       printf("Set led1 to %d\n", current->cmd_arg);
       break;
     case 4:
       state.led2_on = current->cmd_arg;
       printf("Set led2 to %d\n", current->cmd_arg);
       break;
     case 5:
       state.led3_on = current->cmd_arg;
       printf("Set led3 to %d\n", current->cmd_arg);
       break;
     default: 
      /* error handling - not implemented here */
        break;
  }
  inp_byte = 0;
  if (state.led1_on) {
    inp_byte |= LED1_ON;
  }
  if (state.led2_on) {
    inp_byte |= LED2_ON;
  }
  if (state.led3_on) {
    inp_byte |= LED3_ON;
  }
  if (state.buzz_on) {
    inp_byte |= BUZZ_ON;
  }
  shifted_speed = state.motor_speed << 4;
  inp_byte |= shifted_speed;

  driver_send_input(inp_byte);
  
  out_byte = driver_get_byte();
  
  struct alarm_info* info = calloc(1, sizeof(struct alarm_info));
  info->alarm_1 = out_byte & ALARM_1;
  info->alarm_2 = out_byte & ALARM_2;
  info->alarm_3 = out_byte & ALARM_3;
  printf("Got Alarm 1:%d 2:%d 3:%d\n", info->alarm_1, info->alarm_2, info->alarm_3);
  prev_alarm_info->next_alarm = info;
  prev_alarm_info = info;
  revs = (out_byte >> 4) & 0xf;
  if (state.motor_speed){ // don't divide by zero
    ratio = (float) revs / state.motor_speed; // c will do integer division if we don't cast an argument to float
    printf("Reported motor speed is %d/%d=%.2f * set motor speed\n", revs, state.motor_speed, ratio);
    if (ratio < 0.9 || ratio > 1.1){
      /* somethings gone wrong */
      printf("Error: Shutting down\n");
      inp_byte &= 0xf; // Set motor speed to 0
      driver_send_input(inp_byte);
      break; /* break out of our main loop */
    }
  }
  current = current->next;
 }
 
 char output[3];
 FILE* fp;
 fp = fopen("out.data", "wb");
 struct alarm_info* current_alarm = first_alarm_info.next_alarm;
 struct alarm_info* next_alarm;
 while (current_alarm){
  output[0] = current_alarm->alarm_1;
  output[1] = current_alarm->alarm_2;
  output[2] = current_alarm->alarm_3;
  fwrite(output, sizeof(char), 3, fp);
  next_alarm = current_alarm->next_alarm;
  free(current_alarm);
  current_alarm = next_alarm;
 }
 fclose(fp);
}
