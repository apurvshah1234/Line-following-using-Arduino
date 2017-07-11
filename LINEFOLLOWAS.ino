/*
Created by Apurv Shah.
11 june 2017.
*/



// This is a simple code that helps a robot to foillow a black line using a 3 sensor reflectance sensor.
 
#define enableL 6     // ENA speed pin for left motor
#define LPin1 7       // IN1 on Motor controller board
#define LPin2 8       // IN2
// Right motor pins
#define enableR 11     // ENB speed pin for right motor
#define RPin1 9       // IN3 on Motor controller board
#define RPin2 10       // IN4

#define rightSensorPin A0 // pins that the line falloing sensor is on.
#define middleSensorPin A1
#define leftSensorPin A2
#define BLACKlimit 780  // typical range white > 100, black <800
#define WHITElimit 75

int rightspeed = 100; // speed of the right motor.
int leftspeed = 125; // speed of left motor
int response = 1; // no idea what this is

int rightSensor;  // a int to hold the right line fallowing sensors value
int middleSensor; // a int to hold the middle sensor value
int leftSensor;   // a int to hold the left sensors value
int speaker = 12; // the pin the speaker is on (Not used)
int turn = 5;
int speed1 = 5;
int error = 0;
int dir1 = 0;
int errCount = 0;

boolean onLine = false;
int count = 0;

//*********************************************** SETUP ***********************************************//
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(enableR, OUTPUT);
  pinMode(enableL, OUTPUT);
  pinMode(RPin1, OUTPUT);
  pinMode(RPin2, OUTPUT);
  pinMode(LPin1, OUTPUT);
  pinMode(LPin2, OUTPUT);
}

//********************************************* END SETUP *********************************************//


//*********************************************** LOOP ************************************************//

void loop() {
  // set the motors to run forward.
  digitalWrite(LPin1, HIGH);
  digitalWrite(LPin2, LOW);
  digitalWrite(RPin1, HIGH);
  digitalWrite(RPin2, LOW);
  
  
  // read the input on analog pin 0, 1, 2:
  rightSensor = analogRead(rightSensorPin);
  middleSensor = analogRead(middleSensorPin);
  leftSensor = analogRead(leftSensorPin);
  Serial.println(middleSensor);
  Serial.println(rightSensor);

  //*************************************************** CHECK Striaght *********************************************************//
  
  // test if the right sensor is detecting white and the center sensor is detectigng black
  if ((middleSensor > BLACKlimit) || (dir1 == 0)){
    dir1 = 0;
    Serial.println("go Striaght");
    digitalWrite(enableL, HIGH);
    digitalWrite(enableR, HIGH);
    delay(speed1);
    digitalWrite(enableL, LOW);
    digitalWrite(enableR, LOW);
    delay(10);
    
  }

  

  //************************************************** CHECK IF GOING LEFT ****************************************************//
  
  // test if right is not white and center is black
  if (((rightSensor > BLACKlimit) && (middleSensor < BLACKlimit) || (dir1 == 1))){
    dir1 = 1;
    rightspeed = rightspeed - 2;
    Serial.println("turning Right");
    
    
    digitalWrite(enableL, HIGH);
    
    digitalWrite(enableR, LOW);
    delay(turn);
    digitalWrite(enableL, LOW);
    delay(5);
    
  }

  //********************************************************* CHECK IF GOING RIGHT **************************************************//

  // test if right is white and center is not black
  if (((leftSensor > BLACKlimit) && (middleSensor < BLACKlimit)) || (dir1 == 2)){
    dir1 = 2;
    leftspeed = leftspeed - 2;
    Serial.println("turning left");
    
    
    digitalWrite(enableR, HIGH);
    
    digitalWrite(enableL, LOW);
    delay(turn);
    digitalWrite(enableR, LOW);
    delay(5);
    
  }

  if ((middleSensor < BLACKlimit) && (rightSensor < BLACKlimit) && (leftSensor < BLACKlimit)){
    errCount++;
    
  }

  if (errCount > 10){
    onLine = false;
    errCount = 0;
  }

  middleSensor = analogRead(middleSensorPin);
  delay(5);
  while (!onLine){

//********************************************* Right Turn *************************************************//
    digitalWrite(LPin1, HIGH);
    digitalWrite(LPin2, LOW);
    digitalWrite(RPin1, LOW);
    digitalWrite(RPin2, HIGH);
    
    count = 0;
    
    while (!onLine && (count < 30)){
      count++;
      digitalWrite(enableL, HIGH);
      digitalWrite(enableR, HIGH);
      delay(5);
      digitalWrite(enableL, LOW);
      digitalWrite(enableR, LOW);
      delay(turn);
    
      middleSensor = analogRead(middleSensorPin);
      if (middleSensor > BLACKlimit){
        onLine = true;
      }
    }
    
//************************************************** Left Turn ********************************************//
    digitalWrite(LPin2, HIGH);
    digitalWrite(LPin1, LOW);
    digitalWrite(RPin2, LOW);
    digitalWrite(RPin1, HIGH);
    
    count = 0;
    
    while (!onLine && (count < 60)){
      count++;
      digitalWrite(enableL, HIGH);
      digitalWrite(enableR, HIGH);
      delay(5);
      digitalWrite(enableL, LOW);
      digitalWrite(enableR, LOW);
      delay(turn);
    
      middleSensor = analogRead(middleSensorPin);
      if (middleSensor > BLACKlimit){
        onLine = true;
      }
    }

//******************************************* Turn Right Again *************************************//
    digitalWrite(LPin1, HIGH);
    digitalWrite(LPin2, LOW);
    digitalWrite(RPin1, LOW);
    digitalWrite(RPin2, HIGH);
    
    count = 0;
    
    while (!onLine && (count < 30)){
      count++;
      digitalWrite(enableL, HIGH);
      digitalWrite(enableR, HIGH);
      delay(5);
      digitalWrite(enableL, LOW);
      digitalWrite(enableR, LOW);
      delay(turn);
    
      middleSensor = analogRead(middleSensorPin);
      if (middleSensor > BLACKlimit){
        onLine = true;
      }
    }

//********************************************** Go Straight *****************************************//
    digitalWrite(LPin1, HIGH);
    digitalWrite(LPin2, LOW);
    digitalWrite(RPin2, LOW);
    digitalWrite(RPin1, HIGH);

    count = 0;

    while (!onLine && (count < 30)){
      count++;
      digitalWrite(enableL, HIGH);
      digitalWrite(enableR, HIGH);
      delay(5);
      digitalWrite(enableL, LOW);
      digitalWrite(enableR, LOW);
      delay(turn);
    
      middleSensor = analogRead(middleSensorPin);
      if (middleSensor > BLACKlimit){
        onLine = true;
      }
    }
    
    Serial.println(middleSensor);
  }

}

//********************************************* END LOOP ***********************************//
