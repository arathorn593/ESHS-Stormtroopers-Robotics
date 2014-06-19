#pragma config(Sensor, in1,    potent1,        sensorPotentiometer)
#pragma config(Sensor, in6,    lineLeft,       sensorLineFollower)
#pragma config(Sensor, in7,    lineMiddle,     sensorLineFollower)
#pragma config(Sensor, in8,    lineRight,      sensorLineFollower)
#pragma config(Sensor, dgtl1,  touch,          sensorTouch)
#pragma config(Sensor, dgtl2,  sonar,          sensorSONAR_inch)
#pragma config(Sensor, dgtl4,  encoderRight,   sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  encoderLeft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  beltTouch,      sensorTouch)
#pragma config(Sensor, dgtl9,  encoderArm,     sensorQuadEncoder)
#pragma config(Sensor, dgtl11, team,           sensorTouch)
#pragma config(Sensor, dgtl12, jumper,         sensorTouch)
#pragma config(Motor,  port1,           centerBack,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           frontLeft,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port6,           liftRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeft,      tmotorNormal, openLoop)
#pragma config(Motor,  port8,           beltRight,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           beltLeft,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          centerFront,   tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
   int multiplier = 3/4;
int leftAdjust = 0;
   int rightAdjust = -35;

   int distance = 725;
   int doublerDistance = 1030;
   int shortStackDistance = 300;
   int redSquareDistance = 1300;
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

      motor[frontLeft] = 110 + leftAdjust;
      motor[backLeft] = 110 + leftAdjust;
      motor[frontRight] = 110 + rightAdjust;
      motor[backRight] = 110 + rightAdjust;
     wait1Msec(1000);

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < distance)      //drive to goal
    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }



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

      motor[beltLeft] = -127;  //dump
      motor[beltRight]=-127;


    wait1Msec(3000);
         motor[beltLeft] = 0;
      motor[beltRight]=0;


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

      motor[frontLeft] = 110 + leftAdjust;
      motor[backLeft] = 110 + leftAdjust;
      motor[frontRight] = 110 + rightAdjust;
      motor[backRight] = 110 + rightAdjust;
     wait1Msec(1000);

      while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < doublerDistance)           //get doubler
    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }


      motor[beltLeft] = 127;
      motor[beltRight]=127;

    }
      motor[beltLeft] = 0;
      motor[beltRight]=0;


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

      motor[frontLeft] = 110 + leftAdjust;
      motor[backLeft] = 110 + leftAdjust;
      motor[frontRight] = 110 + rightAdjust;
      motor[backRight] = 110 + rightAdjust;
     wait1Msec(1000);

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < distance)      //drive to goal
    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }
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

      motor[beltLeft] = -127;
      motor[beltRight]= -127;


    wait1Msec(3000);
      motor[beltLeft] = 0;
      motor[beltRight]= 0;


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
      motor[frontLeft] = 110 + leftAdjust;
      motor[backLeft] = 110 + leftAdjust;
      motor[frontRight] = 110 + rightAdjust;
      motor[backRight] = 110 + rightAdjust;
     wait1Msec(1000);


          while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < shortStackDistance)           //get short stack to the left of staring blue square
    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }


      motor[beltLeft] = 127;
      motor[beltRight]=127;

    }
       motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;
      wait1Msec(1000);

      motor[beltLeft] = 0;
      motor[beltRight]= 0;


      SensorValue[encoderArm] = 0;

         while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

      if(SensorValue[encoderArm] < 50)
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
      motor[liftLeft] = 0;
      motor[liftRight] = 0;
    while(SensorValue[beltTouch] == 0)
    {
            if(SensorValue[encoderArm] < 50)
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
           while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < shortStackDistance-125)           // go to goal and dump short stack to the left of staring blue square
    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }

    }
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

      motor[beltLeft] = -127;
      motor[beltRight]= -127;


    wait1Msec(3000);

      motor[beltLeft] = 0;
      motor[beltRight]= 0;


      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;
wait1Msec(1000);
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

    while(SensorValue[beltTouch] == 0)
    {
    }

    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < redSquareDistance)       //go to other red square score is 17
    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }

    }
    motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;
wait1Msec(1000);
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

      while(SensorValue[beltTouch] == 0)
    {
    }
    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;                            //at this point in the program the score should be 14 the robot should have
                                                              //deposited all manual loads and one doubler into the middle goal.

          while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < shortStackDistance)           //get short stack to the right of starting red square
    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }
      motor[beltLeft] = 127;
      motor[beltRight]= 127;

    }
          motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;
      wait1Msec(1000);

      motor[beltLeft] = 0;
      motor[beltRight]= 0;


         while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
    {
      motor[frontLeft] = -127 - leftAdjust;
      motor[backLeft] = -127 - leftAdjust;
      motor[frontRight] = -127 - rightAdjust;
      motor[backRight] = -127 - rightAdjust;

      if(SensorValue[encoderArm] < 50)
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
      motor[liftLeft] = 0;
      motor[liftRight] = 0;
    while(SensorValue[beltTouch] == 0)
    {
            if(SensorValue[encoderArm] < 50)
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

        while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < shortStackDistance)           // go to goal and dump short stack to the right of starting red

    {
      if((SensorValue[encoderLeft]) > (SensorValue[encoderRight]))
      {
        motor[frontLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
        motor[backLeft] = 127-(multiplier * (SensorValue[encoderLeft] - SensorValue[encoderRight]));
      }
      else if((SensorValue[encoderLeft]) < (SensorValue[encoderRight]))
      {
        motor[backRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
        motor[frontRight] = 127-(multiplier * (SensorValue[encoderRight] - SensorValue[encoderLeft]));
      }
      else
      {
        motor[frontLeft] = 127;
        motor[backLeft] = 127;
        motor[frontRight] = 127;
        motor[backRight] = 127;
      }
    }
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
      motor[frontRight] = 0;
      motor[backRight] = 0;

      motor[beltLeft] = -127;
      motor[beltRight]= -127;


    wait1Msec(3000);

      motor[beltLeft] = 0;
      motor[beltRight]= 0;

         while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 > 0)           //go back
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

  while(SensorValue[touch] == 0)                                             //lower arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
    motor[liftLeft] = 0;
    motor[liftRight] = 0;
    SensorValue[encoderArm] = 0;

 }



/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{

  int tallHeight = 90;  //variables to adjust heights of preset arm heights
  int midHeight = 61;
  int smallHeight = 42;

  int state = 0;    // not auto lifting
  //1 == base
  //2 == short
  //3 == mid
  //4 == tall

  int tallVal = 0;
  int oldTallVal = 0;

  int midVal = 0;
  int oldMidVal = 0;

  int shortVal = 0;
  int oldShortVal = 0;

  int baseVal = 0;
  int oldBaseVal = 0;

  int lowVal = 0;
  int oldLowVal= 0;

  int highVal = 0;
  int oldHighVal = 0;

  int val = 0;
int old_val = 0;
int stateOP = 0;

int armFixVal = 0;
int armFixOldVal = 0;
int armFixState = 0

// User control code here, inside the loop

	while (true)
	{
    if(vexRT[Btn7D] == 1)
    {
      val = 1;
    }
    else
    {
      val = 0;
    }
    if ((val == 1) && (old_val == 0))
    {
      stateOP = 1 - stateOP;
      wait1Msec(100);
    }

    if(vexRT[Btn7U] == 1)
    {
      armFixVal = 1;
    }
    else
    {
      armFixOldVal = 0;
    }
    if ((armFixVal == 1) && (armFixOldVal == 0))
    {
      armFixState = 1 - armFixState;
      wait1Msec(100);
    }

    old_val = val; // val is now old, let's store it
    //presets
    if(stateOP == 1)
    {
	  tallVal = vexRT[Btn8U];                     //setting values of buttons to variables
    midVal = vexRT[Btn8R];
    shortVal = vexRT[Btn8L];
    baseVal = vexRT[Btn8D];


    if ((tallVal == 1) && (oldTallVal == 0))      //setting state if needed
    {
      state = 4;
      wait1Msec(100);
    }

    if ((midVal == 1) && (oldMidVal == 0))
    {
      state = 3;
      wait1Msec(100);
    }

    if ((shortVal == 1) && (oldShortVal == 0))
    {
      state = 2;
      wait1Msec(100);
    }

    if ((baseVal == 1) && (oldBaseVal == 0))
    {
      state = 1;
      wait1Msec(100);

    }

    oldTallVal = tallVal; // val is now old, let's store it
    oldMidVal = midVal;
    oldShortVal = shortVal;
    oldBaseVal = baseVal;

    //arm fix
    if(armFixState == 1)
    {
          if(vexRT[Btn6D] == 1)
    {
      motor[liftRight] = -127;
      motor[liftLeft] = -127;
    }
    else if(vexRT[Btn6U] == 1)
    {
      motor[liftRight] = 127;
      motor[liftLeft] = 127;
    }
    else
    {
      motor[liftRight] = (vexRT[Ch2])/4;
      motor[liftLeft] = (vexRT[Ch3])/4;
    }
    }
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


    if((vexRT[Btn6D]) == 1)
    {                                     //this segment runs the arm lift
      state = 0;
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
     else
     {
       if((vexRT[Btn6U]) == 1)
       {
         state = 0;
         motor[liftRight] = 127;
         motor[liftLeft]= 127;
       }
       else                             //preset arm controls
       {
         if(state > 0)
         {
           if(state == 1)
           {
             if(SensorValue[touch] == 0)
             {
               motor[liftRight] = -127;
               motor[liftLeft]= -127;
             }
             else
             {
               motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
             }
           }
            else if(state == 2)
            {
              if(SensorValue[encoderArm]<smallHeight)
              {
                motor[liftRight] = 127;
                motor[liftLeft]= 127;
              }
			        else if(SensorValue[encoderArm]>smallHeight+10)
			        {
				        motor[liftRight] = -127;
                motor[liftLeft]= -127;
			        }
              else
              {
                motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
              }

            }
            else if(state == 3)
            {
              if(SensorValue[encoderArm]<midHeight)
              {
                motor[liftRight] = 127;
                motor[liftLeft]= 127;
              }
			        else if(SensorValue[encoderArm]>midHeight+10)
			        {
				        motor[liftRight] = -127;
                motor[liftLeft]= -127;
			        }
              else
              {
                motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
              }

            }

            else if(state == 4)
            {
              if(SensorValue[encoderArm]<tallHeight)
              {
                motor[liftRight] = 127;
                motor[liftLeft]= 127;
              }
              else if(SensorValue[encoderArm]>tallHeight+10)
              {
                motor[liftRight] = -127;
                motor[liftLeft]= -127;
              }
              else
              {
                motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
              }

            }
         }
      else
      {
        motor[liftRight] = 0;
        motor[liftLeft] = 0;
      }
    }



  }
  if(SensorValue[touch] == 1)
  {
    SensorValue[encoderArm] = 0;
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
      motor[beltRight]= 0;

            }
      }
    }
    else if(stateOP == 0)
    {
      tallVal = vexRT[Btn8UXmtr2];                     //setting values of buttons to variables
    midVal = vexRT[Btn8RXmtr2];
    shortVal = vexRT[Btn8LXmtr2];
    baseVal = vexRT[Btn8DXmtr2];


    if ((tallVal == 1) && (oldTallVal == 0))      //setting state if needed
    {
      state = 4;
      wait1Msec(100);
    }

    if ((midVal == 1) && (oldMidVal == 0))
    {
      state = 3;
      wait1Msec(100);
    }

    if ((shortVal == 1) && (oldShortVal == 0))
    {
      state = 2;
      wait1Msec(100);
    }

    if ((baseVal == 1) && (oldBaseVal == 0))
    {
      state = 1;
      wait1Msec(100);

    }

    oldTallVal = tallVal; // val is now old, let's store it
    oldMidVal = midVal;
    oldShortVal = shortVal;
    oldBaseVal = baseVal;
           if( abs(vexRT[Ch2Xmtr2]) > 50)
      {                //threshold for right side
      motor[frontRight] = (vexRT[Ch2Xmtr2]);
      motor[backRight] = (vexRT[Ch2Xmtr2]);
    }
    else{
      motor[frontRight] = 0;
      motor[backRight] = 0;
    }

    if( abs(vexRT[Ch3Xmtr2]) > 50){         //threshold for left side
      motor[frontLeft] = (vexRT[Ch3Xmtr2]);
      motor[backLeft] = (vexRT[Ch3Xmtr2]);
    }
    else{
      motor[frontLeft] = 0;
      motor[backLeft] = 0;
    }


    if((vexRT[Btn6DXmtr2]) == 1)
    {                                     //this segment runs the arm lift
      state = 0;
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
     else
     {
       if((vexRT[Btn6UXmtr2]) == 1)
       {
         state = 0;
         motor[liftRight] = 127;
         motor[liftLeft]= 127;
       }
       else                             //preset arm controls
       {
         if(state > 0)
         {
           if(state == 1)
           {
             if(SensorValue[touch] == 0)
             {
               motor[liftRight] = -127;
               motor[liftLeft]= -127;
             }
             else
             {
               motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
             }
           }
            else if(state == 2)
            {
              if(SensorValue[encoderArm]<smallHeight)
              {
                motor[liftRight] = 127;
                motor[liftLeft]= 127;
              }
			        else if(SensorValue[encoderArm]>smallHeight+10)
			        {
				        motor[liftRight] = -127;
                motor[liftLeft]= -127;
			        }
              else
              {
                motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
              }

            }
            else if(state == 3)
            {
              if(SensorValue[encoderArm]<midHeight)
              {
                motor[liftRight] = 127;
                motor[liftLeft]= 127;
              }
			        else if(SensorValue[encoderArm]>midHeight+10)
			        {
				        motor[liftRight] = -127;
                motor[liftLeft]= -127;
			        }
              else
              {
                motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
              }

            }

            else if(state == 4)
            {
              if(SensorValue[encoderArm]<tallHeight)
              {
                motor[liftRight] = 127;
                motor[liftLeft]= 127;
              }
              else if(SensorValue[encoderArm]>tallHeight+10)
              {
                motor[liftRight] = -127;
                motor[liftLeft]= -127;
              }
              else
              {
                motor[liftRight] = 0;
               motor[liftLeft] = 0;
               state = 0;
              }

            }
         }
      else
      {
        motor[liftRight] = 0;
        motor[liftLeft] = 0;
      }
    }



  }
  if(SensorValue[touch] == 1)
  {
    SensorValue[encoderArm] = 0;
  }

    if((vexRT[Btn5UXmtr2]) == 1)  //Conveyer Control
      {

      motor[beltLeft] = 127;
      motor[beltRight]=127;


      }
    else
      {
          if((vexRT[Btn5DXmtr2]) == 1)
            {
      motor[beltLeft] = -127;
      motor[beltRight]= -127;

            }
          else
            {
      motor[beltLeft] = 0;
      motor[beltRight]= 0;

            }
      }
    }
    }
	}




	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................
