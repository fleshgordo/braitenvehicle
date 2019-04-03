/*
  Reading sharp distance sensor GP2Y0A21YK0F
*/

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

#include "Braitenvehicle.h"
#include "StateMachine.h"

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution


// analog sensors: pin0, pin1, threshold1, threshold2
const uint8_t Sensors[] = {A0, A1, 200, 200};

Braitenvehicle myVehicle(stepsPerRevolution, DOUBLE);

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // init sensors
  myVehicle.initSensors(Sensors);
  myVehicle.AFMS.begin();

  myVehicle.setMaxSpeed(200.0, 200.0);
  myVehicle.setAcceleration(50, 50);
  
  
}

void loop() {
  sensorValue = analogRead(sensorPin);
  while (sensorValue > 100 && sensorValue < 400) {
    //myVehicle.forward(5,100,5,10);
    //myVehicle.run();
    sensorValue = analogRead(sensorPin);
   
  } Serial.println(sensorValue);
  
}
