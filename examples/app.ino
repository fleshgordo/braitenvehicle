/*
 * Braitenvehicle Example File
 * Version 0.1
 * Example by Gordan Savicic (Software) and Tom Pawlofsky (Hardware) 
 * for StuProXtended Course at Bachelor Digital Ideation 2019
 * https://www.hslu.ch/en/lucerne-school-of-information-technology/degree-programs/bachelor/digital-ideation/
 * 
 * You'll need the Stepper library installed https://www.arduino.cc/en/Reference/Stepper
 * State Machine library: https://github.com/jrullan/StateMachine
 * LinkedList: https://github.com/ivanseidel/LinkedList
 * */

#include "Braitenvehicle.h";
#include "StateMachine.h";

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution

// Change this to match the numbers of your motor pins
const byte LeftMotorPins[] = {8, 9, 10, 11};
const byte RightMotorPins[] = {4, 5, 6, 7};
// analog sensors: pin0, pin1, threshold1, threshold2
const uint8_t Sensors[] = {A0,A1,200,200};

// initialize the Braitenvehicle library
Braitenvehicle myVehicle(stepsPerRevolution, LeftMotorPins, RightMotorPins, Sensors);

// initialize State machine
const int STATE_DELAY = 1000;

StateMachine machine = StateMachine();

// initialize states
State* S1 = machine.addState(&state1);
State* S2 = machine.addState(&state2);

void setup() {
  // nothing to do inside the setup
  Serial.begin(9600);
  Serial.println("...starting");

  // init sensors
  myVehicle.initSensors(Sensors);
  
  // define state transitions
  S1->addTransition(&transitionS1S2,S2);
  S2->addTransition(&transitionS2S1,S1);
}

void loop() {
  machine.run();
  delay(1000);
}

void state1(){
  Serial.println("State 1");
  while(myVehicle.watchSensors(Sensors)) {
    myVehicle.forward(20);
  }
}

bool transitionS1S2(){
  return true;
}

void state2(){
  Serial.println("State 2");
}

bool transitionS2S1(){
  return true;
}