# Braitenvehicle

Arduino library for Braitenberg vehicles (using state machine logic)
Developed for the course **Studio Protoyping Extended** at HSLU Digital Ideation March 2019

Heavily based on Adafruit Motorshield v2 library and the AccelStepper library

Course led by Tom Pavlofsky (Hardware) and Gordan Savicic (Software)

## Installation

Download the zip file and put it into the library folder of your Arduino installation. Make sure that following libraries are installed (using the library manager for example):

  - [Adafruit Motor Shield Rev2 Library](https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library)
  - [LinkedList](https://github.com/ivanseidel/LinkedList)
  - [State machine](https://github.com/jrullan/StateMachine)

I am not using the Arduino IDE for development but instead [Visual Studio Code](https://code.visualstudio.com/) with the [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino). You can upload your sketches directly from your text editor.

## Usage

Make sure your steppers are connected to the shield and the coils have correct polarity. Run this [testprogramm](https://github.com/fleshgordo/braitenvehicle/blob/master/examples/Steppertest/Steppertest.ino) to see if the motor makes a nice 360degree turn.

On top of your *.ino file include the library
```
#include "Braitenvehicle.h"
```

Create a vehicle instance. This will be our main object for controlling the motors.
Parameters are stepsize of your stepper, i. e. how many steps for a full rotation
and the steptype (SINGLE | DOUBLE | INTERLEAVE | MICROSTEP)
More infos here on the steptype [here](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/using-stepper-motors)

Make sure you have connected two motors to the shield (motorRight M3/M4 motorLeft M1/M2)

```
Braitenvehicle myVehicle(stepsPerRevolution, DOUBLE);
```

Now we have created an instance of the **myVehicle** object that has several functions.

Within the Arduino setup() routine we'll have to initialize the Motorshield by doing this

```
void setup() {
    myVehicle.AFMS.begin();
}
```

We should set maximum speed and acceleration for our motors. First parameter is for the left motor, second parameter for the right one (myVehicle.setMaxSpeed(leftmotor, rightmotor))

```
myVehicle.setMaxSpeed(200.0, 200.0);
myVehicle.setAcceleration(50, 50);
```

By calling **move()** (for relative movement) or **moveTo()** we can change the positioning for both motors. Making a full turn, we can move both motors by 200steps. Please note that this command won't make the motors turn (yet). We have to call the **run()** function as quick and often possible to achieve smooth movements.

```
myVehicle.move(200, 200);
```

So, inside the Arduino **loop()** function we would call **run()**

```
void loop() {
    myVehicle.run();
}
```

The **run()** function returns true as long as the motors move and a false value once both motors reached their position. 

```
void loop() {
    myVehicle.move(200, 200);
    while(myVehicle.run());
    myVehicle.move(-200, 200);
    while(myVehicle.run());
}
```

## External interrupts 

Read this [excellent guide](https://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/) on why we need external interrupts. The UNO board we are using has two external interrupts on pin 2 and 3. The official Arduino website also has good documentation on how to use [interrupt service routines](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/).

But those external interrupts are only working with digital input signals, i. e. buttons.

If you want to read an analog sensor and trigger the external interrupt once a certain threshold is reached, you'll have to work with analog comparator interrupts. An easy tutorial can be found [here](https://github.com/tardate/LittleArduinoProjects/tree/master/playground/AnalogComparator).

The reference voltage in the example above is created with a simple voltage divider, but you can also just use a PWM output from the Arduino to generate the desired reference voltage.

There's also [library](https://github.com/leomil72/analogComp) for Analog Comparator if none of the above satisfies you. 






