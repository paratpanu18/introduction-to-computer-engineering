// Pin setup
const int ledPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int signalButton = 10;
const int confirmButton = 11;

int inputCount = 0;
int inputNumber = 0;
int initialNumber = 0;
unsigned long lastConfirmTime = 0;

// Forward Declaration
void showNumber(int num);
void resetState();
void cycle();

void setup() {
    Serial.begin(9600);

    for (int i = 0; i < 8; i++) pinMode(ledPin[i], OUTPUT);
    pinMode(signalButton, INPUT);
    pinMode(confirmButton, INPUT);

    showNumber(0);
}

void loop() {
    while (inputCount < 4) {
      if (digitalRead(confirmButton) && millis() - lastConfirmTime > 200) {
        if (digitalRead(signalButton)) {
          bitWrite(inputNumber, 3 - inputCount, 1);
          inputCount++;
          lastConfirmTime = millis(); // Debounce
        }
        else if (!digitalRead(signalButton)) {
          bitWrite(inputNumber, 3 - inputCount, 0);
          inputCount++;
          lastConfirmTime = millis(); // Debounce
        }
      }
    }

    initialNumber = inputNumber;
    Serial.print("Your Number is ");
    Serial.println(initialNumber);
    Serial.println("---------------");
    showNumber(inputNumber);
    delay(1000);
    
    cycle();

    resetState();
}

void showNumber(int num) {
  for(int i = 0; i < 8; i++) digitalWrite(ledPin[i], bitRead(num, i));
}

void cycle() {
  for(int i = 0; i < 3; i++) {
    while (inputNumber * 2 < 256) {
      inputNumber *= 2;
      showNumber(inputNumber);
      Serial.println(inputNumber);
      delay(500);
    }
    while (inputNumber / 2 >= initialNumber) {
      inputNumber /= 2;
      showNumber(inputNumber);
      Serial.println(inputNumber);
      delay(500);
    }
    Serial.println("---------------");
  }
}

void resetState() {
  inputCount = 0;
  inputNumber = 0;
  initialNumber = 0;
  showNumber(0);
}