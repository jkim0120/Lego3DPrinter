task main()
{
	while(true)
	{
		if(nNxtButtonPressed == 1)
		{
			nmotorEncoder[motorA] = 0;
			motor[motorA] = -40;
			while(nMotorEncoder[motorA] > -308);
			motor[motorA] = 0;
		}

		if(nNxtButtonPressed == 2)
		{
			nmotorEncoder[motorA] = 0;
			motor[motorA] = 40;
			while(nMotorEncoder[motorA] < 308);
			motor[motorA] = 0;
		}
	}
}
