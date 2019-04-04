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
boolean endPos = false;
int state = 0; // stillstand = 0, forward 1, backward 2
int endCounter = 0;
long lastTime = 0;
long currentTime = 0;
unsigned long debounceDelay = 100;
int lastreading;
boolean firstTime = false;
int speedLeft = 0;
int speedRight = 0;

void setup() {
 Serial.begin(9600);
 Serial.println("...starting");

 myVehicle.AFMS.begin();
 pinMode(2, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(2), triggerSwitch, CHANGE);
 myVehicle.setMaxSpeed(100, 100);
 myVehicle.setAcceleration(500, 500);
}

void loop() {
   
switch (state) {
  case 0:
  break;
  
}
}

void moveForward() {
myVehicle.forward(10,10,10,20);
   while(myVehicle.run() && !endPos);
}
void triggerSwitch() {
 endPos = true;
 myVehicle.stop();
 // go backward
 myVehicle.backward(100,50,100,50);
 while(myVehicle.run());
 myVehicle.turnLeft(180);
 while(myVehicle.run());
 endPos = false;
}
