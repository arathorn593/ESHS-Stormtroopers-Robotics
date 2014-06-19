#pragma config(Sensor, in1,    ArmPotent,           sensorPotentiometer)
#pragma config(Sensor, dgtl2,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  LeftEncoder,         sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  sonar,               sensorSONAR_mm)
#pragma config(Motor,  port1,           frontCenter,   tmotorNormal, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           backCenter,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           liftRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port8,           liftLeft,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           beltRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port10,          beltLeft,      tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	wait1Msec(2000);						// Robot waits for 2000 milliseconds before executing program

	// Move forward at semi full power for 5 seconds
	motor[rightMotor] = 75;		  // Motor on port2 is run at semi full (75) power forward
	motor[leftMotor]  = 75;		  // Motor on port3 is run at semi full (75) power forward
	wait1Msec(5000);			        // Robot runs previous code for 3000 milliseconds before moving on
}												        // Program ends, and the robot stops