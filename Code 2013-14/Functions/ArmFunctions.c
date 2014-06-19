
#include "MotorFunctions.c"

int ARM_BAR_BUFFER = 40;
int ARM_BUMP_BUFFER = 50;
int ARM_PRESET_BUFFER = 50;
int ARM_POWER = 127;
int ARM_BUMP = 2800;
int ARM_BAR = 2265;
/////////////////////////////////////Autonomous Functions////////////////////////
//moves the arm time = milliseconds; direction: 1 = up, -1 = down
//!!!!!!!!!the potentiometer is reversed so larger values = lower arm
void moveArm(int goal){
	while(SensorValue[armPot] > goal + ARM_PRESET_BUFFER || SensorValue[armPot] < goal - ARM_PRESET_BUFFER){
		if(SensorValue[armPot] < goal){
			if(SensorValue[touchBottom] == 0){
				setArm(-ARM_POWER);
			}else{
				return;
			}
		}else if(SensorValue[armPot] > goal){
			if(SensorValue[touchTop] == 0){
				setArm(ARM_POWER);
			}else{
				return;
			}
		}
	}
	stopArm();
}

task armBump(){
	moveArm(ARM_BUMP);
}

task armBar(){
	moveArm(ARM_BAR);
}

task armBase(){
	while(SensorValue[touchBottom] == 0){
		setArm(-127);
	}
	stopArm();
}

void lowerArm(){
	while(SensorValue[touchBottom] == 0){
		setArm(-127);
	}
	stopArm();
}

void raiseArm(){
	while(SensorValue[touchTop] == 0){
		setArm(127);
	}
	stopArm();
}

task armTop(){
	while(SensorValue[touchTop] == 0){
		setArm(127);
	}
	stopArm();
}

task lastMinDump(){
	ClearTimer(T1);
	while(time1[T1] < 14250){}
	startOuttake();
}

///////////////////////////////////Control Functions/////////////////////////////



int stateArm = 0; //0 = no auto move; 1 = down; 2 = up (24in); 3 = bump; 4 = bar
int valBase = 0;
int valTop = 0;
int valBump = 0;
int valBar = 0;
int oldValBase = 0;
int oldValTop = 0;
int oldValBump = 0;
int oldValBar = 0;

int armPower = 0;
int armLeft = 0;
int armRight = 0;

void controlArm(int chDown, int chUp, int chBase, int chTop, int chBump, int chBar){
	valBase = vexRT[chBase];
	valTop = vexRT[chTop];
	valBar = vexRT[chBar];
	valBump = vexRT[chBump];

	if(valBase == 1 && oldValBase == 0){
		stateArm = 1;
	}else if(valTop == 1 && oldValTop == 0){
		stateArm = 2;
	}else if(valBump == 1 && oldValBump == 0){
		stateArm = 3;
	}else if(valBar == 1 && oldValBar == 0){
		stateArm = 4;
	}


	if(vexRT[chUp] == 1){
		armPower = 127;
		stateArm = 0;
	}else if(vexRT[chDown] == 1){
		armPower = -127;
		stateArm = 0;
	}else{
		if(stateArm == 1){
			if(SensorValue[touchBottom] == 0){
				armPower = -127;
			}
		}else if(stateArm == 2){
			if(SensorValue[touchTop] == 0){
				armPower = 127;
			}
		}else if(stateArm == 3){
			if(SensorValue[armPot] < ARM_BUMP - ARM_PRESET_BUFFER){
				armPower = -127;
			}else if(SensorValue[armPot] > ARM_BUMP + ARM_PRESET_BUFFER){
				armPower = 127;
			}else{
				armPower = 0;
			}
		}else if(stateArm == 4){
			if(SensorValue[armPot] < ARM_BAR - ARM_BAR_BUFFER){
				armPower = -127;
			}else if(SensorValue[armPot] > ARM_BAR + ARM_BAR_BUFFER){
				armPower = 127;
			}else{
				armPower = 0;
			}
		}else{
			armPower = 0;
		}
	}

	//if(armPower == 0){
	//	if(nLCDButtons == 5){
	//		armLeft = 60;
	//		armRight = 60;
	//	}else if(nLCDButtons == 1){
	//		armLeft = 60;
	//		armRight = 0;
	//	}else if(nLCDButtons == 4){
	//		armLeft = 0;
	//		armRight = 60;
	//	}else{
	//		armLeft = 0;
	//		armRight = 0;
	//	}
	//}

	if((SensorValue[touchTop] == 1 && (armPower > 0 || armLeft > 0 || armRight > 0)) ||
	(SensorValue[touchBottom] == 1 && (armPower < 0 || armLeft < 0 || armRight < 0))){
		armPower = 0;
		armLeft = 0;
		armRight = 0;
		stateArm = 0;
	}

	if (armPower == 0 && (armLeft != 0 || armRight != 0)){
		setArmL(armLeft);
		setArmR(armRight);
	}else{
		setArm(armPower);
	}

	oldValBase = valBase;
	oldValTop = valTop;
	oldValBump = valBump;
	oldValBar = valBar;
}

int valPunch = 0;
int oldValPunch = 0;

void controlIntake(int chIn, int chOut, int chAdjust, int chPunch){
	//rollers
	if(vexRT[chAdjust] == 0){
		if(vexRT[chIn] == 1){
			setIntake(127);
		}else if(vexRT[chOut] == 1){
			setIntake(-127);
		}else{
			stopIntake();
		}
	}else{
		setIntakeL(0);
		if(vexRT[chIn] == 1){
			setIntakeR(127/2);
		}else if(vexRT[chOut] == 1){
			setIntakeR(-127/2);
		}else{
			setIntakeR(0);
		}
	}

	if(vexRT[chPunch] == 1){
		movePPunch(1);
	}else{
		movePPunch(0);
	}
}
