/************************************************************************/
/*                                                                      */
/* NXT Port Configuration                                           		*/
/* ======================                                               */
/* MotorA: Y-axis      Sensor1: X-axis             											*/
/* MotorB: X-axis      Sensor2: Y-axis                             			*/
/* MotorC: Z-axis			 Sensor3: Motor Multiplexer											  */
/* Multiplexer Motor1: Axle Release                     								*/
/* Multiplexer Motor2: Rotation																					*/
/*                                                                      */
/************************************************************************/

#include "NXTMMX-lib.h"

void rotateHead(byte way)
{
	MMX_Run_Seconds( S3, 0x06, MMX_Motor_2,
                             way,
                             30, // speed
                             1.9,
                             MMX_Completion_Wait_For,
                             MMX_Next_Action_Brake);
}

void dislodge()
{
	MMX_Run_Seconds( S3, 0x06, MMX_Motor_1,
                       MMX_Direction_Reverse,
                       90, // speed
                       2, // seconds
                       MMX_Completion_Dont_Wait,
                       MMX_Next_Action_Brake);

	motor[motorC] = -25;
	wait10Msec(200);
	MMX_Run_Seconds( S3, 0x06, MMX_Motor_1,
                       MMX_Direction_Forward,
                       90, // speed
                       2, // seconds
                       MMX_Completion_Dont_Wait,
                       MMX_Next_Action_Brake);
	while(nMotorEncoder[motorC] != 0){}
	motor[motorC] = 0;

}

void calibrate ()
{
	//up first, then x, then y
	motor[motorC] = -25;
	//move up
	while(nMotorEncoder[motorC] != 0){}
	// assume 10000 is max time to hit top
	motor[motorC] = 0;
  motor[motorA] = -22;
  motor[motorB] = -20;
  while(motor[motorB] != 0 || motor[motorA] != 0)
  {
  	if(SensorValue[S2] != 0)
  	{
			nMotorEncoder[motorA] = 0;
			motor[motorA] = 10;
			while(nMotorEncoder[motorA] < 55){} // return forward after sensor touch
			motor[motorA] = 0;
		}
		if(SensorValue[S1] != 0)
		{
			nMotorEncoder[motorB] = 0;
			motor[motorB] = 10;
			while(nMotorEncoder[motorB] < 13){}
			motor[motorB] = 0;
		}
		wait10Msec(5);
	}
  wait10Msec(25);
}

void adjust()
{
		motor[motorA] = -10;
		wait10Msec(42);
		motor[motorA] = 10;
		wait10Msec(75);
		motor[motorA] = -10;
		wait10Msec(42);
		motor[motorA] = 0;
		motor[motorB] = -10;
		wait10Msec(42);
		motor[motorB] = 10;
		wait10Msec(75);
		motor[motorB] = -10;
		wait10Msec(42);
		motor[motorB] = 0;
}

float convUnit (float unit, float direction)
{
	if (direction == 1)
		return unit*75.0;
  else if (direction == 2)
  	return unit*37.0;
 	return 0;
}

void moveTo (int xUnit, int yUnit)
{
	nMotorEncoder[motorA]= 0;
	nMotorEncoder[motorB]= 0;

	motor[motorA] = 30; //changed from 20
	while (nMotorEncoder[motorA] < convUnit(1,2)*yUnit){}
	motor[motorA] = 0;
	wait10Msec(20);

	motor[motorB] = 30; //changed from 20
	while (nMotorEncoder[motorB] < convUnit(1,1)*xUnit){}
	motor[motorB] = 0;
	wait10Msec(20);
}

void pickUp (int xUnit, int yUnit)
{
	moveTo (xUnit, yUnit);
	motor[motorC] = 25;
	while (nMotorEncoder[motorC] < 1150){}
	motor[motorC] = 0;
	wait10Msec(20);
	adjust();
	motor[motorC] = 15;
	while (nMotorEncoder[motorC] < 1200){}
	motor[motorC] = 0;
	calibrate();
}

void putBlock (int xUnit, int yUnit, int layer, byte orientation)
{
	moveTo (xUnit, yUnit);
	if (orientation == 0x00)
		rotateHead(orientation);
	motor[motorA] = -10;
	wait10Msec(30);
	motor[motorA] = 0;
	motor[motorB] = -10;
	wait10Msec(25);
	motor[motorB] = 0;
	motor[motorC] = 25;
	while (nMotorEncoder[motorC] < 1220-layer*340){}
	motor[motorC] = 0;
	motor[motorA] = 10;
	wait10Msec(40);
	motor[motorA] = 0;
	motor[motorB] = 10;
	wait10Msec(40);
	motor[motorB] = 0;
	motor[motorC] = 25;
	while (nMotorEncoder[motorC] < 1275-layer*340){}
	motor[motorC] = 0;
	adjust();
	dislodge();
	calibrate();
	if (orientation == 0x00)
		rotateHead(0x01);
}

task main()
{
	MMX_Init(S3, 0x06, 0);
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorTouch;
	int timer = time100[T1];

  nxtDisplayString (1, "Press Square");
  nxtDisplayString (2, "To Begin");
  while (nNxtButtonPressed !=3){}
  while (nNxtButtonPressed ==3){}
  eraseDisplay();
  timer = 0; // resets timer

	motor[motorC] = -25;
	wait10Msec(300);
	motor[motorC] = 0;
	nMotorEncoder[motorC] = 0;
	calibrate();
  pickUp (0,0);
	putBlock (8,10,0,0x01);
	pickUp (3,0);
	putBlock (6,10,0,0x01);
	pickUp (6,0);
	putBlock (4,10,0,0x01);
	pickUp (9,0);
	putBlock (6,11,1,0x00);
	pickUp (12,0);
	putBlock (6,9,1,0x00);
	pickUp (0,4);
	putBlock (6,10,2,0x01);

	int timeElapsed = timer / 10;
	nxtDisplayString (1, "Build time: %d s", timeElapsed);
	nxtDisplayString (3, "Press Square");
  nxtDisplayString (4, "To End");
  while (nNxtButtonPressed !=3){}
  while (nNxtButtonPressed ==3){}
}
