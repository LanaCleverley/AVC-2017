#include <stdio.h>
#include "E101.h" 
#include <time.h>

int move(int error);
int getError();
int turnLeft(int leftMotor, int rightMotor);
int turnRight(int leftMotor, int rightMotor);
int aracheck = 0;
bool quadrant1 = true;
bool quadrant2 = false;
bool quadrant3 = false;
bool whiteLine = false;

int main(){
	init();
	while(quadrant1){
		move(getError());
	}
	while(quadrant2){
		move(getError());
	}
	while(quadrant3){
		turnLeft(0,0);
	}
}

int move(int error){
		int turn;

		//int error = getError();

		if(error > 0){
			turn =(45);
			turnLeft(15,turn);

		} else if (error < 0){
			turn =(45);
			turnRight(turn,15);

		} else if(error == 0) {
			turnLeft(-50,-50);
		}
		else if(error == 666){
			turnLeft(-50,50);
		}
		else if(error == 420){
			turnLeft(50,50);
			sleep1(0,250000);
			printf("white Line \n");

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
	int quad = 0;
	int blackCount = 0;
	int whiteCount = 0;
	while(count<320){
		if(count == 0){
			blackCount = 0;
			whiteCount = 0; 
		}
		char pixel = get_pixel(120, count, 3);
		if(pixel > 115){ // if the pixel is white
			array[count]=1;
			whiteCount++;
		}
		else{
			array[count]=0;
			blackCount++;
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
	if( blackCount > 120){
		error = 666;
	}
	if( whiteCount > 310 ){
		 if (quadrant1){
			quadrant1 = false;
			quadrant2 = true;
		}	
		else if (quadrant2){
			error = 420;
		}
	/**	if (quad == 0){
			quadrant1 = false;
			quadrant2 = true;
			quad = 1;
			printf("white line \n");
		}
		else if (quad == 1){
			quadrant2 = false;
			quadrant3 = true;
			quad = 2;
			printf("white Line \n");
		}
	**/

	}

	return error;

}






//void quad1(){
//	while(true){
//		
//	}
//}



/** int propResponse(int error){
	
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
*/
