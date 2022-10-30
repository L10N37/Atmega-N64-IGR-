//  ************* ORIGINAL KUDOS *************
/**
 * Author: John Crain Welsby (john.welsby@gmail.com)
 * Date: October 2016
 * Version: 1.0
 * 
 * Simple demonstration of communication with a Nintendo 64 controller.
 * Controller must be connected as described in N64_Interface.h (GND, Data, 3V3).
 * Serial output at 115200 baud.
 */



//  V2.00
//  VajskiDs consoles (October 2022)
//  Reworked into an In Game reset!


// **************  IGR Combination L+R+A+B+Z  **************


#include "N64_Interface.h"
#define resetpin 4
#define serialpin 2


//Global variables
N64_Interface interface(serialpin); //N64 controller Data wire is connected to pin 2.
N64_Status status, oldStatus; //Status of joystick and buttons.

void setup() {
  pinMode (resetpin, INPUT);
  
  //Start by clearing the status variables
  memset(&status, 0, status_size);
  memset(&oldStatus, 0, status_size);
}


void loop() {
  
  noInterrupts(); //Disable interrupts, they interfere with timings.
  interface.sendStatusQuery(); //This is how we send the status query (1 byte).
  interface.receiveStatus(status); //This is how we receive the status response (4 bytes).
  interrupts(); //Timing critical section complete, re-enable interrupts.
  IGR(status);
  delay(500);
 
}
