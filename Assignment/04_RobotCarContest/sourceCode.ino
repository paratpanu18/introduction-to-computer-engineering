////////////////////////////////////////////////////
//                 !!! Motor Pin !!!              //
//  Right Speed Control = 11 | Direction = 6 & 7  //
//  Left Speed Control = 5   | Direction = 9 & 10 //
// --------------------------------------------   //
//       Direction 1 | Direction 2 | Robot        //
//           LOW          HIGH      FORWARD       //
//           HIGH         LOW       BACKWARD      //
////////////////////////////////////////////////////

const int leftMotorPin = 5, leftMotorDirection1 = 10, leftMotorDirection2 = 9;
const int rightMotorPin = 11, rightMotorDirection1 = 7, rightMotorDirection2 = 6;

const int onoffButton = 13;
const int LDR = 2 ; 


// ---------------------------------------------- //


///////////////////////////
// IR pin = analog 0 - 4  //
///////////////////////////
const int irAmout = 5;
const int irPin[irAmout] = {};
int irSensorRead[irAmout] = {};
int irSensor[irAmout] = {};
const float irTreshold = 500;

bool isEndClockTriggered = false;

int hardturn = 0 ;
int count_hardturn = 0 ;

unsigned long time = 0 , time_stop = 0  , end_stop = 0 ;
unsigned long time_intersec = 0 ;
unsigned long delay_end = 0 ; 

long stopClock = 0;

bool istime = false ;
bool islight = false ;
int count_light = 0 ;
int count_stop = 0 ;
const int baseSpeed = 150;
int errorShiftLeft = 40, errorShiftRight = 0;
int leftSPD, rightSPD;

// Forward Declare
void motor(int leftMotorSPD, int rightMotorSPD);
void readSensor();
void calculateSpeed();
void setForward();
void setBackward();
void intersections();


void setup() {
  //////////////////////////////////////////////
  // Turn Serial of when not in use naja eiei //
  //////////////////////////////////////////////
  //Serial.begin(9600); // <--- Comment this line

  /////////////////////
  // MOTOR PIN SETUP //
  ////////////////////
  pinMode(rightMotorPin, OUTPUT);
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorDirection1, OUTPUT);
  pinMode(rightMotorDirection2, OUTPUT);
  pinMode(leftMotorDirection1, OUTPUT);
  pinMode(leftMotorDirection2, OUTPUT);

  pinMode(onoffButton, INPUT);
  pinMode(LDR , INPUT);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

}

//**********************************************************************************
void loop() {
  if (!digitalRead(onoffButton)) {
    motor(0, 0);
    delay(1000);
  }
  else if (digitalRead(onoffButton)) {
    readSensor();
    calculateSpeed();
    motor(rightSPD, leftSPD); // r l 
  }
}
//*********************************************************************************

void readSensor() {
  irSensorRead[0] = analogRead(A0);
  irSensorRead[1] = analogRead(A1);
  irSensorRead[2] = analogRead(A2);
  irSensorRead[3] = analogRead(A3);
  irSensorRead[4] = analogRead(A4);


  for (int i = 0; i < irAmout; i++) {
    if (irSensorRead[i] > irTreshold) irSensor[i] = 1  ;
    else if (irSensorRead[i] <= irTreshold) irSensor[i] = 0;
  }
}

void motor(int rightMotorSPD, int leftMotorSPD) {
  if (rightMotorSPD < 0) rightMotorSPD = 0;
  if (leftMotorSPD < 0) leftMotorSPD = 0;

  analogWrite(rightMotorPin, rightMotorSPD);
  analogWrite(leftMotorPin, leftMotorSPD);
}

void calculateSpeed() {
    if(count_stop == 2 && !isEndClockTriggered) {
      stopClock = millis();
      isEndClockTriggered = true;
    }

  if (irSensor[0] == 0 || irSensor[1] == 0 || irSensor[2] == 0 || irSensor[3] == 0 || irSensor[4] == 0) time = millis();

  // Full Forward W-W-B-W-W
  if (irSensor[0] == 1 && irSensor[1] == 1 && irSensor[2] == 0 && irSensor[3] == 1 && irSensor[4] == 1) {
    setForward();
    rightSPD = 100  + errorShiftRight;
    leftSPD = 100 + errorShiftLeft;
  }

  // Encounter Intersection B-B-B-B-B
  else if (irSensor[0] == 0 && irSensor[1] == 0 && irSensor[2] == 0 && irSensor[3] == 0 && irSensor[4] == 0 && count_stop < 2 ) {//11011
    intersections();
    count_stop++;
  }
  else if ((irSensor[0] == 0 && irSensor[1] == 0 && irSensor[2] == 0 && irSensor[3] == 0 && irSensor[4] == 0) && millis() - stopClock >= 26500) {
    while (1) {
      digitalWrite(3, HIGH);
      motor(0, 0);
    }
  }

  // Force Backward W-W-W-W-W in case the robot is out of track more than 140ms
  else if ((irSensor[0] == 1 && irSensor[1] == 1 && irSensor[2] == 1 && irSensor[3] == 1 && irSensor[4] == 1) && millis() - time >= 140) {
    // New Bacward
    while (!(irSensor[0] == 0 || irSensor[1] == 0 || irSensor[2] == 0 || irSensor[3] == 0 || irSensor[4] == 0)) {
      readSensor();
      setBackward();
      rightSPD = 130;
      leftSPD = 130;
      motor(rightSPD, leftSPD);
    }
  }

  // Hard turning
  else if((irSensor[0] == 1 && irSensor[1] == 1 && irSensor[2] == 0 && irSensor[3] == 1 && irSensor[4] == 0) && count_stop >= 2){ // hard turn right 
  digitalWrite(3, HIGH);
    //Old hardturn
    setBackward();
    motor(130 + errorShiftRight, 130 + errorShiftLeft);
    delay(200);

    setForward();
    motor(0, 110);
    delay(950);
    digitalWrite(3, LOW);
  }
  else if((irSensor[0] == 0 && irSensor[1] == 1 && irSensor[2] == 0 && irSensor[3] == 1 && irSensor[4] == 1) && count_stop >= 2){ // hard turn left
    digitalWrite(3, HIGH);

    setBackward();
    motor(130 + + errorShiftRight, 130 + errorShiftLeft);
    delay(200);

    setForward();
    motor(110 , 0);
    delay(900);
    digitalWrite(3, LOW);
  }

  // Normal turning
  else if (irSensor[0] == 0 || irSensor[1] == 0) {
    // Left Turn
      setForward();
      rightSPD = 90;
      leftSPD = 0;
  }
  else if (irSensor[3] == 0 || irSensor[4] == 0) {
    // Right Turn
      setForward();
      rightSPD = 0;
      leftSPD = 90 + errorShiftLeft;
  }

  // Default Case
  else  {
    setForward();
    rightSPD = 110;
    leftSPD = 110;
  }
}

void setForward() {
  digitalWrite(rightMotorDirection1, LOW);
  digitalWrite(rightMotorDirection2, HIGH);
  digitalWrite(leftMotorDirection1, LOW);
  digitalWrite(leftMotorDirection2, HIGH);
}

void setBackward() {
  digitalWrite(rightMotorDirection1, HIGH);
  digitalWrite(rightMotorDirection2, LOW);
  digitalWrite(leftMotorDirection1, HIGH);
  digitalWrite(leftMotorDirection2, LOW);
}

void intersections(){
  motor(0,0);
  
  while(1){
    if(digitalRead(LDR) == 0){
      count_light++;
      while(digitalRead(LDR) == 0) {
        Serial.println(count_light);
        Serial.println("STOP");
        time_intersec = millis();
      }
    }

    else if(count_light > 0 ){
      if(count_light >= 2 && millis() - time_intersec >= 1000){
		// turn right
        setForward();
        motor(0, 130);
        delay(450);
        count_light = 0;
        break ; 
      }
      else if(count_light == 1 && millis() - time_intersec >= 2000 ){
        //turn left
        setForward();
        motor(130, 0);
        delay(450);
        count_light = 0; 
        break ;
      }
    }
  }
}