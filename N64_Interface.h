//  ************* ORIGINAL KUDOS ************* https://github.com/LogicalUnit/N64_Interface
/**
 * Author: John Crain Welsby (john.welsby@gmail.com) in collaboration with Arduino community, especially Nick Gammon.
 * Date: October 2016
 * Version: 1.0
 *
 * Use this header file to communicate with a Nintendo 64 controller. It is specifically designed to run on a 16MHz 5V Arduino Uno, or compatible.
 * Looking into the N64 controller connector, arrow on top, wires from left to right are: GND, Data, 3V3.
 * You must specify which pin is connected to the Data wire in the constructor of N64_Interface. Valid pins are: 2, 3, 4, 5, 6, or 7.
 * If you just want to get the status of the N64 controller's joystick and buttons, use the convenience functions to send and receive status queries.
 * Multi-byte queries, such as when communicating with a memory card, have not been tested -- but might work.
 * Be sure to disable interrupts when communicating with the controller.
 * Search online for more information about the N64 controller communication protocol.
 */


//  V2.00
//  VajskiDs consoles (October 2022)
//  Reworked into an In Game reset!


// **************  IGR Combination L+R+A+B+Z  **************


#ifndef N64_INTERFACE_H
#define N64_INTERFACE_H



//Status buttons1:
const char BUTTON_D_RIGHT = 0x01;
const char BUTTON_D_LEFT = 0x02;
const char BUTTON_D_DOWN = 0x04;
const char BUTTON_D_UP = 0x08;
const char BUTTON_START = 0x10;
const char BUTTON_Z = 0x20;
const char BUTTON_B = 0x40;
const char BUTTON_A = 0x80;

//Status buttons2:
const char BUTTON_C_RIGHT = 0x01;
const char BUTTON_C_LEFT = 0x02;
const char BUTTON_C_DOWN = 0x04;
const char BUTTON_C_UP = 0x08;
const char BUTTON_R = 0x10;
const char BUTTON_L = 0x20;

//Controller commands (queries to send).
const char COMMAND_IDENFITY = 0x00;
const char COMMAND_STATUS = 0x01;

//Structure for storing controller status (joystick and buttons).
typedef struct {
  char buttons1;
  char buttons2;
  char stick_x;
  char stick_y;
} N64_Status;

//Number of bytes in a N64_Status struct
const int status_size = sizeof(N64_Status);

//Print the contents of a N64_Status struct to serial
void IGR(const N64_Status& status); 

//Interface to the Nintendo 64 controller
class N64_Interface {

public:
  //Specify which pin is connected to the N64 controller's Data wire. Choose pin 2, 3, 4, 5, 6, or 7.
  N64_Interface(int serialpin = 2); 

  //Convenience function. Send the status query byte to the controller.
  void sendStatusQuery();

  //Convenience function. Receive the status response from the controller.
  void receiveStatus(N64_Status& status);

  //Send bytes starting at input to controller, length is number of bytes to send.
  void send(char const* input, unsigned int length);

  //Receive bytes starting at output from controller, length is number of bytes to receive.
  void receive(char* output, unsigned int length);

private:
  //Hex representation of the data pin.
  char mask_; 

};

#endif
