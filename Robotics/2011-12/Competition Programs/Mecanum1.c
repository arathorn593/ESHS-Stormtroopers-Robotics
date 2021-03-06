#pragma config(Motor,  port2,           frontLeft,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port5,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           armLeft,       tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           armRight,      tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main ()
{
 while(true)
 {
     if((vexRT[Btn7R]) == 1)
     {
      motor[frontLeft] = 127;
      motor[frontRight] = -127;
      motor[backLeft] = -127;
      motor[backRight] = 127;
    }

    else if ((vexRT[Btn7L]) == 1)
    {
      motor[frontLeft] = -127;
      motor[frontRight] = 127;
      motor[backLeft] = 127;
      motor[backRight] = -127;
    }
     else if(abs(vexRT[Ch2]) >30 || abs(vexRT[Ch3]) >30)
  {

      motor[frontLeft] = (vexRT[Ch3]);
      motor[frontRight] = (vexRT[Ch2]);
      motor[backLeft] = (vexRT[Ch3]);
      motor[backRight] = (vexRT[Ch2]);
 }
     else
    {
      motor[frontLeft] = 0;
      motor[frontRight] = 0;
      motor[backLeft] = 0;
      motor[backRight] = 0;

    }

     if((vexRT[Btn5U]) == 1)  //intake control
      {

      motor[armLeft] = 127;
      motor[armRight]=127;

      }
    else
      {
          if((vexRT[Btn5D]) == 1)
            {
      motor[armLeft] = -127;
      motor[armRight]= -127;

            }
          else
            {
      motor[armLeft] = 0;
      motor[armRight]= 0;

            }
      }

}
}
