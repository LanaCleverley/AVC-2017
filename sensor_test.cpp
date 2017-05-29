#include <stdio.h>
#include "E101.h" 
#include <time.h>

int getSensor(int side);
int turnLeft(int leftMotor, int rightMotor);
int turnRight(int leftMotor, int rightMotor);
bool t = true;

int main(){
	init();
	while(t){
		int left = getSensor(2);
		int right = getSensor(0);
		int front = getSensor(1);
		printf("Left - %d\n", left);
		printf("Front - %d\n", front);
		printf("Right - %d\n", right);
	}
}
int doQuad4(){
	int Left = getSensor(2);
	int Right = getSensor(0);
	if(Left<Right){
		turnRight(50, 25);
	}
	if(Left>Right){
		turnLeft(50,25);
	}
	else{
		turnLeft(50,50); //Making the robot go forward. Same as code in move
	}
	return 0;
}
	
int getSensor(int sensor){
	int x = 0;
	for(int i=0; i<5; i++){
		x = x+read_analog(sensor);//read from the slected sensor 0,1 or 2.
	}
	x = x/5;
	return x;
}

int turnLeft(int leftMotor, int rightMotor){		

	set_motor(1,-leftMotor);	//left motor speed
	set_motor(2,-rightMotor);	//right motor speed
	//printf("%d,%d\n", -leftMotor, -rightMotor);	//print the motor speeds for error checking
	return 0;
}

int turnRight(int leftMotor, int rightMotor){
	set_motor(1, -leftMotor);	//left motor speed
	set_motor(2, -rightMotor);	//right motor speed
printf("%d,%d\n",-leftMotor,-rightMotor);
	return 0;
}
