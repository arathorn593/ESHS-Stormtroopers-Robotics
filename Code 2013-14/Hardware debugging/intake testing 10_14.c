#pragma config(Sensor, dgtl1,  encoderR,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderL,       sensorQuadEncoder)
#pragma config(Motor,  port1,           intakeL,       tmotorVex393, openLoop)
#pragma config(Motor,  port2,           RU,            tmotorVex393, openLoop)
#pragma config(Motor,  port3,           liftRU,        tmotorVex393, openLoop)
#pragma config(Motor,  port4,           RD,            tmotorVex393, openLoop)
#pragma config(Motor,  port5,           liftRD,        tmotorVex393, openLoop)
#pragma config(Motor,  port6,           liftLD,        tmotorVex393, openLoop)
#pragma config(Motor,  port7,           LD,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           liftLU,        tmotorVex393, openLoop)
#pragma config(Motor,  port9,           LU,            tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          intakeR,       tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
task main()
{

	while(true){
		motor[intakeL] = 127;
		motor[intakeR] = 127;
	}
}