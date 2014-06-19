






int cutOff = 20;
void setMotors(int leftPower, int rightPower){
	if(abs(leftPower) <= cutOff){
		leftPower = 0;
	}
	if(abs(rightPower) <= cutOff){
		rightPower = 0;
	}
	motor[Backleft] = leftPower;
	motor[Backright] = rightPower;
	motor[Frontleft] = leftPower;
	motor[Frontright] = rightPower;
}

task main()
{



}
