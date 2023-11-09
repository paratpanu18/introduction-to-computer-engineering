const int ledPin[4] = {8, 9, 10, 11};
void setup() {
  for(int i = 0; i < 4; i++) pinMode(ledPin[i], OUTPUT);
  for(int i = 0; i < 4; i++) {
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  for(int i = 0; i < 4; i++) {
    digitalWrite(ledPin[i], HIGH);
    delay(500);
  }
  
  for(int i = 3; i >= 0; i--) {
    digitalWrite(ledPin[i],LOW);
    delay(500);
  }
}