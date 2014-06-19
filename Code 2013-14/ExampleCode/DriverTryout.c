#include "Functions/ChassisFunctions.c"
#include "Functions/ArmFunctions.c"

//void driverMaster(){
//	controlDriveTank(Ch3Xmtr2, Ch2Xmtr2, 105, 2);

//	controlArm(Btn6DXmtr2, Btn6UXmtr2, Btn8DXmtr2, Btn8UXmtr2, Btn8RXmtr2, Btn8LXmtr2);

//	controlIntake(Btn5UXmtr2, Btn5DXmtr2, Btn7RXmtr2, Btn7DXmtr2);
//}

//void driverNathan(){
//	controlDriveArcade(Ch3, Ch4, 105, 1.7);

//	controlIntake(Btn5U, Btn5D, Btn7R, Btn7D);

//	controlArm(Btn6D, Btn6U,Btn8D, Btn8U, Btn8R, Btn8L);

//}

void driverJoseph(){
	controlDriveTank(Ch3, Ch2, 105, 2, 20, Btn7R);

	controlArm(Btn6D, Btn6U, Btn8D, Btn8U, Btn8L, Btn8R);

	controlIntake(Btn5U, Btn5D, Btn7R, Btn7D);
}

//void driverConnor(){
//	controlDriveArcade(Ch3, Ch1, 105, 2);

//	controlIntake(Btn5U, Btn5D, Btn7R, Btn7D);

//	controlArm(Btn5U, Btn6U,Btn8D, Btn8U, Btn8R, Btn8L);
//}
/*
task main()
{
	int masterButton = Btn8DXmtr2;
	int masterVal = 0;
	int masterOldVal = 0;
	int masterState = 0; //0 = slave; 1 = master

	wait1Msec(250);
	while(true){
		/*masterVal = vexRT[masterButton];
		if(masterVal == 1 && masterOldVal == 0){
			masterState = 1 - masterState;
		}

		masterState = 0;
		if(masterState == 1){
			driverMaster();
		}else{
			driverNathan();
		}
		masterOldVal = masterVal;
	}
}
*/
