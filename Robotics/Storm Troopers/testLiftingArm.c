#pragma config(Motor,  port1,           lift1,         tmotorVex393, openLoop)
#pragma config(Motor,  port2,           lift2,         tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
   while(true)
   {
      if(vexRT[Btn8U] == 1)
      {
        motor[lift1] = 127;
        motor[lift2] = 127;
      }
      else if(vexRT[Btn8D] == 1)
      {
        motor[lift1] = -127;
        motor[lift2] = -127;
      }
      else
      {
        motor[lift1] = 0;
        motor[lift2] = 0;
      }
   }
}
