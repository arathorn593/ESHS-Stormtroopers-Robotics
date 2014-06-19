void resetDriveEncoders(){
	SensorValue[encoderL] = 0;
	SensorValue[encoderR] = 0;
}

void waitForPress(){
	while(nLCDButtons == 0){}
}


float change;

float PID(int error, int oldError, float Kp, float Ki, float Kd, float integral, int dt){
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! do the declarations slow it down!!!!!!!!!!!!!!!!!!1
	change = 0;

	change += error * Kp;

	change += (integral + error) * Ki * dt;

	change += (error - oldError) * Kd * dt;

	return change;
}
