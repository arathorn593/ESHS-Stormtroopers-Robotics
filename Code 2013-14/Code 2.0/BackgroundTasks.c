#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Code 2.0\structRobot.c"
#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Code 2.0\globalComVars.c"
#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Functions\motorFunctions.c"
//task to update everything (may need to split into data updating and pid controlling)

//!!!!!!!!!!!is this byref? ahh.... pointers
/*
float PID(pid *controller){

	change = 0;

	change += error * Kp;

	change += (integral + error) * Ki * dt;

	change += (error - oldError) * Kd * dt;

	return change;
}
*/
int currentTime;
int oldTime;
int time;

task background(){
	//this pointer should probably go somewhere else.....
	//pid *speedLeft = &adam.pidSpeedLeft;
	//pid *speedRight = &adam.pidSpeedRight;
	//ClearTimer(T1);
	while(true){
		//start chassis fancyness
		//if(!adam.pidSpeedLeft.activated && !adam.pidSpeedRight.activated){
		adam.chasLeftPos = SensorValue[adam.chasLeftEncoder];
		adam.chasRightPos = SensorValue[adam.chasRightEncoder];
		if(adam.chasPriority == CHAS_PRIORITY_AUTO){
			if(adam.chasLeftGoal > adam.chasLeftPos + CHAS_AUTO_BUFF){
				setDriveL(adam.chasLeftPower);
			}else if(adam.chasLeftGoal < adam.chasLeftPos - CHAS_AUTO_BUFF){
				setDriveL(-adam.chasLeftPower);
			}else{
				setDriveL(0);
			}

			if(adam.chasRightGoal > adam.chasLeftPos + CHAS_AUTO_BUFF){
				setDriveR(adam.chasRightPower);
			}else if(adam.chasRightGoal < adam.chasRightPos - CHAS_AUTO_BUFF){
				setDriveR(-adam.chasRightPower);
			}else{
				setDriveR(0);
			}

			if(adam.chasRightGoal > adam.chasLeftPos + CHAS_AUTO_BUFF && adam.chasRightGoal < adam.chasRightPos - CHAS_AUTO_BUFF
			&& adam.chasLeftGoal > adam.chasLeftPos + CHAS_AUTO_BUFF && adam.chasLeftGoal < adam.chasLeftPos - CHAS_AUTO_BUFF){
				adam.chasPriority = CHAS_PRIORITY_FREE;
			}
		}else{
			setDrive(adam.chasLeftPower, adam.chasRightPower);
		}
		/*}else{
			//prepare for this loop
			adam.pidSpeedLeft.setPoint = adam.chasLeftPower;

			adam.pidSpeedRight.setPoint = adam.chasRightPower;

			//prepare for next loop
			adam.pidSpeedLeft.oldTime = adam.pidSpeedLeft.curTime;
			adam.pidSpeedLeft.oldError = adam.pidSpeedLeft.error;
			adam.pidSpeedRight.oldTime = adam.pidSpeedRight.curTime;
			adam.pidSpeedRight.oldError = adam.pidSpeedRight.error;
		}*/
		//end chassis fanciness

		setIntake(adam.intakePower);

		//begin arm coding madness
		if(adam.armGoal == ARM_GOAL_DOWN){
			adam.armPower = -ARM_BASE_POWER;
		}else if(adam.armGoal == ARM_GOAL_UP){
			adam.armPower = ARM_BASE_POWER;
		}else if(adam.armGoal == ARM_GOAL_BASE){
			if(SensorValue[adam.armTouchBottom] != 1){
				adam.armPower = -ARM_BASE_POWER;
			}
		}else if(adam.armGoal == ARM_GOAL_TOP){
			if(SensorValue[adam.armTouchTop] != 1){
				adam.armPower = ARM_BASE_POWER;
			}
		}else if(adam.armGoal != ARM_GOAL_NONE){
			if(SensorValue[adam.armPot] > adam.armGoal + ARM_PRESET_BUFFER){
				adam.armPower = -ARM_BASE_POWER;
			}else if(SensorValue[adam.armPot] < adam.armGoal - ARM_PRESET_BUFFER){
				adam.armPower = ARM_BASE_POWER;
			}else{
				adam.armPower = 0;
				adam.armGoal = ARM_GOAL_NONE;
			}
		}else{
			adam.armPower = 0;
		}
		if(adam.armPower < 0 && SensorValue[adam.armTouchBottom] == 1){
			adam.armPower = 0;
			adam.armGoal = ARM_GOAL_NONE;
		}else if(adam.armPower > 0 && SensorValue[adam.armTouchTop] == 1){
			adam.armPower = 0;
			adam.armGoal = ARM_GOAL_NONE;
		}
		//if there is no goal, release arm priority
		if(adam.armGoal == ARM_GOAL_NONE){
			adam.armPriority = ARM_PRIORITY_FREE;
		}

		setArm(adam.armPower);
		//end arm coding madness

		//updates channels that are being used !!!!!possibly too much overhead
		for(int index = 0; index < CH_ARRAY_LENGTH; index++){
			//if(adam.channels[index][CH_ACTIVE] == 1){
				adam.channels[index][CH_OLD] = adam.channels[index][CH_CURRENT];
				adam.channels[index][CH_CURRENT] = vexRT[index];
			//}
		}
		currentTime = time1[T1];
		time = currentTime - oldTime;
		oldTime = currentTime;
	}
}
