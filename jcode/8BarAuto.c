#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  encoderLeft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderRight,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  encoderArmLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  encoderArmRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  touchTop,       sensorTouch)
#pragma config(Sensor, dgtl10, touchBottom,    sensorTouch)
#pragma config(Motor,  port1,           intakeL,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           FR,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           armLL,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           BL,            tmotorVex393, openLoop)
#pragma config(Motor,  port5,           BR,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           armLU,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           armRU,         tmotorVex393, openLoop)
#pragma config(Motor,  port8,           FL,            tmotorVex393, openLoop)
#pragma config(Motor,  port9,           armRL,         tmotorVex393, openLoop)
#pragma config(Motor,  port10,          intakeR,       tmotorVex393, openLoop)
#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
//!!!!!!!! status port on power expander goes analog2(in8) on the cortex!!!!!!!!!!//
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "8BarFunctions.c"
#include "ChassisFunctions.c"
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
	int gyroVal;

//cutOff = a motor power beneath which no power will be sent to the motor
task gyroLCD()
{
	while(true)
	{
		clearLCDLine(0);
	displayLCDNumber(0, 0, SensorValue[gyro]);
	wait1Msec(100);
	}
}

void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}

task main()
{
	resetGyro();
	//StartTask(gyroLCD);
	//waitForPress();
	////forward to trough bonus and pick up
	//startIntake(intakeSpeed, intakeCutOff);
	//forward(55, (int)(SensorValue[gyro]/10), driveSpeed, driveCutOff);
	//wait1Msec(1000);
	//stopIntake();
	////back and lift arm
	//forward(-35, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	//arm(trough, armPower, armCutOff);
	////forward and dump
	//forward(17, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	//startIntake(-intakeSpeed, intakeCutOff);
	//wait1Msec(1000);
	//stopIntake();
	////back to base
	//forward(-20, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	//StartTask(taskLowerArm);
	//forward(-30, SensorValue[gyro]/10, driveSpeed, driveCutOff);
	//waitForPress();
	////5 stack and middle bonus
	forward(40, 0, driveSpeed, driveCutOff);
	rotate(90, driveCutOff);
	//startIntake(intakeSpeed, intakeCutOff);
	//forward(40, 90, driveSpeed, driveCutOff);
	//wait1Msec(500);
	//stopIntake();

	////get in position and dump
	//forward(-20, 90, driveSpeed, driveCutOff);
	//StartTask(troughArm);
	//rotate(0, driveCutOff);
	//forward(20, 0, driveSpeed, driveCutOff);
	//startIntake(-intakeSpeed, intakeCutOff);
	//wait1Msec(1000);
	//stopIntake();

	////get in position for other 5 stack
	//forward(-20, 0, driveSpeed, driveCutOff);
	//StartTask(taskLowerArm);
	//rotate(90, driveCutOff);

	////get other 5 stack
	//startIntake(intakeSpeed, intakeCutOff);
	//forward(45, 90, driveSpeed, driveCutOff);
	//wait1Msec(1000);
	//stopIntake();

	////get in position for bonus
	//forward(12, 90, driveSpeed, driveCutOff);
	//rotate(0, driveCutOff);

	////get bonus
	//startIntake(intakeSpeed, intakeCutOff);
	//forward(30, 0, driveSpeed, driveCutOff);
	//stopIntake();

	////get in position to dump
	//forward(-35, 0, driveSpeed, driveCutOff);
	//arm(trough, armPower, armCutOff);
	//forward(25, 0, driveSpeed, driveCutOff);

	////dump and return
	//startIntake(-intakeSpeed, intakeCutOff);
	//wait1Msec(1000);
	//stopIntake();
	//forward(-20, 0, driveSpeed, driveCutOff);
	//StartTask(taskLowerArm);
	//forward(-30, 0, driveSpeed, driveCutOff);

}