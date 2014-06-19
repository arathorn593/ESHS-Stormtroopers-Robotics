#include "Tasks.c"

int drvPress(int ch){
	//if it is a joystick, convert it to boolean
	if(ch <= 3){
		if(ch > 0){
			if(vexRT[ch] > JOY_BUTTON){
				return 1;
			}else{
				return 0;
			}
		}else{
			if(vexRT[ch] < JOY_BUTTON){
				return 1;
			}else{
				return 0;
			}
		}
	//if channel is a negative joytick (down or left preset)
	}else{
		return vexRT[ch];
	}
}

//moves the arm to a specific location (special goal values applicable)
void armPreset(int channel, int goal){
	if(drvPress(channel) == 1){
		setArmGoal(goal, PRI_PSET);
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

void armContinuous(int chUp, int chDown){
	if(drvPress(chUp) == 1){
		setArmPwr(ARM_PWR, PRI_LIVE);
	}else if(drvPress(chDown) == 1){
		setArmPwr(-ARM_PWR, PRI_LIVE);
	}else{
		releaseArm(PRI_LIVE);
	}
}

void intake(int chIn, int chOut){
	if(drvPress(chIn) == 1){
		adam.intkPwr = INTK_PWR;
	}else if(drvPress(chOut) == 1){
		adam.intkPwr = -INTK_PWR;
	}else{
		adam.intkPwr = 0;
	}
}

int pwrLeft;
int pwrRight;

void chasTank(int chLeft, int chRight, int threshBot, int threshGear, float gear){
		if(abs(vexRT[chLeft]) < threshBot){
			pwrLeft = 0;
		}else if(abs(vexRT[chLeft]) < threshGear){
			pwrLeft = ceil((float)vexRT[chLeft]/gear);
		}else{
			pwrLeft = vexRT[chLeft];
		}

		if(abs(vexRT[chRight]) < threshBot){
			pwrRight = 0;
		}else if(abs(vexRT[chRight]) < threshGear){
			pwrRight = ceil((float)vexRT[chRight]/gear);
		}else{
			pwrRight = vexRT[chRight];
		}

		if(pwrLeft == 0 && pwrRight == 0){
			releaseChas(PRI_LIVE);
		}else{
			setChasPwrLeft(pwrLeft, PRI_LIVE);
			setChasPwrRight(pwrRight, PRI_LIVE);
		}
}

float zVal = 0;
float rotateVal = 0;

float zWeight = 0;
float rotateWeight = 0;

void chasArcade(int chZ, int chRotate, int threshBot, int threshGear, float gear){
	zVal = vexRT[chZ];
	rotateVal = vexRT[chRotate];

	if(abs(zVal) < threshBot){
		zVal = 0;
	}else if(abs(zVal) < threshGear){
		zVal = ceil((float)zVal/gear);
	}

	if(abs(rotateVal) < threshBot){
		rotateVal = 0;
	}else if(abs(rotateVal) < threshGear){
		rotateVal = ceil((float)rotateVal/gear);
	}

	if((abs(zVal) + abs(rotateVal)) == 0){
		return;
	}

	zWeight = abs(zVal)/(abs(zVal) + abs(rotateVal));
	rotateWeight = abs(rotateVal)/(abs(zVal) + abs(rotateVal));

	pwrLeft = ceil(zWeight * zVal + rotateWeight * rotateVal);
	pwrRight = ceil(zWeight * zVal + rotateWeight * rotateVal * -1);

	if(pwrLeft == 0 && pwrRight == 0){
		releaseChas(PRI_LIVE);
	}else{
		setChasPwrLeft(pwrLeft, PRI_LIVE);
		setChasPwrRight(pwrRight, PRI_LIVE);
	}
}

void intkPunch(int chPunch){
	if(drvPress(chPunch) == 1){
		adam.intkPunchState = 1;
	}
}

//the time since move start in ms.
int mvTime;
bool intkMv;
bool intkPunchActive;
void intkMovePunch(int chMPunch){
	if(drvPress(chMPunch) == 1){
		intkMv = true;
		setChasPwrLeft(PUNCH_CHAS_PWR, PRI_PSET);
		setChasPwrRight(PUNCH_CHAS_PWR, PRI_PSET);
	}else if(intkMv){
		if(!intkPunchActive){
			intkPunchActive = true;
			adam.intkPunchState = 1;
		}else{
			if(adam.intkPunchState == 0){
				intkMv = true;
				intkPunchActive = true;
				releaseChas(PRI_PSET);
			}
		}
	}
}
