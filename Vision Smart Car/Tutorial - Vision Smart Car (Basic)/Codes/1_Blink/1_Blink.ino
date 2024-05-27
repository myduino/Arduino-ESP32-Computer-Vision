/*
  Keyestudio ESP32-CAM Video Smart Car
  Control LED Flashing
  https://www.keyestudio.com
*/
#define LED 12  //Define LED as 12 pin
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);  //Set IO12 pin as output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED,HIGH);   //IO12 pin outputs high level
  delay(1000);              //delay 1s
  digitalWrite(LED,LOW);    //IO12 pin outputs low level
  delay(1000);              //delay 1s
}
