//This file holds all the stuff to create and update the robot structure
const int ARM_STOPPED = 0;
const int ARM_AUTO = 1;
const int ARM_LIVE_DRIVER = 2;


typedef struct{
	bool activated;
	float Kp;
	float Ki;
	float Kd;
	float setPoint;
	float currentVal;
	int curTime;
	int oldTime;
	int dT;
	float error;
	float oldError;
	float integral;
	float change;
} pid;

typedef struct{
	int x; 	//feet from red hanging corner
	int y; 	//feet from red haning corner
	int direction;	//degrees
	int tilt; 			//degrees
} position;

typedef struct{
	int chasLeftPower;
	int chasRightPower;
	int chasLeftPos;
	int chasRightPos;
	int chasLeftGoal;
	int chasRightGoal;
	int chasPriority;

	int armPower;
	int armGoal;
	int armPos;
	int armPriority;
	int armTop;			//hit the top? 1 or 0	//!!!!!!!!!!!these still need to be implemented
	int armBottom;	//hit the bottom? 1 or 0

	int intakePower;

	tSensors armTouchTop;
	tSensors armTouchBottom;
	tSensors armPot;
	tSensors chasLeftEncoder;
	tSensors chasRightEncoder;

	int channels[38][3]; //holds current and past channel values.
											 //0-15 in the first dimension are the channel identifiers
											 //second dimension: 0 = activated(1) or not(0); 1 = current val; 2 = oldVal
	pid pidSpeedLeft;
	pid pidSpeedRight;
	pid pidAngle;
} Robot;
