void setup() {
  Serial.begin(9600); 
}

void loop() {  
  int potentiometerValue = analogRead(A0);
  float potentiometerVoltage = potentiometerValue * (3.3 / 1024.0);

  Serial.print("ADC Value: ");
  Serial.print(potentiometerValue);
  Serial.print("\tVoltage: ");
  Serial.print(potentiometerVoltage);
  Serial.println(" V");
  
  delay(1000);
}
