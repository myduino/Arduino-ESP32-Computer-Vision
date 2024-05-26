const int buttonPin = 4;  // the number of the pushbutton pin
const int ledPin =  5;    // the number of the LED pin

void setup() {
  pinMode(buttonPin, INPUT);  // declaring GPIO4 as an INPUT pin.
  pinMode(ledPin, OUTPUT); // declaring GPIO5 as an OUTPUT pin.

}

void loop() {
  // we use if() function to compare the GPIO4 reading state with the HIGH state.
  // if the GPIO4 reading is HIGH, light ON the LED on GPIO2 with HIGH state.
  // else means, the GPIO4 reading is LOW, light OFF the LED on GPIO4 with LOW state.
  int buttonState = digitalRead(buttonPin);
  Serial.println(pbState);
  
  if(buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW);
  }
}