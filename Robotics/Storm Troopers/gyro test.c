#pragma config(Sensor, in1,    gyro,           sensorGyro)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  int gyroVal;
  while(true)
  {
    gyroVal = SensorValue(gyro);
  }
}
