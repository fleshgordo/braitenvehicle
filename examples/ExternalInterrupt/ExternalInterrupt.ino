/*
   Braitenvehicle Example File with external interrupt
   Version 0.1
   You'll need the Stepper Adafruit Rev2 stepper library
   https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/library-reference
   and AccelStepper https://www.airspayce.com/mikem/arduino/AccelStepper/

 * */

#include "Braitenvehicle.h"

// switch on/off debug statements
//#define DEBUG 1

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution


/*
   Initialize the Braitenvehicle library
   @params
   stepsPerRevolution  200 (1.8 degree)
   SINGLE | DOUBLE | INTERLEAVE | MICROSTEP
   connect two motors to the shield (motorRight M3/M4 motorLeft M1/M2)
 * */
Braitenvehicle myVehicle(stepsPerRevolution, DOUBLE);

const byte interruptPin = 2;

int speedLeft = 200;
int speedRight = 150;
int state = 1;

long debouncing_time = 250; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("...starting");
#endif

  myVehicle.AFMS.begin();

  myVehicle.setMaxSpeed(200.0, 200.0);
  myVehicle.setAcceleration(5000, 5000);
  myVehicle.setSpeed(speedLeft, speedRight);

  attachInterrupt(digitalPinToInterrupt(interruptPin), debounceInterrupt, CHANGE);
}

void loop() {
  // only when vehicle is not at final position
  if (!myVehicle.isRunning()) {
    state % 2 == 0 ? myVehicle.move(20, 20) : myVehicle.move(-20, -20);
  }
  myVehicle.runSpeed();

#ifdef DEBUG
  Serial.print("State: ");
  Serial.print(state);
  Serial.print(" speedLeft: ");
  Serial.print(speedLeft);
  Serial.print(" speedRight: ");
  Serial.println(speedRight);
#endif
}

void debounceInterrupt() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000 && (digitalRead(interruptPin) == LOW)) {
    toggleSpeed();
    last_micros = micros();
  }
}

void toggleSpeed() {
  int oldSpeedLeft = speedLeft;
  speedLeft = speedRight * -1;
  speedRight = oldSpeedLeft * -1;
#ifdef DEBUG
  Serial.println("****** bumper *******");
#endif
  state += 1;
  myVehicle.setSpeed(speedLeft, speedRight);
}
