/*
 * Braitenvehicle.cpp
 * Version 0.2
 * Original library        (0.2)   Gordan Savicic, (pointer wizardry for AccelStepper by Gottfried Haider)
 * */

#include "AccelStepperOO.h"
#include "Arduino.h"
#include "Braitenvehicle.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>

/*
 *  Constructor for Braitenvehicle class (two four-pin stepper motor)
 */
Braitenvehicle::Braitenvehicle(const int numberOfSteps, byte coilSteps): 
  numberOfSteps(numberOfSteps),AFMS(Adafruit_MotorShield())
{
  this->coilSteps = coilSteps;
  motorLeft = this->AFMS.getStepper(numberOfSteps, 1);
  motorRight = this->AFMS.getStepper(numberOfSteps, 2);
  stepperLeft = new AccelStepperOO(Braitenvehicle::forwardstep1, Braitenvehicle::backwardstep1, (void*)this);
  stepperRight = new AccelStepperOO(Braitenvehicle::forwardstep2, Braitenvehicle::backwardstep2, (void*)this);
  
}

/* run
 * Poll the motor and step it if a step is due, implementing accelerations and decelerations
 * @return true   if reached to position
 */
boolean Braitenvehicle::run() {
  while(stepperLeft->run() || stepperRight->run()) {
    stepperRight->run();
    stepperLeft->run();
    return true;
  };
  return false;
}


/* run
 * Poll the motor and step it if a step is due, implementing accelerations and decelerations
 * @return true   if reached to position
 */
void Braitenvehicle::runSpeed() {
  stepperLeft->runSpeed();
  stepperRight->runSpeed();
}

/* 
 * Moves both motors to absolute position
 * @param   {int} leftPos   move left motor to specific position 
 * @param   {int} rightPos  move right motor to specific position 
 * @return  true  if reached to position
 */
void Braitenvehicle::moveTo(int leftPos, int rightPos) {
  stepperLeft->moveTo(leftPos);
  stepperRight->moveTo(rightPos);
}

/* 
 * isRunning
 * @return  true  if one of the steppers is moving (i. e. not reached position)
 */
bool Braitenvehicle::isRunning() {
  return (stepperLeft->isRunning() || stepperRight->isRunning());
} 

/* 
 * Moves both motors to relative position
 * @param   {int} leftPos   move left motor to specific position 
 * @param   {int} rightPos  move right motor to specific position 
 * @return  true  if reached to position
 */
void Braitenvehicle::move(int leftPos, int rightPos) {
  stepperLeft->move(leftPos);
  stepperRight->move(rightPos);
}

/* 
 * Stops the motors
 */
void Braitenvehicle::stop() {
  stepperLeft->stop();
  stepperRight->stop();
}

/* 
 * Set maximum speed for accelerated motors
 * @param {float} leftSpeed   speed for left motor
 * @param {float} rightSpeed  speed for right motor
 */
void Braitenvehicle::setMaxSpeed(float leftSpeed, float rightSpeed) {
  stepperLeft->setMaxSpeed(leftSpeed);
  stepperRight->setMaxSpeed(rightSpeed);
}

/* 
 * Set speed for accelerated motors (needs to be used with runSpeed())
 * The desired constant speed in steps per second. Positive is clockwise. Speeds of more than 1000 steps per second are unreliable. 
 * Very slow speeds may be set (eg 0.00027777 for once per hour, approximately. Speed accuracy depends on the Arduino crystal.
 * @param {float} leftSpeed   speed for left motor
 * @param {float} rightSpeed  speed for right motor
 */
void Braitenvehicle::setSpeed(float leftSpeed, float rightSpeed) {
  stepperLeft->setSpeed(leftSpeed);
  stepperRight->setSpeed(rightSpeed);
}

/* 
 * Set acceleration for accelerated motors
 * @param {float} leftAccel   acceleration for left motor
 * @param {float} rightAccel  acceleration for right motor
 */
void Braitenvehicle::setAcceleration(float leftAccel, float rightAccel) {
  stepperLeft->setAcceleration(leftAccel);
  stepperRight->setAcceleration(rightAccel);
}

/* 
 * Move vehicle straight forwards
 * @param {int}   speedLeft     speed
 * @param {int}   speedRight    speed
 */

void Braitenvehicle::forward(int stepsLeft, int speedLeft, int stepsRight, int speedRight) {
  this->setSpeed(speedLeft, speedRight);
  stepperLeft->move(stepsLeft);
  stepperRight->move(stepsRight);
}

/* 
 * Move vehicle straight backwards
 * @param {int} speed   speed
 */
void Braitenvehicle::backward(int stepsLeft, int speedLeft, int stepsRight, int speedRight) {
  this->setSpeed(speedLeft, speedRight);
  stepperLeft->move(-1 * stepsLeft);
  stepperRight->move(-1 * stepsRight);
}

/* 
 * Wrapper one-step functions for Accelstepper
 */
static void Braitenvehicle::forwardstep1(void *user) {
  Braitenvehicle *self = (Braitenvehicle*)user;
  self->motorLeft->onestep(FORWARD, self->coilSteps);
}
static void Braitenvehicle::forwardstep2(void *user) {
  Braitenvehicle *self = (Braitenvehicle*)user;
  self->motorRight->onestep(FORWARD, self->coilSteps);
}
static void Braitenvehicle::backwardstep1(void *user) {
  Braitenvehicle *self = (Braitenvehicle*)user;
  self->motorLeft->onestep(BACKWARD, self->coilSteps);
}
static void Braitenvehicle::backwardstep2(void *user) {
  Braitenvehicle *self = (Braitenvehicle*)user;
  self->motorRight->onestep(BACKWARD, self->coilSteps);
}

/* 
 * Release switches off both motors 
 */
void Braitenvehicle::release() {
  motorLeft->release();
  motorRight->release();
}

/* 
 * Turn left
 * @param {int} angle
 */
void Braitenvehicle::turnLeft(int angle) {
  stepperLeft->move(angle);
  stepperRight->move(angle * -1);
}

/* 
 * Turn right
 * @param {int} angle
 */
void Braitenvehicle::turnRight(int angle) {
  stepperLeft->move(angle * -1);
  stepperRight->move(angle);
}

/*
 *   Initialize sensor states
 *   @params {byteArray}  Sensors[] Holds pin numbers[0-1] and thresholds [2-3]
 */
void Braitenvehicle::initSensors(const byte Sensors[]) {
  pinMode(Sensors[0],INPUT);
  pinMode(Sensors[1],INPUT);
}

/*
 *   Check sensor state
 *   @param {byteArray}  Sensors[] Holds pin numbers[0-1] and thresholds [2-3]
 *   return true                   if threshold surpassed or false
 */
bool Braitenvehicle::watchSensors(const byte Sensors[]) {
  int threshold1 = Sensors[2];
  int threshold2 = Sensors[3];

  if (analogRead(Sensors[0]) < threshold1 || analogRead(Sensors[1]) < threshold2) {
    Serial.println("sensors threshold");
    return false;
  }
  Serial.println(analogRead(Sensors[0]));
  return true;
}

/*
 *   Show version number - for testing purpose only
 */
int Braitenvehicle::version(void) {
  return 1;
}