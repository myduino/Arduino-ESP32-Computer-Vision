void setup() {
  // declaring GPIO2 as an OUTPUT pin.
  pinMode(2, OUTPUT);

}

void loop() {
  // strobe light effect, such on the aeroplane.
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);

  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(2000);
}