#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, in2,    accelX,         sensorGyro)
#pragma config(Sensor, in3,    accelY,         sensorAnalog)
#pragma config(Sensor, in4,    accelZ,         sensorAnalog)
#pragma config(Sensor, in5,    gyro,           sensorAnalog)
#pragma config(Sensor, in6,    pwrExp,         sensorPotentiometer)
#pragma config(Sensor, in7,    autoPosition,   sensorPotentiometer)
#pragma config(Sensor, in8,    autoPlan,       sensorPotentiometer)
#pragma config(Sensor, dgtl1,  encoderR,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderL,       sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  touchBottom,    sensorTouch)
#pragma config(Sensor, dgtl6,  touchTop,       sensorTouch)
#pragma config(Sensor, dgtl7,  touchAuto,      sensorTouch)
#pragma config(Sensor, dgtl11, pIntakeU,       sensorDigitalOut)
#pragma config(Sensor, dgtl12, pIntakeD,       sensorDigitalOut)
#pragma config(Motor,  port1,           intakeL,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           armRD,         tmotorVex393, openLoop)
#pragma config(Motor,  port3,           armRU,         tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RD,            tmotorVex393, openLoop)
#pragma config(Motor,  port5,           RU,            tmotorVex393, openLoop)
#pragma config(Motor,  port6,           LU,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           LD,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           armLU,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           armLD,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          intakeR,       tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\DriverTryout.c"

#define Vref 5.0
#define Sensitivity 0.3
#define tipAngle 15

float gAccel(tSensors accel){
	return ((SensorValue[accel]) * Vref / 4095 - Vref / 2) / Sensitivity;
}

float gAccelX;
float gAccelY;
float gAccelZ;

float forceG;

float angleX;
float angleY;
float angleZ;

task main()
{
	SensorType[in2] = sensorNone;
	SensorType[in3] = sensorNone;
	SensorType[in4] = sensorNone;
	wait1Msec(1000);

	SensorType[in2] = sensorAnalog;
	SensorType[in3] = sensorAnalog;
	SensorType[in4] = sensorAnalog;
	wait1Msec(1500);

	while(true){
		gAccelX = gAccel(accelX);
		gAccelY = gAccel(accelY);
		gAccelZ = gAccel(accelZ);

		forceG = sqrt(pow(gAccelX, 2) + pow(gAccelY, 2) + pow(gAccelZ, 2));

		angleX = acos(gAccelX/forceG) * 180 / PI;
		angleY = acos(gAccelY/forceG) * 180 / PI;
		angleZ = acos(gAccelZ/forceG) * 180 / PI;

	}
}