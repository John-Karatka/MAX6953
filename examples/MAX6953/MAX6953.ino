#include <MAX6953.h>

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
  textSize = sizeof(text);
}

void loop() {
  MAX_6356.displayScrollText(text, textSize, SCROLL_SPEED_100MS);
}
