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
#pragma config(Motor,  port10,          middleBack,    tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main
{

   int leftAdjust = 0;
   int rightAdjust = -48;

   int distance = 725;

     while(SensorValue[touch] == 0)                           //drop arm
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
  motor[liftLeft] = 0;
  motor[liftRight] = 0;

  SensorValue[encoderArm] = 0;                          //reset arm encoder
                                                          //program start
    while(SensorValue[beltTouch] == 0 && SensorValue[encoderArm] < 93)                    //wait for button
    {
      if (SensorValue[encoderArm] < 93)
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

    motor[beltLeft] = -127;                                                         //dump objects
    motor[beltRight] = -127;
    wait1Msec(3000);
    motor[beltLeft] = 0;
    motor[beltRight] = 0;

       while(SensorValue[beltTouch] == 0 && SensorValue[touch] == 0)                    //wait for button
    {
      if (SensorValue[touch] == 0)
      {
        motor[liftLeft] = -127;                               //drop arm until it hits bottom
        motor[liftRight] = -127;
      }
      else
      {
        motor[liftLeft] = 0;                               //stop arm
        motor[liftRight] = 0;
        SensorValue[encoderArm] = 0;                          //reset arm encoder
      }
    }


    SensorValue[encoderLeft] = 0;
    SensorValue[encoderRight] = 0;



 while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < distance)  //go forward specified distance to pick up three objects
{
      motor[frontLeft] = 127 + leftAdjust;
      motor[backLeft] = 127 + leftAdjust;
      motor[frontRight] = 127 + rightAdjust;
      motor[backRight] = 127 + rightAdjust;

      motor[beltLeft] = 127;
      motor[beltRight] = 127;

}



      motor[frontRight] = 0;                                                  //wait after distance and continue to run motors so we can pick up any we push
      motor[backRight] = 0;
      motor[beltLeft] = 0;
      motor[beltRight] = 0;

      motor[beltLeft] = 127;
      motor[beltRight] = 127;

      wait1Msec(500);

      motor[beltLeft] = 0;
      motor[beltRight] = 0;

}
