#pragma config(Sensor, dgtl1,  Touch1,              sensorTouch)
#pragma config(Motor,  port2,           right1,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           right2,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           left1,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           left2,         tmotorNormal, openLoop)

task main()
{
  motor[right1]=100;
  motor[right2]=100;
  motor[left1]=100;
  motor[left2]=100;

wait1Msec(5000);
  motor[right1]=0;
  motor[right2]=0;
  motor[left1]=0;
  motor[left2]=0;


}
