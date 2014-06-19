//functions for driver control
#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Code 2.0\structRobot.c"
#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Code 2.0\globalComVars.c"

//this activates buttons and channels for use with the driver control
void activate(int channel){
	adam.channels[channel][CH_ACTIVE] = 1;
}

void activateMain(){
				AA																												activate(Ch1);activate(Ch2);activate(Ch3);activate(Ch4);
	activate(Btn5D);activate(Btn5U);
	activate(Btn6D);activate(Btn6U);
	activate(Btn7D);activate(Btn7U);activate(Btn7L);activate(Btn7R);
	activate(Btn8D);activate(Btn8U);activate(Btn8L);activate(Btn8R);
}

void activateAlt(){
	activate(Ch1Xmtr2);activate(Ch2Xmtr2);activate(Ch3Xmtr2);activate(Ch4Xmtr2);
	activate(Btn5DXmtr2);activate(Btn5UXmtr2);
	activate(Btn6DXmtr2);activate(Btn6UXmtr2);
	activate(Btn7DXmtr2);activate(Btn7UXmtr2);activate(Btn7LXmtr2);activate(Btn7RXmtr2);
	activate(Btn8DXmtr2);activate(Btn8UXmtr2);activate(Btn8LXmtr2);activate(Btn8RXmtr2);
}
//!!!!!!!!!!only 1 chassis drive scheme can be used

//sets the left and right drive powers based on a tank control setup
//left and right channels are the channels you want for your tank control: only Ch1-4
//bottomThresh is the value below which the channel does not register in the calculations
//gearThresh is the value below which the channel value is divided by the variable gear.
void chasTank(int leftChannel, int rightChannel, int bottomThresh, int gearThresh, float gear){
		if(abs(adam.channels[leftChannel][CH_CURRENT]) < bottomThresh){
			adam.chasLeftPower = 0;
		}else if(abs(adam.channels[leftChannel][CH_CURRENT]) < gearThresh){
			adam.chasLeftPower = ceil((float)adam.channels[leftChannel][CH_CURRENT]/gear);
		}else{
			adam.chasLeftPower = adam.channels[leftChannel][CH_CURRENT];
		}

		if(abs(adam.channels[rightChannel][CH_CURRENT]) < bottomThresh){
			adam.chasRightPower = 0;
		}else if(abs(adam.channels[rightChannel][CH_CURRENT]) < gearThresh){
			adam.chasRightPower = ceil((float)adam.channels[rightChannel][CH_CURRENT]/gear);
		}else{
			adam.chasRightPower = adam.channels[rightChannel][CH_CURRENT];
		}
}

float zVal = 0;
float rotateVal = 0;

float zWeight = 0;
float rotateWeight = 0;

void chasArcade(int zChannel, int rotateChannel, int bottomThresh, int gearThresh, float gear){
	zVal = adam.channels[zChannel][CH_CURRENT];
	rotateVal = adam.channels[rotateChannel][CH_CURRENT];

	if(abs(zVal) < bottomThresh){
		zVal = 0;
	}else if(abs(zVal) < gearThresh){
		zVal = ceil((float)zVal/gear);
	}

	if(abs(rotateVal) < bottomThresh){
		rotateVal = 0;
	}else if(abs(rotateVal) < gearThresh){
		rotateVal = ceil((float)rotateVal/gear);
	}

	if((abs(zVal) + abs(rotateVal)) == 0){
		return;
	}

	zWeight = abs(zVal)/(abs(zVal) + abs(rotateVal));
	rotateWeight = abs(rotateVal)/(abs(zVal) + abs(rotateVal));

	adam.chasLeftPower = ceil(zWeight * zVal + rotateWeight * rotateVal);
	adam.chasRightPower = ceil(zWeight * zVal + rotateWeight * rotateVal * -1);
}

//these are button functions, channel = the button used,
//norm is the default state, 0 is off, 1 is on

//this function just sends a one or zero after determining if it is a valid press
//!!!!!!!!!!!!!!!!reformat so you don't need to have driveAction(channel, adam.channels[channel][CH_CURRENT]) every
//because that is ANNOYING
int driveAction(int channel, int value){
	//if it is a joystick, convert it to boolean
	if(channel <= 3){
		if(value > JOYSTICK_BUTTON){
			return 1;
		}else{
			return 0;
		}
	//if channel is a negative joytick (down or left preset)
	}else if(channel >= -3){
		if(value < JOYSTICK_BUTTON){
			return 1;
		}else{
			return 0;
		}
	}else{
		return value;
	}
}


//moves the arm to a specific location (special goal values applicable)
void armPreset(int channel, int goal){
	if(driveAction(channel, adam.channels[channel][CH_CURRENT]) == 1
	&& driveAction(channel, adam.channels[channel][CH_OLD]) && adam.armPriority <= ARM_PRIORITY_AUTO){
		adam.armGoal = goal;
		adam.armPriority = ARM_PRIORITY_AUTO;
	}
}

//lowers arm to lowest possible position
void armBasePreset(int channel){
	armPreset(channel, ARM_GOAL_BASE);
}

void armBumpPreset(int channel){
	armPreset(channel, ARM_GOAL_BUMP);
}

void armBarPreset(int channel){
	armPreset(channel, ARM_GOAL_BAR);
}

void armTopPreset(int channel){
	armPreset(channel, ARM_GOAL_TOP);
}

//base for the continuous movement arm functions
void armContinuous(int channel, int goal){
	if(driveAction(channel, adam.channels[abs(channel)][CH_CURRENT]) == 1
	&& adam.armPriority <= ARM_PRIORITY_LIVE){
		adam.armGoal = goal;
		adam.armPriority = ARM_PRIORITY_LIVE;
	}else if(driveAction(channel, adam.channels[abs(channel)][CH_CURRENT]) == 0 && adam.armGoal == goal){
		//if the robot is raising the arm and it shouldn't be, turn goal to none
		adam.armGoal = ARM_GOAL_NONE;
	}
}

void armUp(int channel){
	armContinuous(channel, ARM_GOAL_UP);
}

void armDown(int channel){
	armContinuous(channel, ARM_GOAL_DOWN);
}

//!!!!!!!!!!change this to move more control to background task intead of using the function
void intake(int inChannel, int outChannel){
	if(driveAction(inChannel, adam.channels[abs(inChannel)][CH_CURRENT]) == 1){
		adam.intakePower = INTAKE_POWER;
	}else if(driveAction(outChannel, adam.channels[abs(outChannel)][CH_CURRENT]) == 1){
		adam.intakePower = -INTAKE_POWER;
	}else{
		adam.intakePower = 0;
	}
}
