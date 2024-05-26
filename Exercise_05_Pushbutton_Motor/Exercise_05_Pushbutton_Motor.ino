int led = 5; // LED Pin (D1)
int button = 16; // Pushbutton is connected to D0
int temp = 0; // Temporary variable for reading the button pin status

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  // declare LED as output
  // declare push button as input
  temp = digitalRead(button);
  
  if (temp == HIGH) {
    digitalWrite(led, HIGH);
    Serial.println("Motor Start");
    delay(1000);
  }
  
  else {
    digitalWrite(led, LOW);
    Serial.println("Motor Stop");
    delay(1000);
  }
}