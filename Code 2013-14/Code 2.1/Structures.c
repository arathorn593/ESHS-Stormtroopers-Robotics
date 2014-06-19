

typedef struct{
//arm//////////
	int armPwr;
	//the potentiometer value that the arm is aiming for
	int armGoal; //-1 = no goal
	//this is the priority of the current arm power lower values overide high
	int armPri; //0 = live; 1 = preset; 2 = autonomous
	//the position of the arm, just the potentiometer values flipped so they are sensible
	int armPos;

//chas/////////
	int chasPwrLeft;
	int chasPwrRight;
	//current speed of drive in degrees/second
	float chasSpdLeft;
	float chasSpdRight;
	//goal encoder value for the chassis (when setting, assume current value = 0)
	int chasGoalLeft;
	int chasGoalRight;
	//the motor power for autonomous always positive
	int chasPwrAutoLeft;
	int chasPwrAutoRight;
	//speeds of the motors determined by the Pid controller
	int chasPidLeft;
	int chasPidRight;
	//the encoder value from the previous speed calculation
	int chasEncOldLeft;
	int chasEncOldRight;
	//the last time the speed was calculated
	int chasSpdTime;
	//true or false to decide if speed is calculated
	bool chasSpd;
	//true or false to determine if pid is enabled
	bool chasPid;
	//set arm variable above
	int chasPri;

	float gAccelX;
	float gAccelY;
	float gAccelZ;

	float forceG;

	float angleX;
	float angleY;
	float angleZ;

	//tipping info
	int tip;

	int intkPwr;
	int punchState;

	int intkPunchTime;
	int intkPunchState; //0 = back, 1 = activating, 2 = holding

	//tell background task what to put on the lcd. see variables for constants that define what specific numbers code for
	int lcdLine1;
	int lcdLine2;
	int lcdAltLine1;
	int lcdAltLine2;
}Robot;
