#pragma config(Motor,  port2,           frontLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           middle,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           center,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main ()
{

  while(1 == 1)
  {
    if((vexRT[Btn6U]) == 0)
    {
      motor[frontRight]  = (vexRT[Ch2Xmtr2]);
      motor[backRight] = (vexRT[Ch2Xmtr2]);
      motor[frontLeft] = (vexRT[Ch3Xmtr2]);
      motor[backLeft] = (vexRT[Ch3Xmtr2]);

  }
  else if((vexRT[Btn6U]) == 1)
  {
    motor[frontRight]  = (vexRT[Ch2]);
      motor[backRight] = (vexRT[Ch2]);
      motor[frontLeft] = (vexRT[Ch3]);
      motor[backLeft] = (vexRT[Ch3]);


  }
      }
}