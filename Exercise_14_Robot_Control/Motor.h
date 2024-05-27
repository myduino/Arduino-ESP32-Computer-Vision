#ifndef SERMOTOR_H
#define SERMOTOR_H

#include "Arduino.h"
#include <Wire.h>

#define SDA 14
#define SCL 13

uint8_t i2c_addr = 0x30;

uint8_t M1_PWM = 0x01;
uint8_t M1_IN = 0x02;
uint8_t M2_IN = 0x03;
uint8_t M2_PWM = 0x04;

void i2c_init() {
  Wire.begin(SDA, SCL);  // join I2C bus as master (no address provided).
}

// motor: Motor
// pwmvalue：PWM Value
void i2c_write(uint8_t motor, uint8_t pwmvalue) {
  Wire.beginTransmission(i2c_addr);
  Wire.write(motor);
  Wire.write(pwmvalue);
  Wire.endTransmission();
}

void forward(uint8_t M1_speed, uint8_t M2_speed) {
  i2c_write(M1_PWM, M1_speed);
  i2c_write(M1_IN, 0);
  i2c_write(M2_PWM, 0);
  i2c_write(M2_IN, M2_speed);
}

void backward(uint8_t M1_speed, uint8_t M2_speed) {
  i2c_write(M1_PWM, 0);
  i2c_write(M1_IN, M1_speed);
  i2c_write(M2_PWM, M2_speed);
  i2c_write(M2_IN, 0);
}

void turn_left(uint8_t M1_speed, uint8_t M2_speed) {
  i2c_write(M1_PWM, M1_speed);
  i2c_write(M1_IN, 0);
  i2c_write(M2_PWM, M2_speed);
  i2c_write(M2_IN, 0);
}

void turn_right(uint8_t M1_speed, uint8_t M2_speed) {
  // Serial.println("right");
  i2c_write(M1_PWM, 0);
  i2c_write(M1_IN, M1_speed);
  i2c_write(M2_PWM, 0);
  i2c_write(M2_IN, M2_speed);
}

void stop() {
  // Serial.println("Stop");
  i2c_write(M1_PWM, 0);
  i2c_write(M1_IN, 0);
  i2c_write(M2_PWM, 0);
  i2c_write(M2_IN, 0);
}

#endif