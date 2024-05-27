#include "Motor.h"

void setup() {
  i2c_init();
}

void loop() {
  forward(100, 100);  // right speed, left speed
  delay(2000);
  backward(100, 100);
  delay(2000);
  turn_left(100, 100);
  delay(2000);
  turn_right(100, 100);
  delay(2000);
  stop();
  delay(2000);
}