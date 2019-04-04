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
   
    void forward(int stepsLeft, int speedLeft, int stepsRight, int speedRight);
    void backward(int stepsLeft, int speedLeft, int stepsRight, int speedRight);
    void release();

    bool watchSensors(const byte Sensors[]);
    void initSensors(const byte Sensors[]);

    void moveTo(int leftPos, int rightPos);
    void move(int leftPos, int rightPos);
    
    void turnLeft(int angle);
    void turnRight(int angle);

    void setMaxSpeed(float leftSpeed, float rightSpeed);
    void setSpeed(float leftSpeed, float rightSpeed);
    void setAcceleration(float leftAccel, float rightAccel);
    
    boolean run(void);
    void stop();

    Adafruit_MotorShield AFMS;
 
    AccelStepperOO *stepperLeft;
    AccelStepperOO *stepperRight; 
  
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
};

#endif