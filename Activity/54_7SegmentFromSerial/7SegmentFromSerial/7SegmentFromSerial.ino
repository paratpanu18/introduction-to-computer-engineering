const int segmentPin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
bool number[10][7] = {1, 1, 1, 1, 1, 1, 0,
                        0, 1, 1, 0, 0, 0, 0,
                        1, 1, 0, 1, 1, 0, 1,
                        1, 1, 1, 1, 0, 0, 1,
                        0, 1, 1, 0, 0, 1, 1,
                        1, 0, 1, 1, 0, 1, 1,
                        1, 0, 1, 1, 1, 1, 1,
                        1, 1, 1, 0, 0, 0, 0,
                        1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 0, 1, 1};
int incommingByte = '0';

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 9; i++) {
    pinMode(segmentPin[i], OUTPUT);
  }
}

void ShowNum(int num) {
  for (int i = 0; i < 7; i++) {
  	digitalWrite(segmentPin[i], !number[num][i]);
  }
}


void loop()
{
  delay(500);
  if (Serial.available() > 0) {
    incommingByte = Serial.read();
    if (incommingByte >= '0' && incommingByte <= '9') {
      digitalWrite(9, HIGH);
      ShowNum(incommingByte - '0');
    }
    else if (incommingByte != 10) {
      digitalWrite(9, LOW); 
      for (int i = 0; i < 7; i++) {
  	    digitalWrite(segmentPin[i], HIGH);
      }
    }
  }
}