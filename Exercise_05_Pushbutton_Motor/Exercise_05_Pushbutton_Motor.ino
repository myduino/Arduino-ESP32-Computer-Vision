const int buttonPin = 4;  // the number of the pushbutton pin
const int ledPin =  5;    // the number of the LED pin

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);  // declaring GPIO4 as an INPUT pin.
  pinMode(ledPin, OUTPUT); // declaring GPIO5 as an OUTPUT pin.
}

void loop() {

  int buttonState = digitalRead(buttonPin);
  Serial.println(pbState);
  
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motor Start");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Motor Stop");
  }
}