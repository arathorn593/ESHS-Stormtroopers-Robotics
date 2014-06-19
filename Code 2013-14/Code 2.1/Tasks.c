#include "Variables.c"

//these functions allow the power of an area to be set while taking into account the priority
//pwr = motor power; pri = priority of power; assumes that Robot adam is used
void setArmPwr(int pwr, int pri){
	if(adam.armPri >= pri){
		adam.armPwr = pwr;
		adam.armPri = pri;
	}
}

void setArmGoal(int goal, int pri){
	if(adam.armPri >= pri){
		adam.armGoal = goal;
		adam.armPri = pri;
	}
}

//this releases the arm from the control of the priority "pri"
void releaseArm(int pri){
	if(adam.armPri == pri){
		adam.armPwr = 0;
		adam.armPri = PRI_NONE;
	}
}
void setChasPwrLeft(int pwr, int pri){
	if(adam.chasPri >= pri){
			adam.chasPwrLeft = pwr;
			adam.chasPri = pri;
	}
}

void setChasGoalLeft(int goal, int pri){
	if(adam.chasPri >= pri){
		adam.chasGoalLeft = goal;
		adam.chasPri = pri;
	}
}

void setChasGoalRight(int goal, int pri){
	if(adam.chasPri >= pri){
		adam.chasGoalRight = goal;
		adam.chasPri = pri;
	}
}


void setChasPwrRight(int pwr, int pri){
	if(adam.chasPri >= pri){
			adam.chasPwrRight = pwr;
			adam.chasPri = pri;
	}
}

void releaseChas(int pri){
	if(adam.chasPri == pri){
			adam.chasPwrLeft = 0;
			adam.chasPwrRight = 0;
			adam.chasPri = PRI_NONE;
		}
}

float mainBat;
float secondBat;
float backupBat;
string strMain;
string strSecond;
string strBack;

bool backup;

void batLCD(){
		clearLCDLine(0);
		clearLCDLine(1);

		mainBat = (float)nImmediateBatteryLevel/(float)1000;
		backupBat = (float)BackupBatteryLevel/(float)1000;

		secondBat = (float)SensorValue[pwrExp] / (float)280;

		sprintf(strMain, "%f", mainBat);
		sprintf(strSecond, "%f", secondBat);
		sprintf(strBack, "%f", backupBat);

		if(nLCDButtons == 2){
			displayLCDString(0, 0, "Backup: ");
			displayLCDString(0, 8, strBack);
		}else{
			displayLCDString(0, 0, "Main: ");
			displayLCDString(1, 0, "PwrExp: ");

			displayLCDString(0, 6, strMain);
			displayLCDString(1, 8, strSecond);
		}
}

void chasLCD(){
		clearLCDLine(0);
		clearLCDLine(1);

		displayLCDString(0, 0, "EncoderL: ");
		displayLCDString(1, 0, "EncoderR: ");

		displayLCDNumber(0, 10, SensorValue[encoderL]);
		displayLCDNumber(1, 10, SensorValue[encoderR]);

		if(nLCDButtons == 2){
			resetChasEnc();
		}
}


float gAccel(tSensors accel){
	return ((SensorValue[accel]) * Vref / 4095 - Vref / 2) / Sensitivity;
}

//-1 = back; 1 = forward, 0 = none
int tipPrevention(){
	adam.gAccelX = gAccel(accelX);
	adam.gAccelY = gAccel(accelY);
	adam.gAccelZ = gAccel(accelZ);

	adam.forceG = sqrt(pow(adam.gAccelX, 2) + pow(adam.gAccelY, 2) + pow(adam.gAccelZ, 2));

	if(adam.forceG > 10){
		return 0;
	}

	adam.angleX = acos(adam.gAccelX/adam.forceG) * 180 / PI;
	adam.angleY = acos(adam.gAccelY/adam.forceG) * 180 / PI;
	adam.angleZ = acos(adam.gAccelZ/adam.forceG) * 180 / PI;

	if(initYAng == -1){
		if(adam.angleY > 90 - Y_ANG_RANGE && adam.angleY < 90 + Y_ANG_RANGE){
			initYAng = adam.angleY;
		}
	}else{
		adam.angleY = adam.angleY - (initYAng - 90);
	}
	if(adam.angleY < 90 - tipAng){
		return 1;
	}else if(adam.angleY > 90 + tipAng){
		return -1;
	}else{
		return 0;
	}
}

task background(){
	initRobot(&adam, true);
	ClearTimer(T1);
	resetChasEnc();
	while(true){
		//update
		adam.armPos = 4095 - SensorValue[armPot];

		//if chassis speed calculation is enabled
		if(adam.chasSpd){
			//if there has been enough delay since the last speed calculation
			if(time10[T1] - adam.chasSpdTime > CHAS_SPD_DELAY){
				//calculate speed
				adam.chasSpdLeft = (float)((SensorValue[encoderL] - adam.chasEncOldLeft))/(float)((time10[T1] - adam.chasSpdTime));
				adam.chasSpdRight = (float)((SensorValue[encoderR] - adam.chasEncOldRight))/(float)((time10[T1] - adam.chasSpdTime));

				//update variables
				adam.chasEncOldLeft = SensorValue[encoderL];
				adam.chasEncOldRight = SensorValue[encoderR];
				adam.chasSpdTime = time10[T1];
			}
		}

		if(abs(adam.chasPwrLeft) > 50 || abs(adam.chasPwrRight) > 50){
			tipAng = MV_TIP_ANG;
		}else{
			tipAng = STP_TIP_ANG;
		}

		adam.tip = tipPrevention();

		//punch handling
		if(adam.intkPunchState == 1){
			movePPunch(1);
			adam.intkPunchState = 2;
			adam.intkPunchTime = time10[T1];
		}else if(adam.intkPunchState == 2){
			if(time10[T1] - adam.intkPunchTime >= PUNCH_TIME){
				movePPunch(0);
				adam.intkPunchState = 0;
			}
		}

		setIntake(adam.intkPwr);
		//arm
		//if the arm is live controlled, cancel goals
		if(adam.armPri == PRI_LIVE){
			adam.armGoal = ARM_GOAL_NONE;
		}

		if(adam.armGoal != ARM_GOAL_NONE){
			if(adam.armGoal == ARM_GOAL_BASE){
				if(SensorValue[touchBase] == 0){
					adam.armPwr = -ARM_PWR;
				}else{
					adam.armPwr = 0;
					adam.armGoal = ARM_GOAL_NONE;
					adam.armPri = PRI_NONE;
				}
			}else if(adam.armGoal == ARM_GOAL_TOP){
				if(SensorValue[touchTop] == 0){
					adam.armPwr = ARM_PWR;
				}else{
					adam.armPwr = 0;
					adam.armGoal = ARM_GOAL_NONE;
					adam.armPri = PRI_NONE;
				}
			}else{
				if(adam.armPos > adam.armGoal + ARM_PSET_BUF){
					adam.armPwr = -ARM_PWR;
				}else if(adam.armPos < adam.armGoal - ARM_PSET_BUF){
					adam.armPwr = ARM_PWR;
				}else{
					adam.armPwr = 0;
					adam.armGoal = ARM_GOAL_NONE;
					adam.armPri = PRI_NONE;
				}
			}
		}
		//if arm has hit physical limit, stop moving
		if(adam.armPwr > 0 && SensorValue[touchTop] == 1){
			adam.armPwr = 0;
		}else if(adam.armPwr < 0 && SensorValue[touchBase] == 1){
			adam.armPwr = 0;
		}
		setArm(adam.armPwr);

		//chas
		if(adam.chasPri == PRI_LIVE){
			adam.chasGoalLeft = CHAS_GOAL_NONE;
			adam.chasGoalRight = CHAS_GOAL_NONE;
			resetChasEnc(); //reset encoders
		}
		if(adam.chasGoalLeft != CHAS_GOAL_NONE || adam.chasGoalRight != CHAS_GOAL_NONE){
			if(SensorValue[encoderL] < adam.chasGoalLeft - CHAS_GOAL_BUF){
				adam.chasPwrLeft = adam.chasPwrAutoLeft;
			}else if(SensorValue[encoderL] > adam.chasGoalLeft + CHAS_GOAL_BUF){
				adam.chasPwrLeft = -adam.chasPwrAutoLeft;
			}else{
				adam.chasPwrLeft = 0;
			}

			if(SensorValue[encoderR] < adam.chasGoalRight - CHAS_GOAL_BUF){
				adam.chasPwrRight = adam.chasPwrAutoRight;
			}else if(SensorValue[encoderR] > adam.chasGoalRight + CHAS_GOAL_BUF){
				adam.chasPwrRight = -adam.chasPwrAutoRight;
			}else{
				adam.chasPwrRight = 0;
			}

			if(abs(adam.chasGoalLeft) == abs(adam.chasGoalRight)){
				if((abs(SensorValue[encoderL]) + abs(SensorValue[encoderR]))/2 - abs(adam.chasGoalLeft) <= CHAS_GOAL_BUF){
					adam.chasPwrLeft = 0;
					adam.chasPwrRight = 0;
				}
			}

			if(adam.chasPwrRight == 0 && adam.chasPwrLeft == 0){
				adam.chasGoalLeft = CHAS_GOAL_NONE;
				adam.chasGoalRight = CHAS_GOAL_NONE;
				resetChasEnc();
			}
		}
		//if pid is enabled and the two sides are equal in magnitude (turning or straight)
		if(adam.chasPid && abs(adam.chasPwrLeft) == abs(adam.chasPwrRight)){

		}

		//only check for tipping above a certain arm height
		if(adam.armPos > ARM_TIP && adam.tip != 0){
			setChas(CHAS_TIP_SPD * adam.tip, CHAS_TIP_SPD * adam.tip);
			//adam.armGoal = ARM_GOAL_BAR;
		}else{
			setChas(adam.chasPwrLeft, adam.chasPwrRight);
		}
	}
}
