#include "miscFunctions.c"
#include "MotorFunctions.c"


#define Vref 5.0
#define Sensitivity 0.3
#define tipAngle 20
#define tipArm 2250

int tip;

float gAccel(tSensors accel){
	return ((SensorValue[accel]) * Vref / 4095 - Vref / 2) / Sensitivity;
}

float gAccelX;
float gAccelY;
float gAccelZ;

float forceG;

float angleX;
float angleY;
float angleZ;

//-1 = back; 1 = forward, 0 = none
int tipPrevention(){
	gAccelX = gAccel(accelX);
	gAccelY = gAccel(accelY);
	gAccelZ = gAccel(accelZ);

	forceG = sqrt(pow(gAccelX, 2) + pow(gAccelY, 2) + pow(gAccelZ, 2));

	if(forceG > 10){
		return 0;
	}

	angleX = acos(gAccelX/forceG) * 180 / PI;
	angleY = acos(gAccelY/forceG) * 180 / PI;
	angleZ = acos(gAccelZ/forceG) * 180 / PI;

	if(angleY < 90 - tipAngle){
		return 1;
		}else if(angleY > 90 + tipAngle){
		return -1;
		}else{
		return 0;
	}
}

//drives forward over the bump
void moveBump(){
	float BUMP_UP1 = 0.25;
	float BUMP_UP2 = 0.1; //different b/c accelerometer will have upward accel as back goes over
	float BUFFER = 0.02;

	float initialY = gAccel(accelY);
	float currentY = initialY;
	setDrive(127, 127);
	//while the robot is approaching the bump
	while(abs(initialY - currentY) < BUMP_UP1){
		currentY = gAccel(accelY);
	}
	//the robot has started going over the bump

	//while the robot is angled up
	while(abs(initialY - currentY) > BUFFER){
		currentY = gAccel(accelY);
	}
	//first wheel over

	//while the second wheel is aproaching
	while(abs(initialY - currentY) < BUMP_UP2){
		currentY = gAccel(accelY);
	}
	//second wheel going over the bump

	//while the back is going over
	while(abs(initialY - currentY) > BUFFER){
		currentY = gAccel(accelY);
	}
	//second wheel over

	stopDrive();
}

/////////////////////////////////////////Autonomous////////////////////////////////
//distance = encoder value
void move(int power, int distance, int leftAdjust, int rightAdjust, bool tipCheck){
	resetDriveEncoders();
	while((abs(SensorValue[encoderL]) + abs(SensorValue[encoderR]))/2 < abs(distance)){
		if(tipCheck){
			tip = tipPrevention();
			if(tip != 0){
				setDrive(127*tip, 127*tip);
				break;
			}
		}
		setDrive(power + leftAdjust, power + rightAdjust);
	}
	stopDrive();
	resetDriveEncoders();
}

void move(int distance, bool tipCheck){
	move(127, distance, 0, 0, tipCheck);
}

/*!!!!!!!move and rotate functions look very simmilar, change?
*/
//distance = encoder value; direction: 1 = right, -1 = left
void rotate(int power, int distance, int direction, bool tipCheck){
	resetDriveEncoders();
	while((abs(SensorValue[encoderL]) + abs(SensorValue[encoderR]))/2 < abs(distance)){
		if(tipCheck){
			tip = tipPrevention();
			if(tip != 0){
				setDrive(127*tip, 127*tip);
				break;
			}
		}
		setDrive(power * 1 * direction, power * -1 * direction);
	}
	stopDrive();
	resetDriveEncoders();
}
/////////////////////////////////////////Driver/////////////////////////////////////



void controlDriveTank(int chLeft, int chRight, int gearThresh, float gear, int punchThresh, int punchCh){
	if(SensorValue[armPot] < tipArm){
		tip = tipPrevention();
		if(tip != 0){
			setDrive(127*tip, 127*tip);
			return;
		}
	}
	if(abs(vexRT[chLeft]) < punchThresh && abs(vexRT[chRight]) < punchThresh){
		if(vexRT[punchCh] == 1){
			setDrive(127, 127);
			return;
		}
	}
	if(abs(vexRT[chLeft]) < gearThresh){
		setDriveL(ceil(vexRT[chLeft]/gear));
		}else{
		setDriveL(vexRT[chLeft]);
	}

	if(abs(vexRT[chRight]) < gearThresh){
		setDriveR(ceil(vexRT[chRight]/gear));
		}else{
		setDriveR(vexRT[chRight]);
	}


}

float zVal = 0;
float rotateVal = 0;

float zWeight = 0;
float rotateWeight = 0;

int leftPower = 0;
int rightPower = 0;

void controlDriveArcade(int chZ, int chRotate, int gearThresh, float gear){
	if(SensorValue[armPot] < tipArm){
		tip = tipPrevention();
		if(tip != 0){
			setDrive(127*tip, 127*tip);
			return;
		}
	}
	zVal = vexRT[chZ];
	rotateVal = vexRT[chRotate];

	if(abs(zVal) < gearThresh){
		zVal = ceil(zVal/gear);
	}

	if(abs(rotateVal) < gearThresh){
		rotateVal = ceil(rotateVal/gear);
	}

	if((abs(zVal) + abs(rotateVal)) == 0){
		stopDrive();
		return;
	}

	zWeight = abs(zVal)/(abs(zVal) + abs(rotateVal));
	rotateWeight = abs(rotateVal)/(abs(zVal) + abs(rotateVal));

	leftPower = ceil(zWeight * zVal + rotateWeight * rotateVal);
	rightPower = ceil(zWeight * zVal + rotateWeight * rotateVal * -1);

	setDrive(leftPower, rightPower);
}

void chasLCD(){
	clearLCDLine(0);
	clearLCDLine(1);

	displayLCDString(0, 0, "EncoderL: ");
	displayLCDString(1, 0, "EncoderR: ");

	displayLCDNumber(0, 10, SensorValue[encoderL]);
	displayLCDNumber(1, 10, SensorValue[encoderR]);

	if(nLCDButtons == 2){
		resetDriveEncoders();
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

/*
float gAccelX;
float gAccelY;
float gAccelZ;

float forceG;

float angleX;
float angleY;
float angleZ;

bool isTip(){
gAccelX = gAccel(accelX);
gAccelY = gAccel(accelY);
gAccelZ = gAccel(accelZ);

forceG = sqrt(pow(gAccelX, 2) + pow(gAccelY, 2) + pow(gAccelZ, 2));

angleX = acos(gAccelX/forceG) * 180 / PI;
angleY = acos(gAccelY/forceG) * 180 / PI;
angleZ = acos(gAccelZ/forceG) * 180 / PI;
}
*/
