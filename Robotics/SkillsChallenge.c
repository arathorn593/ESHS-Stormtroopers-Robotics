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

int threshold;
int motorSpeed;
int motorChange;
int distance;
int turnValue;

//|||||||||||||||||||||||||||||||||||||||||||||||FINAL||||||||||||||||||||||||||||||||||||||||||||||||||||
void final()
{
   while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < 600)
  {
    motor[frontLeft] = motorSpeed;
     motor[frontRight] = motorSpeed;
     motor[backLeft] = motorSpeed;
     motor[backRight] = motorSpeed;
   }
   motor[frontLeft] = 0;
     motor[frontRight] = 0;
     motor[backLeft] = 0;
     motor[backRight] = 0;
  }

//|||||||||||||||||||||||||||||||||||||||||||||||BASE||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void base()
{
  while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < 1750)
  {
    motor[frontLeft] = -127;
     motor[frontRight] = -127;
     motor[backLeft] = -127;
     motor[backRight] = -127;
   }
   motor[frontLeft] = 0;
     motor[frontRight] = 0;
     motor[backLeft] = 0;
     motor[backRight] = 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||DOUBLER||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void doubler()
{
   SensorValue[encoderLeft] = 0;         //reset encoders
   SensorValue[encoderRight] = 0;



     motor[liftLeft] = -127;
     motor[liftRight] = -127;

   while(SensorValue[encoderLeft] < 720)        //swing turn
   {
     if(SensorValue[touch] == 0)                //lower arm
     {
      motor[liftLeft] = -127;
      motor[liftRight] = -127;
     }
     else
     {
       motor[liftLeft] = 0;
        motor[liftRight] = 0;
     }
     motor[frontLeft] = motorSpeed;
     motor[backLeft] = motorSpeed;
   }
   motor[frontLeft] = 0;                         //stop motors
   motor[backLeft] = 0;

   SensorValue[encoderLeft] = 0;         //reset encoders
  SensorValue[encoderRight] = 0;

   while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < 800)      //get doubler
   {
     motor[beltLeft] = 127;
     motor[beltRight] = 127;
     motor[frontLeft] = motorSpeed;
     motor[frontRight] = motorSpeed;
     motor[backLeft] = motorSpeed;
     motor[backRight] = motorSpeed;
   }
   motor[beltLeft] = 0;
   motor[beltRight] = 0;
   motor[frontLeft] = 0;
   motor[frontRight] = 0;
   motor[backLeft] = 0;
   motor[backRight] = 0;

   SensorValue[encoderLeft] = 0;         //reset encoders
  SensorValue[encoderRight] = 0;
  while (  SensorValue[encoderLeft] > -turnValue * 2 && SensorValue[encoderRight] < turnValue * 2)      // 180 turn
  {
    motor[frontLeft] = -40;
    motor[frontRight] = 40;
    motor[backLeft] = -40;
    motor[backRight] = 40;
  }
    motor[frontLeft] = 0;
    motor[frontRight] = 0;
    motor[backLeft] = 0;
    motor[backRight] = 0;

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < 800)      //get in position to dump
   {
     if(SensorValue[potent1]>1814)
     {
        motor[liftLeft]=127;
        motor[liftRight] = 127;
     }
      else
      {
        motor[liftLeft]= 0;
        motor[liftRight] = 0;
      }
     motor[frontLeft] = motorSpeed;
     motor[frontRight] = motorSpeed;
     motor[backLeft] = motorSpeed;
     motor[backRight] = motorSpeed;
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||DUMP||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void dump()
{
 motor[beltLeft] = -127;
 motor[beltRight] = -127;
 wait1Msec(5000);                                   // wait so it has time to dump
 motor[beltLeft] = 0;
 motor[beltRight] = 0;

}

//||||||||||||||||||||||||||||||||||||||||||||||JUKE|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void juke()
{
  SensorValue[encoderLeft] = 0;         //reset encoders
  SensorValue[encoderRight] = 0;
  while (  SensorValue[encoderLeft] > -50 && SensorValue[encoderRight] < 50)         //angle robot
  {
    motor[frontLeft] = -40;
    motor[frontRight] = 40;
    motor[backLeft] = -40;
    motor[backRight] = 40;
  }
    motor[frontLeft] = 0;
    motor[frontRight] = 0;
    motor[backLeft] = 0;
    motor[backRight] = 0;

    SensorValue[encoderLeft] = 0;         //reset encoders
    SensorValue[encoderRight] = 0;

   while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < 600)         //go next to the stack
   {
     motor[frontLeft] = motorSpeed;
     motor[frontRight] = motorSpeed;
     motor[backLeft] = motorSpeed;
     motor[backRight] = motorSpeed;
   }
    motor[frontLeft] = 0;
    motor[frontRight] = 0;
    motor[backLeft] = 0;
    motor[backRight] = 0;

     SensorValue[encoderLeft] = 0;         //reset encoders
    SensorValue[encoderRight] = 0;

    while (  SensorValue[encoderLeft] > 150 && SensorValue[encoderRight] < -150)         //knock stack away
  {
    motor[frontLeft] = 40;
    motor[frontRight] = -40;
    motor[backLeft] = 40;
    motor[backRight] = -40;
  }
    motor[frontLeft] = 0;
    motor[frontRight] = 0;
    motor[backLeft] = 0;
    motor[backRight] = 0;

     SensorValue[encoderLeft] = 0;         //reset encoders
    SensorValue[encoderRight] = 0;

    while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < 200)         //drive up to goal
   {
     motor[frontLeft] = motorSpeed;
     motor[frontRight] = motorSpeed;
     motor[backLeft] = motorSpeed;
     motor[backRight] = motorSpeed;
   }
    motor[frontLeft] = 0;
    motor[frontRight] = 0;
    motor[backLeft] = 0;
    motor[backRight] = 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||||||LEFT TURN||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void left90()
{

  SensorValue[encoderLeft] = 0;         //reset encoders
  SensorValue[encoderRight] = 0;
  while (  SensorValue[encoderLeft] > -turnValue && SensorValue[encoderRight] < turnValue)
  {
    motor[frontLeft] = -40;
    motor[frontRight] = 40;
    motor[backLeft] = -40;
    motor[backRight] = 40;
  }
    motor[frontLeft] = 0;
    motor[frontRight] = 0;
    motor[backLeft] = 0;
    motor[backRight] = 0;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||LINE FOLLOW||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void lineFollow()
{
  SensorValue[encoderLeft] = 0;         //reset encoders
  SensorValue[encoderRight] = 0;
  SensorValue[encoderArm] = 0;
   while((SensorValue[encoderLeft] + SensorValue[encoderRight])/2 < distance)        //while the average encoder value is less than the distance you are going
  {
   if(SensorValue[encoderArm]<85)
   {
     motor[liftLeft]=127;
     motor[liftRight] = 127;
   }
   else
   {
     motor[liftLeft]= 0;
     motor[liftRight] = 0;
   }
   if(SensorValue[lineMiddle] < threshold)                                          //if the middle sensor is on the line go forward
   {
    motor[frontLeft] = motorSpeed;
    motor[frontRight] = motorSpeed;
    motor[backLeft] = motorSpeed;
    motor[backRight] = motorSpeed;
  }
   else //if it's not on the line make adjustments
 {
   if(SensorValue[lineRight] < threshold)                                           //if the right sees the line turn right to adjust
     {
       motor[frontLeft] = motorSpeed + motorChange;
       motor[backLeft] = motorSpeed + motorChange;
       motor[frontRight] = motorSpeed - motorChange;
       motor[backRight] = motorSpeed - motorChange;
     }
     else if(SensorValue[lineLeft] < threshold)                                        // if the left sees the line turn left to adjust
     {
       motor[frontLeft] = motorSpeed - motorChange;
       motor[backLeft] = motorSpeed - motorChange;
       motor[frontRight] = motorSpeed + motorChange;
       motor[backRight] = motorSpeed + motorChange;

     }
   }
  }
  while(!((SensorValue[lineRight] < threshold) && (SensorValue[lineMiddle] < threshold) && (SensorValue[lineLeft] < threshold))) //looking fo line
  {
    if(SensorValue[potent1]>1814)
   {
     motor[liftLeft]=127;
     motor[liftRight] = 127;
   }
   else
   {
     motor[liftLeft]= 0;
     motor[liftRight] = 0;
   }
   if(SensorValue[lineMiddle] < threshold)                                          //if the middle sensor is on the line go forward
   {
    motor[frontLeft] = motorSpeed-30;
    motor[frontRight] = motorSpeed-30;
    motor[backLeft] = motorSpeed-30;
    motor[backRight] = motorSpeed-30;
  }
   else //if it's not on the line make adjustments
 {
   if(SensorValue[lineRight] < threshold)                                           //if the right sees the line turn right to adjust
     {
       motor[frontLeft] = motorSpeed + motorChange-30;
       motor[backLeft] = motorSpeed + motorChange-30;
       motor[frontRight] = motorSpeed - motorChange-30;
       motor[backRight] = motorSpeed - motorChange-30;
     }
     else if(SensorValue[lineLeft] < threshold)                                        // if the left sees the line turn left to adjust
     {
       motor[frontLeft] = motorSpeed - motorChange-30;
       motor[backLeft] = motorSpeed - motorChange-30;
       motor[frontRight] = motorSpeed + motorChange-30;
       motor[backRight] = motorSpeed + motorChange-30;

     }
   }

 }
    motor[frontLeft] = 0;
    motor[frontRight] = 0;
    motor[backLeft] = 0;
    motor[backRight] = 0;
}


task main
{
  while(SensorValue(beltTouch)==0)
  {
  }
     while(SensorValue[touch] == 0)
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
  threshold = 2000;
  motorSpeed = 50;
  motorChange = 10;
  distance = 2400;
  lineFollow();
  turnValue = 340;
  left90();
  juke();
  /*dump();
  doubler();
  dump();
  base();
  while(SensorValue(beltTouch)==0)
  {
  }

  lineFollow();
  left90();
  final();
  dump();
*/
  while(SensorValue[touch] == 0)
  {
    motor[liftLeft] = -127;
    motor[liftRight] = -127;
  }
}


//point turn 50
