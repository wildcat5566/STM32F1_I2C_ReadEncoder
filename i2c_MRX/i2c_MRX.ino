#include <Wire.h>
#define FR_addr 0x4A
#define FL_addr 0x4B
#define RR_addr 0x4C
#define RL_addr 0x4D
#define WR_addr 0x4E
#define WL_addr 0x4F
#define ExtReset 22

int FR, FL, RR, RL, WR, WL;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // External reset for all slaves
  pinMode(ExtReset, OUTPUT);
  digitalWrite(ExtReset, LOW);
  delay(10);
  digitalWrite(ExtReset, HIGH);
}

void loop() {
  FR = hex2dec(FR_addr);
  FL = hex2dec(FL_addr);
  RR = hex2dec(RR_addr);
  RL = hex2dec(RL_addr);
  WR = hex2dec(WR_addr);
  WL = hex2dec(WL_addr);

  Serial.print(FR); Serial.print(", ");
  Serial.print(FL); Serial.print(", ");
  Serial.print(RR); Serial.print(", ");
  Serial.print(RL); Serial.print(", ");
  Serial.print(WR); Serial.print(", ");
  Serial.print(WL); Serial.println();
}

int hex2dec(uint8_t address){
  Wire.requestFrom(address, 5); 
  int dec;
  uint8_t hex[5];
   while (Wire.available()) {
    for(int i = 0; i < 5; i ++){
      hex[i] = Wire.read();
    }
  }
  dec = 16777216*hex[1] + 65536*hex[2] + 256*hex[3] + hex[4];
  if(hex[0]==1){
    dec = dec*(-1);
  }
  return dec;
}
