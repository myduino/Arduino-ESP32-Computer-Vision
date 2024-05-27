/*
  Keyestudio ESP32-CAM Video Smart Car
  Control the brightness of LED
  https://www.keyestudio.com
*/
#define LED 12  //Define LED as 12 pin
void setup() {
  // put your setup code here, to run once:
  ledcSetup(0, 3000, 8);  //Set pwm channel, frequency and accuracy
  ledcAttachPin(LED, 0);  //Attach the IO port to the ledc channel
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 255; i++) {  //for loop, control i to increase from 0 to 255
    ledcWrite(0, i);               //output pwm
    delay(10);
  }
  for (int i = 255; i > 1; i--) {  //for loop, control i to decrease from 255 to 0
    ledcWrite(0, i);               //output pwm
    delay(10);
  }
}
