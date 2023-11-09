const int segmentPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
boolean number[9][7] = {
                        0, 1, 1, 0, 0, 0, 0, // 1
                        1, 1, 0, 1, 1, 0, 1, // 2
                        1, 1, 1, 1, 0, 0, 1, // 3
                        0, 1, 1, 0, 0, 1, 1, // 4
                        1, 0, 1, 1, 0, 1, 1, // 5
                        1, 0, 1, 1, 1, 1, 1, // 6
                        1, 1, 1, 0, 0, 0, 0, // 7
                        1, 1, 1, 1, 1, 1, 1, // 8
                        1, 1, 1, 1, 0, 1, 1}; // 9
#define button1pin 12 // A Button
#define button2pin 13 // G Button

int currentNum = 1;
int Ans;
int isCorrect = 1;

// ----- Use for debounce -----

int buttonState1 = HIGH;
int lastButtonState1 = HIGH;

int buttonState2 = HIGH;
int lastButtonState2 = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// ----- Use for debounce -----

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 9; i++) {
    pinMode(segmentPin[i], OUTPUT);
  }
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
  randomSeed(analogRead(0));
  
}

void ShowNum(int num) {
  for (int i = 0; i < 7; i++) {
  	digitalWrite(segmentPin[i], !number[num-1][i]);
  }
}

void submit(int& ans, int& currentNum) { 
  if (ans == currentNum) {
    currentNum = 1;
    int arry[7] = {1, 1, 1, 1, 1, 1, 0};
    for (int k = 0; k < 7; k++) {
    	digitalWrite(segmentPin[k], !arry[k]);   	
    }
    Serial.println("Correct");
    isCorrect = 1;
    delay(1000);
    return;
  }
  if (ans > currentNum) {
    int arry[7] = {1, 0, 0, 0, 1, 1, 0};
    for (int k = 0; k < 7; k++) {
    	digitalWrite(segmentPin[k], !arry[k]);   	
    }
    delay(1000);
  }
  if (ans < currentNum) {
    int arry[7] = {0, 0, 0, 1, 1, 1, 0};
    for (int k = 0; k < 7; k++) {
    	digitalWrite(segmentPin[k], !arry[k]);   	
    }
    delay(1000);
  }
  

}

void loop()
{
  // Reset game if user answer correctly
  if (isCorrect == 1) {
  	Ans = random(1, 9);
    Serial.println(Ans);
    isCorrect = 0;
    
  }
  
  	// ----------- debounce -----------
  	int reading1 = digitalRead(button1pin);
	  int reading2 = digitalRead(button2pin);

    if (reading1 != lastButtonState1) {
      lastDebounceTime = millis();
    }
  
  	if ((millis() - lastDebounceTime) > debounceDelay) {
      
    // If button 1 State change
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      if (buttonState1 == LOW) {
        if (currentNum + 1 > 9) currentNum = 1;
        else currentNum++;
      }
    }
      
      
     // If button 2 State change
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == LOW) {
        submit(Ans, currentNum);
      }
    }
  }
  // ----------- debounce -----------
 
  ShowNum(currentNum);
  
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  
}