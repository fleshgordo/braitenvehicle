/*
 * Braitenvehicle.cpp - library for StuProXtended Course at Bachelor Digital Ideation 2019
 * Version 0.1
 *
 * Original library        (0.1)   by Gordan Savicic (Software) and Tom Pawlofsky (Hardware)
 * Further development     (0.2)   by Students HSLU :) 
 * 
 * You'll need the Stepper library installed https://www.arduino.cc/en/Reference/Stepper
 * State Machine library: https://github.com/jrullan/StateMachine
 * LinkedList: https://github.com/ivanseidel/LinkedList
 * */

#include "Arduino.h"
#include "Stepper.h"
#include "Braitenvehicle.h"


/*
 *   constructor for two four-pin stepper motor
 */
Braitenvehicle::Braitenvehicle(byte numberOfSteps, const byte l[], const byte r[], const byte Sensors[]): 
  numberOfSteps(numberOfSteps),
  leftStepper(numberOfSteps, l[0],l[1], l[2], l[3]),
  rightStepper(numberOfSteps, r[0], r[1], r[2], r[3])
{
  
  
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

/* 
 * Move vehicle straight forwards
 * @steps int number of steps 
 */

void Braitenvehicle::forward(int steps) {
  this->leftStepper.step(steps);
  this->rightStepper.step(steps);
}

/* 
 * Move vehicle straight backwards
 * @steps int number of steps 
 */
void Braitenvehicle::backward(int steps) {
  this->leftStepper.step(steps * -1);
  this->rightStepper.step(steps * -1);
}

