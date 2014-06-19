

#include "MiscFunctions.c"
#include "ChassisFunctions.c"

/////////////////////////////////////////////autonomous functions////////////////////////////////////////////////////////////////////////
void waitForCenter()
{
	while(nLCDButtons != 2){}
}

void shakeIntake(int direction)
{
	setRightDrive(127*direction, 0);
	setLeftDrive(127*direction, 0);
	wait1Msec(500);
	setRightDrive(-127*direction, 0);
	setLeftDrive(-127*direction, 0);
	wait1Msec(500);
	stopDrive();
}


void lowerArm()
{
	while(SensorValue[touchBottom] == 0)
	{
		setArm(-127, 0);
	}
	stopArm();
	SensorValue[encoderArmLeft] = 0;
	SensorValue[encoderArmRight] = 0;
}

int troughHeight = 75;

task taskLowerArm()
{
	while(SensorValue[touchBottom] == 0)
	{
		setArm(-127, 0);
	}
	stopArm();
	SensorValue[encoderArmLeft] = 0;
	SensorValue[encoderArmRight] = 0;
}

//simple arm control
void arm(int goal, int basePower, int cutOff)
{
	int goalRange= 5;
	basePower = abs(basePower);
	bool endArm = false;
	while(!endArm)
	{
		if(SensorValue[touchBottom] == 1)
		{
			resetArmEncoders();
		}
		if(SensorValue[encoderArmLeft] > goal+ goalRange)
		{
			setArm(-basePower, cutOff);
			if(SensorValue[touchBottom] == 1)
			{
				stopArm();
				endArm = true;
			}
		}
		else if(SensorValue[encoderArmLeft] < goal)
		{
			setArm(basePower, cutOff);
			if(SensorValue[touchTop] == 1)
			{
				stopArm();
				endArm = true;
			}
		}
		else
		{
			stopArm();
			endArm = true;
		}
	}
}

////raises or lowers arm to desired height while keeping sides equal
////goal will be always positive
////basePower will always be positive
//void arm(int goal, int basePower, int cutOff)
//{
//	int direction;

//	//this sets the direction of the arm
//	if((SensorValue[encoderArmLeft] + SensorValue[encoderArmRight])/2 > goal)
//	{
//		direction = 1;
//		basePower = abs(basePower); //just in case someone messed up
//	}
//	else if((SensorValue[encoderArmLeft] + SensorValue[encoderArmRight])/2 < goal)
//	{
//		direction = -1;
//		basePower = abs(basePower) * -1;
//	}
//	else
//	{
//		return; //the arm is already there
//	}

//	//variables used in the PID controller
//	int error;
//	int oldError = 0;
//	int change = 0;

//	//sets the constants for PID
//	int Kp = .5;
//	int Ki = 0;
//	int Kd = 0;

//	//clears these for use later
//	proportion = 0;
//	integral = 0;
//	derivative = 0;

//	//if the arm is at the bottom, zero out the encoders for accuracy
//	if(SensorValue[touchBottom] == 1)
//	{
//		SensorValue[encoderArmLeft] = 0;
//		SensorValue[encoderArmRight] = 0;
//	}

//	while((SensorValue[encoderArmLeft] + SensorValue[encoderArmRight])/2 < goal)
//	{
//		//these prevent the arm from moving outside its range of motion
//		if(SensorValue[touchTop] == 1)
//		{
//			stopArm();
//		}
//		else if(SensorValue[touchBottom] == 1)
//		{
//			stopArm();
//		}

//		//find how off the 2 sides are
//		error = SensorValue[encoderArmLeft] - SensorValue[encoderArmRight];

//		//retrieve the results from the PID controller
//		change = 1//PID(Kp, Ki, Kd, error, oldError);

//		//puts the change into effect!!!!!!!!!!copied from drive, if bugs, check here
//		if((change * direction) > 0)//if change and direction are both positive or negative
//		{
//			setArmRight(basePower, cutOff);
//			setArmLeft((basePower /*- change*/), cutOff);
//		}
//		else if((change * direction) < 0)//if either change or direction but not both are negative
//		{
//			setArmRight((basePower /*+ change*/), cutOff);
//			setArmLeft(basePower, cutOff);
//		}
//		else//sides equal aka change = 0
//		{
//			setArmRight(basePower, cutOff);
//			setArmLeft(basePower, cutOff);
//		}

//		//preparing for next loop
//		oldError = error;

//		//ensures each time through is an equal increment
//		wait1Msec(50);
//	}
//	stopArm();
//}

task troughArm()
{
	arm(75, 127, 0);
}

//see misc functions for intake drivers

////////////////////////////////////////////////Driver Funcions////////////////////////////////////////////////////////////////////////

//variables for arm control
int baseNewVal = 0;
int baseOldVal=0;
int midNewVal=0;
int midOldVal=0;
int topNewVal=0;
int topOldVal=0;
int overNewVal = 0;
int overOldVal = 0;
int overState = 0;
int state = 0;
int error;
int oldError = 0;
int Kp = .5;
int Ki = 0;
int Kd = 0;
int change = 0;
int direction = 1;

//arm adjust power
int adjustPower = 60;


//contols the arm and allows presets at base, hieght trough, and height highGoal
//speed = magnitude, and there is a cutoff
void armControl(int trough, int highGoal, int magnitude, int cutOff)
{
	//determines the range above the preset that the arm can stop in
	int presetRange = 5;

	overNewVal = vexRT[BTn7U];

	if((overNewVal == 1)&&(overOldVal == 0))
	{
		overState = 1-overState;
	}
	overOldVal = overNewVal;
	//these prevent the arm from moving outside its range of motion
	if(SensorValue[touchTop] == 1)
	{
		stopArm();
	}
	else if((SensorValue[touchBottom] == 1) && (overState == 0))
	{
		stopArm();
	}

	//resets encoders to promote accuracy
	if(SensorValue[touchBottom] == 1)
	{
		SensorValue[encoderArmLeft] = 0;
		SensorValue[encoderArmRight] = 0;
	}

	//variable that keeps track of the motor power for use in the pid
	int motorPower = 0;

	//these put the value of the top and bottom buttons in the apropriate variable
	if(controllerState == 0)
	{
		baseNewVal = vexRT[Btn8D];
		midNewVal = vexRT[Btn8U];
	}
	else if(controllerState == 1)
	{
		baseNewVal = vexRT[Btn8DXmtr2];
		midNewVal = vexRT[Btn8UXmtr2];
	}

	//this allows either of the middle buttons to trigger the middle varible
	if(controllerState == 0)
	{
		if((vexRT[Btn8R] == 1)||(vexRT[Btn8L] == 1))
		{
			midNewVal = 1;
		}
	}
	else if(controllerState == 1)
	{
		if((vexRT[Btn8RXmtr2] == 1)||(vexRT[Btn8LXmtr2] == 1))
		{
			midNewVal = 1;
		}
	}
	//These 3 if statements say that for each of the hieghts
	//if the new value is 1(pressed) and the old value is 0(unpressed)
	//then it was a legitamate button press and sets the state to the
	//correct level.
	if((baseNewVal == 1) && (baseOldVal == 0))
	{
		state = 1;
	}

	if((midNewVal == 1) && (midOldVal == 0))
	{
		state = 2;
	}

	if((topNewVal == 1) && (topOldVal == 0))
	{
		state = 3;
	}

	topOldVal = topNewVal;
	midOldVal = midNewVal;
	baseOldVal = baseNewVal;

	if((vexRT[Btn6D] == 1) || (vexRT[Btn6DXmtr2] && controllerState == 1))
	{
		state = 0;
		if(SensorValue[touchBottom] == 0)
		{
			motorPower = -127;
		}
		else if(overState == 1)
		{
			motorPower = -127;
		}
		else
		{
			motorPower = 0;
		}
	}
	else if((vexRT[Btn6U] == 1) || (vexRT[Btn6UXmtr2] && controllerState == 1))
	{
		state = 0;
		if(SensorValue[touchTop] == 0)
		{
			motorPower = 127;
		}
		else
		{
			motorPower = 0;
		}
	}
	else
	{
		if(state == 1)
		{
			if(SensorValue[touchBottom] == 0)
			{
				motorPower = -127;
			}
			else
			{
				motorPower = 0;
				state = 0;
			}
		}
		else if(state == 2)
		{
			if(SensorValue[encoderArmLeft] > trough+ presetRange)
			{
				motorPower = -127;
			}
			else if(SensorValue[encoderArmLeft] < trough)
			{
				motorPower = 127;
			}
			else
			{
				motorPower = 0;
				state = 0;
			}
		}
		else if(state == 3)
		{
			if(SensorValue[encoderArmLeft] > highGoal)
			{
				motorPower = -127;
			}
			else if(SensorValue[encoderArmLeft]< highGoal)
			{
				motorPower = 127;
			}
			else
			{
				motorPower = 0;
				state = 0;
			}
		}
		else
		{
			motorPower = 0;
		}
	}

	//if the arm isn't moving set the power otherwise go to pid
	if((motorPower == 0)||(SensorValue[touchBottom] == 1) ||(SensorValue[touchTop] == 1))
	{
		//resets pid values for use later
		proportion = 0;
		integral = 0;
		derivative = 0;
		//built in arm adjust
			if((nLCDButtons == 1) || (nLCDButtons == 4))
			{
				if(nLCDButtons == 1)
				{
					setArmLeft(adjustPower, cutOff);
				}
				else if(nLCDButtons == 4)
				{
					setArmRight(adjustPower, cutOff);
				}
				return;
			}
			else
			{
				setArm(motorPower, cutOff);
			}
	}
	else
	{
		if(motorPower > 0)
		{
			direction = 1;
		}
		else
		{
			direction = -1;
		}

		//find how off the 2 sides are
		error = SensorValue[encoderArmLeft] - SensorValue[encoderArmRight];

		//retrieve the results from the PID controller
		change = PID(Kp, Ki, Kd, error, oldError);

		//puts the change into effect!!!!!!!!!!copied from drive, if bugs, check here
		if((change * direction) > 0)//if change and direction are both positive or negative
		{
			setArmRight(motorPower, cutOff);
			setArmLeft((motorPower /*- change*/), cutOff);
		}
		else if((change * direction) < 0)//if either change or direction but not both are negative
		{
			setArmRight((motorPower /*+ change*/), cutOff);
			setArmLeft(motorPower, cutOff);
		}
		else//sides equal aka change = 0
		{
			setArmRight(motorPower, cutOff);
			setArmLeft(motorPower, cutOff);
		}

		//preparing for next loop
		oldError = error;
	}
}

//runs intake control, in and out magnitude are both positive
void intake(int inMagnitude, int outMagnitude, int cutOff)
{
	if((vexRT[Btn5D] == 1) || (vexRT[Btn5DXmtr2] && controllerState == 1))
	{
		startIntake(inMagnitude, cutOff);
	}
	else if((vexRT[Btn5U] == 1) || (vexRT[Btn5UXmtr2] && controllerState == 1))
	{
		startIntake(-1*outMagnitude, cutOff);
	}
	else
	{
		stopIntake();
	}
}
