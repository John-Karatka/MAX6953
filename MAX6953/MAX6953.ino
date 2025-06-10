#include <Wire.h>

const int DEVICE_ADDRESS = 80; //Double check your address pins
const byte START_REGISTER = 0x20;
const int DELAY_MS = 500; //Delay between updates

void setup() {
  Wire.begin();
  setupDisplay();
}

void loop() {
  for (int count = 0; count <= 9999; count++) {
    sendNumber(count);
    delay(DELAY_MS);
  }
}

void sendNumber(int number) {
  int thousands = (number / 1000) % 10;
  int hundreds  = (number / 100) % 10;
  int tens      = (number / 10) % 10;
  int ones      = number % 10;

  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(START_REGISTER);

  Wire.write(0b00110000 | thousands);
  Wire.write(0b00110000 | hundreds);
  Wire.write(0b00110000 | tens);
  Wire.write(0b00110000 | ones);

  Wire.endTransmission();
}

void setupDisplay() {
  //Turn on Chip and set configs
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(0x04);

  //Wire.write(0x0D); //blink
  Wire.write(0x01); //no blink

  Wire.endTransmission();
  delay(100);

  //Set brightness (12.5mA)
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(0x01);
  Wire.write(0x77);
  Wire.endTransmission();
  delay(100);
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(0x02);
  Wire.write(0x77);
  Wire.endTransmission();
  delay(100);

  //Enable all 4 digits
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write(0x03);
  Wire.write(0x01);
  Wire.endTransmission();
}
