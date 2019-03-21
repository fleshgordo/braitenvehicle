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

/* 
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

/* 
 * Moves both motors to position
 * @param   {int} leftPos   move left motor to specific position 
 * @param   {int} rightPos  move right motor to specific position 
 * @return  true  if reached to position
 */
void Braitenvehicle::moveTo(int leftPos, int rightPos) {
  stepperLeft->moveTo(leftPos);
  stepperRight->moveTo(rightPos);
}

/* 
 * Set maximum speed for accelerated motors
 * @param {float} leftSpeed   speed for left motor
 * @param {float} rightSpeed  speed for right motor
 */
void Braitenvehicle::setMaxSpeed(float leftSpeed, float rightSpeed) {
  stepperLeft->setMaxSpeed(leftSpeed);
  stepperLeft->setAcceleration(500);
  stepperRight->setMaxSpeed(rightSpeed);
  stepperRight->setAcceleration(500);
}

/* 
 * Move vehicle straight forwards
 * @param {int}   steps   number of steps 
 */

void Braitenvehicle::forward(int steps) {
  for (int i = 0; i < steps; i++) {
    motorLeft->onestep(FORWARD, this->coilSteps);
    motorRight->onestep(FORWARD, this->coilSteps); 
  }
}

/* 
 * Move vehicle straight backwards
 * @param {int} steps number of steps 
 */
void Braitenvehicle::backward(int steps) {
   for (int i = 0; i < steps; i++) {
    motorLeft->onestep(BACKWARD, this->coilSteps);
    motorRight->onestep(BACKWARD, this->coilSteps); 
  }
}

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

void moveAcceleration() {

}
/*
 *   Show version number - for testing purpose only
 */
int Braitenvehicle::version(void) {
  return 1;
}