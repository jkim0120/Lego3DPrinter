/************************************************************************/
/*                                                                      */
/* Program Name: NXTMMX-lib.h                                           */
/* =============================                                        */
/* BASED ON THE NXC LIBRARY WRITTEN BY DEEPAK PATIL                     */
/* Copyright (c) 2010 by mindsensors.com                                */
/* Email: info (<at>) mindsensors (<dot>) com                           */
/*                                                                      */
/* This program is free software. You can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation; version 3 of the License.              */
/* Read the license at: http://www.gnu.org/licenses/gpl.txt             */
/*                                                                      */
/* When             Who             Comments                            */
/* 26 APRIL 2010    Rudolf Lapie    RobotC version of the NXC library   */
/*                                                    by Deepak Patil   */
/************************************************************************/

#pragma systemFile

#ifndef _NXTMMX_INCLUDED
#define _NXTMMX_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// INTERFACE ROUTINES
////////////////////////////////////////////////////////////////////////////////
void MMX_GetFirmware (tSensors port, byte addr, string &result) ;
void MMX_GetVendorID (tSensors port, byte addr, string &result) ;
void MMX_GetDeviceID (tSensors port, byte addr, string &result) ;

void MMX_Init( tSensors port, byte addr, byte profile_for_pid ) ;
int MMX_Run_Unlimited( tSensors port, byte addr, byte motor_number, byte direction, byte speed ) ;
int MMX_Run_Seconds( tSensors port, byte addr, byte motor_number, byte direction, byte speed, byte duration, byte wait_for_completion, byte next_action ) ;
int MMX_Run_Tachometer( tSensors port, byte addr, byte motor_number, byte direction, byte speed, long tachometer, byte relative, byte wait_for_completion, byte next_action ) ;
int MMX_Run_Degrees( tSensors port, byte addr, byte motor_number, byte direction, byte speed, long degrees, byte wait_for_completion, byte next_action );
int MMX_Run_Rotations( tSensors port, byte addr, byte motor_number, byte direction, byte speed, byte rotations, byte wait_for_completion, byte next_action ) ;
int MMX_Stop( tSensors port, byte addr, byte motor_number, byte next_action );
int MMX_GetBattVoltage(tSensors port, byte addr) ;
long MMX_ReadTachometerPosition( tSensors port, byte addr, byte motor_number) ;
void MMX_SetPerformanceParameters( tSensors port, byte addr, int KP_tacho, int KI_tacho, int KD_tacho, int KP_speed, int KI_speed,int KD_speed, byte pass_count, byte tolerance);
byte MMX_MotorStatus(tSensors port, byte addr, byte motor_number) ;
bool MMX_IsTimeDone(tSensors port, byte addr, byte motor_number) ;
void MMX_WaitUntilTimeDone(tSensors port, byte addr, byte motor_number) ;
bool MMX_IsTachoDone(tSensors port, byte addr, byte motor_number) ;
void MMX_WaitUntilTachoDone(tSensors port, byte addr, byte motor_number) ;
int MMX_SendCommand(tSensors port, byte addr, byte cmd) ;

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS TO BE USED IN THE USER PROGRAM
////////////////////////////////////////////////////////////////////////////////

#define MMX_ADDRESS               0x06

//  Motor selection related constants
#define MMX_Motor_1                0x01
#define MMX_Motor_2                0x02
#define MMX_Motor_Both             0x03

// Motor action constants
// stop and let the motor coast.
#define MMX_Next_Action_Float      0x00
// apply brakes, and resist change to tachometer
#define MMX_Next_Action_Brake      0x01
// apply brakes, and restore externally forced change to tachometer
#define MMX_Next_Action_BrakeHold  0x02

// Motor Direction related constants
#define MMX_Direction_Forward      0x01
#define MMX_Direction_Reverse      0x00

// Tachometer related constants
#define MMX_Move_Relative 0x01
#define MMX_Move_Absolute 0x00

// Next action (upon completion of current action)
#define MMX_Completion_Wait_For    0x01
#define MMX_Completion_Dont_Wait   0x00

// Commonly used speed constants, these are just convenience constants,
// You can use any value between 0 and 100.
#define MMX_Speed_Full 90
#define MMX_Speed_Medium 60
#define MMX_Speed_Slow 25

////////////////////////////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////////////////////////////
#define MMX_FIRMWARE         0x00
#define MMX_VENDOR_ID        0x08
#define MMX_DEVICE_ID        0x10

#define MMX_CONTROL_SPEED      0x01
#define MMX_CONTROL_RAMP       0x02
#define MMX_CONTROL_RELATIVE   0x04
#define MMX_CONTROL_TACHO      0x08
#define MMX_CONTROL_BRK        0x10
#define MMX_CONTROL_ON         0x20
#define MMX_CONTROL_TIME       0x40
#define MMX_CONTROL_GO         0x80

#define MMX_SETPT_M1     0x42
#define MMX_SPEED_M1     0x46
#define MMX_TIME_M1      0x47
#define MMX_CMD_B_M1     0x48
#define MMX_CMD_A_M1     0x49

#define MMX_SETPT_M2     0x4A
#define MMX_SPEED_M2     0x4E
#define MMX_TIME_M2      0x4F
#define MMX_CMD_B_M2     0x50
#define MMX_CMD_A_M2     0x51

/*
 * Read registers.
 */
#define MMX_POSITION_M1  0x62
#define MMX_POSITION_M2  0x66
#define MMX_STATUS_M1    0x72
#define MMX_STATUS_M2    0x73
#define MMX_TASKS_M1     0x76
#define MMX_TASKS_M2     0x77


////////////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATIONS OF AUXILIARY ROUTINES (do not use these in main program)
////////////////////////////////////////////////////////////////////////////////
static void _MMX_FlushPort(tSensors port) ;
static byte _MMX_ReadByte(tSensors port, byte addr, byte reg) ;
static byte _MMX_ReadSecondByte(tSensors port, byte addr, byte reg) ;
static int  _MMX_ReadInteger(tSensors port, byte addr, byte reg) ;
static long _MMX_ReadLong (tSensors port, byte addr, byte reg) ;
static void _MMX_ReadString (tSensors port, byte addr, byte mmx_register, string &result) ;
static void _MMX_WriteByte(tSensors port, byte addr, byte location, byte data) ;
static void _MMX_WriteData3(tSensors port, byte addr, byte data1, byte data2, byte data3) ;
static void _MMX_WriteData5(tSensors port, byte addr, byte data1, byte data2, byte data3, byte data4, byte data5) ;
static void _MMX_WriteData9(tSensors port, byte addr, byte data1, byte data2, byte data3, byte data4, byte data5, byte data6, byte data7, byte data8, byte data9) ;

////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF INTERFACE ROUTINES (for the interested only)
////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------
void MMX_GetFirmware(tSensors port, byte addr, string &result)
{
   _MMX_ReadString(port, addr, MMX_FIRMWARE, result);
}
//---------------------------------------------------------------
void MMX_GetVendorID(tSensors port, byte addr, string &result)
{
  _MMX_ReadString(port, addr, MMX_VENDOR_ID, result);
}
//---------------------------------------------------------------
void MMX_GetDeviceID(tSensors port, byte addr, string &result)
{
  _MMX_ReadString(port, addr, MMX_DEVICE_ID, result );
}

//---------------------------------------------------------------
void MMX_Init( tSensors port, byte addr, byte profile_for_pid )
{
  SensorType[port] = sensorI2CCustom;
  //_MMX_FlushPort(port);
  //MMX_SendCommand(port, addr, 'R');
}

//---------------------------------------------------------------
int MMX_Run_Unlimited( tSensors port,
                             byte addr,
                             byte motor_number,
                             byte direction,
                             byte speed )
{
  byte ctrl;
  byte sp;

  ctrl = 0;
  ctrl |= MMX_CONTROL_SPEED;

  if ( direction == MMX_Direction_Forward ) sp = speed;
  if ( direction != MMX_Direction_Forward ) sp = (speed*(-1));
  if ( motor_number != MMX_Motor_Both ) ctrl |= MMX_CONTROL_GO;

  if ( (motor_number & 0x01) != 0 ) {
    _MMX_WriteData5(port, addr, MMX_SPEED_M1, sp, 0, 0, ctrl);
  }
  if ( (motor_number & 0x02) != 0 ) {
    _MMX_WriteData5(port, addr, MMX_SPEED_M2, sp, 0, 0, ctrl);
  }
  if ( motor_number == MMX_Motor_Both ) {
    MMX_SendCommand(port, addr, 'S');
  }
  _MMX_FlushPort(port);

  return 0;
}

//---------------------------------------------------------------
int MMX_Run_Seconds( tSensors port,
                             byte addr,
                             byte motor_number,
                             byte direction,
                             byte speed,
                             byte duration,
                             byte wait_for_completion,
                             byte next_action )
{
  byte ctrl;
  byte sp;

  ctrl = 0;
  ctrl |= MMX_CONTROL_SPEED;
  ctrl |= MMX_CONTROL_TIME;

  if ( next_action == MMX_Next_Action_Brake ) ctrl |= MMX_CONTROL_BRK;
  if ( next_action == MMX_Next_Action_BrakeHold ) {
    ctrl |= MMX_CONTROL_BRK;
    ctrl |= MMX_CONTROL_ON;
  }
  if ( motor_number != MMX_Motor_Both ) ctrl |= MMX_CONTROL_GO;
  if ( direction == MMX_Direction_Forward ) sp = speed;
  if ( direction != MMX_Direction_Forward ) sp = (speed*(-1));

  if ( (motor_number & 0x01) != 0 ) {
    _MMX_WriteData5(port, addr, MMX_SPEED_M1, sp, duration, 0, ctrl);
  }
  if ( (motor_number & 0x02) != 0 ) {
    _MMX_WriteData5(port, addr, MMX_SPEED_M2, sp, duration, 0, ctrl);
  }
  if ( motor_number == MMX_Motor_Both ) {
    MMX_SendCommand(port, addr, 'S');
  }

  _MMX_FlushPort(port);
  if ( wait_for_completion == MMX_Completion_Wait_For ) {
    wait1Msec(50);  // this delay is required for the status byte to be available for reading.
    MMX_WaitUntilTimeDone(port, addr, motor_number);
  }
  _MMX_FlushPort(port);

  return 0;
}

//---------------------------------------------------------------
int MMX_Run_Tachometer( tSensors port,
                             byte addr,
                             byte motor_number,
                             byte direction,
                             byte speed,
                             long tachometer,
                             byte relative,
                             byte wait_for_completion,
                             byte next_action )
{
  byte ctrl;
  long tch;
  int stp1,stp2,stp3,stp4;

  ctrl = 0;
  ctrl |= MMX_CONTROL_TACHO;
  ctrl |= MMX_CONTROL_SPEED;

  if ( relative == MMX_Move_Relative ) {
    ctrl |= MMX_CONTROL_RELATIVE;
    /*
     * if the move requested is relative,
     * follow the direction to set the tachometer value.
     */

    if ( direction == MMX_Direction_Forward ) tch = tachometer;
    if ( direction != MMX_Direction_Forward ) tch = (tachometer*(-1));
  } else {
    /*
     * if the move is absolute,
     * use the tach value as is and ignore the direction.
     */
    tch = tachometer;
  }

  stp1 = 0xff&tch;
  stp2 = 0xff&((0x0000ff00&tch)>>8);
  stp3 = 0xff&((0x00ff0000&tch)>>16);
  stp4 = 0xff&((0xff000000&tch)>>24);

  if ( next_action == MMX_Next_Action_Brake ) ctrl |= MMX_CONTROL_BRK;
  if ( next_action == MMX_Next_Action_BrakeHold ) {
    ctrl |= MMX_CONTROL_BRK;
    ctrl |= MMX_CONTROL_ON;
  }
  if ( motor_number != MMX_Motor_Both ) ctrl |= MMX_CONTROL_GO;

  if ( (motor_number & 0x01) != 0 ) {
    _MMX_WriteData9(port, addr, MMX_SETPT_M1, stp1, stp2, stp3, stp4, speed, 0, 0, ctrl);
  }
  if ( (motor_number & 0x02) != 0 ) {
    _MMX_WriteData9(port, addr, MMX_SETPT_M2, stp1, stp2, stp3, stp4, speed, 0, 0, ctrl);
  }
  if ( motor_number == MMX_Motor_Both ) {
    MMX_SendCommand(port, addr, 'S');
  }

  _MMX_FlushPort(port);
  if ( wait_for_completion == MMX_Completion_Wait_For ) {
    wait1Msec(50);  // this delay is required for the status byte to be available for reading.
    MMX_WaitUntilTachoDone(port, addr, motor_number);
  }
  _MMX_FlushPort(port);

  return 0;
}

//---------------------------------------------------------------
int MMX_Run_Degrees( tSensors port,
                             byte addr,
                             byte motor_number,
                             byte direction,
                             byte speed,
                             long degrees,
                             byte wait_for_completion,
                             byte next_action )
{
  return MMX_Run_Tachometer( port, addr, motor_number, direction,
                             speed, degrees, MMX_Move_Relative,
                             wait_for_completion, next_action);
}

//---------------------------------------------------------------
int MMX_Run_Rotations( tSensors port,
                             byte addr,
                             byte motor_number,
                             byte direction,
                             byte speed,
                             byte rotations,
                             byte wait_for_completion,
                             byte next_action )
{
  return MMX_Run_Tachometer( port, addr, motor_number, direction,
                             speed, (rotations*360), MMX_Move_Relative,
                             wait_for_completion, next_action);
}

//---------------------------------------------------------------
/*
 * Stop command supports floating of motors or brake.
 * When brake is issued, it does not support further hold.
 * i.e. BrakeHold works as Brake.
 *
 */
int MMX_Stop( tSensors port, byte addr,
                     byte motor_number,
                     byte next_action )
{
  if ( next_action == MMX_Next_Action_Brake ||
       next_action == MMX_Next_Action_BrakeHold ) {
    if ( (motor_number & 0x01) != 0 ) {
      MMX_SendCommand(port, addr, 'A');
    }
    if ( (motor_number & 0x02) != 0 ) {
      MMX_SendCommand(port, addr, 'B');
    }
    if ( motor_number == MMX_Motor_Both ) {
      MMX_SendCommand(port, addr, 'C');
    }
  } else {  // float
    if ( (motor_number & 0x01) != 0 ) {
      MMX_SendCommand(port, addr, 'a');
    }
    if ( (motor_number & 0x02) != 0 ) {
      MMX_SendCommand(port, addr, 'b');
    }
    if ( motor_number == MMX_Motor_Both ) {
      MMX_SendCommand(port, addr, 'c');
    }
  }
  _MMX_FlushPort(port);
  return 0;
}

//---------------------------------------------------------------
/*===================================
**
** Read voltage supplied to MMX
** from the external battery
** (in mili-volts)
**
===================================*/
int  MMX_GetBattVoltage(tSensors port, byte addr)
{
  ubyte replyMessage[2] ;
  ubyte I2CMessage[4];

  I2CMessage[0] = 2;
  I2CMessage[1] = addr ;
  I2CMessage[2] = 0x41;

 	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 2);

  while (nI2CStatus[port] == STAT_COMM_PENDING)	wait1Msec(1);
	readI2CReply(port, & replyMessage[0], 1);

  return(37*(0x00FF & replyMessage[0]));  // 37 is calculated from supply from NXT =4700 mv /128
}

//---------------------------------------------------------------
long MMX_ReadTachometerPosition( tSensors port, byte addr,
                     byte motor_number)
{
  if ( motor_number == MMX_Motor_1 ) {
    return _MMX_ReadLong(port, addr, MMX_POSITION_M1);
  } else if ( motor_number == MMX_Motor_2 ) {
    return _MMX_ReadLong(port, addr, MMX_POSITION_M2);
  }
  else {
    return 0;
  }
}

//---------------------------------------------------------------
void MMX_SetPerformanceParameters( tSensors port, byte addr,
                 int KP_tacho,
                 int KI_tacho,
                 int KD_tacho,
                 int KP_speed,
                 int KI_speed,
                 int KD_speed,
                 byte pass_count,
                 byte tolerance)
{
  ubyte I2CMessage[16];

  I2CMessage[0] = addr;
  I2CMessage[1] = 0x7A; // location where the PID begins
  I2CMessage[2] =    (KP_tacho & 0xFF);
  I2CMessage[3] =  (((KP_tacho &0xFF00)>>8) & 0xFF);
  I2CMessage[4] =    (KI_tacho & 0xFF);
  I2CMessage[5] =  (((KI_tacho &0xFF00)>>8) & 0xFF);
  I2CMessage[6] =    (KD_tacho & 0xFF);
  I2CMessage[7] =  (((KD_tacho &0xFF00)>>8) & 0xFF);

  I2CMessage[8] =    (KP_speed & 0xFF);
  I2CMessage[9] =  (((KP_speed &0xFF00)>>8) & 0xFF);
  I2CMessage[10] =   (KI_speed & 0xFF);
  I2CMessage[11] = (((KI_speed &0xFF00)>>8) & 0xFF);
  I2CMessage[12] =   (KD_speed & 0xFF);
  I2CMessage[13] = (((KD_speed &0xFF00)>>8) & 0xFF);
  I2CMessage[14] = pass_count;
  I2CMessage[15] = tolerance;

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 15);
	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
}

//---------------------------------------------------------------
byte MMX_MotorStatus(tSensors port, byte addr, byte motor_number)
{
  if ( motor_number == MMX_Motor_1 ) {
    return (_MMX_ReadByte(port, addr, MMX_STATUS_M1));
  }
  else if ( motor_number == MMX_Motor_2 ) {
    return (_MMX_ReadSecondByte(port, addr, MMX_STATUS_M1));
  }
  else  {  // not supported
    return 0xff;
  }

}

//---------------------------------------------------------------
bool MMX_IsTimeDone(tSensors port, byte addr, byte motor_number)
{
  int retval ;
  byte result, result2;

  if ( motor_number == MMX_Motor_1 ) {
    result = _MMX_ReadByte(port, addr, MMX_STATUS_M1);
    // look for the time bit to be zero.
    if (( result & 0x40 ) == 0 ) return true;
  } else if ( motor_number == MMX_Motor_2 ) {
    result = (_MMX_ReadSecondByte(port, addr, MMX_STATUS_M1));
    // look for the time bit to be zero.
    if (( result & 0x40 ) == 0 ) return true;
  } else if ( motor_number == MMX_Motor_Both ) {
    retval = _MMX_ReadInteger(port, addr, MMX_STATUS_M1);
    // look for both time bits to be zero
    result = retval & 0xFF ;
    result2 = retval << 8;
    if (((result & 0x40) == 0) && ((result2 & 0x40) == 0) ) return true;
  }
  return false;
}

//---------------------------------------------------------------
void MMX_WaitUntilTimeDone(tSensors port, byte addr, byte motor_number)
{
    while ( MMX_IsTimeDone(port, addr, motor_number) != true ) wait1Msec(50);
}


//---------------------------------------------------------------
bool MMX_IsTachoDone(tSensors port, byte addr, byte motor_number)
{
  int retval ;
  byte result, result2;

  if ( motor_number == MMX_Motor_1 ) {
    result = _MMX_ReadByte(port, addr, MMX_STATUS_M1);
    // look for the tacho bit to be zero.
    if (( result & 0x08 ) == 0 ) return true;
  } else if ( motor_number == MMX_Motor_2 ) {
    result = _MMX_ReadSecondByte(port, addr, MMX_STATUS_M1);
    // look for the tacho bit to be zero.
    if (( result & 0x08 ) == 0 ) return true;
  } else if ( motor_number == MMX_Motor_Both ) {
    retval = _MMX_ReadInteger(port, addr, MMX_STATUS_M1);
    // look for both tacho bits to be zero
    result = retval & 0xFF;
    result2 = retval<<8;
    if (((result & 0x08) == 0) && ((result2 & 0x08) == 0) ) return true;
  }
  return false;
}

//---------------------------------------------------------------
void MMX_WaitUntilTachoDone(tSensors port, byte addr, byte motor_number)
{
    while ( MMX_IsTachoDone(port, addr, motor_number) != true ) wait1Msec(50);
}

//---------------------------------------------------------------
int MMX_SendCommand(tSensors port, byte addr, byte cmd)
{
  byte I2CMessage[4];

  I2CMessage[0] = 3 ;
  I2CMessage[1] = addr ;
  I2CMessage[2] = 0x41 ;
  I2CMessage[3] = cmd ;

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 3);
	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  return nI2CStatus[port];
}


////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF AUXILIARY ROUTINES (for the interested only)
////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
static void _MMX_FlushPort(tSensors port)
{
    nI2CBytesReady[port] = 0 ; // flush the port
}

//---------------------------------------------------------------
static byte _MMX_ReadByte(tSensors port, byte addr, byte reg)
{
  ubyte replyMessage[2] ;
  ubyte I2CMessage[4];

  I2CMessage[0] = 2; // Message size
	I2CMessage[1] = addr; // I2C Device Address
	I2CMessage[2] = reg ; // I2C Register to read

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 2);

  while (nI2CStatus[port] == STAT_COMM_PENDING)	wait1Msec(1);
	readI2CReply(port, & replyMessage[0], 1);

	return (replyMessage[0]);
}

//---------------------------------------------------------------
static byte _MMX_ReadSecondByte(tSensors port, byte addr, byte reg)
{
  ubyte replyMessage[2] ;
  ubyte I2CMessage[4];

  I2CMessage[0] = 2; // Message size
	I2CMessage[1] = addr; // I2C Device Address
	I2CMessage[2] = reg ; // I2C Register to read

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 2);

  while (nI2CStatus[port] == STAT_COMM_PENDING)	wait1Msec(1);
	readI2CReply(port, & replyMessage[0], 2);

	return (replyMessage[1]);
}

//---------------------------------------------------------------
static int _MMX_ReadInteger (tSensors port, byte addr, byte reg)
{
  ubyte replyMessage[2] ;
  ubyte I2CMessage[4];

  I2CMessage[0] = 2;    // Message size
	I2CMessage[1] = addr; // I2C Device Address
	I2CMessage[2] = reg ; // I2C Register to read

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 2);

  while (nI2CStatus[port] == STAT_COMM_PENDING)	wait1Msec(1);
	readI2CReply(port, & replyMessage[0], 2);

	return (replyMessage[0] + (replyMessage[1]<<8));
}


//---------------------------------------------------------------
static long _MMX_ReadLong (tSensors port, byte addr, byte reg)
{
  ubyte replyMessage[4] ;
  ubyte I2CMessage[4];
  long result ;

  I2CMessage[0] = 2; // Message size
	I2CMessage[1] = addr; // I2C Device Address
	I2CMessage[2] = reg ; // I2C Register to read

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 4);

  while (nI2CStatus[port] == STAT_COMM_PENDING)	wait1Msec(1);
	readI2CReply(port, & replyMessage[0], 4);

	result = ((long)replyMessage[3] << 24) +
           ((long)replyMessage[2] << 16) +
           ((long)replyMessage[1] <<  8) +
            (long)replyMessage[0];

  return result ;

}

//---------------------------------------------------------------
static void _MMX_ReadString (tSensors port, byte addr, byte mmx_register, string &result)
{
  byte replyMessage[9] ;
  ubyte I2CMessage[4];

  I2CMessage[0] = 2; // Message size
	I2CMessage[1] = addr; // I2C Device Address
	I2CMessage[2] = mmx_register ; // I2C Register to read

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 8);

  while (nI2CStatus[port] == STAT_COMM_PENDING)	wait1Msec(1);
	readI2CReply(port, & replyMessage[0], 8);
	replyMessage[8] = 0 ;

	StringFromChars (result, & replyMessage) ;
}

//---------------------------------------------------------------
void _MMX_WriteData9(tSensors port, byte addr, byte data1, byte data2,
                               byte data3, byte data4, byte data5,
                               byte data6, byte data7, byte data8,
                               byte data9)
{
  byte I2CMessage[11];

  I2CMessage[0] = 10 ;
  I2CMessage[1] = addr ;
  I2CMessage[2] = data1;
  I2CMessage[3] = data2;
  I2CMessage[4] = data3;
  I2CMessage[5] = data4 ;
  I2CMessage[6] = data5 ;
  I2CMessage[7] = data6 ;
  I2CMessage[8] = data7;
  I2CMessage[9] = data8 ;
  I2CMessage[10] = data9;

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 10);
	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
}

//---------------------------------------------------------------
void _MMX_WriteData3(tSensors port, byte addr, byte data1, byte data2, byte data3)
{
  byte I2CMessage[5];

  I2CMessage[0] = 4 ;
  I2CMessage[1] = addr ;
  I2CMessage[2] = data1;
  I2CMessage[3] = data2;
  I2CMessage[4] = data3;

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 4);
	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
}

//---------------------------------------------------------------
void _MMX_WriteData5(tSensors port, byte addr, byte data1, byte data2, byte data3, byte data4, byte data5)
{
  byte I2CMessage[7];

  I2CMessage[0] = 6 ;
  I2CMessage[1] = addr ;
  I2CMessage[2] = data1;
  I2CMessage[3] = data2;
  I2CMessage[4] = data3;
  I2CMessage[5] = data4 ;
  I2CMessage[6] = data5 ;

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 6);
	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
}

//---------------------------------------------------------------
void _MMX_WriteByte(tSensors port, byte addr, byte location, byte data)
{
  byte I2CMessage[3];

  I2CMessage[0] = 2 ;
  I2CMessage[1] = addr ;
  I2CMessage[2] = data;

	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);
  sendI2CMsg(port, & I2CMessage[0], 2);
	while (nI2CStatus[port] == STAT_COMM_PENDING) wait1Msec(1);

}

#endif
/////////////////////////////////////////////////////////////////////////////////////////
// That's all, folks !
/////////////////////////////////////////////////////////////////////////////////////////
