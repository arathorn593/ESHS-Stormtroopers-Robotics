#pragma config(Sensor, in1,    potent1,        sensorPotentiometer)
#pragma config(Sensor, in6,    lineLeft,       sensorLineFollower)
#pragma config(Sensor, in7,    lineMiddle,     sensorLineFollower)
#pragma config(Sensor, in8,    lineRight,      sensorLineFollower)
#pragma config(Sensor, dgtl1,  touch,          sensorTouch)
#pragma config(Sensor, dgtl2,  sonar,          sensorSONAR_inch)
#pragma config(Sensor, dgtl4,  encoderRight,   sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  encoderLeft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  beltTouch,      sensorTouch)
#pragma config(Sensor, dgtl9,  encoderArm,     sensorQuadEncoder)
#pragma config(Sensor, dgtl11, team,           sensorTouch)
#pragma config(Sensor, dgtl12, jumper,         sensorTouch)
#pragma config(Motor,  port1,           beltRight2,    tmotorNormal, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           liftRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port8,           beltRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port9,           beltLeft,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          beltLeft2,     tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(VEX)

void MoveForward(int SpeedValue)
{
	motor[frontLeft] = SpeedValue;
 	motor[frontRight] = SpeedValue;
	motor[backLeft] = SpeedValue;
  motor[backRight] = SpeedValue;
}

void MoveBackward(int SpeedValue)
{
	motor[frontLeft] = -SpeedValue;
 	motor[frontRight] = -SpeedValue;
	motor[backLeft] = -SpeedValue;
  motor[backRight] = -SpeedValue;
}

void PointRight(int SpeedValue)
{
	motor[frontLeft] = SpeedValue;
 	motor[frontRight] = -SpeedValue;
	motor[backLeft] = SpeedValue;
  motor[backRight] = -SpeedValue;
}

void PointLeft(int SpeedValue)
{
	motor[frontLeft] = -SpeedValue;
 	motor[frontRight] = SpeedValue;
	motor[backLeft] = -SpeedValue;
  motor[backRight] = SpeedValue;
}

void LiftArm(int SpeedValue)
{
  motor[liftLeft] = SpeedValue;
  motor[liftRight] = SpeedValue;

}

void LowerArm(int SpeedValue)
{
  motor[liftLeft] = -SpeedValue;
  motor[liftRight] = -SpeedValue;

}

void StopArm()
{
  motor[liftLeft] = 0;
  motor[liftRight] = 0;
}

void LowerArmToGround()
{
while (sensor? >0)
	{
	LowerArm(127);
	}
}

void Stop()
{
	motor[frontLeft] = 0;
 	motor[frontRight] = 0;
	motor[backLeft] = 0;
  motor[backRight] = 0;
}

void GoDistance(int ModeValue, int Distance)
{
  if (ModeValue==0)
    {
      int Distance=encodervalue+DistanceValue
      while (encoderLeft<DistanceValue)
        {
        MoveForward(127);
        }
    }
  if (ModeValue==1)
    {
      int Distance=encodervalue-DistanceValue
      while (encoderLeft>DistanceValue)
        {
        MoveBackward(127);
        }
    }
}

task main
{
while(true)
{
while the user touches the button
{
	MoveForward(127);
}
  Stop();
}
