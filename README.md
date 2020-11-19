# A low level example program 

## Example scenario
The scenario is making a user-space application that controls some hardware through a driver  
This driver provides a header which contains various #DEFINEs and function prototypes  
The driver also provides documentation on how to communicate with the hardware  
The task was to make a user-space application that reads instructions from a file and executes those instructions on the hardware

## Modifications

program.c is the main program that was modified  
driver.h / driver.c are a dummy driver  
perfect_run.c / some_alarms.c / unreliable.c control the driver behaviour  

Firstly I made convert_txt_to_bin.c to convert the given .txt input files to .bin and modified program.c to read these .bin files.  
Next, I made sure program.c saved only the steps which triggered alarms.   
Finally, I introduced manual control so that the user can give commands to the driver manually rather than through an input file, by typing "manual" rather than the file path after the a.out executable.  

