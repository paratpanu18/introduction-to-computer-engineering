void setup() {
  Serial.begin(9600);
  for (int i = 8; i < 12; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  int reading = analogRead(0);
  Serial.println(reading);
  
  if (reading >= 505 && reading <= 515) {
    digitalWrite(8, HIGH);
  }
  else if (reading >= 997 && reading <= 1007) {
    digitalWrite(9, HIGH);
  }
  else if (reading >= 691 && reading <= 701) {
    digitalWrite(10, HIGH);
  }
  else if (reading >= 832 && reading <= 842) {
    digitalWrite(11, HIGH);
  }
  else {
    for (int i = 8; i < 12; i++) {
      digitalWrite(i, LOW);
    }
  }
  
}
