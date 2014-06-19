#pragma config(Sensor, dgtl1,  encoderLeft,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  encoderRight,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  topTouchSensor, sensorTouch)
#pragma config(Sensor, dgtl6,  bottomTouchSensor, sensorTouch)
#pragma config(Sensor, dgtl7,  armEncoderLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  armEncoderRight, sensorQuadEncoder)
#pragma config(Motor,  port2,           left1,         tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           left2,         tmotorVex393, openLoop)
#pragma config(Motor,  port4,           right1,        tmotorVex393, openLoop)
#pragma config(Motor,  port5,           right2,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           rightArmMotor1, tmotorVex393, openLoop)
#pragma config(Motor,  port7,           rightArmMotor2, tmotorVex393, openLoop)
#pragma config(Motor,  port8,           leftArmMotor1, tmotorVex393, openLoop)
#pragma config(Motor,  port9,           leftArmMotor2, tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void driveForward(int distance, int speed)
{
   distance=abs(distance);
   speed=abs(speed);
   SensorValue[encoderLeft] = 0;          //reset encoders
   SensorValue[encoderRight] = 0;

   while((SensorValue[encoderLeft]< distance) || (SensorValue[encoderRight] < distance))  //while one of the sides has not reached the destination
   {
      if(SensorValue[encoderLeft]<distance)     //move left if left hasn't make it
      {
        motor[left1] = speed;
        motor[left2] = speed;
      }
      else                                      //stop when done
      {
        motor[left1] = 0;
        motor[left2] = 0;
      }

      if(SensorValue[encoderRight]<distance)  //move right if it hasn't make it
      {
        motor[right1] = speed;
        motor[right2] = speed;
      }
      else                                    //stop when done
      {
        motor[right1] = 0;
        motor[right2] = 0;
      }
   }
}

void driveBackward(int distance, int speed)
{
   speed = -1 * abs(speed);                       //fool proof so if a negative or positive speed or distance
   distance = -1 * abs(distance);                 // is entered the right value is used in the function

   SensorValue[encoderLeft] = 0;                  //reset encoders
   SensorValue[encoderRight] = 0;

   while((SensorValue[encoderLeft] > distance) || (SensorValue[encoderRight] > distance))   //if one side hasn't maken it continue loop
   {
      if(SensorValue[encoderLeft] > distance)     //move left if it hasn't maken it
      {
        motor[left1] = speed;
        motor[left2] = speed;
      }
      else                                      //stop when done
      {
        motor[left1] = 0;
        motor[left2] = 0;
      }

      if(SensorValue[encoderRight] > distance)    //move right if it hasn't maken it
      {
        motor[right1] = speed;
        motor[right2] = speed;
      }
      else                                  //stop when done
      {
        motor[right1] = 0;
        motor[right2] = 0;
      }
   }
}
void turn(int angle, int speed, string direction)
{
   angle=abs(angle);
   speed=abs(speed);
   SensorValue[encoderLeft] = 0;          //reset encoders
   SensorValue[encoderRight] = 0;
   int distance=angle;
   if(direction=="left")
   {
      while((SensorValue[encoderLeft] > -distance) || (SensorValue[encoderRight] < distance))   //if one side hasn't maken it continue loop
         {
          if(SensorValue[encoderLeft] > -distance)     //left motors go backward until the negative distance quantity is reached
          {
            motor[left1] = -speed;
            motor[left2] = -speed;
          }
          else                                      //stop when done
          {
            motor[left1] = 0;
            motor[left2] = 0;
          }

          if(SensorValue[encoderRight] < distance)    //right motors go forward until the distance quantity is reached
          {
            motor[right1] = speed;
            motor[right2] = speed;
          }
          else                                  //stop when done
          {
            motor[right1] = 0;
            motor[right2] = 0;
          }
       }
   }
   if(direction=="right")
   {
      while((SensorValue[encoderLeft] < distance) || (SensorValue[encoderRight] > -distance))   //if one side hasn't maken it continue loop
         {
          if(SensorValue[encoderLeft] < distance)     //left motors go forward until the distance quantity is reached
          {
            motor[left1] = speed;
            motor[left2] = speed;
          }
          else                                      //stop when done
          {
            motor[left1] = 0;
            motor[left2] = 0;
          }

          if(SensorValue[encoderRight] > -distance)    //right motors go backward until the negative distance quantity is reached
          {
            motor[right1] = -speed;
            motor[right2] = -speed;
          }
          else                                  //stop when done
          {
            motor[right1] = 0;
            motor[right2] = 0;
          }
       }
   }
}
void changeArmPosition(string direction, int angle, int speed)
{
  if (direction=="up")
  {
    while (SensorValue[topTouchSensor]==0)
    {
      if (SensorValue[armEncoderRight]<angle)
      {
        motor[rightArmMotor1]=speed;
        motor[rightArmMotor2]=speed;
        motor[leftArmMotor1]=speed;
        motor[leftArmMotor1]=speed;
      }
    }
  }
  if (direction=="down")
  {
    while (SensorValue[bottomTouchSensor]==0)
    {
      if (SensorValue[armEncoderRight]>angle)
      {
        motor[rightArmMotor1]=-speed;
        motor[rightArmMotor2]=-speed;
        motor[leftArmMotor1]=-speed;
        motor[leftArmMotor1]=-speed;
      }
    }
  }
}
task main{
  //changeArmPosition("up",30,127);
  //driveForward(50,100);
  //driveBackward(50,100);
  turn(1080,100,"left");
}
