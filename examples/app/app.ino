/*
 * Braitenvehicle Example File
 * Version 0.1
 * You'll need the Stepper Adafruit Rev2 stepper library 
 * https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/library-reference
 * */


#include "Braitenvehicle.h"
#include "StateMachine.h"

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution


// analog sensors: pin0, pin1, threshold1, threshold2
const uint8_t Sensors[] = {A0,A1,200,200};

/*
 * Initialize the Braitenvehicle library
 * @params
 * stepsPerRevolution  200 (1.8 degree)
 * SINGLE | DOUBLE | INTERLEAVE | MICROSTEP
 * connect two motors to the shield (motorRight M3/M4 motorLeft M1/M2)
 * */
Braitenvehicle myVehicle(stepsPerRevolution,DOUBLE);

// initialize State machine
StateMachine machine = StateMachine();

// initialize states
State* S1 = machine.addState(&state1);
State* S2 = machine.addState(&state2);

/*
 * // For adding a state, first initialise
 * State* S3 = machine.addState(&state3);
 * 
 * // Add transition within setup() function
 * S3->addTransition(&transitionS3S1,S1);
 * 
 * define void transitionS3S1() { // transition here, if not needed just do return true;}
 * define void state3() {}
 * */

void setup() {
  Serial.begin(9600);
  Serial.println("...starting");

  // init sensors
  myVehicle.initSensors(Sensors);
  myVehicle.AFMS.begin();
  
  // define state transitions
  S1->addTransition(&transitionS1S2,S2);
  S2->addTransition(&transitionS2S1,S1);
}

void loop() {
  machine.run();
  delay(1000);
}

/*
 * FIRST STATE
 * return false will exit this state and call transition
 * */
void state1(){
  Serial.println("State 1");
  while(myVehicle.watchSensors(Sensors)) {
    myVehicle.forward(200);
  }
}

/*
 * TRANSITION FROM State1 to State2
 * return true will pass to next state (state2)
 * */
bool transitionS1S2(){
  return true;
}

void state2(){
  Serial.println("State 2");
  while(myVehicle.watchSensors(Sensors)) {
    myVehicle.release();
  }
}

bool transitionS2S1(){
  return true;
}
