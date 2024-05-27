#ifndef SERMOTOR_H
#define SERMOTOR_H
#include "Arduino.h"
#include <Wire.h>

// Serial.begin(115200);
#define sda 14
#define scl 13
uint8_t slave_addr = 0x30;
uint8_t M1_PWM = 0x01;
uint8_t M1_IN = 0x02;
uint8_t M2_IN = 0x03;
uint8_t M2_PWM = 0x04;

void i2c_init() {
  Wire.begin(sda, scl);  // join I2C bus as master (no address provided).
}

 //motor:    Motor
 //pwmvalue：PWM Value
void i2c_Write(uint8_t motor, uint8_t pwmvalue) {
  Wire.beginTransmission(slave_addr);  // transmit to device
  Wire.write(motor);                   // sends one byte
  Wire.write(pwmvalue);
  Wire.endTransmission();
}

void Car_forward(uint8_t M1_speed,uint8_t M2_speed) {
  //  Serial.println("forward");
  i2c_Write(M1_PWM, M1_speed);
  i2c_Write(M1_IN, 0);
  i2c_Write(M2_PWM, 0);
  i2c_Write(M2_IN, M2_speed);
}

void Car_backwards(uint8_t M1_speed,uint8_t M2_speed) {
  // Serial.println("backwards");
      i2c_Write(M1_PWM, 0);
      i2c_Write(M1_IN, M1_speed);
      i2c_Write(M2_PWM, M2_speed);
      i2c_Write(M2_IN, 0);
}

void Car_left(uint8_t M1_speed,uint8_t M2_speed) {
  // Serial.println("left");
      i2c_Write(M1_PWM, M1_speed);
      i2c_Write(M1_IN, 0);
      i2c_Write(M2_PWM, M2_speed);
      i2c_Write(M2_IN, 0);
}

void Car_right(uint8_t M1_speed,uint8_t M2_speed) {
  // Serial.println("right");
      i2c_Write(M1_PWM, 0);
      i2c_Write(M1_IN, M1_speed);
      i2c_Write(M2_PWM, 0);
      i2c_Write(M2_IN, M2_speed);
}

void Car_stop() {
  // Serial.println("Stop");
  i2c_Write(M1_PWM, 0);
  i2c_Write(M1_IN, 0);
  i2c_Write(M2_PWM, 0);
  i2c_Write(M2_IN, 0);
}

#endif