/*
 * Braitenvehicle.h
 */

// ensure this library description is only included once
#ifndef Braitenvehicle_h
#define Braitenvehicle_h

#include "AccelStepperOO.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// library interface description
class Braitenvehicle {
  public:
    // constructors:
   Braitenvehicle(const int numberOfSteps, byte coilSteps);

    int version(void);
   
    void forward(int steps);
    void backward(int steps);
    void release();

    bool watchSensors(const byte Sensors[]);
    void initSensors(const byte Sensors[]);

    // void setMotorSpeed(boolean left, boolean right, int speed);
    // void moveTo(boolean left, boolean right, int position);
    void run();

    Adafruit_MotorShield AFMS;
 
  private:
    const int numberOfSteps;

    byte coilSteps;
    byte Sensors;
    
    Adafruit_StepperMotor *motorLeft;
    Adafruit_StepperMotor *motorRight;

    static void forwardstep1(void *user);
    static void backwardstep1(void *user);
    static void forwardstep2(void *user);
    static void backwardstep2(void *user);

    AccelStepperOO *stepperLeft;
    AccelStepperOO *stepperRight;    
};

#endif