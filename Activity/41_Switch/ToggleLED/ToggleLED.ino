// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 3;  // the number of the pushbutton pin
const int ledPin1 = 8;    // the number of the LED pin

const int buttonPin2 = 4;  // the number of the pushbutton pin
const int ledPin2 = 9;    // the number of the LED pin

const int buttonPin3 = 2;  // the number of the pushbutton pin
const int ledPin3 = 10;    // the number of the LED pin

// Variables will change:
int ledState1 = LOW;        // the current state of the output pin
int ledState2 = HIGH;        // the current state of the output pin
int ledState3 = HIGH;        // the current state of the output pin

int buttonState1 = LOW;            // the current reading from the input pin
int buttonState2 = LOW;            // the current reading from the input pin
int buttonState3 = LOW;            // the current reading from the input pin

int lastButtonState1 = LOW;  // the previous reading from the input pin
int lastButtonState2 = LOW;  // the previous reading from the input pin
int lastButtonState3 = LOW;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(ledPin1, OUTPUT);

  pinMode(buttonPin2, INPUT);
  pinMode(ledPin2, OUTPUT);

  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(ledPin3, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
  
}

void loop() {
  // read the state of the switch into a local variable:
  int reading1 = digitalRead(buttonPin1);
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);


  // If the switch changed, due to noise or pressing:
  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (reading3 != lastButtonState3) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      // only toggle the LED if the new button state is HIGH
      if (buttonState1 == HIGH) {
        ledState1 = !ledState1;
      }
    }

      if (reading2 != buttonState2) {
      buttonState2 = reading2;

        // only toggle the LED if the new button state is HIGH
        if (buttonState2 == HIGH) {
          ledState2 = !ledState2;
        }
      }

      if (reading3 != buttonState3) {
      buttonState3 = reading3;

        // only toggle the LED if the new button state is HIGH
        if (buttonState3 == HIGH) {
          ledState3 = !ledState3;
        }
      }
  }

  // set the LED:
  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
}


