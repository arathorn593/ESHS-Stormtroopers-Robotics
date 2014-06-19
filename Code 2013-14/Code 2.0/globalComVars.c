//this file contains all of the global variables that serve as a communication link between tasks

#include "C:\Documents and Settings\Robot\Desktop\StormTroopers\Code 2013-14\Code 2.0\structRobot.c"
//create robot structure and initialize
Robot adam;	//the robot is named adam after our choir director as pennance for letting some of our team miss choir a lot....


//pid stuff
//adam.pidSpeed.Kp = 2;
//adam.pidSpeed.Ki = 0.01;
//adam.pidSpeed.Kd = 0;
///////////////////constants////////////////////////////
const int ARM_PRESET_BUFFER = 3;
const int JOYSTICK_BUTTON = 110; //the value a joystick has to be above for it to register in the code as a boolean true
const int ARM_GOAL_BASE = -3;
const int ARM_GOAL_TOP = -2;
const int ARM_GOAL_NONE = -1;
const int ARM_GOAL_UP = -4;
const int ARM_GOAL_DOWN = -5;
const int ARM_GOAL_BAR = 300;
const int ARM_GOAL_BUMP = 50;
const int ARM_PRIORITY_LIVE = 2;	//priority to higher values
const int ARM_PRIORITY_AUTO = 1;
const int ARM_PRIORITY_FREE = 0;
const int ARM_BASE_POWER = 127;
const int CHAS_PRIORITY_LIVE = 2;
const int CHAS_PRIORITY_AUTO = 1;
const int CHAS_PRIORITY_FREE = 0;
const int CHAS_AUTO_BUFF = 0;
const int CH_ACTIVE = 0;
const int CH_CURRENT = 1; //used with channels[][] array so you don't have to remember it
const int CH_OLD = 2;
const int INTAKE_POWER = 127;
const int CH_ARRAY_LENGTH = sizeof(adam.channels)/sizeof(adam.channels[0]);

void initializeAdam(){
	adam.armTouchTop = touchTop;
	adam.armTouchBottom = touchBottom;
	adam.armPot = armPotentiometer;
	adam.chasLeftEncoder = encoderL;
	adam.chasRightEncoder = encoderR;
	SensorValue[adam.chasRightEncoder] = 0;
	SensorValue[adam.chasLeftEncoder] = 0;
	adam.chasPriority = CHAS_PRIORITY_FREE;
	adam.armPriority = ARM_PRIORITY_FREE;

	//for some reason, the robot starts with some values and I don't know why, this is trying to flush those out
	for(int index = 0; index < CH_ARRAY_LENGTH; index++){
		adam.channels[index][CH_CURRENT] = vexRT[index];
	}
	for(int index = 0; index < CH_ARRAY_LENGTH; index++){
		adam.channels[index][CH_CURRENT] = 0;
	}
}
