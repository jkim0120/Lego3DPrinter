task main()
{
nMotorEncoder[motorA] = 0;
nMotorEncoder[motorB] = 0;
nMotorEncoder[motorC] = 0;

	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorTouch;

while (nNxtButtonPressed != 0)
{
		motor[motorC]=-20;
	//move up
	wait1Msec(5500);
	// assume 10000 is max time to hit top
	motor[motorC] = 0;

	while (SensorValue[S1] == 0 || SensorValue[S2] == 0)
  {
  	motor[motorA] = (SensorValue[S2]-1)*20;
    motor[motorB] = (SensorValue[S1]-1)*20;
	}
	motor[motorA] = 0;
	motor[motorB] = 0;
	while (nNxtButtonPressed == 3);
  wait10Msec(50);
	nxtDisplayString (1, "X Motor:");
	while (nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 1)
		{
			nMotorEncoder[motorB] = 0;
			motor[motorB] = 20;
			while (nMotorEncoder[motorB] < 73.1);
				motor[motorB] = 0;
			while (nNxtButtonPressed == 1);
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			nMotorEncoder[motorB] = 0;
			motor[motorB] = -20;
			while (nMotorEncoder[motorB] > -73.1);
			motor[motorB] = 0;
				while (nNxtButtonPressed == 2);
		}
	}
	while (nNxtButtonPressed == 3);
	wait10Msec(50);
	nxtDisplayString (1, "Y Motor: ");
	while (nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 1)
		{
			nMotorEncoder[motorA] = 0;
			motor[motorA] = 20;
			while (nMotorEncoder[motorA] < 37.1);
				motor[motorA] = 0;
			while (nNxtButtonPressed == 1);
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			nMotorEncoder[motorA] = 0;
			motor[motorA] = -20;
			while (nMotorEncoder[motorA] > -37.1);
				motor[motorA] = 0;
		while (nNxtButtonPressed == 2);
		}

	}
	while (nNxtButtonPressed == 3);
	wait10Msec(50);
	nxtDisplayString (1, "Z Motor:");
	while (nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 1)
		{
			motor[motorC] = 20;
	    while (nMotorEncoder[motorC] < 1275);
    	motor[motorC] = 0;
		}
		else if(nNxtButtonPressed == 2)
		{
     	motor[motorC] = 20;
    	while (nMotorEncoder[motorC] < 1395);
    	motor[motorC] = 0;
		}
		motor[motorC] = -15;
	}
}}
