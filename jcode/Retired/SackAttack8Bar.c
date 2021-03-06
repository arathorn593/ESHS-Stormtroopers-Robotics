#pragma config(Sensor, dgtl1,  Ttop,           sensorTouch)
#pragma config(Sensor, dgtl2,  Tbottom,        sensorTouch)
#pragma config(Motor,  port1,           intakeLeft,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           RightBack,     tmotorVex393, openLoop)
#pragma config(Motor,  port3,           LiftLeftTop,   tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RightFront,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           LeftFront,     tmotorVex393, openLoop)
#pragma config(Motor,  port6,           LiftLeftBottom, tmotorVex393, openLoop)
#pragma config(Motor,  port7,           LiftRightBottom, tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           LeftBack,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           LiftRightTop,  tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          intakeRight,   tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  motor[LeftBack]=-127;
  motor[LeftFront]=-127;
  motor[RightBack]=-127;
  motor[RightFront]=-127;

  wait1Msec(1000);

  motor[LeftBack]=127;
  motor[LeftFront]=127;
  motor[RightBack]=127;
  motor[RightFront]=127;
  wait1Msec(100);
  motor[LeftBack]=-127;
  motor[LeftFront]=-127;
  motor[RightBack]=-127;
  motor[RightFront]=-127;
wait1Msec(100);
  motor[LeftBack]=127;
  motor[LeftFront]=127;
  motor[RightBack]=127;
  motor[RightFront]=127;
  wait1Msec(500);

  motor[LeftBack]=0;
  motor[LeftFront]=0;
  motor[RightBack]=0;
  motor[RightFront]=0;

  wait1Msec(100);

  motor[intakeLeft] = 127;
  motor[intakeRight]= 127;

  wait1Msec(3000);

  motor[intakeLeft] = 0;
  motor[intakeRight]= 0;

  motor[LeftBack]=-80;
  motor[LeftFront]=-80;
  motor[RightBack]=-80;
  motor[RightFront]=-80;

  wait1Msec(1000);

  motor[LeftBack] = -80;
  motor[LeftFront] = -80;
  motor[RightBack] = 80;
  motor[RightFront] = 80;

  wait1Msec(700);

   motor[LeftBack]=0;
  motor[LeftFront]=0;
  motor[RightBack]=0;
  motor[RightFront]=0;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  if(abs(vexRT[Ch2]) > 50)
	  {
	    if(abs(vexRT[Ch2]) <120)
	    {
	      motor[RightBack] = vexRT[Ch2]/2;
	      motor[RightFront] = vexRT[Ch2]/2;
	    }
	    else
	    {
	      motor[RightBack] = vexRT[Ch2];
	      motor[RightFront] = vexRT[Ch2];
	    }
	   }
	   else
	   {
	      motor[RightBack] = 0;
	      motor[RightFront] = 0;
	   }


	  if(abs(vexRT[Ch3]) > 50)
	  {
	    if(abs(vexRT[Ch3]) <115)
	    {
	      motor[LeftBack] = vexRT[Ch3]/2;
	      motor[LeftFront] = vexRT[Ch3]/2;
	    }
	    else
	    {
	      motor[LeftBack] = vexRT[Ch3];
	      motor[LeftFront] = vexRT[Ch3];
	    }
	   }
	   else
	   {
	      motor[LeftBack] = 0;
	      motor[LeftFront] = 0;
	   }


	  if(vexRT(Btn5U) == 1)
	  {
	    motor[intakeLeft] = 127;
	    motor[intakeRight] = 127;
	  }
	  else if(vexRT(Btn5D) == 1)
	  {
	    motor[intakeLeft] = -127;
	    motor[intakeRight] = -127;
	  }
	  else
	  {
	    motor[intakeLeft] = 0;
	    motor[intakeRight] = 0;
	  }

	  if(vexRT(Btn8D)==1)
	  {
	  if(vexRT(Btn6U) == 1)
	  {
	    motor[LiftLeftBottom] = 80;
	    motor[LiftLeftTop] = 80;
	    motor[LiftRightBottom] = 80;
	    motor[LiftRightTop] = 80;
	  }
	  else if(vexRT(Btn6D) == 1)
	  {
	    if(SensorValue[Tbottom] == 1)
	    {
	      motor[LiftLeftBottom] = 0;
	      motor[LiftLeftTop] = 0;
	      motor[LiftRightBottom] = 0;
	      motor[LiftRightTop] = 0;
	    }
	    else
	    {
	      motor[LiftLeftBottom] = -80;
	      motor[LiftLeftTop] = -80;
	      motor[LiftRightBottom] = -80;
	      motor[LiftRightTop] = -80;
	    }

	  }
	  else
	  {
	    motor[LiftLeftBottom] = 0;
	    motor[LiftLeftTop] = 0;
	    motor[LiftRightBottom] = 0;
	    motor[LiftRightTop] = 0;
	  }
	}
	else
	{
	  	  if(vexRT(Btn6U) == 1)
	  {
	    motor[LiftLeftBottom] = 127;
	    motor[LiftLeftTop] = 127;
	    motor[LiftRightBottom] = 127;
	    motor[LiftRightTop] = 127;
	  }
	  else if(vexRT(Btn6D) == 1)
	  {
	    if(SensorValue[Tbottom] == 1)
	    {
	      motor[LiftLeftBottom] = 0;
	      motor[LiftLeftTop] = 0;
	      motor[LiftRightBottom] = 0;
	      motor[LiftRightTop] = 0;
	    }
	    else
	    {
	      motor[LiftLeftBottom] = -127;
	      motor[LiftLeftTop] = -127;
	      motor[LiftRightBottom] = -127;
	      motor[LiftRightTop] = -127;
	    }

	  }
	  else
	  {
	    motor[LiftLeftBottom] = 0;
	    motor[LiftLeftTop] = 0;
	    motor[LiftRightBottom] = 0;
	    motor[LiftRightTop] = 0;
	  }
	}
	}
}
