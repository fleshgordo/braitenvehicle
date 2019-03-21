/*
   Braitenvehicle Example File with Statemachine Logic
   Version 0.1
   You'll need the Stepper Adafruit Rev2 stepper library
   https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/library-reference
   and AccelStepper https://www.airspayce.com/mikem/arduino/AccelStepper/

 * */


#include "Braitenvehicle.h"

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution

/*
   Initialize the Braitenvehicle library
   @params
   stepsPerRevolution  200 (1.8 degree)
   SINGLE | DOUBLE | INTERLEAVE | MICROSTEP
   connect two motors to the shield (motorRight M3/M4 motorLeft M1/M2)
 * */
Braitenvehicle myVehicle(stepsPerRevolution, DOUBLE);

void setup() {
  Serial.begin(9600);
  Serial.println("...starting");

  myVehicle.AFMS.begin();
}

void loop() {
  // move forward - make full rotation
  myVehicle.forward(stepsPerRevolution);
  delay(1000);

  // move forward - make full rotation
  myVehicle.backward(stepsPerRevolution);
  delay(1000);
}
