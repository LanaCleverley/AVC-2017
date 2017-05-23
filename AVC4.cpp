#include <stdio.h>
#include "E101.h" 
#include <time.h>

int move(int error);
int getError();
int turnLeft(int leftMotor, int rightMotor);
int turnRight(int leftMotor, int rightMotor);
int aracheck = 0;

int main(){
	init();
	while(true){
		move(getError());
	}
}

int move(int error){
		int turn;

		//int error = getError();

		if(error > 0){
			turn =(50);
			turnLeft(20,turn);

		} else if (error < 0){
			turn =(50);
			turnRight(turn,20);

		} else if(error == 0) {
			turnLeft(50,50);
		}
		else if(error == 666){
			turnLeft(50,50);
		}
		return 0;
}

int turnLeft(int leftMotor, int rightMotor){

	set_motor(1,- leftMotor);
	set_motor(2,- rightMotor);
	printf("%d,%d\n", leftMotor, rightMotor);
	return 0;
}

int turnRight(int leftMotor, int rightMotor){
	set_motor(1,- leftMotor);
	set_motor(2,- rightMotor);
printf("%d,%d\n",leftMotor,rightMotor);
	return 0;
}

int getError(){
	take_picture();
	int array[320];
	int error = 0;
	int count = 0;
	int blackCount=0;
	while(count<320){
		char pixel = get_pixel(120, count, 3);
		if(pixel > 120){ // if the pixel is white
			array[count]=1;
		}
		else{
			array[count]=0;
	  	}
    		count++;
	}
	for(int i=0; i<320; i++){
		if(array[i]==1){
			error=error+(i-160.5)/4;
		}
		else if (array[i]==0){
			blackCount++;
		}
	}
//		printf("Error = %d\n", error);
	if( blackCount == 320){
		error = 666;
	}

	return error;

}

