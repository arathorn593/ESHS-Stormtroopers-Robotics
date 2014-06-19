//functions for driver control
#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Code 2.0\structRobot.c"
#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Code 2.0\globalComVars.c"


//direction: 1 = up, -1 = down
void moveArm(int goal){
	adam.armPriority = ARM_PRIORITY_AUTO;
	adam.armGoal = goal;
}

void armLower(){
	moveArm(ARM_GOAL_BASE);
}

void armRaise(){
	moveArm(ARM_GOAL_TOP);
}

void armBar(){
	moveArm(ARM_GOAL_BAR);
}

void armBump(){
	moveArm(ARM_GOAL_BUMP);
}


//distance = encoder value, positive or negative based on direction
void move(int power, int distance){
	if(adam.chasPriority = CHAS_PRIORITY_FREE){
		adam.chasPriority = CHAS_PRIORITY_AUTO;
		adam.chasLeftPower = power;
		adam.chasRightPower = power;
		adam.chasLeftGoal = adam.chasLeftPos + distance;
		adam.chasRightGoal = adam.chasRightPos + distance;
	}
}

/*!!!!!!!move and rotate functions look very simmilar, change?
*/
//distance = encoder value; direction: 1 = right, -1 = left
void rotate(int power, int distance, int direction){
	if(adam.chasPriority = CHAS_PRIORITY_FREE){
		adam.chasPriority = CHAS_PRIORITY_AUTO;
		adam.chasLeftPower = power;
		adam.chasRightPower = power;
		adam.chasLeftGoal = adam.chasLeftPos + distance * direction;
		adam.chasRightGoal = adam.chasRightPos + distance * direction * -1;
	}
}
