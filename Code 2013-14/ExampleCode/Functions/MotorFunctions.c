

////////////////////////////////CONSTANTS////////////////////////////////////////////
int CUT_OFF_INTAKE = 15;
int CUT_OFF_ARM = 25;
int CUT_OFF_DRIVE = 25;

int PID_DEFAULT_PWR = 100;


////////////////////////////////Inividual Motors/Pistons/////////////////////////////////////

//name = motor; power = motor power; cutOff = motor cutoff value
void setMotor(tMotor name, int power, int cutOff){
	if(abs(power) < cutOff){
		motor[name] = 0;
	}else{
		motor[name] = power;
	}
}

//name = piston name; state: default == 0, active == 1
void movePiston(tSensors name, int state){
	SensorValue[name] = state;
}

void setIntakeL(int power){
	setMotor(intakeL, power, CUT_OFF_INTAKE);
}
void setIntakeR(int power){
	setMotor(intakeR, power, CUT_OFF_INTAKE);
}

void setArmRU(int power){
	setMotor(armRU, power, CUT_OFF_ARM);
}
void setArmRD(int power){
	setMotor(armRD, power, CUT_OFF_ARM);
}
void setArmLU(int power){
	setMotor(armLU, power, CUT_OFF_ARM);
}
void setArmLD(int power){
	setMotor(armLD, power, CUT_OFF_ARM);
}

void setLU(int power){
	setMotor(LU, power, CUT_OFF_DRIVE);
}
void setLD(int power){
	setMotor(LD, power, CUT_OFF_DRIVE);
}
void setRU(int power){
	setMotor(RU, power, CUT_OFF_DRIVE);
}
void setRD(int power){
	setMotor(RD, power, CUT_OFF_DRIVE);
}

void movePPunch(int state){
	movePiston(pPunchL, state);
	movePiston(pPunchR, state);
}


////////////////////////////////Groups////////////////////////////////
//positive power = intake, negative = outtake
void setIntake(int power){
	setIntakeL(power);
	setIntakeR(power);
}
void startIntake(){
	setIntake(127);
}
void startOuttake(){
	setIntake(-127);
}
void stopIntake(){
	setIntake(0);
}

void setArmL(int power){
	setArmLD(power);
	setArmLU(power);
}
void setArmR(int power){
	setArmRD(power);
	setArmRU(power);
}
void setArm(int power){
	setArmL(power);
	setArmR(power);
}
void stopArm(){
	setArm(0);
}

void setDriveL(int power){
	setLD(power);
	setLU(power);
}
void setDriveR(int power){
	setRD(power);
	setRU(power);
}
void setDrive(int powerLeft, int powerRight){
	setDriveL(powerLeft);
	setDriveR(powerRight);
}
void stopDrive(){
	setDrive(0, 0);
}
