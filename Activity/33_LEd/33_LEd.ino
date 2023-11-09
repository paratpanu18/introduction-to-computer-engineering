int delayTime = 100;

void setup() {
 
}


void LEDon(char mode1[10],char mode2[10],char mode3[10], char lvl1[10], char lvl2[10], char lvl3[10]) {
  pinMode(8, mode1);
  pinMode(9, mode2);
  pinMode(10, mode3);

  digitalWrite(8, lvl1);
  digitalWrite(9, lvl2); 
  digitalWrite(10, lvl3);
}

void loop() {
  // LED 1
  LEDon(OUTPUT, OUTPUT, INPUT, LOW, HIGH, LOW);
  delay(delayTime);

  // LED 2
  LEDon(OUTPUT, OUTPUT, INPUT, HIGH, LOW, LOW);
  delay(delayTime);

  // LED 3
  LEDon(INPUT, OUTPUT, OUTPUT, LOW, LOW, HIGH);
  delay(delayTime);

  // LED 4
  LEDon(INPUT, OUTPUT, OUTPUT, LOW, HIGH, LOW);
  delay(delayTime);

  // LED 5
  LEDon(OUTPUT, INPUT, OUTPUT, LOW, LOW, HIGH);
  delay(delayTime);

  // LED 6
  LEDon(OUTPUT, INPUT, OUTPUT, HIGH, LOW, LOW);
  delay(delayTime);

  // LED 5
  LEDon(OUTPUT, INPUT, OUTPUT, LOW, LOW, HIGH);
  delay(delayTime);

  // LED 4
  LEDon(INPUT, OUTPUT, OUTPUT, LOW, HIGH, LOW);
  delay(delayTime);

  // LED 3
  LEDon(INPUT, OUTPUT, OUTPUT, LOW, LOW, HIGH);
  delay(delayTime);

  // LED 2
  LEDon(OUTPUT, OUTPUT, INPUT, HIGH, LOW, LOW);
  delay(delayTime);
}


