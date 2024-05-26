void setup() {
  // configure PWM controller congfiguration.
  ledcSetup(0, 5000, 8);
  // declare the GPIO number for PWM signal output.
  ledcAttachPin(2, 0);
}

void loop() {
  // function for() to create decremental value by 1 start from 255 --> 0
  // from OFF LED to linear increasing brightness, for active-low circuit.
  for(int brightness = 255; brightness >= 0; brightness--){   
    // ledcWrite() function will generate PWM output signal according to variable brightness value
    // 1st argument: PWM channel number.
    // 2nd argument: Tone frequency.
    ledcWrite(0, brightness);
    delay(15);
  }
  // wait for 0.2 seconds before start again.
  delay(200);
}