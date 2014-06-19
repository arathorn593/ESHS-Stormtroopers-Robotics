#pragma config(Sensor, in1,    potent1,             sensorPotentiometer)
#pragma config(Sensor, in6,    lineLeft,            sensorLineFollower)
#pragma config(Sensor, in7,    lineMiddle,          sensorLineFollower)
#pragma config(Sensor, in8,    lineRight,           sensorLineFollower)
#pragma config(Sensor, dgtl1,  touch,               sensorTouch)
#pragma config(Sensor, dgtl2,  sonar,               sensorSONAR_inch)
#pragma config(Sensor, dgtl4,  encoderRight,        sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  encoderLeft,         sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  beltTouch,           sensorTouch)
#pragma config(Sensor, dgtl9,  encoderArm,          sensorQuadEncoder)
#pragma config(Motor,  port1,           middleFront,   tmotorNormal, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           liftRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port8,           beltRight,     tmotorNormal, openLoop)
#pragma config(Motor,  port9,           beltLeft,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          middleBack,    tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
task main ()
{
   while(SensorValue[touch] == 0)                           //drop arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
  motor[liftLeft] = 0;
  motor[liftRight] = 0;

 SensorValue[encoderArm] = 0;                          //reset arm encoder
while (true)
	{



          if( abs(vexRT[Ch2]) > 50)
      {                //threshold for right side
      motor[frontRight] = (vexRT[Ch2]);
      motor[backRight] = (vexRT[Ch2]);
    }
    else{
      motor[frontRight] = 0;
      motor[backRight] = 0;
    }

    if( abs(vexRT[Ch3]) > 50){         //threshold for left side
      motor[frontLeft] = (vexRT[Ch3]);
      motor[backLeft] = (vexRT[Ch3]);
    }
    else{
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
    }


    if((vexRT[Btn8L]) == 1)  //runs center omni wheels for crabing
      {
      motor[middleFront] = -127;
      motor[middleBack]= -127;
      }
    else
      {
          if((vexRT[Btn8R]) == 1)
            {
              motor[middleFront] = 127;
              motor[middleBack]= 127;
            }
          else
            {
              motor[middleFront] = 0;
              motor[middleBack] = 0;
            }
      }

      if ((vexRT[Btn8U])==1)
      {
        while ((SensorValue[encoderArm]) < 100)
        {
          motor[liftRight] = 127;
          motor[liftLeft]= 127;

     if( abs(vexRT[Ch2]) > 50)
      {                                     //threshold for right side
      motor[frontRight] = (vexRT[Ch2]);
      motor[backRight] = (vexRT[Ch2]);
    }
    else{
      motor[frontRight] = 0;
      motor[backRight] = 0;
    }

    if( abs(vexRT[Ch3]) > 50){         //threshold for left side
      motor[frontLeft] = (vexRT[Ch3]);
      motor[backLeft] = (vexRT[Ch3]);
    }
    else{
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
    }
  }
  else
{
 if ((vexRT[Btn8D])==1)
      {
        while ( (SensorValue[touch])==0)
        {
          motor[liftRight] = -127;
          motor[liftLeft]= -127;

     if( abs(vexRT[Ch2]) > 50)
      {                                     //threshold for right side
      motor[frontRight] = (vexRT[Ch2]);
      motor[backRight] = (vexRT[Ch2]);
    }
    else{
      motor[frontRight] = 0;
      motor[backRight] = 0;
    }

    if( abs(vexRT[Ch3]) > 50){         //threshold for left side
      motor[frontLeft] = (vexRT[Ch3]);
      motor[backLeft] = (vexRT[Ch3]);
    }
    else{
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
    }
  }

}
    if((vexRT[Btn8L]) == 1)  //runs center omni wheels for crabing
      {
      motor[middleFront] = -127;
      motor[middleBack]= -127;
      }
    else
      {
          if((vexRT[Btn8R]) == 1)
            {
              motor[middleFront] = 127;
              motor[middleBack]= 127;
            }
          else
            {
              motor[middleFront] = 0;
              motor[middleBack] = 0;
            }
      }

    if((vexRT[Btn6D]) == 1)
      {                                     //this segment runs the arm lift
      if(SensorValue[touch]==1)
        {
          motor[liftRight] = 0;
           motor[liftLeft] = 0;
        }
      else
        {
      motor[liftRight] = -127;
      motor[liftLeft]= -127;
        }
      }
     else{
    if((vexRT[Btn6U]) == 1)
      {
      motor[liftRight] = 127;
      motor[liftLeft]= 127;
    }
    else
      {
      motor[liftRight] = 0;
      motor[liftLeft] = 0;
    }



  }


    if((vexRT[Btn5U]) == 1)  //Conveyer Control
      {
      motor[beltLeft] = 127;
      motor[beltRight]=127;
      }
    else
      {
          if((vexRT[Btn5D]) == 1)
            {
              motor[beltLeft] = -127;
              motor[beltRight]= -127;
            }
          else
            {
              motor[beltLeft] = 0;
              motor[beltRight] = 0;
            }
      }

}

}
