#include "NXTMMX-lib.h"

void rotateHead(byte way)
{
	MMX_Run_Seconds( S3, 0x06, MMX_Motor_2,
                             way,
                             15, // speed
                             2,
                             MMX_Completion_Wait_For,
                             MMX_Next_Action_Brake);
}

void dislodge()
{
	MMX_Run_Seconds( S3, 0x06, MMX_Motor_1,
                       MMX_Direction_Reverse,
                       90, // speed
                       3, // seconds
                       MMX_Completion_Wait_For,
                       MMX_Next_Action_Brake);

  motor[motorC]=-25;
	wait1Msec(1000);
	motor[motorC] = 0;

  MMX_Run_Seconds( S3, 0x06, MMX_Motor_1,
                       MMX_Direction_Forward,
                       90, // speed
                       3, // seconds
                       MMX_Completion_Wait_For,
                       MMX_Next_Action_Brake);
}

void calibrate ()
{
//up first, then x, then y
	motor[motorC]=-25;
	//move up
	wait1Msec(5000);
	// assume 10000 is max time to hit top
	motor[motorC] = 0;
  motor[motorA] = -18;
	while (SensorValue[S2] == 0);
	nMotorEncoder[motorA]=0;
	motor[motorA] = 10;
	while(nMotorEncoder[motorA] < 55); // return forward after sensor touch
	motor[motorA] = 0;
	motor[motorB] = -18;
	while (SensorValue[S1] == 0);
	nMotorEncoder[motorB] = 0;
	motor[motorB] = 10;
	while (nMotorEncoder[motorB] < 13);
	motor[motorB] = 0;
  wait10Msec(25);
	}

void adjust()
{
		motor[motorA] = -10;
		wait10Msec(35);
		motor[motorA] = 10;
		wait10Msec(60);
		motor[motorA] = -10;
		wait10Msec(35);
		motor[motorA] = 0;
		motor[motorB] = -10;
		wait10Msec(35);
		motor[motorB] = 10;
		wait10Msec(60);
		motor[motorB] = -10;
		wait10Msec(35);
		motor[motorB] = 0;
		MMX_Run_Degrees( S3, 0x06, MMX_Motor_2,
                             MMX_Direction_Forward,
                             10, // speed
                             45,// degrees
                             MMX_Completion_Wait_For,
                             MMX_Next_Action_Brake);
    MMX_Run_Degrees( S3, 0x06, MMX_Motor_2,
                             MMX_Direction_Forward,
                             10, // speed
                             -45,// degrees
                             MMX_Completion_Wait_For,
                             MMX_Next_Action_Brake);
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

	for (int i = 0; i < yUnit; i++)
	{
	motor[motorA] = 20;
	while (nMotorEncoder[motorA] < convUnit(1,2)*i);
	motor[motorA] = 0;
	wait10Msec(20);
  }

	for (int i = 0; i < xUnit; i++)
	{
	motor[motorB] = 20;
	while (nMotorEncoder[motorB] < convUnit(1,1)*i);
	motor[motorB] = 0;
	wait10Msec(20);
  }
}

void pickUp (int xUnit, int yUnit)
{
	calibrate();
	moveTo (xUnit, yUnit);
	nMotorEncoder[motorC]= 0;

	motor[motorC] = 25;
	while (nMotorEncoder[motorC] < 1150);
	motor[motorC] = 0;
	wait10Msec(20);
	adjust();
	motor[motorC] = 15;
	while (nMotorEncoder[motorC] < 1150);
	motor[motorC] = 0;
	calibrate();
}

void putBlock (int xUnit, int yUnit)
{
	moveTo (xUnit, yUnit);
	motor[motorA] = -10;
	wait10Msec(35);
	motor[motorA] = 0;
	motor[motorB] = -10;
	wait10Msec(35);
	motor[motorB] = 0;
	nMotorEncoder[motorC]= 0;
	motor[motorC] = 25;
	while (nMotorEncoder[motorC] < 1200);
	motor[motorC] = 0;
	motor[motorA] = 10;
	wait10Msec(42);
	motor[motorA] = 0;
	motor[motorB] = 10;
	wait10Msec(42);
	motor[motorB] = 0;
	motor[motorC] = 25;
	while (nMotorEncoder[motorC] < 1250);
	motor[motorC] = 0;
	adjust();
	//lin function
	dislodge();
	calibrate();
}

task main()
{
	MMX_Init(S3, 0x06, 0);
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorTouch;

	TFileHandle   hFileHandle;              // will keep track of our file
  TFileIOResult nIOResult;                // will store our IO results
  string        sFileName = "squareFile.txt";   // the name of our file
  int           nFileSize = 0; // will store our file size

  float numLayers, numObj, size, posX, posY;
  byte orientation;

  OpenRead(hFileHandle, nIOResult, sFileName, nFileSize);

  ReadFloat(hFileHandle, nIOResult, numLayers);
  ReadFloat(hFileHandle, nIOResult, numObj);
  ReadFloat(hFileHandle, nIOResult, size);
  ReadFloat(hFileHandle, nIOResult, posX);
  ReadFloat(hFileHandle, nIOResult, posY);
	ReadByte(hFileHandle, nIOResult, orientation);

	Close(hFileHandle, nIOResult);

	nxtDisplayString(1,"%f", numLayers);


}

	/*
	if (size == 4)
			{
				pickUp(1, 5);
			}
			else if (size == 8)
			{
				pickUp(1, 1);
			}

			rotateHead(orientation);

			putBlock(posX, posY);
			//move and place brick

			rotateHead(orientation*-1);

		*/








	/*OpenRead(printThing, IOResult, "squareFile.txt", fileSize);
	short numLayers;
	ReadShort(printThing, IOResult, numLayers);
	short 2x2Taken = 0;
	short 2x4Taken = 0;

	short numObj, size, posX, posY, orientation;
	for (short i = 1 ; i <= numLayers, i++) 
	{
		ReadShort(printThing, IOResult, numObj);
		for (short k = 1 ; k <= numObj, k++)
		{
			ReadShort(printThing, IOResult, size);
			ReadShort(printThing, IOResult, posX);
			ReadShort(printThing, IOResult, posY);
			ReadShort(printThing, IOResult, orientation);

			checkInventory(2x2Taken, 2x4Taken);

			if (size == 4)
			{
				pickUp(2x2Taken*3+1, 5);
				2x2Taken++;
			}
			else if (size == 8)
			{
				pickUp(2x4Taken*3+1, 1);
				2x4Taken++;
			}

			rotateHead(orientation);

			putDown(posX, posY, i);
			//move and place brick

			rotateHead(orientation*-1);

			Close(printThing, IOResult);


		}

	}

}
*/
