#include <AccelStepper.h>

const int turnLPin = 1; //The button to turn the cannon left
const int turnRPin = 2;//The button to turn the cannon right
const int fireBPin = 3;//The button to fire the cannon
const int firePowerUpPin = 4;//The button to turn the cannon right
const int firePowerDownPin = 5;//The button to fire the cannon

const int turnStepPin = 8;//The motor to tun the cannon
const int turnDirPin  = 9;//The direction to turn the cannon
const int fireStepPin = 10;//The motor to fire the cannon
const int fireDirPin  = 11;//The direction to fire the cannon

AccelStepper turnMotor(1,turnStepPin,turnDirPin);
AccelStepper fireMotor(1,fireStepPin,fireDirPin);

int turnLState = 0;
int turnRState = 0;
int fireBState = 0;
int firePowerUpState = 0;
int firePowerDownState = 0;
int firePower = 50;
int currentAngle = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(turnLPin,INPUT); //Check if the tower should be turned left
  pinMode(turnRPin,INPUT);//Check if the tower should be turned right
  pinMode(fireBPin,INPUT); //check for firing
  pinMode(firePowerUpPin,INPUT);// check if the firepower should be raised
  pinMode(firePowerDownPin,INPUT);//check if the firepower should be lowered

  pinMode(turnStepPin,OUTPUT); // output for turning the tower
  pinMode(turnDirPin,OUTPUT); //output for choosing turn direction
  pinMode(fireStepPin,OUTPUT); // Output for the throwing arm 
  pinMode(fireDirPin,OUTPUT); //Output for fireing or retracting arm
  
  fireMotor.setMaxSpeed(2000);
  fireMotor.setAcceleration(200000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  updateStates();
  turnTheTower();
  tuneThePower();
  if (fireBState == HIGH){
    fireInTheHall();
  } 
}

void updateStates() {
  turnLState = digitalRead(turnLPin);
  turnRState = digitalRead(turnRPin);
  fireBState = digitalRead(fireBPin);
  firePowerUpState = digitalRead(firePowerUpPin);
  firePowerDownState = digitalRead(firePowerDownPin);
}

void fireInTheHall() {
  // this runs when the catapult is fired.
  int currentFirePower = firePower;
  stepTheGun(currentFirePower);
  delay(500);
  while(currentFirePower > 0){
    stepTheGun(-1);
    currentFirePower--; 
    delay(100);
  } 
}

void stepTheGun (int steps) { 
  /*
	This function handles the fireing arm
	it uses the pin fireStepPin and fireDirPin
  */
  digitalWrite(fireDirPin,HIGH);
  if (steps < 0){
    steps = steps*-1;
    digitalWrite(fireDirPin,LOW);
  }
  while (steps > 0){
    steps--;
    digitalWrite(fireStepPin,HIGH);
    delayMicroseconds(750);
    digitalWrite(fireStepPin,LOW);
    delayMicroseconds(750);
  }
}



void turnTheTower() {
  /* 
 	This function is for turning the tower
	The poins it use are turnStepPin and turnDirPin
  */

  if ((turnLState == HIGH) && (currentAngle < 51)) {
    digitalWrite(turnDirPin, turnLState);
    delay(10);
    digitalWrite(turnStepPin, HIGH);
    delay(10);
    currentAngle++;
  }
  if ((turnRState == HIGH) && (currentAngle > -51)) {
    digitalWrite(turnDirPin, LOW);
    delay(10);
    digitalWrite(turnStepPin, HIGH);
    delay(10);
    currentAngle--;
  }
  digitalWrite(turnStepPin, LOW);
}

void tuneThePower(){
/*
	This function sets the firepower
	It useses the staes firePowerUpState and firePowerDownState
	the firepower should be between 0 and 50
*/
  if (firePowerUpState == HIGH && firePower < 50){
    firePower++;    
  }
  if (firePowerDownState == HIGH && firePower > 0){
    firePower--;    
  }
}

