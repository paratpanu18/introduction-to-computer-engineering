const int ledRed = 8;
const int ledYellow = 9;
const int ledGreen = 10;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT);

  Serial.begin(9600);

  attachInterrupt(1, EXIT1, FALLING);
  attachInterrupt(0, EXIT2, FALLING);

}

void EXIT1() {
  // Right
  //Serial.println("EXIT2");

  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
  delay(5000);
}

int EXIT2() {
  
  // Left

  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);

  digitalWrite(ledRed, HIGH);
  delay(5000);
  digitalWrite(ledRed, LOW);

  Serial.println("EXIT2");
}

void Red() {
  digitalWrite(ledRed, HIGH);
  delay(5000);
  digitalWrite(ledRed, LOW);
  
}

void Yellow() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledYellow, HIGH);
    delay(250);
    digitalWrite(ledYellow, LOW);
    delay(250);
  }
}

void Green() {
  digitalWrite(ledGreen, HIGH);
  delay(7000);
  digitalWrite(ledGreen, LOW);
}

void loop() {
    Green();
    Yellow();
    Red();
}
