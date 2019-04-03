/*
   Braitenvehicle Example File with Statemachine Logic
   Version 0.1
   You'll need the Stepper Adafruit Rev2 stepper library
   https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/library-reference
   and AccelStepper https://www.airspayce.com/mikem/arduino/AccelStepper/

 * */


#include "Braitenvehicle.h"
#include "StateMachine.h"

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution


// analog sensors: pin0, pin1, threshold1, threshold2
const uint8_t Sensors[] = {A0, A1, 200, 200};

/*
   Initialize the Braitenvehicle library
   @params
   stepsPerRevolution  200 (1.8 degree)
   SINGLE | DOUBLE | INTERLEAVE | MICROSTEP
   connect two motors to the shield (motorRight M3/M4 motorLeft M1/M2)
 * */
Braitenvehicle myVehicle(stepsPerRevolution, DOUBLE);

// initialize State machine
StateMachine machine = StateMachine();

// initialize states
State* S1 = machine.addState(&state1);
State* S2 = machine.addState(&state2);
State* S3 = machine.addState(&state3);

boolean extButton = false;
const int interruptPin = 2;
/*
   // For adding a state, first initialise
   State* S3 = machine.addState(&state3);

   // Add transition within setup() function
   S3->addTransition(&transitionS3S1,S1);

   define void transitionS3S1() { // transition here, if not needed just do return true;}
   define void state3() {}
 * */

void setup() {
  Serial.begin(9600);
  Serial.println("...starting");

  // init sensors
  myVehicle.initSensors(Sensors);
  myVehicle.AFMS.begin();

  myVehicle.setMaxSpeed(200.0, 200.0);
  myVehicle.setAcceleration(50, 50);

  // define state transitions
  S1->addTransition(&transitionS1S2, S2);
  S2->addTransition(&transitionS2S3, S3);
  S3->addTransition(&transitionS3S1, S1);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), changeDir, RISING);
  
}

void loop() {
  machine.run();
  Serial.print("current state: ");
  Serial.println(machine.currentState);
  delay(1000);
}

void changeDir() {
  extButton = true;
}
/*
   FIRST STATE
   return false will exit this state and call transition
 * */
void state1() {
  //Serial.println("******* State 1 *******");
  myVehicle.setMaxSpeed(200, 200);
  myVehicle.move(10, 10);
  while (extButton == false) {
      myVehicle.move(10, 10);
      myVehicle.run();
  }
  //while(myVehicle.runSpeed());
}

/*
   TRANSITION FROM State1 to State2
   return true will pass to next state (state2)
 * */
bool transitionS1S2() {
  //Serial.println(">>>>>>> Transition 1 -> 2 <<<<<<<<");
  return true;
}

void state2() {
  Serial.println("******* State 2 *******");
  myVehicle.setMaxSpeed(100, 100);
  myVehicle.move(-100,-100);
  while(myVehicle.run());
  myVehicle.move(-200,200);
  while(myVehicle.run());
  extButton = false;
}

bool transitionS3S1() {
  Serial.println(">>>>>>> Transition 3 -> 1 <<<<<<<<");
  return true;
}

bool transitionS2S3() {
  Serial.println(">>>>>>> Transition 2 -> 3 <<<<<<<<");
  return true;
}

void state3() {
  Serial.println("******* State 3 *******");
  myVehicle.setMaxSpeed(50, 50);
  myVehicle.move(200, -200);
  while (myVehicle.run());
}
