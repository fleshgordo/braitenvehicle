/*
 * Braitenvehicle.h
 */

// ensure this library description is only included once
#ifndef Braitenvehicle_h
#define Braitenvehicle_h

#include "Stepper.h"

// library interface description
class Braitenvehicle {
  public:
    // constructors:
   Braitenvehicle(byte numberOfSteps, const byte l[], const byte r[], const byte Sensors[]);

    int version(void);
   
    void forward(int steps);
    void backward(int steps);
  bool watchSensors(const byte Sensors[]);
  void initSensors(const byte Sensors[]);
  
    enum State {STOP, FORWARD, ROTATE_RIGHT, ROTATE_LEFT};
    enum Sensors {NONE, SENSOR_RIGHT, SENSOR_LEFT, BOTH};

    
  private:
    byte numberOfSteps;
    byte Sensors;
    

    Stepper leftStepper;
    Stepper rightStepper;
};

#endif