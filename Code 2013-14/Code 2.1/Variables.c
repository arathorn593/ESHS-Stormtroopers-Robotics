#include "Structures.c"
#include "MotorFunctions.c"
/*
STYLE GUIDE FOR CODE 2.1
	Abreviations:
		buf = buffer
		ch = channel
		chas = chassis
		drv = drive
		enc = encoder
		init = initial
		joy = joystick
		pri = priority
		pset = preset
		pwr = power
		spd = speed
	Variable Naming:
		AreaOfRobot Function Side(if any)
		ex. ChasPwrLeft
*/
#define ARM_GOAL_NONE -1
#define ARM_GOAL_TOP -2
#define ARM_GOAL_BASE -3
#define ARM_GOAL_BUMP 1100
#define ARM_GOAL_BAR 1900
#define ARM_PWR 127
#define ARM_PSET_BUF 3
#define PUNCH_TIME 30 //in centiseconds
#define PUNCH_CHAS_TIME 25//in centiseconds time before punch
#define PUNCH_CHAS_PWR 127
//chas
//minimum milliseconds between chassis speed calculations
#define CHAS_SPD_DELAY 1

#define CHAS_GOAL_NONE 0
#define CHAS_GOAL_BUF 10

//other
//joystick value that registers as a button push
#define JOY_BUTTON 110
#define PRI_LIVE 0
#define PRI_PSET 1
#define PRI_AUTO 2
#define PRI_NONE 3
#define INTK_PWR 127

#define PUNCH_BACK 0
#define PUNCH_ACTIVE 1
#define PUNCH_FORWARD 2

//constants for accel calculations
#define Vref 5.0
#define Sensitivity 0.3
#define ARM_TIP 1700
#define CHAS_TIP_SPD 127
#define MV_TIP_ANG 15 //tip angle when moving
#define STP_TIP_ANG MV_TIP_ANG//tip angle when stopped
#define Y_ANG_RANGE 5 //the -\+range of y angles that register as reasonable
int tipAng = 20;
float initYAng = -1;


Robot adam;

void initRobot(Robot *robot, bool chasSpdVal){
	(*robot).chasSpd = chasSpdVal;
	(*robot).armPri = PRI_NONE;
	(*robot).chasPri = PRI_NONE;
	(*robot).armGoal = -1; // makes sure the robot doesn't start lowering the arm right away
}
