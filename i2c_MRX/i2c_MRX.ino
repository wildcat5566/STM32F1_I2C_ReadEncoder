#include "MotorState_v1.h"
#define ExtResetPin 22
MotorObject WL;
int wl_count;
bool wl_collide;

void setup() {
  Serial.begin(115200);
  Motor_Init(ExtResetPin);
  WL.setSlaveAddress(0x4F);
  WL.Reverse();
}

void loop() {
  WL.getMotorState(&wl_count, &wl_collide);
  Serial.print(wl_count); Serial.print(", "); Serial.println(wl_collide);
}

