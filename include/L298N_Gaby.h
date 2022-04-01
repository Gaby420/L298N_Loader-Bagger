#ifndef L298N_Gaby01_h
#define L298N_Gaby01_h

#include "Arduino.h"
typedef void (*CallBackFunction)();

class L298N_Gaby
{
public:
    //ESP32 dual motor 
    L298N_Gaby(int IN1,int IN2,int ENA, int CHA,int IN3,int IN4, int ENB, int CHB);
    //use motor
    void rotate(int motor, int speed, int direktion);

    void begin();

    //how to stop motor
    void brake(int motor);

private:
   void printDebug1(int motor, int p1, int v1, int p2, int v2, int dir, int speed);
   void printDebug2(int motor1, int p1, int v1, int p2, int v2, int dir1, int speed1, int motor2, int p3, int v3, int p4, int v4, int dir2, int speed2) ;

   void printDebug3(int motor, int p1, int v1, int p2, int v2, int dir, int speed, int duty);
   void printDebug4(int motor1, int p1, int v1, int p2, int v2, int dir1, int speed1, int duty1, int motor2, int p3, int v3, int p4, int v4, int dir2, int speed2, int duty2) ;
  
   int _in1, _in2, _enA, _in3, _in4,  _enB, _pwmBit, _chA, _chB;
   boolean _debug = false;
   boolean _dual;
   int _resulotion =12;
   int _frequency = 5000;
   int _bits = pow(2,_resulotion);
   
 
   int toPWM(int v);   

};

#endif/*  */