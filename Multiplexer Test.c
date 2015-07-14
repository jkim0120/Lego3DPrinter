#include "NXTMMX-lib.h"

task main()
{
		int i = 0;
		MMX_Init(S1, 0x06, 0);
		for(int n = 0; n < 2; n++)
		{

  	MMX_Run_Degrees( S1, 0x06, MMX_Motor_1,
                               MMX_Direction_Forward,
                               30, // speed
                               328 + i, // degrees
                               MMX_Completion_Wait_For,
                               MMX_Next_Action_Brake);

    wait10Msec(50);

    MMX_Run_Degrees( S1, 0x06, MMX_Motor_1,
                               MMX_Direction_Forward,
                               30, // speed
                               -330, // degrees
                               MMX_Completion_Wait_For,
                               MMX_Next_Action_Brake);

                               wait10Msec(50);


    i += 3;
   }
}
