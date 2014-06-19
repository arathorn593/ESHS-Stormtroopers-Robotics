#include "Tasks.c"

void moveLR(int goalLeft, int goalRight, int pwrLeft, int pwrRight, bool wait){
	setChasGoalLeft(goalLeft, PRI_AUTO);
	setChasGoalRight(goalRight, PRI_AUTO);
	adam.chasPwrAutoLeft = pwrLeft;
	adam.chasPwrAutoRight = pwrRight;
	if(wait){
		while(adam.chasPri == PRI_AUTO){}
	}
}

void move(int goal, int pwr, bool wait){
	moveLR(goal, goal, pwr, pwr, wait);
}

void moveWait(int goal, int pwr){
	move(goal, pwr, true);
}

void moveWait(int goal){
	move(goal, 127, true);
}

//direction: 1 = right, -1 = left
void rotateLR(int goalLeft, int goalRight, int pwrLeft, int pwrRight, int direction){
	setChasGoalLeft(goalLeft * direction, PRI_AUTO);
	setChasGoalRight(goalRight * direction * -1, PRI_AUTO);
	adam.chasPwrAutoLeft = pwrLeft;
	adam.chasPwrAutoRight = pwrRight;
}

void rotate(int goal, int pwr, int direction){
	rotateLR(goal, goal, pwr, pwr, direction);
}

void rotateWait(int goal, int pwr, int direction){
	rotate(goal, pwr, direction);
	while(adam.chasPri == PRI_AUTO){}
}

void rotateWait(int goal, int direction){
	rotateWait(goal, 127, direction);
}

void setArmAuto(int goal){
	setArmGoal(goal, PRI_AUTO);
}

void setArmWait(int goal){
	setArmAuto(goal);
	while(adam.armPri == PRI_AUTO){}
}

void startIntake(){
	adam.intkPwr = INTK_PWR;
}

void startOuttake(){
	adam.intkPwr = -INTK_PWR;
}

void stopIntake(){
	adam.intkPwr = 0;
}

void waitForPress(){
	while(nLCDButtons == 0){}
}

task lastMinDump(){
	ClearTimer(T2);
	while(time1[T2] < 14250){}
	startOuttake();
}



//RED SIDE!!!!!!!!!
void skillsAutonomous(){
	int TIME_INTAKE = 100;
	int TIME_OUTTAKE = 300;
	int TIME_WAIT_BAR = 100;
	int TIME_ARM_STASH = 250;
	int TIME_ARM_STASH_RETURN = 250;
	int DIST_OVER_BUMP = 1000;
	int DIST_2_BALLS = 600;
	int DIST_RB1 = 550;
	int DIST_STASH_1 = 1500;
	int DIST_STASH_2 = 300;
	int DIST_RH1 = 1700;
	int DIST_BACK_CROSS = 680;
	int ROTATE_RH1 = 300;
	int DIST_RB2 = 550;
	int TURN_LASTDITCH = 300;
	int DIST_LASTDITCH = 1000;


	//start in middle zone Red with preload in robot (other red preload in corner of hanging zone alliance tile)
	//setArmAuto(ARM_GOAL_BUMP);
	waitForPress();
	//go over bump
	moveWait(DIST_OVER_BUMP);
	//lower arm and pick up two bucky balls on wall
	setArmAuto(ARM_GOAL_BASE);
	startIntake();
	moveWait(DIST_2_BALLS);
	wait1Msec(TIME_INTAKE);
	stopIntake();
	//go back to RH
	setArmAuto(ARM_GOAL_BUMP);
	moveWait(-DIST_2_BALLS);
	waitForPress();
	////cross bump and bump off RB1
	//moveWait(DIST_OVER_BUMP);
	//setArmAuto(ARM_GOAL_BAR);
	//moveWait(DIST_RB1);
	////return to RM
	//move(-DIST_RB1, 127, false);
	//wait1Msec(TIME_WAIT_BAR);
	//setArmAuto(ARM_GOAL_BASE);
	//waitForPress();
	////stash 3 buckyballs
	//moveWait(DIST_STASH_1);
	//setArmAuto(ARM_GOAL_TOP);
	//wait1Msec(TIME_ARM_STASH);
	//moveWait(DIST_STASH_2);
	//startOuttake();
	//wait1Msec(TIME_OUTTAKE);
	//stopIntake();
	////return
	//setArmAuto(ARM_GOAL_BASE);
	//moveWait(-DIST_STASH_2);
	//wait1Msec(TIME_ARM_STASH_RETURN);
	//moveWait(-DIST_STASH_1);
	////cross bump
	//setArmAuto(ARM_GOAL_BUMP);
	//waitForPress();
	//moveWait(DIST_OVER_BUMP);
	//setArmAuto(ARM_GOAL_BASE);
	////run other autonomous
	//waitForPress();
	////start parallel to bump
	//startIntake();
	//moveWait(DIST_RH1);
	//moveWait(-DIST_BACK_CROSS);
	//stopIntake();
	//setArmAuto(ARM_GOAL_BUMP);
	//rotateWait(ROTATE_RH1, -1);
	//moveWait(DIST_OVER_BUMP);
	//setArmAuto(ARM_GOAL_BAR);
	//moveWait(DIST_RB2);
	//startOuttake();
	////back up to bump to align
	//moveWait(-DIST_RB2);
	////turn with one side and bump ball off
	//moveLR(TURN_LASTDITCH, 0, 127, 127, true);
	//moveWait(DIST_LASTDITCH);
}

/*description: this process starts with a preload, intakes two bucky balls,
drops them over the bump, and pushes over three other buckyballs. Scores 6-12 points.
*/
//red = 1; blue = -1
void A1(int color){
	int DIST_TO_BALLS = 600;
	int DIST_TO_TURN = 1000;
	int TURN = 340;
	int DIST_OVER_BUMP= 250;

	startIntake();
	moveWait(DIST_TO_BALLS);
	moveWait(-DIST_TO_BALLS-200);
	stopIntake();
	waitForPress();
	setArmAuto(ARM_GOAL_BAR);
	moveWait(DIST_TO_TURN);
	rotateWait(TURN, -color);
	wait1Msec(250);
	startOuttake();
	setArmAuto(ARM_GOAL_BAR);
	wait1Msec(250);
	moveWait(DIST_OVER_BUMP);
}

/*descripton: tstartIntakerocess starts with a preload ,
knocks two large balls off of the barrier,
and takes a bucky ball to the goalzone. Scores 10-15 points.
*/
//1 = red side; -1 = blue side
void B1(int color){
	int DIST_TO_BARRIER1 = 550;
	int DIST_TO_BARRIER2 = 950;  // BARRIER2 is at an angle and distances may be adjusted and be different
	int DIST_TO_STASH1 = 1500;
	int DIST_TO_STASH2 = 300;
	int DIST_FINISH = 200;
	int DIST_ROTATE = 400;
	int TIME_DUMP = 1500;
	int TURN = 300;

	setArmAuto(ARM_GOAL_BAR);
	waitForPress();
	moveWait(DIST_TO_BARRIER1);
	startOuttake();
	wait1Msec(TIME_DUMP);
	stopIntake();
	moveWait(-(DIST_TO_BARRIER1-300)); //turn robot
	waitForPress ();
	moveWait(DIST_TO_BARRIER2);
	rotateWait(TURN, -color);
	moveWait(DIST_TO_BARRIER1);
	//move(-POWER,DIST_TO_BARRIER2-400, 0, 80); //maybe only half the distance??
	//StartTask(armBase);
	//waitForPress();
	//move(POWER,DIST_TO_STASH1, 0, 0);
	//StartTask(armTop);
	//wait1Msec(250);
	//move(POWER, DIST_TO_STASH2,0 ,0);
	//startOuttake();
}

/*descripton: tstartIntakerocess starts with a preload ,
knocks two large balls off of the barrier,
and takes a bucky ball to the goalzone. Scores 10-15 points.
*/
//1 = red side; -1 = blue side
void B2(int color){
	int DIST_TO_BARRIER1 = 550;
	int DIST_TO_BARRIER2 = 950;  // BARRIER2 is at an angle and distances may be adjusted and be different
	int DIST_TO_STASH1 = 1500;
	int DIST_TO_STASH2 = 300;
	int DIST_FINISH = 200;
	int DIST_ROTATE = 400;
	int TIME_DUMP = 1500;
	int TURN = 300;

	StartTask(lastMinDump);
	setArmAuto(ARM_GOAL_BAR);
	waitForPress();
	moveWait(DIST_TO_BARRIER1);
	moveWait(-(DIST_TO_BARRIER1-300)); //turn robot
	waitForPress();
	moveWait(DIST_TO_BARRIER2);
	moveWait(-(DIST_TO_BARRIER2-400)); //maybe only half the distance??
	wait1Msec(200);
	setArmAuto(ARM_GOAL_BASE);
	waitForPress();
	moveWait(DIST_TO_STASH1);
	setArmAuto(ARM_GOAL_TOP);
	wait1Msec(250);
	moveWait(DIST_TO_STASH2);
	startOuttake();
	StopTask(lastMinDump);
	wait1Msec(TIME_DUMP);

}



//red = 1, blue = -1
void A3(int color){
	int DIST_TO_BALL = 1700;
	int DIST_BACK = 680;
	int ROTATE_DIST = 300;
	int DIST_TO_BUMP = 1500;

	//start parallel to bump
	startIntake();
	moveWait(DIST_TO_BALL);
	moveWait(-DIST_BACK);
	stopIntake();
	rotateWait(ROTATE_DIST, -color);
	setArmAuto(ARM_GOAL_BAR);
	wait1Msec(750);
	moveWait(DIST_TO_BUMP);
	startOuttake();
}
