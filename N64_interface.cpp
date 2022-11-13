/**
 * Author: John Crain Welsby (john.welsby@gmail.com) in collaboration with Arduino community, especially Nick Gammon.
 * Date: October 2016
 * Version: 1.0
 * 
 * Implementation of N64_Interface. Specifically designed to run on 16MHz 5V Arduino Uno, or compatible.
 */




//  V2.00
//  VajskiDs consoles (October 2022)
//  Reworked into an In Game reset!


// **************  IGR Combination L+R+A+B+Z  **************


#include "N64_Interface.h"
#include "Arduino.h"

//Do nothing for 1 cycle, 1/16 of a microsecond on Arduino Uno
#define NOP asm volatile ("nop\n\t") //as per original, delayMicroseconds doesn't seem to be as accurate - insta crash. Tried using 1 and 3 microseconds respectively. Moved to macros.
#define OneMicroSecondDelay NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;
#define ThreeMicroSecondDelay NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP; NOP;
#define low bitWrite(DDRD, 2, 1);   //Make data pin an output (low)
#define high bitWrite(DDRD, 2, 0);  //Make data pin an input (high impedence, lets if float, console pulls it up)
#define resetpin 4
#define rst bitWrite (DDRD, resetpin, 1), bitWrite(PORTD, resetpin, 0), delay(100), bitWrite (DDRD, resetpin, 0)
int timer = 0x00;

N64_Interface::N64_Interface(int serialpin) : mask_(1 << serialpin) {

}


void N64_Interface::send(char const* input, uint16_t length) {
  
  for (int i = 0; i < length; i++) {
    char currentByte = input[i];

    for (int j = 0; j < 8; j++) {
      bool currentBit = currentByte & 0x80;  //get leftmost bit
      currentByte <<= 1;                     //shift left

      if (currentBit) {
        //send logical 1
        low
        OneMicroSecondDelay
        high
        ThreeMicroSecondDelay
      } else {
        //send logical 0
        low
        ThreeMicroSecondDelay
        high
        OneMicroSecondDelay
      }
    }
  }

  //send stop bit
  bitWrite(DDRD, 2, 1);  //Make data pin an output (low)
  OneMicroSecondDelay
  bitWrite(DDRD, 2, 0);  //Make data pin an input (high impedence, simulates high
}


void N64_Interface::receive(char* output, uint16_t length) {

  char mask = mask_;  //Create a local copy for speed reasons


  for (int i = 0; i < length; i++) {
    char currentByte = 0;

    for (int j = 0; j < 8; j++) {
      while (PIND & mask) {};     //wait for low

      //wait 1 microsecond
      OneMicroSecondDelay

      currentByte <<= 1;                  //shift left
      currentByte |= (PIND & mask) != 0;  //add latest bit

      while (!(PIND & mask)) {};    //wait for high
    }

    output[i] = currentByte;
  }

  //wait for stop bit
  while (PIND & mask)
    ;
  while (!(PIND & mask))
    ;

}


void IGR(const N64_Status& status) {
  if (status.buttons1 & BUTTON_A && status.buttons1 & BUTTON_B && status.buttons1 & BUTTON_Z && status.buttons2 & BUTTON_L && status.buttons2 && BUTTON_R) timer++;  // Wanted to use START instead of Z but this can't catch that combo for some reason.
  else timer = 0x00;
  
  if (timer == 4) rst;
}


void N64_Interface::sendStatusQuery() {
  send(&COMMAND_STATUS, 1);  //Pass the status command byte to the send() function.
}

void N64_Interface::receiveStatus(N64_Status& status) {
  receive((char*)&status, status_size);  //Pass the status struct to the receive() function.
}