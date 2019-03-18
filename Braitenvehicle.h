/*
 * Braitenvehicle.h
 */

// ensure this library description is only included once
#ifndef Braitenvehicle_h
#define Braitenvehicle_h

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>

// library interface description
class Braitenvehicle {
  public:
    // constructors:
   Braitenvehicle(const int numberOfSteps, byte coilSteps);

    int version(void);
   
    void forward(int steps);
    void backward(int steps);
    
    bool watchSensors(const byte Sensors[]);
    void initSensors(const byte Sensors[]);

    Adafruit_MotorShield AFMS;
 
  private:
    const int numberOfSteps;

    byte coilSteps;
    byte Sensors;
    
    Adafruit_StepperMotor *motorLeft;
    Adafruit_StepperMotor *motorRight;

    void forwardstep1();
    void backwardstep1();
    void forwardstep2();
    void backwardstep2();

    AccelStepper stepperLeft;
    AccelStepper stepperRight;
    
};

#endif