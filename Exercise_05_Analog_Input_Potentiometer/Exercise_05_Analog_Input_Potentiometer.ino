void setup() {
  Serial.begin(115200);
}

void loop() {  
  int adc = analogRead(34);
  float voltage = adc * (3.3 / 4095.0);

  Serial.print("ADC Value: ");
  Serial.print(adc);
  Serial.print("\tVoltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  
  delay(500);
}
