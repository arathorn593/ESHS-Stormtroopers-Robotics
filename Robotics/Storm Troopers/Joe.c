#pragma config(Sensor, dgtl1,  Touch1,              sensorTouch)
#pragma config(Motor,  port2,           right1,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           right2,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           left1,         tmotorNormal, openLoop)
#pragma config(Motor,  port5,           left2,         tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



task main()
{
    motor[left1]= 63;
    motor[left2]= 63;
    motor[right1]= 7;
    motor[right2]= 7;

    wait1Msec (20000);

    motor[left1]= -63;
    motor[left2]= -63;
    motor[right1]= -7;
    motor[right2]= -7;

    wait1Msec (20000);

     motor[left1]= 0;
    motor[left2]= 0;
    motor[right1]= 0;
    motor[right2]= 0;
}
