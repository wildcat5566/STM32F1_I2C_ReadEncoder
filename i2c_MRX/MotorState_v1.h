#ifndef _MOTORSTATE_V1_H_
#define _MOTORSTATE_V1_H_

#include "Wire.h"
#include "Arduino.h"

void Motor_Init(int ExtReset);                   // Externally initialize & reset all slave devices

class MotorObject{
public:
  MotorObject();
  void getMotorState(int* count, bool* collide); // Motor state components: encoder count (int32_t) & collision (bool)
  void setSlaveAddress(uint8_t addr);            // Specify slave address
  void Reverse();                                // Call to set flag & reverse default direction

private:
  uint8_t address;                               // Slave address of STM32 motor control module
  bool rev;                                      // Direction reverse flag
  int hex2dec(uint8_t* hex);                     // Convert hexadecimal byte readings to decimal integer values
};

#endif

