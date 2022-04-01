# L298N Library

An easy to use L298N library to control DC Motors with ESP32.

## NOTICE

To instantiate both motors at once use the L298NX2 variant of the library.

L298NX2 is not a new version of module or IC,
but it stands for a double implementation of L298N library.

## INSTALL THE LIBRARY

Download this repository as a .zip file and from the Arduino IDE go to _Sketch -> Include library -> Add .ZIP Library_

## IMPORT

You can import the library in your code using the Arduino IDE going to _Sketch -> Include library -> L298N_
or directly writing the include statement in your code:
```
// For two motors
#include <L298N_Gaby.h>
```

### Same thing for L298NX2 variant

```
// With Enable pin to control speed

                     Motor A            Motor B
                |------------------||------------------|
L298NX2 myMotors(ENA, IN1, IN2, CHA, ENB, IN3, IN4, CHB);
```

#### Direction

| Constant          | Int Value |
| :---------------: | :-------: |
| FORWARD           |    CCW    |
| BACKWARD          |    CW     |
| STOP              |    STOP   |

## L298NX2 Methods

L298N_Gaby have the same methods of L298N identified by A or B suffix to drive each motor.

Methods list follows soon:)

| Method            | Paramsmeters  |
|                   |               | 
|                   |               | 
|                   |               |    
|                   |               | 
|                   |               | 


## Examples

Examples can be founds in the examples folder or if installed in Arduino IDE, by the Menu -> File -> Example -> L298N.

Wiring schema can be found in _schema_ folder.

## Donations

maybe next time:)