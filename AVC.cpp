#include <stdio.h>
#include <time.h>
#include "E101.h" 

void quad1(){
	while(true){
		
	}
}

void function(int leftMotor, int rightMotor){
	set_motor(0, leftMotor);
	set_motor(1, -rightMotor);
}

int getError(){
	take_picture();
	//display_picture(1,0);
	int error = 0;
	int count = 0;
	
	while(count<320){
		char pixel = get_pixel(120, count, 3);
		
		//printf("%d\n", pixel);
		
		if(pixel > 100){ // if the pixel is white
			error += count - 160; //Add its error value to the total error
		}
		
		/*if(pixel>max_white){
			max_white=pixel;
		}
		if(pixel>max_black && pixel<100){
			max_black = pixel;
		}*/


		count = count+1;
	}
	return error;
}

int main(){
	init();

	
	int max_white = 0;
	int max_black = 0;
	int average = 0;
	int prevError = 0;

	while(true){
		int error = getError();
		if(error > 0){
			turnLeft();
		} else if (error < 0){
			turnRight();
		} else {

		}
		printf("Error = %d\n", error);
		if(error != 0)
			prevError = error;
	}
	/*
	average = (max_black+max_white)/2;
	printf("%d Is your max value", max_white);	
	printf("%d\n");
	printf("%d Is your max black value", max_black);
	printf("%d\n");
	printf("%d Is your average value", average);
	*/


}
