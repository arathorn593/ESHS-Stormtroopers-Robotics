#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  encoderLeft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderRight,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  encoderArmLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  encoderArmRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  touchTop,       sensorTouch)
#pragma config(Sensor, dgtl10, touchBottom,    sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intakeL,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           FR,            tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port3,           armLL,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           BL,            tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port5,           BR,            tmotorVex393HighSpeed, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port6,           armLU,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           armRU,         tmotorVex393, openLoop)
#pragma config(Motor,  port8,           FL,            tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port9,           armRL,         tmotorVex393, openLoop)
#pragma config(Motor,  port10,          intakeR,       tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!!!!!!! status port on power expander goes analog2(in8) on the cortex!!!!!!!!!!//
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "MiscFunctions.c"

float ZVal;		//stores channel controlling forward/back movement
  float XVal;		//stores channel controlling left/right movement
  float RotateVal;//stores channel controlling rotational movement

  //these store the value that controlls how much each direction is "wieghted"
  //in the final setup
  float XWeight;
  float ZWeight;
  float RotateWeight;

  //these hold the value of each wheel's power so it can be manipulated
  int FRPower;
  int FLPower;
  int BLPower;
  int BRPower;

void MechanumDrive(int bottomThresh, int topThresh, int lowGear, int cutOff)
{
	//these variables allow you to change which channels conrtol different movements
  XVal = vexRT[Ch4];	//left/right
  ZVal = vexRT[Ch3];	//forward/back
  RotateVal = vexRT[Ch1];	//rotational

  //these manipulate the channel values going into the main function
  //*see top and bottom thresh above
  if(abs(ZVal)< bottomThresh)
  {
    ZVal = 0;
  }
  else if(abs(ZVal) < topThresh)
  {
    ZVal = ZVal/lowGear;
  }

  if(abs(XVal)< bottomThresh)
  {
    XVal = 0;
  }
  else if(abs(XVal) < topThresh)
  {
    XVal = XVal/lowGear;
  }

  if(abs(RotateVal)< bottomThresh)
  {
    RotateVal = 0;
  }
  else if(abs(RotateVal) < topThresh)
  {
    RotateVal = RotateVal/lowGear;
  }

	//this weights each direction by finding what percentage of
  //the total movement they make up
  XWeight = abs(XVal)/(abs(RotateVal) + abs(ZVal) + abs(XVal));
  ZWeight = abs(ZVal)/(abs(RotateVal) + abs(ZVal) + abs(XVal));
  RotateWeight = abs(RotateVal)/(abs(RotateVal) + abs(ZVal) + abs(XVal));

  //these calculate the power on each motor by adding each scenario(Z, X, rotate)
  //each scenario is found by multiplying the channel value by the channel weight
  // by a -1 if those motors are reversed in that scenario.
  FRPower = ceil(XVal*XWeight + ZVal*ZWeight + -1 * RotateVal * RotateWeight);
  FLPower = ceil(-1*XVal*XWeight + ZVal*ZWeight + 0);
  BLPower = ceil(XVal*XWeight + ZVal*ZWeight + RotateVal * RotateWeight);
  BRPower = ceil(-1*XVal*XWeight + ZVal*ZWeight + 0);

  //Set powers to motors
	setFR(FRPower, cutOff);
	setFL(FLPower, cutOff);
	setBL(BLPower, cutOff);
	setBR(BRPower, cutOff);
}

task main()
{
	while(true)
	{
		mechanumDrive(0,0,0,0);
	}

}
