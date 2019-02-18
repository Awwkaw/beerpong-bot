#include <AccelStepper.h>

#define PIN_A0 (14)
#define PIN_A1 (15)
#define PIN_A2 (16)
#define PIN_A3 (17)
#define PIN_A4 (18)
#define PIN_A5 (19)

const int fireBPin = 2;//The button to fire the cannon
const int powerAngleTogglePin = 3;//The button to fire the cannon
const int firePowerUpPin = 4;//The button to turn the cannon right
const int firePowerDownPin = 5;//The button to fire the cannon
const int turnLPin = 6; //The button to turn the cannon left
const int turnRPin = 7;//The button to turn the cannon right

const int turnStepPin = 8;//The motor to tun the cannon
const int turnDirPin  = 9;//The direction to turn the cannon
const int turnDriverPin  = 10;//The pin to turn on the turning driver
const int fireStepPin = 11;//The motor to fire the cannon
const int fireDirPin  = 12;//The direction to fire the cannon
const int fireDriverPin  = 13;//The pin to turn on the firing driver

const byte redLatchPin   = 14;
const byte redClockPin   = 15;
const byte redDataPin    = 16;
const byte greenLatchPin = 17;
const byte greenClockPin = 18;
const byte greenDataPin  = 19;

AccelStepper turnMotor(1,turnStepPin,turnDirPin);
AccelStepper fireMotor(1,fireStepPin,fireDirPin);

bool turnLState = 0;
bool turnRState = 0;
bool fireBState = 0;
bool powerAngleToggle = 0;
bool firePowerUpState = 0;
bool firePowerDownState = 0;
int fireAngle = 100;
const int maxFireAngle = 130;
const int minFireAngle = 40;
int fireMaxSpeed = 1800;
int fireAccel = 14000;
int currentAngle = 0;
const int currentAngleLow = -50;
const int currentAngleHigh = 50;

byte redLEDStates = B00000000;
byte GreenLEDStates = B00000000;

int redPinsOn = 0;
int greenPinsOn = 0;
int oRedPinsOn = 0;
int oGreenPinsOn = 0;
int pinWriteNumber = 0;
byte pinByteLight;

void setup() {
  // put your setup code here, to run once:
  //steppintest();
  pinMode(turnLPin,INPUT); //Check if the tower should be turned left
  pinMode(turnRPin,INPUT);//Check if the tower should be turned right
  pinMode(fireBPin,INPUT); //check for firing
  pinMode(powerAngleTogglePin,INPUT);//
  pinMode(firePowerUpPin,INPUT);// check if the firepower should be raised
  pinMode(firePowerDownPin,INPUT);//check if the firepower should be lowered

  pinMode(turnStepPin,OUTPUT); // output for turning the tower
  pinMode(turnDirPin,OUTPUT); //output for choosing turn direction
  pinMode(turnDriverPin,OUTPUT); //Output for fireing or retracting arm

  pinMode(fireStepPin,OUTPUT); // Output for the throwing arm 
  pinMode(fireDirPin,OUTPUT); //Output for fireing or retracting arm
  pinMode(fireDriverPin,OUTPUT); //Output for fireing or retracting arm

  pinMode(redLatchPin  ,OUTPUT);
  pinMode(redClockPin  ,OUTPUT);
  pinMode(redDataPin   ,OUTPUT);
  pinMode(greenLatchPin,OUTPUT);
  pinMode(greenClockPin,OUTPUT);
  pinMode(greenDataPin ,OUTPUT);
  
  digitalWrite(fireDriverPin,HIGH);
  digitalWrite(turnDriverPin,HIGH);
  
  fireMotor.setMaxSpeed(fireMaxSpeed);
  fireMotor.setAcceleration(fireAccel);
  fireMotor.setCurrentPosition(0);
  turnMotor.setMaxSpeed(10);
  turnMotor.setAcceleration(10);
  turnMotor.setCurrentPosition(0);
  Serial.begin(19200);
  getAndSetPinsOn();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float uptime = millis();
  updateStates();
  float turntime = millis();
  turnTheTower();
  float tunetime = millis();
  tuneThePower();
  float firetime = millis();
  if (fireBState == LOW){
    fireInTheHall();
  } 
  float endtime = millis();
  ////Serial.print("update time: ");
  ////Serial.println(turntime-uptime);
  ////Serial.print("turn time: ");
  ////Serial.println(tunetime-turntime);
  ////Serial.print("tune time: ");
  ////Serial.println(firetime-tunetime);
  ////Serial.print("fire time: ");
  ////Serial.println(endtime-firetime);
  ////Serial.print("totaltime: ");
  ////Serial.println(endtime-uptime);
  //Serial.println(fireMaxSpeed);
  //Serial.println(fireAngle);
 
}

void updateStates() {
  turnLState = digitalRead(turnLPin);
  turnRState = digitalRead(turnRPin);
  fireBState = digitalRead(fireBPin);
  powerAngleToggle = digitalRead(powerAngleTogglePin);
  firePowerUpState = digitalRead(firePowerUpPin);
  firePowerDownState = digitalRead(firePowerDownPin);
  Serial.println(powerAngleToggle);
  Serial.println(firePowerUpState);
  Serial.println(firePowerDownState);
  Serial.println(turnLState);
  Serial.println(turnRState);
  Serial.println(fireBState);
}

void fireInTheHall() {
  // this runs when the catapult is fired.
  Serial.println(fireAngle);
  digitalWrite(fireDriverPin,LOW);
  digitalWrite(turnDriverPin,LOW);
  fireMotor.moveTo(fireAngle);
  fireMotor.runToPosition();
  delay(500);
  fireMotor.setMaxSpeed(20);

  fireMotor.moveTo(fireAngle/2);
  fireMotor.runToPosition();
  fireMotor.setMaxSpeed(fireMaxSpeed);
  digitalWrite(fireDriverPin,HIGH);
  digitalWrite(turnDriverPin,HIGH);
  fireMotor.moveTo(0);
  fireMotor.runToPosition();
}



void turnTheTower() {
  /* 
 	This function is for turning the tower
	The poins it use are turnStepPin and turnDirPin
  */

  if ((turnLState == LOW) ) {
    if (currentAngle < currentAngleHigh){
      digitalWrite(turnDriverPin,LOW);
      currentAngle++;
      if (powerAngleToggle == LOW ){
        currentAngle +=5;
      }
     turnMotor.moveTo(currentAngle);
     turnMotor.runToPosition();
     digitalWrite(turnDriverPin,HIGH);
    }
  }
  if ((turnRState == LOW)) {
    if (currentAngle > currentAngleLow){
      digitalWrite(turnDriverPin,LOW);
      currentAngle--;
      if (powerAngleToggle == LOW ){
        currentAngle -=5;
      }
      turnMotor.moveTo(currentAngle);
      turnMotor.runToPosition();
      digitalWrite(turnDriverPin,HIGH);
    }
  }
}

void tuneThePower(){
/*
	This function sets the fireMaxSpeed and fireAngle
	It useses the staes firePowerUpState and firePowerDownState
	the fireAngle should be between 0 and 60
	the fireMaxSpeed should be between 100 and 900
*/
  if (powerAngleToggle == HIGH){
    if (firePowerUpState == LOW ){
      if (fireAngle < maxFireAngle){
        fireAngle++;    
        getAndSetPinsOn();
        delay(20);
      }
    }
    if (firePowerDownState == LOW){
      if(fireAngle > minFireAngle){
        fireAngle--;    
        getAndSetPinsOn();
        delay(20);
      }
    }
  }
  else{
    if (firePowerUpState == LOW ){
      if (fireMaxSpeed <= 1790){
        fireMaxSpeed += 10;    
        getAndSetPinsOn();
        delay(20);
      }
    }
    if (firePowerDownState == LOW){
      if(fireMaxSpeed >= 910){
        fireMaxSpeed -= 10;    
        getAndSetPinsOn();
        delay(20);
      }
    }
  }
}
void getAndSetPinsOn(){
  
  oRedPinsOn = redPinsOn;
  oGreenPinsOn = greenPinsOn;
  redPinsOn = round(8*(fireMaxSpeed-900)/900.0);
  greenPinsOn = round(8*(fireAngle-minFireAngle)/(maxFireAngle-minFireAngle));

  if (oRedPinsOn != redPinsOn){

    //Serial.println(firePower);
    //Serial.println(redPinsOn);
    //Serial.println((1 << redPinsOn)-1,BIN);
    //Serial.println("--------");

    digitalWrite(redLatchPin,LOW);
    shiftOut(redDataPin,redClockPin,MSBFIRST,(1 << redPinsOn)-1);
    digitalWrite(redLatchPin,HIGH);
  }
  else if (oGreenPinsOn != greenPinsOn){

    digitalWrite(greenLatchPin,LOW);
    shiftOut(greenDataPin,greenClockPin,MSBFIRST,(1 << greenPinsOn)-1);
    digitalWrite(greenLatchPin,HIGH);
  }
}

void steppintest(){
  digitalWrite(turnDriverPin,LOW);
  while(HIGH){
  digitalWrite(turnStepPin,HIGH);
  digitalWrite(turnStepPin,LOW);delay(100);}
}
