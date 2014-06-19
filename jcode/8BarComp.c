#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    sidePot,        sensorPotentiometer)
#pragma config(Sensor, in3,    choicePot,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  encoderLeft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderRight,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  encoderArmLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  encoderArmRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  touchTop,       sensorTouch)
#pragma config(Sensor, dgtl10, touchBottom,    sensorTouch)
#pragma config(Sensor, dgtl11, jumper,         sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intakeL,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           FR,            tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port3,           armLL,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           BL,            tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port5,           BR,            tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port6,           armLU,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           armRU,         tmotorVex393, openLoop)
#pragma config(Motor,  port8,           FL,            tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port9,           armRL,         tmotorVex393, openLoop)
#pragma config(Motor,  port10,          intakeR,       tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!!!!!!! status port on power expander goes analog2(in8) on the cortex!!!!!!!!!!//
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "8BarFunctions.c"
#include "ChassisFunctions.c"
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

//cutOff = a motor power beneath which no power will be sent to the motor
int driveCutOff = 30;
int armCutOff = 0;
int intakeCutOff = 0;

int forwardPower = 127;
int intakePower = -127;
int armPower = 127;


const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

int driveSpeed = 127;
	int intakeSpeed = -127;
	int intakeTime = 2000;
	int troughTime = 2000;
	int bonusTime = 2300;
	int stackTime = 1250;

	int trough = 75;


//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}

task gyroLCD()
{
	while(true)
	{
		clearLCDLine(0);
	displayLCDNumber(0, 0, SensorValue[gyro]);
	wait1Msec(100);
	}
}

task autonomous()
{
	if(SensorValue[jumper] == 1)
	{
	lowerArm();

	////shakeIntake(1);
	////go dump preloads
	//while(SensorValue[encoderArmLeft] <75)
	//{
	//	setArm(127, 0);
	//}

	//stopArm();
	//waitForPress();
	//setDrive(driveSpeed, 0);
	//wait1Msec(troughTime);
	//stopDrive();
	//startIntake(-1*intakeSpeed, 0);
	//wait1Msec(intakeTime);
	//stopIntake();
	//setDrive(-1*driveSpeed, 0);
	//wait1Msec(troughTime);
	//stopDrive();
	//lowerArm();

	////pick up stack
	////waitForPress();
	////setDrive(driveSpeed, 0);
	////startIntake(intakeSpeed, 0);
	////wait1Msec(stackTime);
	////stopDrive();
	////wait1Msec(intakeTime);
	////stopIntake();
	////setDrive(-1*driveSpeed, 0);
	////wait1Msec(stackTime);
	////stopDrive();

	////get bonus
	//waitForPress();
	//setDrive(driveSpeed, 0);
	//startIntake(intakeSpeed, 0);
	//wait1Msec(bonusTime);
	//stopDrive();
	//wait1Msec(intakeTime);
	//stopIntake();
	//setDrive(-1*driveSpeed, 0);
	//wait1Msec(bonusTime);
	//stopDrive();
	//while(SensorValue[encoderArmLeft] <75)
	//{
	//	setArm(127, 0);
	//}
	//stopArm();

	////go dump bonus
	//waitForPress();
	//setDrive(driveSpeed, 0);
	//wait1Msec(troughTime);
	//stopDrive();
	//startIntake(-1*intakeSpeed, 0);
	//wait1Msec(intakeTime);
	//stopIntake();
	//setDrive(-1*driveSpeed, 0);
	//wait1Msec(troughTime);
	//stopDrive();
	//lowerArm();

	resetGyro();
	StartTask(gyroLCD);
	waitForPress();
	//forward to trough bonus and pick up
	startIntake(intakeSpeed, intakeCutOff);
	forward(55, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	wait1Msec(1000);
	stopIntake();
	//back and lift arm
	forward(-22, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	arm(trough, armPower, armCutOff);
	//forward and dump
	forward(12, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	startIntake(-intakeSpeed, intakeCutOff);
	wait1Msec(1000);
	stopIntake();
	//back to base
	forward(-20, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	StartTask(taskLowerArm);
	forward(-30, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	waitForPress();
	//5 stack
	startIntake(intakeSpeed, intakeCutOff);
	forward(42, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
			wait1Msec(500);
	stopIntake();

			forward(-20, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	arm(trough, armPower, armCutOff);

	forward(25, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	//dump
	startIntake(-intakeSpeed, intakeCutOff);
	wait1Msec(1000);
	stopIntake();
//back to base
	forward(-20, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	StartTask(taskLowerArm);
	forward(-30, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	waitForPress();
	//middle bonus and transfer
		startIntake(intakeSpeed, intakeCutOff);
	forward(50, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	wait1Msec(250);
	stopIntake();
	setLeftDrive(127, 0);
	setRightDrive(-127, 0);
	wait1Msec(650);
	stopDrive();
		setDrive(127, 0);
		wait1Msec(2250);
		stopDrive();
	waitForPress();

		//5 stack
	waitForPress();
	startIntake(intakeSpeed, intakeCutOff);
	forward(42, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	wait1Msec(500);
	forward(-12, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	stopIntake();
	forward(-30, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	waitForPress();
	if(nLCDButtons == 2)
	{
			//forward to trough bonus and pick up
	startIntake(intakeSpeed, intakeCutOff);
	forward(55, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	wait1Msec(1000);
	stopIntake();
	//back and lift arm
	forward(-22, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	arm(trough, armPower, armCutOff);
	//forward and dump
	forward(12, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	startIntake(-intakeSpeed, intakeCutOff);
	wait1Msec(2000);
	stopIntake();
	//back to base
	forward(-20, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	StartTask(taskLowerArm);
	forward(-30, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	}
	else if((nLCDButtons == 1)||(nLCDButtons == 4))
	{
		//forward and dump
	StartTask(troughArm);
	forward(47, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	startIntake(-intakeSpeed, intakeCutOff);
	wait1Msec(2000);
	stopIntake();
	//back to base
	forward(-20, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	StartTask(taskLowerArm);
	forward(-30, SensorValue[gyro]/10, driveSpeed, driveCutOff);
}


	}
	else
	{
		const int RIGHT = 1;
		const int RIGHT_NO_PID = 2;
		const int LEFT_NO_PID = 3;
		const int LEFT = 4;

		const int FIVE_STACK = 1;
		const int CENTER_GOLD = 2;
		const int TROUGH_GOLD = 3;

  	int side_1_2 = 1024;
  	int side_2_3 = 2048;
  	int side_3_4 = 3071;

  	int choice_1_2 = 1365;
  	int choice_2_3 = 2730;

  	int sidePotVal = SensorValue[sidePot];
  	int choicePotVal = SensorValue[choicePot];
  	int sideVal = 0;
  	int choiceVal = 0;

  	if(sidePotVal <= side_1_2)
  	{
  		sideVal = 1;
  	}
  	else if(sidePotVal <= side_2_3)
  	{
  		sideVal = 2;
  	}
  	else if(sidePotVal <= side_3_4)
  	{
  		sideVal = 3;
  	}
  	else
  	{
  		sideVal = 4;
  	}

  	if(choicePotVal <= choice_1_2)
  	{
  		choiceVal = 1;
  	}
  	else if(choicePotVal <= choice_2_3)
  	{
  		choiceVal = 2;
  	}
  	else
  	{
  		choiceVal = 3;
  	}

  	if(choiceVal == FIVE_STACK)
  	{
  		intakeTime = 2000;
			troughTime = 2000;
			stackTime = 2000;
  		if((sideVal == LEFT)||(sideVal == RIGHT))
  		{
  			clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "5-stack");
				//5 stack
				resetGyro();
				displayLCDCenteredString(0, "ready");
				waitForPress();
				startIntake(intakeSpeed, intakeCutOff);
				forward(42, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
				wait1Msec(500);
				stopIntake();
				StartTask(troughArm);
				forward(-42, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
				//dump
				waitForPress();
				forward(43, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
				startIntake(-intakeSpeed, intakeCutOff);
				wait1Msec(1000);
				stopIntake();
				//back to base
				forward(-25, SensorValue[gyro]/10, driveSpeed, driveCutOff);
				StartTask(taskLowerArm);
  		}
  		if((sideVal == LEFT_NO_PID)||(sideVal == RIGHT_NO_PID))
  		{
  			clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "5-stack");
				displayLCDCenteredString(1, "NO PID");

				waitForPress();
				startIntake(intakeSpeed, 0);
				setDrive(driveSpeed, 0);
				wait1Msec(stackTime);
				stopDrive();

				wait1Msec(intakeTime);
				stopIntake();
				setDrive(-1*driveSpeed, 0);
				wait1Msec(stackTime);
				stopDrive();
				while(SensorValue[encoderArmLeft] <75)
				{
					setArm(127, 0);
				}
				stopArm();

				//go dump bonus
				waitForPress();
				setDrive(driveSpeed, 0);
				wait1Msec(troughTime);
				stopDrive();
				startIntake(-1*intakeSpeed, 0);
				wait1Msec(intakeTime);
				stopIntake();
				setDrive(-1*driveSpeed, 0);
				wait1Msec(troughTime);
				stopDrive();
				lowerArm();
  		}
  	}
  	else if(choiceVal == TROUGH_GOLD)
  	{
  		intakeTime = 1000;
  		int troughGold = 2500;
  		int backUp = 1500;
  		int toTrough = 1000;
  		if(sideVal == LEFT)
  		{
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "trogold LEFTONLY");
				resetGyro();
				displayLCDCenteredString(0, "ready");
				waitForPress();
				//forward to trough bonus and pick up
				startIntake(intakeSpeed, intakeCutOff);
				forward(55, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
				wait1Msec(1000);
				stopIntake();
				//back and lift arm
				forward(-22, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
				arm(trough, armPower, armCutOff);
				//forward and dump
				forward(12, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
				startIntake(-intakeSpeed, intakeCutOff);
				wait1Msec(1000);
				stopIntake();
				//back to base
				forward(-25, SensorValue[gyro]/10, driveSpeed, driveCutOff);
				StartTask(taskLowerArm);

  			wait1Msec(1000);
  		}
  		if(sideVal == LEFT_NO_PID)
  		{
  			clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "troughGold left");
				displayLCDCenteredString(1, "NO PID");

				waitForPress();
				//forward to trough bonus and pick up
				startIntake(intakeSpeed, intakeCutOff);
				setDrive(driveSpeed, 0);
				wait1Msec(troughGold);
				stopDrive();
				wait1Msec(intakeTime);
				stopIntake();
				//back and lift arm
				setDrive(-driveSpeed, 0);
				wait1Msec(backUp);
				stopDrive();
				arm(trough, armPower, armCutOff);
				//forward and dump
				setDrive(driveSpeed, 0);
				wait1Msec(toTrough);
				stopDrive();
				startIntake(-intakeSpeed, intakeCutOff);
				wait1Msec(intakeTime);
				stopIntake();
				//back to base
				setDrive(-driveSpeed, 0);
				wait1Msec(backUp);
				stopDrive();
				StartTask(taskLowerArm);

  			wait1Msec(1000);
  		}
  		if(sideVal == RIGHT_NO_PID)
  		{
  			clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "troGold stay");
				displayLCDCenteredString(1, "NO PID");

				waitForPress();
				//forward to trough bonus and pick up
				startIntake(intakeSpeed, intakeCutOff);
				setDrive(driveSpeed, 0);
				wait1Msec(troughGold);
				stopDrive();
				wait1Msec(intakeTime);
				stopIntake();
				setDrive(-driveSpeed, 0);
				wait1Msec(700);
				stopDrive();
  		}
  		if(sideVal == RIGHT)
  		{
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "trougold NO DUMP");
				//forward to trough bonus and pick up
				resetGyro();
				displayLCDCenteredString(0, "ready");
				waitForPress();
				startIntake(intakeSpeed, intakeCutOff);
				forward(55, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
				wait1Msec(intakeTime);
				stopIntake();
				forward(-20, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);

  		}
  	}
  	else if(choiceVal == CENTER_GOLD)
  	{
  		intakeTime = 2000;
			troughTime = 2000;
			bonusTime = 2300;
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0, "center gold");
				lowerArm();
				//shakeIntake(1);
				//get bonus
				waitForPress();
				setDrive(driveSpeed, 0);
				wait1Msec(bonusTime);
				stopDrive();
				startIntake(intakeSpeed, 0);
				wait1Msec(intakeTime);
				stopIntake();
				setDrive(-1*driveSpeed, 0);
				wait1Msec(bonusTime);
				stopDrive();
				while(SensorValue[encoderArmLeft] <75)
				{
					setArm(127, 0);
				}
				stopArm();

				//go dump bonus
				waitForPress();
				setDrive(driveSpeed, 0);
				wait1Msec(troughTime);
				stopDrive();
				startIntake(-1*intakeSpeed, 0);
				wait1Msec(intakeTime);
				stopIntake();
				setDrive(-1*driveSpeed, 0);
				wait1Msec(troughTime);
				stopDrive();
				lowerArm();
  	}
	}

}




/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

//////////////////mechanum drive//////////////////////////////////////
//bottomThresh = a value beneath which a channel will not have any input
int bottomThresh = 0;
//topThresh = a value beneath which a channel will input a fraction of its value
int topThresh = 100;
//lowGear = a value by which a channel will be divided when below topThresh
int lowGear = 2;

//////////////////////////arm/////////////////////////////////
//trough = the height of the trough as specified by the encoders
//highGoal = the height of the trough as specified by the encoders
int highGoal = 0;
//armSpeed = the base value for the arm
int armSpeed = 127;

//////////////////////////intake//////////////////////////////
//inSpeed = speed of intaking
int inSpeed = 127;
//outSpeed = speed of depositing
int outSpeed = 127;


task usercontrol()
{
	// User control code here, inside the loop
	int newControlVal = 0;
	int oldControlVal = 0;
	while(true)
	{
		newControlVal = vexRT[Btn7D];
		if(newControlVal == 1 && oldControlVal == 0)
		{
			controllerState = 1- controllerState;
		}
		oldControlVal = newControlVal;
		//runs the joystick control of the chassis
		MechanumDrive(bottomThresh, topThresh, lowGear, driveCutOff);

		//runs arm control with presets and arm adjust on the LCD buttons
		armControl(trough, highGoal, armSpeed, armCutOff);

		//runs intake with control
		intake(inSpeed, outSpeed, intakeCutOff);

		//if the center button is pressed
		if(nLCDButtons == 2)
		{
			if(!batteryView)
			{
				//StartTask(battery, 2);
				batteryView = true;
			}
		}

		//universal framerate for PID
		wait1Msec(50); //*******!!!!!!!!if you change this make sure you look at the accel function-
		//need to change how much change trips the accel fuction
		//also the amount of change per loop
	}
}
//THAT'S WHAT'S UP!!!!!!!!!!!!!!