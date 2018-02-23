#include <Wire.h>
int enc;
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(0x4E, 5); 
  int dec;
  byte hex[5];
   while (Wire.available()) { // slave may send less than requested
    for(int i = 0; i < 5; i ++){
      hex[i] = Wire.read();
      Serial.print(hex[i]);
      Serial.print(", ");
    }
  }
  dec = 16777216*hex[1] + 65536*hex[2] + 256*hex[3] + hex[4];
  if(hex[0]==1){
    dec = dec*(-1);
  }
  Serial.println(dec);
}

