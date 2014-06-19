

#include "MiscFunctions.c"


float ZVal;		//stores channel controlling forward/back movement
float XVal;		//stores channel controlling left/right movement
float RotateVal;//stores channel controlling rotational movement

//the number of miliseconds the robot must not be sending power to the motors for the robot to end the rotate function
int rotateWait = 200;

//this is the constant that is used to convert inches to travel into rotations for forward/backward functions
const float forConversion = 13;
//this is the same but for sideways
const float sideConversion = 26;
/////////////////////////////////////////////autonomous functions////////////////////////////////////////////////////////////////////////
void setDrive(int magnitude, int cutOff)
{
	setRightDrive(magnitude, cutOff);
	setLeftDrive(magnitude, cutOff);
}

//rotates(point turn) the robot to reach a certain degree
void rotate(int goal, int cutOff)
{

	//more variables for later
	float error = 1800;
	proportion = 0;
	float Kp = 5;

	//prepares goal for use with gyro since gyro measures 10 increments for each degree
	goal *= 10;

	//carrier for the sensor value
	int gyroValue;

	//buffer in gyro units
	int buffer = 175;
	//main loop. will continue adjusting until set at right angle
	while(!((error<buffer) && (error> -buffer)))
	{
		//preparing error...mostly magic
		gyroValue = SensorValue[gyro];
		gyroValue = adjustGyro(gyroValue);
		//error = centerGyro(goal, gyroValue);
		error = goal - gyroValue;

		if(gyroValue < goal)
		{
			setRightDrive(-127, cutOff);
			setLeftDrive(127, cutOff);
		}
		else if(gyroValue >goal)
		{
			setRightDrive(127, cutOff);
			setLeftDrive(-127, cutOff);
		}
		else
		{
			stopDrive();
		}
/*
		proportion = 127//(int)(abs(error) * Kp);
		if(error > 0)
		{
		//when error is positive robot needs to rotate counter clockwise and if it is negative it is reversed
		setRightDrive(-proportion, cutOff);
		setLeftDrive(proportion, cutOff);
		}
		else
		{
			setRightDrive(proportion, cutOff);
		setLeftDrive(-proportion, cutOff);
		}
		*/
		//if the motors arn't moving due to low power input then check the timer else clear it
	}
	stopDrive();
}

//go forward for distance(in degrees) in a straight line at heading goal
//distance is always a positive integer = the distance in inches
//goal should be 0 if comming out of a turn or it should be the current gyro heading
//base power is positive or negative depending on desired direction
void forward(int distance, int goal, int basePower, int cutOff)
{
	nMotorEncoder[BL] = 0;
	nMotorEncoder[BR] = 0;

	int direction;

	//sets direction for use later
	if(distance <= 0)
	{
		direction = -1;
	}
	else
	{
		direction = 1;
	}
	basePower*=direction;
	//adjusts distance
	distance = (int)(51 * distance -(277*direction));
	//error variables for use later
	float error;
	float oldError = 0;
	int change = 0;

	//resets variables for use later
	proportion = 0;
	integral = 0;
	derivative = 0;

	//set constants for PID
	float Kp = 0.5;
	float Ki = 0.075;
	float Kd = 6;

	//prepares goal for use with gyro
	goal *= 10;

	//holds gyro value for future use
	int gyroValue;

	bool endLoop = false;

	int encoderLeftVal = nMotorEncoder[BL];
	int encoderRightVal = nMotorEncoder[BR];

	//will loop while the average of the sides is less than the direction
	while(!endLoop)
	{
		encoderLeftVal = nMotorEncoder[BL];
		encoderRightVal = nMotorEncoder[BR];
		if(direction > 0)
		{
			if(!(((nMotorEncoder[BL] + (nMotorEncoder[BR]*-1))/2) < distance))
			{
				endLoop = true;
			}
		}
		else
		{
			if(!((nMotorEncoder[BL] + (nMotorEncoder[BR]*-1))/2 > distance))
			{
				endLoop = true;
			}
		}

		//preparing error...mostly magic
		gyroValue = SensorValue[gyro];
		gyroValue = adjustGyro(gyroValue);
		error = centerGyro(goal, gyroValue);


		change = PID(Kp, Ki, Kd, error, oldError);

		//subtracts(or adds a negative since change will be negaive in that case/..) to the side that is ahead
		//multiplies by direction so that change is reversed
		//when both signs are the same left is affected, when signs are different right is effected
		if((change * direction) > 0)//if change and direction are both positive or negative
		{
			setRightDrive(basePower, cutOff);
			setLeftDrive((basePower - change), cutOff);
		}
		else if((change * direction) < 0)//if either change or direction but not both are negative
		{
			setRightDrive((basePower + change), cutOff);
			setLeftDrive(basePower, cutOff);
		}
		else
		{
			setRightDrive(basePower, cutOff);
			setLeftDrive(basePower, cutOff);
		}

		//sets the current error to be the old error for the next iteration
		oldError = error;

		//waits so that calculations are at even intervals
		wait1Msec(50);
	}
	stopDrive();
}

//go sideways for distance(in degrees) in a straight line at heading goal(front of robot)
//distance is always a positive integer
//goal should be 0 coming out of a turn so it finishes adjustments it couldn't do because of the motor cutoff
//alternately the goal could be the current gyro heading
//base power is positive or negative depending on desired direction-negative = left; positive = right
void sideways(int distance, int goal, int basePower, int cutOff)
{
	//adjusts distance
	distance = abs(distance);
	distance = (int)(distance*(360/sideConversion));

	int direction;

	//sets direction for use later
	if(basePower <= 0)
	{
		direction = -1;
	}
	else
	{
		direction = 1;
	}

	//error variables for use later
	float error;
	float oldError = 0;
	float change = 0;

	//resets variables for use later
	proportion = 0;
	integral = 0;
	derivative = 0;

	//set constants for PID
	float Kp = 0.5;
	float Ki = 0.054;
	float Kd = 1.5;

	//prepares goal for use with gyro
	goal *= 10;

	//stores gyro value
	int gyroValue;

	//will loop while the average of the sides is less than the direction
	while((direction * nMotorEncoder[BL] + direction * (-1*nMotorEncoder[BR]))/2 < distance)
	{
		//preparing error...mostly magic
		gyroValue = SensorValue[gyro];
		gyroValue = centerGyro(goal, gyroValue);
		error = adjustGyro(gyroValue);

		change = PID(Kp, Ki, Kd, error, oldError);
		change = change * -1;
		weightMechanum(basePower, 0, change);

		setFR(FRPower, cutOff);
		setFL(FLPower, cutOff);
		setBL(BLPower, cutOff);
		setBR(BRPower, cutOff);

		//sets the current error to be the old error for the next iteration
		oldError = error;

		//waits so that calculations are at even intervals
		wait1Msec(50);
	}
	stopDrive();
}

////////////////////////////////////////////////Driver Funcions////////////////////////////////////////////////////////////////////////


/*Runs the mechanum drive using the following motors
FR = front right
FL = front left
BL = Back left
BR = back right

bottomThresh = a value beneath which a channel will not have any input
topThresh = a value beneath which a channel will input a fraction of its value
lowGear = a value by which a channel will be divided when below topThresh
cutOff = a motor power beneath which no power will be sent to the motor
*/

//this tells how much the channel must change in one loop before using the accel function
int accelCutOff = 70;
//the ammount of time between changes in the motor power
int accelTime = 50;
//this determines the ammount of power added each time the accel function run
float accelMultiplier = 1;

//is an accel in progress
bool accel = false;

int accelDirection = 0;

//variables to hold old channel values for use in determining if accel is needed
int oldZVal=0;

int accelChange=0;

int accelRun(int ZVal)
{
	if(oldZVal == 0)
	{
		oldZVal = 1;
	}
	int newZVal = (int)(oldZVal + (abs(oldZVal) * accelMultiplier) * accelDirection);
	if(accelDirection == 1)
  {
  		//if the z val can be increased without going over the goal then do it otherwise, no action
  		if(newZVal < ZVal)
  		{
  			ZVal = newZVal;
  		}
  		else
  		{
  			//current zval(goal) will change the same and function ends
  			accel = false;
  			accelDirection = 0;
  		}
  	}
  	else if(accelDirection == -1)
  	{
  		if(newZVal > ZVal)
  		{
  			ZVal = newZVal;
  		}
  		else
  		{
  			//current zval(goal) will change the same and function ends
  			accel = false;
  			accelDirection = 0;
  		}
  	}
  	return ZVal;
}

void MechanumDrive(int bottomThresh, int topThresh, int lowGear, int cutOff)
{
	//these variables allow you to change which channels conrtol different movements
  XVal = 0;	//left/right
  ZVal = vexRT[Ch3];	//forward/back
  RotateVal = vexRT[Ch1];	//rotational


 		accelChange = abs(ZVal - oldZVal);
 	//if accel is in progress continue and aim for ZVal always
 	if(accel)
  {
  	ZVal = accelRun(ZVal);
  }

  	//if the ZVal has changed enough turn on accel
  	if(abs(ZVal - oldZVal) >= accelCutOff)
  	{
  		if(ZVal > oldZVal)
  		{
  			accelDirection = 1;
  		}
  		else
  		{
  			accelDirection = -1;
  		}
  		ZVal = accelRun(ZVal);
  		accel = true;
  	}
  oldZVal = ZVal;

  //these manipulate the channel values going into the main function
  //*see top and bottom thresh above
  if(abs(ZVal)< bottomThresh)
  {
    ZVal = 0;
  }
  else if(abs(ZVal) < topThresh)
  {
  	if(SensorValue[touchTop] == 1)
  	{
    	ZVal = ZVal/lowGear;
  	}
  }

  if(abs(XVal)< bottomThresh)
  {
    XVal = 0;
  }
  else if(abs(XVal) < topThresh)
  {
  	if(SensorValue[touchTop] == 1)
  	{
     	XVal = XVal/lowGear;
  	}
  }

  if(abs(RotateVal)< bottomThresh)
  {
    RotateVal = 0;
  }
  else if(abs(RotateVal) < topThresh)
  {
  	if(SensorValue[touchTop] == 1)
  	{
    	RotateVal = RotateVal/lowGear;
  	}
  }

	weightMechanum(XVal, ZVal, RotateVal);

  //Set powers to motors
	setFR(FRPower, cutOff);
	setFL(FLPower, cutOff);
	setBL(BLPower, cutOff);
	setBR(BRPower, cutOff);
}
