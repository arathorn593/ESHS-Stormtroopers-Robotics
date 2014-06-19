#pragma config(Sensor, dgtl1,  encoderR,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderL,       sensorQuadEncoder)
#pragma config(Sensor, dgtl11, pIntakeU,       sensorDigitalOut)
#pragma config(Sensor, dgtl12, pIntakeD,       sensorDigitalOut)
#pragma config(Motor,  port1,           intakeL,       tmotorVex393, openLoop)
#pragma config(Motor,  port2,           RU,            tmotorVex393, openLoop)
#pragma config(Motor,  port3,           armRU,         tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RD,            tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armRD,         tmotorVex393, openLoop)
#pragma config(Motor,  port6,           armLD,         tmotorVex393, openLoop)
#pragma config(Motor,  port7,           LD,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           armLU,         tmotorVex393, openLoop)
#pragma config(Motor,  port9,           LU,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          intakeR,       tmotorVex393, openLoop, reversed)

#include "Functions/MotorFunctions.c"

int val = 0;
int oldVal = 0;
int state = 0; //0 = main; 1 = alternate
task main()
{
	while(true){
		setDrive(vexRT[Ch3], vexRT[Ch2]);
	}
}
