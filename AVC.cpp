#include <stdio.h>
#include <time.h>
#include "E101.h" 

void quad1(){
	while(true){
		
	}
}

void turnLeft(int leftMotor, int rightMotor){
	set_motor(0, leftMotor);
	set_motor(1, -rightMotor);
}

void turnRight(int leftMotor, int rightMotor){
	set_motor(0, leftMotor);
	set_motor(1, -rightMotor);
}

int getError(){
	take_picture();
	int error = 0;
	int count = 0;
	
	while(count<320){
		char pixel = get_pixel(120, count, 3);
		
		
		
		if(pixel > 100){ // if the pixel is white
			error += count - 160; //Add its error value to the total error
		}

		count = count+1;
	}
	return error;
}

int propResponse(int error){
	
	int kp = 0.5;
	int proportional_signal;
			
	
	proportional_signal = error*kp;
	
	return ((proportional_signal/(160*1*kp))*255);
	}
	
	int der (int error, int prevError){
		int prev_error = prevError;
		int current_error = error;
		int kd = 5.0;
		int der_signal = 0;
			
			der_signal = (current_error-prev_error/0.1)*kd;
			return der_signal;
	}

int main(){
	init();

	

	int prevError = 0;

	while(true){
		int error = getError();
		if(error > 0){
			turnLeft(propResponse(error)+der(error, prevError), 50);
		} else if (error < 0){
			turnRight(50, propResponse(error)+der(error, prevError));
		} else {

		}
		printf("Error = %d\n", error);
		if(error != 0)
			prevError = error;
	}
	


}
