#pragma config(Motor,  port1,           intakeLeft,    tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393, openLoop)
#pragma config(Motor,  port4,           backRight,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port10,          intakeRight,   tmotorVex269, openLoop)

task main()
{
 while(true)
 {
 if (vexRT[Btn6U]==1)                      //this make the chasisi go left and right
  {
   motor[frontRight]=-127;
   motor[backRight]=127;
   motor[frontLeft]=127;
   motor[backLeft]=-127;
  }
  else
  {
   if(vexRT[Btn5U]==1)
   {
     motor[frontRight]=127;
     motor[backRight]=-127;
     motor[frontLeft]=-127;
     motor[backLeft]=127;
    }
    else                                    //this makes the the wheels turnn regularly
    {
     if (abs(vexRT[Ch3]) >50)
      {
      motor[frontLeft]=vexRT[Ch3];
      motor[backLeft]=vexRT[Ch3];
    }
    else
    {
      motor[frontLeft]=0;
      motor[backLeft]=0;
   }

   if (abs(vexRT[Ch2]) >50)
   {
    motor[frontRight]=vexRT[Ch2]-10;
    motor[backRight]=vexRT[Ch2]-10;
   }
   else
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            //:)
  {
     motor[frontRight]=0;
     motor[backRight]=0;
    }
    }
  }
  if(vexRT[Btn8U] == 1)                       //this part makes the intake start
  {
   motor[intakeLeft] = 127;
   motor[intakeRight] = 127;
  }
  else
  {
    if(vexRT[Btn8D] == 1)
    {
    motor[intakeLeft] = -127;
    motor[intakeRight] = -127;
  }
  else
{
    motor[intakeLeft] = 0;
    motor[intakeRight] = 0;
  }
  }
 }
}
