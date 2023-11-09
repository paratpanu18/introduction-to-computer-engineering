// Active LED

int buttonState1 = 0;
int buttonState2 = 1;
int buttonState3 = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  Serial.begin(9600);
}

void loop() {
   buttonState1 = digitalRead(3);
   buttonState2 = digitalRead(4);
   buttonState3 = digitalRead(2);

  Serial.println(buttonState3);


  if (buttonState1 == 1) digitalWrite(8, HIGH);
  else digitalWrite(8, LOW);

  if (buttonState2 == 0) digitalWrite(9, HIGH);
  else digitalWrite(9, LOW);

  if (buttonState3 == 0) digitalWrite(10, HIGH);
  else digitalWrite(10, LOW);
}
