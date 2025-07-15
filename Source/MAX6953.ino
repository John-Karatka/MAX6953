#include "MAX6953.h"
#include <Wire.h>

#define address 0x50

MAX6953 MAX_6356(address);

void setup() {
  Serial.begin(115200);
  int ret;
  Serial.println("Enter main");
  do {
    delay(100);
    MAX_6356.init(NO_BLINK);
  } while(ret != MAX_INIT_SUCCESS);
  Serial.println("Success");
  MAX_6356.updateDisplayPane0('1', '2', '3', '4');
  Serial.println("Updated");
}

void loop() {
  delay(1000);
}
