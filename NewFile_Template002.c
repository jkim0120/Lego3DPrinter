#include "NXTMMX-lib.h"
task main()
{
MMX_Init(S2, 0x06, 0);
MMX_Run_Seconds( S3, 0x06, MMX_Motor_1,
                       MMX_Direction_Forward,
                       90, // speed
                       2, // seconds
                       MMX_Completion_Wait_For,
                       MMX_Next_Action_Brake);

}
