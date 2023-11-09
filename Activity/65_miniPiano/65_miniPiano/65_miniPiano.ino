#define Do 261
#define Re 294
#define Mi 330
#define Fa 349
#define Sol 392
#define La 440
#define Si 494
#define DoH 523

int buttonState[8];
int recordedNote[100] = {};
int noteCount = 0;
int isRecord;
int currentNote = 0;

int j = 0;


void record(int note) {
  if (note != 0) {
    recordedNote[j] = note;
    noteCount++;
    j++;
    Serial.println(note);
  }
}


void setup() {

  Serial.begin(9600);

  for (int i = 0; i < 100; i++) {
    Serial.println(" ");
  }

  Serial.println("Welcome to Mini Piano");

  for (int i = 5; i <= 12; i++) {
    pinMode(i, INPUT_PULLUP);
    }

  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    buttonState[i] = digitalRead(i+5);
   }
   
   int recordButtonState = digitalRead(0);
   int playButtonState = digitalRead(2);

  //Serial.println(recordButtonState);

   if (recordButtonState == LOW) {
     isRecord = 1;
     j = 0;
     noteCount = 0;
     Serial.println("Start Recorded");
     delay(100);
   }

   if (playButtonState == LOW) {
     isRecord = 0;
     Serial.println("Start Playing");
     for (int i = 0; i < noteCount; i++) {
       tone(3, recordedNote[i]);
       delay(700);
       noTone(3);
     }
     delay(1000);
   }

   if (buttonState[0] == LOW) {
      tone(3, Do);
      if (isRecord) currentNote = Do;
   }
    else if (buttonState[1] == LOW) {
      tone(3, Re);
      if (isRecord) currentNote = Re;
    }
    else if (buttonState[2] == LOW) {
      tone(3, Mi);
      if (isRecord) currentNote = Mi;
    }
    else if (buttonState[3] == LOW) {
      tone(3, Fa);
      if (isRecord) currentNote = Fa;
    }
    else if (buttonState[4] == LOW) {
      tone(3, Sol);
      if (isRecord) currentNote = Sol;
    }
    else if (buttonState[5] == LOW) {
      tone(3, La);
      if (isRecord) currentNote = La;
    }
    else if (buttonState[6] == LOW) {
      tone(3, Si);
      if (isRecord) currentNote = Si;
    }
    else if (buttonState[7] == LOW) {
      tone(3, DoH);
      currentNote = DoH;
    }
    else {
      if (isRecord) {
        record(currentNote);
        currentNote = NULL;
      }
      noTone(3);
     }


}