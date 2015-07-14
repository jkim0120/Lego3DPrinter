task main()
{
nMotorEncoder[motorA] = 0;
nMotorEncoder[motorB] = 0;
nMotorEncoder[motorC] = 0;

while (nNxtButtonPressed != 0)
{
	while (nNxtButtonPressed == 3)
  wait10Msec(50);
	nxtDisplayString (1, "X Motor:");
	while (nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 1)
		{
			eraseDisplay();
			nMotorEncoder[motorA] = 0;
			motor[motorA] = 20;
			while (nNxtButtonPressed == 1);
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			nMotorEncoder[motorA] = 0;
			motor[motorA] = -20;
			while (nNxtButtonPressed == 2);
		}
	  else
	  {
	  	motor[motorA] = 0;
	  }
	  nxtDisplayString (3, "Encoder Count: %d" , nMotorEncoder[motorA]);
	}
	while (nNxtButtonPressed == 3);
	wait10Msec(50);
	nxtDisplayString (1, "Y Motor: ");
	while (nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 1)
		{
			eraseDisplay();
			nMotorEncoder[motorB] = 0;
			motor[motorB] = 20;
			while (nNxtButtonPressed == 1);
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			nMotorEncoder[motorB] = 0;
			motor[motorB] = -20;
			while (nNxtButtonPressed == 2);
		}
	  else
	  {
	  	motor[motorB] = 0;
	  }
	  nxtDisplayString (3, "Encoder Count: %d" , nMotorEncoder[motorB]);
	}
	while (nNxtButtonPressed == 3);
	wait10Msec(50);
	nxtDisplayString (1, "Z Motor:");
	while (nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 1)
		{
			eraseDisplay();
			nMotorEncoder[motorC] = 0;
			motor[motorC] = 20;
			while (nNxtButtonPressed == 1);
		}
		else if(nNxtButtonPressed == 2)
		{
			eraseDisplay();
			nMotorEncoder[motorC] = 0;
			motor[motorC] = -20;
			while (nNxtButtonPressed == 2);
		}
	  else
	  {
	  	motor[motorC] = 0;
	  }
	}

}}
