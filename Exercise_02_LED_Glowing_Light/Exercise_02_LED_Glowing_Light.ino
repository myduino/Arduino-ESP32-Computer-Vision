void setup() {
  // configure PWM controller congfiguration.
  ledcSetup(0, 5000, 8);
  // declare the GPIO number for PWM signal output.
  ledcAttachPin(2, 0);
}

void loop() {
  // for() statement to create incremental value by +1 start from 0 --> 255
  // from the LED OFF to linear increasing brightness.
  for(int brightness = 0; brightness <= 255; brightness++){   
    // ledcWrite() function will generate PWM output signal according to variable brightness value
    // 1st argument: PWM channel number.
    // 2nd argument: PWM value.
    ledcWrite(0, brightness);
    delay(15);
  }
  // wait for 0.2 seconds before start again.
  delay(200);
}