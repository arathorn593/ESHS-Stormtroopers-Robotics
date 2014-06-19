#include "ArmFunctions.c"
#include "ChassisFunctions.c"
#include "MotorFunctions.c"
#include "MiscFunctions.c"
/*These functions are named by the starting tile (A or B) and a number
ex. A1 or B3.
A is in the non-scoring zone, B is in the middle zone
*/

//////////////////////CONSTANTS////////////////////////////
int POWER = 127;
int DIST_TO_STASH = 700;


///////////////////////FUNCTIONS///////////////////////////
/*description: this process starts with a preload, intakes two bucky balls,
drops them over the bump, and pushes over three other buckyballs. Scores 6-12 points.
*/
//red = 1; blue = -1
void A1(int color){
	int DIST_TO_BALL = 1500;
	int DIST_BACK = 480;
	int ROTATE_DIST = 300;
	int DIST_TO_BUMP = 1100;

	//start parallel to bump
	startIntake();
	move(POWER, DIST_TO_BALL, 0, 0, true);
	move(-POWER, DIST_BACK, 0, 0, true);
	stopIntake();
	rotate(POWER, ROTATE_DIST, -color, true);
	StartTask(armBar);
	wait1Msec(750);
	move(POWER, DIST_TO_BUMP, 0, 0, false);
	movePPunch(1);
}

/*descripton: tstartIntakerocess starts with a preload ,
knocks two large balls off of the barrier,
and takes a bucky ball to the goalzone. Scores 10-15 points.
*/
//1 = red side; -1 = blue side
void B1(int color){
	int DIST_TO_BARRIER1 = 250;
	int DIST_TO_BARRIER2 = 300;  // BARRIER2 is at an angle and distances may be adjusted and be different
	int DIST_TO_STASH1 = 1500;
	int DIST_TO_STASH2 = 300;
	int DIST_FINISH = 200;
	int DIST_ROTATE = 400;
	int TIME_DUMP = 1500;
	int TURN = 300;

	StartTask(lastMinDump);
	StartTask(armBar);
	waitForPress();
	move(POWER,DIST_TO_BARRIER1,0 ,0, true);
	startOuttake();
	wait1Msec(TIME_DUMP);
	stopIntake();
	move(-POWER,DIST_TO_BARRIER1-50, 0, 0, true); //turn robot
	waitForPress ();
	move(POWER,DIST_TO_BARRIER2, 0, 0, true);
	rotate(POWER, TURN, -color, true);
	move(POWER, DIST_TO_BARRIER1, 0, 0,true);
	//move(-POWER,DIST_TO_BARRIER2-400, 0, 80); //maybe only half the distance??
	//StartTask(armBase);
	//waitForPress();
	//move(POWER,DIST_TO_STASH1, 0, 0);
	//StartTask(armTop);
	//wait1Msec(250);
	//move(POWER, DIST_TO_STASH2,0 ,0);
	//startOuttake();
}

/* description: this process does not have a preload, collects the three
bucky balls off of the bump, and stashes them in the goal. Scores 15 points.
*/
/*
void A2(){
int DIST_TO_BALLS = 400;
int BACKUP = 150; //robot backs up to go over bump
int DIST_TO_BARRIER = 1130;
int DIST_GOAL_ZONE = 400;

moveArm(1,ARM_TIME_BUMP);
move(POWER, DIST_TO_BALLS);
movePIntake(1);
move(-POWER,BACKUP); //need turn??
move(POWER,DIST_TO_BARRIER);
moveArm(-1,ARM_TIME_BARRIER);
move(POWER,DIST_GOAL_ZONE);
startOuttake();
}
*/
/* description: takes preload and stashes. Scores 5 points.
*/

void B2(int color){
	int TRANSFER = 1000;
	int DIST_TO_BALLS = 200;
	int DIST_TO_STASH1 = 850;
	int DIST_TO_STASH2 = 150;
	int DIST_TO_BARRIER1 = 250;
	int DIST_TO_BARRIER2 = 700;  // BARRIER2 is at an angle and distances may be adjusted and be different
	int TURN_BARRIER3 = 200;
	int DIST_BARRIER3 = 400;

	int DIST_FINISH = 200;
	int DIST_ROTATE = 400;
	int TIME_DUMP = 1500;
	int TURN = 300;

	StartTask(lastMinDump);
	StartTask(armBar);
	waitForPress();
	move(POWER,DIST_TO_BARRIER1,0 ,0, true);
	move(-POWER,DIST_TO_BARRIER1-300, 0, 0, true); //turn robot
	waitForPress ();
	move(POWER,DIST_TO_BARRIER2, 0, 0, true);
	rotate(POWER, TURN, -color, true);
	move(POWER, DIST_TO_BARRIER1, 0, 0,true);
	move(-POWER, DIST_TO_BARRIER1, 0, 0, true);
	StartTask(armBase);
	rotate(POWER, TURN, color, true);
	move(-POWER,DIST_TO_BARRIER2, 0, 0, true);

	waitForPress();
	move(DIST_TO_STASH1, true);
	StartTask(armTop);
	wait1Msec(250);
	move(DIST_TO_STASH2, true);
	startOuttake();
}

//red = 1, blue = -1
void A3(int color){
	int DIST_TO_BALL = 1500;
	int DIST_BACK = 480;
	int ROTATE_DIST = 300;
	int DIST_TO_BUMP = 1350;

	//start parallel to bump
	startIntake();
	move(POWER, DIST_TO_BALL, 0, 0, true);
	move(-POWER, DIST_BACK, 0, 0, true);
	stopIntake();
	rotate(POWER, ROTATE_DIST, -color, true);
	StartTask(armBar);
	wait1Msec(750);
	move(POWER, DIST_TO_BUMP, 0, 0, false);
	startOuttake();
}

//void skills(){
//	int TRANSFER = 550;
//	int DIST_TO_BALLS = 300;
//	int DIST_TO_BARRIER1 = 550;
//	int DIST_TO_STASH1 = 1200;
//	int DIST_TO_STASH2 = 350;
//	int TIME_DUMP = 750;

//	//preload and big ball in scoring zone.
//	StartTask(armBar);
//	waitForPress();
//	move(POWER,DIST_TO_BARRIER1,0 ,0, false);
//	startOuttake();
//	wait1Msec(TIME_DUMP);
//	stopIntake();
//	move(-POWER,DIST_TO_BARRIER1-300, 0, 0, false); //turn robot
//	StartTask(armBump);
//	waitForPress ();
//	//pick up other preload and 2 bucky balls
//	startIntake();
//	move(POWER, TRANSFER, 0, 0, false);
//	lowerArm();
//	waitForPress();
//	startIntake();
//	move(POWER, DIST_TO_BALLS, 0, 0, false);
//	move(-POWER, DIST_TO_BALLS - 100, 0, 0, false);
//	stopIntake();
//	StartTask(armBump);
//	waitForPress();
//	//stash those 3
//	move(POWER, TRANSFER, 0, 0, false);
//	StartTask(armBase);
//	waitForPress();
//	move(POWER,DIST_TO_STASH1, 0, 0, false);
//	raiseArm();
//	move(POWER, DIST_TO_STASH2,0 ,0, false);
//	startOuttake();
//	wait1Msec(1000);
//	//go back and A3.
//	stopIntake();
//	move(-POWER, DIST_TO_STASH2, 0, 0, false);
//	lowerArm();
//	move(-POWER, DIST_TO_STASH1, 0, 0, false);
//	StartTask(armBump);
//	waitForPress();
//	move(POWER, TRANSFER, 0, 0, false);
//	StartTask(armBase);
//	waitForPress();
//	A3(-1);

//}


void skillsAutonomous(){
	int TRANSFER = 1000;
	int DIST_TO_BALLS = 200;
	int DIST_TO_STASH1 = 850;
	int DIST_TO_STASH2 = 150;
	int DIST_TO_BARRIER1 = 250;
	int DIST_TO_BARRIER2 = 700;  // BARRIER2 is at an angle and distances may be adjusted and be different
	int TIME_DUMP = 1000;
	int TURN_BARRIER3 = 200;
	int DIST_BARRIER3 = 400;

	lowerArm();
	startIntake();
	move(100, DIST_TO_BALLS, 0, 0, false);
	wait1Msec(1000);
	move(-100, DIST_TO_BALLS - 50, 0, 0, false);
	stopIntake();
	StartTask(armBar);
	waitForPress();
	move(POWER, TRANSFER-300, 0, 0, false);
	waitForPress();
	move(POWER,DIST_TO_BARRIER1,0 ,0, true);
	move(-POWER,DIST_TO_BARRIER1-100, 0, 0, true); //turn robot
	StartTask(armBase);
	waitForPress ();
	move(POWER,DIST_TO_STASH1, 0, 0, false);
	raiseArm();
	move(POWER, DIST_TO_STASH2,0 ,0, false);
	startOuttake();
	wait1Msec(TIME_DUMP);
	//go back and A3.
	stopIntake();
	move(-POWER, DIST_TO_STASH2, 0, 0, false);
	lowerArm();
	move(-POWER, DIST_TO_STASH1-100, 0, 0, false);
	StartTask(armBump);
	waitForPress();
	move(POWER, TRANSFER, 0, 0, false);
	StartTask(armBase);
	waitForPress();
	A3(1);
	wait1Msec(500);
	move(-POWER, DIST_TO_BARRIER1, 0, 0, true);
	rotate(POWER, TURN_BARRIER3, 1, true);
	move(POWER, DIST_BARRIER3, 0, 0, true);
	//int TIME_INTAKE = 100;
	//int TIME_OUTTAKE = 300;
	//int TIME_WAIT_BAR = 100;
	//int TIME_ARM_STASH = 250;
	//int TIME_ARM_STASH_RETURN = 250;
	//int DIST_OVER_BUMP = 1000;
	//int DIST_2_BALLS = 600;
	//int DIST_RB1 = 550;
	//int DIST_STASH_1 = 1500;
	//int DIST_STASH_2 = 300;
	//int DIST_RH1 = 1700;
	//int DIST_BACK_CROSS = 680;
	//int ROTATE_RH1 = 300;
	//int DIST_RB2 = 550;
	//int TURN_LASTDITCH = 300;
	//int DIST_LASTDITCH = 1000;


	////start in middle zone Red with preload in robot (other red preload in corner of hanging zone alliance tile)
	////setArmAuto(ARM_GOAL_BUMP);
	//waitForPress();
	////go over bump
	//moveWait(DIST_OVER_BUMP);
	////lower arm and pick up two bucky balls on wall
	//setArmAuto(ARM_GOAL_BASE);
	//startIntake();
	//moveWait(DIST_2_BALLS);
	//wait1Msec(TIME_INTAKE);
	//stopIntake();
	////go back to RH
	//setArmAuto(ARM_GOAL_BUMP);
	//moveWait(-DIST_2_BALLS);
	//waitForPress();
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
