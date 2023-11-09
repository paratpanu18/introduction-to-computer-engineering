void allLOW() {
  for (int i = 5; i < 13; i++) {
    digitalWrite(i, LOW);
  }
}

void showO() {
// Show 0
  digitalWrite(10, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  delay(5);

  allLOW();


  digitalWrite(11, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  delay(5);

  allLOW();

  digitalWrite(12, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  delay(5);
}

void showX() {
// Show X
  digitalWrite(10, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  delay(5);

  allLOW();

  digitalWrite(11, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(5);

  allLOW();

  digitalWrite(12, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  delay(5);
}

void setup() {
  for (int i = 5; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 65; i++) {
    showO();
  }
  for (int i = 0; i < 65; i++) {
    showX();
  }
}
