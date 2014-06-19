#pragma config(Sensor, in1,    autoSelect,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  encoderR,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderL,       sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  touchTop,       sensorTouch)
#pragma config(Sensor, dgtl6,  touchBottom,    sensorTouch)
#pragma config(Sensor, dgtl7,  touchAuto,      sensorTouch)
#pragma config(Sensor, dgtl11, pIntakeU,       sensorDigitalOut)
#pragma config(Sensor, dgtl12, pIntakeD,       sensorDigitalOut)
#pragma config(Motor,  port1,           intakeL,       tmotorVex393, openLoop)
#pragma config(Motor,  port2,           RU,            tmotorVex393, openLoop)
#pragma config(Motor,  port3,           armRU,         tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RD,            tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armRD,         tmotorVex393, openLoop)
#pragma config(Motor,  port6,           armLD,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           LD,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           armLU,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           LU,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          intakeR,       tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Functions\ArmFunctions.c"
#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Functions\ChassisFunctions.c"



task main()
{
	while(true){
		controlArm();
	  controlDriveTest();
	  controlIntake();
	}
}