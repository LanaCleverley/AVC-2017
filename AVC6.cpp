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

int main(){
	init();
	while(quadrant1){
		move(getError());
	}
	while(quadrant2){
		move(getError());
		}
}

int move(int error){
		int turn;
		printf("quadrant 3 %d\n",quadrant3);
		//int error = getError();
		if(error==0){
			turnLeft(50,50);
			quadrant3=false;
			}
		else if (error==666 && quadrant3==true){
			sleep1(0,250000);
			turnLeft(-15,25);
			sleep1(0,250000);
			printf("print\n");
			quadrant3=false;
		}
		else if(error == 666){
			turnLeft(-50,-50);
			quadrant3=false;
		}
		else if (error == 420){
			turnLeft(30,30);
			sleep1(0,250000);
			printf("white Line \n");
			quadrant3=true;
			}
		else if(error == 1234567){//left
			printf("turn straight left");
			turnLeft(50, -50);
			sleep1(0,250000);
		}
		else if(error == 7654321){//right
			printf("turn striaght right");
			turnRight(-50,50);
			sleep1(0,250000);
		}
		else if (error > 0){
			turn =(50);
			turnLeft(20,turn);
			quadrant3=false;

		} else if (error < 0){
			turn =(50);
			turnRight(turn,20);
			quadrant3=false;;

		} 
		return 0;
}

int turnLeft(int leftMotor, int rightMotor){

	set_motor(1,-leftMotor);
	set_motor(2,-rightMotor);
	printf("%d,%d\n", -leftMotor, -rightMotor);
	return 0;
}

int turnRight(int leftMotor, int rightMotor){
	set_motor(1, -leftMotor);
	set_motor(2, -rightMotor);
printf("%d,%d\n",-leftMotor,-rightMotor);
	return 0;
}

int getError(){
	take_picture();
	int array[320];
	int error = 0;
	int count = 0;
	int blackCount=0;
	int whiteCount=0;
	int left = 0;
	int right = 0;
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
			whiteCount++;
		}
		else if (array[i]==0){
			blackCount++;
		}
		if(array[i] < 160){
			left++;
		}
		else if(array[i] >= 160){
			right++;
		}
	}
//		printf("Error = %d\n", error);
	if( blackCount == 320){
		error = 666;
	}
	if(left == 160){
		error = 1234567;
	}
	else if (right == 160){
		error = 7654321;
	}
	if( whiteCount > 310 ){
		if (quadrant1){
			quadrant1 = false;
			quadrant2 = true;
		}
		
		else if (quadrant2){
			error = 420;
		}
	}
	return error;

}

