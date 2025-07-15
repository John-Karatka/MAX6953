#include "MAX6953.h"
#include <Wire.h>

#define address 0x50

MAX6953 MAX_6356(address);
char text[] = "Hello world!";
int textSize;

void setup() {
  Serial.begin(115200);
  int ret;
  do {
    delay(100);
    MAX_6356.init();
  } while(ret != MAX_INIT_SUCCESS);
  delay(100);
  textSize = sizeof(text);
}

void loop() {
  MAX_6356.displayScrollText(text, textSize, SLOW_SCROLL);
}
