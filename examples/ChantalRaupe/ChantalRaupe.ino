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
int stats = 0; // stillstand = 0, forward 1, backward 2
int endCounter = 0;
long lastTime = 0;
long currentTime = 0;
unsigned long debounceDelay = 100;
int lastreading;
boolean firstTime = false;

void setup() {
 Serial.begin(9600);
 Serial.println("...starting");

 myVehicle.AFMS.begin();
 pinMode(2, INPUT_PULLUP);
 //attachInterrupt(digitalPinToInterrupt(2), triggerSwitch, CHANGE);
 myVehicle.setMaxSpeed(100, 100);
 myVehicle.setAcceleration(500, 500);
}

void loop() {

 int readswitch = digitalRead(2);
 Serial.println(readswitch);
 if (readswitch != lastreading) {
   lastTime = millis();
 }

 if ((millis() - lastTime) > debounceDelay) {
   while (digitalRead(2) == 1) {
     myVehicle.move(10, 10);
     firstTime = false;
     myVehicle.run();
     Serial.println("vorwaerts");
   }

   // dreh dich
   while (digitalRead(2) == 0) {
     if (firstTime == false) {
       myVehicle.move(-120, -120);
       Serial.println("ruckwaerts");
       while(myVehicle.run());
       firstTime = true;
     }
     myVehicle.move(5, -5);
     myVehicle.run();
     Serial.println("dreh dich");
   }
 }
 // nur vorwaerts


 lastreading = readswitch;
}

void triggerSwitch() {
 Serial.println(" button");
 endPos = true;
 myVehicle.stop();
}
