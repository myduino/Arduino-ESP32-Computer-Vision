void setup() {
  Serial.begin(9600); 
}

void loop() {  
  int sensorValue = analogRead(A0);
  float sensorVoltage = sensorValue * (3.3 / 1024.0);
  
  Serial.print("ADC Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  
  delay(1000);
}
