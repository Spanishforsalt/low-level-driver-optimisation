# A low level example program 

**Program.c and convert_txt_to_bin.c are the files I created / modified**

## Example scenario
The scenario is making a user-space application that controls some hardware through a driver  
This driver provides a header which contains various #DEFINEs and function prototypes  
The driver also provides documentation on how to communicate with the hardware  
  
  
The task was to make a user-space application that reads instructions from a file and executes those instructions on the hardware

## Device Specification
![Screenshot from 2020-11-19 19-54-30](https://user-images.githubusercontent.com/72558704/99721387-0cf1a480-2aa7-11eb-89db-2e9ab84a5cee.png)
![Screenshot from 2020-11-19 19-54-46](https://user-images.githubusercontent.com/72558704/99721513-44605100-2aa7-11eb-95ee-8c6c16014aec.png)

The device has
  * An array of 3 LEDs
  * A buzzer
  * A 4-bit motor speed controller
  * A 4-bit revolution sensor (speed of motor)
  * A 1-bit motor status sensor (on/off)
  * 3 1-bit alarm sensors (should be recorded)
  * Communication by a specially formatted 8-bit input/output bytes passed to the driver

## Program Requirements

* Read a sequence of commands from a text file given on command line
* Execute those commands on the hardware
* Monitor and record any alarms that happen
* If the revolution sensor and speed the motor was set to disagree by more than 10%, stop the motor and quit the program
* Write the alarms to a binary file


## Modifications

program.c is the main program that was modified  
driver.h / driver.c are a dummy driver  
perfect_run.c / some_alarms.c / unreliable.c control the driver behaviour  

Firstly I made convert_txt_to_bin.c to convert the given .txt input files to .bin and modified program.c to read these .bin files.  
Next, I made sure program.c saved only the steps which triggered alarms.   
Finally, I introduced manual control so that the user can give commands to the driver manually rather than through an input file, by typing "manual" rather than the file path after the a.out executable.  

