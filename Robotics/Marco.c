#pragma config(Motor,  port2,           frontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port4,           frontRight,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           backRight,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
 while(true)
  {
    if (abs(vexRT[Ch3])>25)
    {
      motor[frontLeft] = (vexRT[Ch3]);
      motor[backLeft] = (vexRT[Ch3]);

    }
    else
    {
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
    }

    if (abs(vexRT[Ch2])>25)
    {
      motor[frontRight] = (vexRT[Ch2]);
      motor[backRight] = (vexRT[Ch2]);
    }

        else
    {
      motor[frontRight] = 0;
      motor[backRight] = 0;
    }

}
}