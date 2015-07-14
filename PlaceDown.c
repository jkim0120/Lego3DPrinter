void calibrate ()
{
nxtDisplayString(1, "Calibrate");
//up first, then x, then y
	motor[motorC]=-25;
	//move up
	wait1Msec(4500);
	nxtDisplayString(1, "Calibrate2");
	// assume 10000 is max time to hit top
	motor[motorC] = 0;

	while (SensorValue[S1] == 0 || SensorValue[S2] == 0)
  {
  	motor[motorA] = (SensorValue[S2]-1)*20;
    motor[motorB] = (SensorValue[S1]-1)*20;
	}
	motor[motorA] = 0;
	motor[motorB] = 0;
	nxtDisplayString(1, "           ");
}

float convUnit (float Unit, int direction)
{
	if (direction == 1)
		return Unit*73.1;
  else if (direction == 2)
		return Unit*37.1;
  else
  	return 0;
}

void moveTo (float xUnit, float yUnit)
{
  nxtDisplayString(2, "MoveTo");
  nMotorEncoder[motorA]= 0;
	nMotorEncoder[motorB]= 0;
	motor[motorB] = 20;
	while (nMotorEncoder[motorB] < convUnit(xUnit,1));
	motor[motorB] = 0;

	motor[motorA] = 20;
	while (nMotorEncoder[motorA] < convUnit(yUnit,2);
	motor[motorA] = 0;
	nxtDisplayString(2, "      ");
}

void pickUp (int xUnit, int yUnit)
{
	nxtDisplayString(3, "Pick Up");
	calibrate();
	moveTo (xUnit, yUnit);
	nMotorEncoder[motorC]= 0;

	motor[motorC] = 17;
	while (nMotorEncoder[motorC] < 1275);
	motor[motorC] = 0;
	calibrate();
	nxtDisplayString(3, "        ");
}

void putBlock (int xUnit, int yUnit)
{
	nxtDisplayString(4, "Put Block");
	calibrate();
	moveTo (xUnit, yUnit);
	nMotorEncoder[motorC]= 0;

	motor[motorC] = 17;
	while (nMotorEncoder[motorC] < 1395);
	motor[motorC] = 0;
	calibrate();
	nxtDisplayString(4, "          ");
}

task main()
{
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorTouch;
	pickUp(0,0);
	putBlock(13,9);
	// place block 1400
	// pick up 1300
}
