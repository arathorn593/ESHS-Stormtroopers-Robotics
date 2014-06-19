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

task main
{
   int leftAdjust = 0;
   int rightAdjust = -48;

   int distance = 725;
   int doublerDistance = 930;
   int shortStackDistance = 300;
   int redSquareDistance = 675;
   int homeDistance = 1400;
   while(SensorValue[touch] == 0)                           //drop arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
  motor[liftLeft] = 0;
    motor[liftRight] = 0;

    SensorValue[encoderArm] = 0;                          //reset arm encoder
                                                          //program starts


    while(SensorValue[beltTouch] == 0)                    //wait for button
    {
      if (SensorValue[encoderArm] < 100)
      {
        motor[liftLeft] = 127;                               //lift arm
        motor[liftRight] = 127;
      }
      else
      {
        motor[liftLeft] = 0;                               //stop arm
        motor[liftRight] = 0;
      }
    }
    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;
    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < distance)      //drive to goal
    {
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;
      if(SensorValue[encoderArm] < 100)
      {
        motor[liftLeft] = 127;                                //lift arm
        motor[liftRight] = 127;
      }
      else
      {
        motor[liftLeft] = 0;
        motor[liftRight] = 0;
      }

    }

    motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

    motor[beltLeft] = -127;                                                         //dump objects
    motor[beltRight] = -127;
    wait1Msec(3000);
    motor[beltLeft] = 0;
    motor[beltRight] = 0;


      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

      wait1Msec(1000);

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

     if(SensorValue[touch] == 0)                                             //lower arm
      {
       motor[liftLeft] = -127;
       motor[liftRight] = -127;
      }
      else
      {
       motor[liftLeft] = -127;
       motor[liftRight] = -127;
      }
}

      motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;


   while(SensorValue[touch] == 0)                                             //lower arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
    motor[liftLeft] = 0;
    motor[liftRight] = 0;
    SensorValue[encoderArm] = 0;
    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;
     while(SensorValue[beltTouch] == 0)                                       //wait for button
    {
    }


      while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < doublerDistance)           //get doubler
    {
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;
      motor[beltLeft] = 127;
      motor[beltRight] = 127;

    }
      motor[beltLeft] = 0;
      motor[beltRight] = 0;

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //come back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;
    }

    motor[frontLeft] = 0;
    motor[backLeft] = 0;
    motor[frontRight] = 0;
    motor[backRight] = 0;

    while(SensorValue[beltTouch] == 0)                    //wait for button
    {
      if (SensorValue[encoderArm] < 100)
      {
        motor[liftLeft] = 127;                               //lift arm
        motor[liftRight] = 127;
      }
      else
      {
        motor[liftLeft] = 0;                               //stop arm
        motor[liftRight] = 0;
      }
    }
    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < distance)      //drive to goal
    {
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;
      if(SensorValue[encoderArm] < 100)
      {
        motor[liftLeft] = 127;                                //lift arm
        motor[liftRight] = 127;
      }
      else
      {
        motor[liftLeft] = 0;
        motor[liftRight] = 0;
      }

    }

    motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

    motor[beltLeft] = -127;                                                         //dump objects
    motor[beltRight] = -127;
    wait1Msec(3000);
    motor[beltLeft] = 0;
    motor[beltRight] = 0;

     while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

     if(SensorValue[touch] == 0)                                             //lower arm
      {
       motor[liftLeft] = -127;
       motor[liftRight] = -127;
      }
      else
      {
       motor[liftLeft] = -127;
       motor[liftRight] = -127;
      }
}

      motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;


   while(SensorValue[touch] == 0)                                             //lower arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
    motor[liftLeft] = 0;
    motor[liftRight] = 0;
    SensorValue[encoderArm] = 0;
    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;

    while(SensorValue[beltTouch] == 0)
    {
    }
    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;                            //at this point in the program the score should be 14 the robot should have
                                                              //deposited all manual loads and one doubler into the middle goal.

          while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < shortStackDistance)           //get short stack to the left of staring blue square
    {
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;
      motor[beltLeft] = 127;
      motor[beltRight] = 127;

    }
      motor[beltLeft] = 0;
      motor[beltRight] = 0;

         while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

      if(SensorValue[encoderArm] < 45)
      {
        motor[liftLeft] = 127;                                //lift arm
        motor[liftRight] = 127;
      }
      else
      {
        motor[liftLeft] = 0;
        motor[liftRight] = 0;
      }
}
    while(SensorValue[beltTouch] == 0)
    {
    }
           while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < shortStackDistance)           // go to goal and dump short stack to the left of staring blue square
    {
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;

    }
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

     motor[beltLeft] = -127;                                                         //dump objects
    motor[beltRight] = -127;
    wait1Msec(3000);
    motor[beltLeft] = 0;
    motor[beltRight] = 0;
         while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

        while(SensorValue[touch] == 0)                                             //lower arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
    motor[liftLeft] = 0;
    motor[liftRight] = 0;
    SensorValue[encoderArm] = 0;

    while(SensorValue[beltTouch] == 0)
    {
    }

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < redSquareDistance)       //go to other red square
    {
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;

    }
    motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

      while(SensorValue[beltTouch] == 0)
    {
    }
    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;

      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;
      wait1Msec(2000);
        while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < shortStackDistance)           // go to goal and dump short stack to the right of starting red

    {
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;

    }
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

     motor[beltLeft] = -127;                                                         //dump objects
    motor[beltRight] = -127;
    wait1Msec(3000);
    motor[beltLeft] = 0;
    motor[beltRight] = 0;
         while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

        while(SensorValue[touch] == 0)                                             //lower arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
    motor[liftLeft] = 0;
    motor[liftRight] = 0;
    SensorValue[encoderArm] = 0;

 }
}
}