/*
 * Braitenvehicle.cpp
 * Version 0.1
 *
 * Original library        (0.1)   by Gordan Savicic with help from Gottfried Haider
 * */

#include "AccelStepperOO.h"
#include "Arduino.h"
#include "Braitenvehicle.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>

/*
 *   constructor for two four-pin stepper motor
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
 * Move vehicle straight forwards
 * @steps int number of steps 
 */

void Braitenvehicle::forward(int steps) {
  motorLeft->step(steps, FORWARD, this->coilSteps); 
  motorRight->step(steps, FORWARD, this->coilSteps); 
}

/* 
 * Move vehicle straight backwards
 * @steps int number of steps 
 */
void Braitenvehicle::backward(int steps) {
  motorLeft->step(steps, BACKWARD, this->coilSteps);
  motorRight->step(steps, BACKWARD, this->coilSteps); 
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

int Braitenvehicle::version(void) {
  return 1;
}


/*
 *   Initialize sensor states
 *   @params Sensors[] byte array with pin numbers and thresholds
 */
void Braitenvehicle::initSensors(const byte Sensors[]) {
  pinMode(Sensors[0],INPUT);
  pinMode(Sensors[1],INPUT);
}

/*
 *   Check sensor state
 *   @params Sensors[] byte array with pin numbers and thresholds
 *   returns true (if threshold surpassed) or false
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