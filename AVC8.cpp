#include <stdio.h>
#include "E101.h" 
#include <time.h>

int move(int error);
int getError();
int turnLeft(int leftMotor, int rightMotor);
int turnRight(int leftMotor, int rightMotor);
int aracheck = 0;
bool start = true;
bool quadrant1 = false;
bool quadrant2 = false;
bool quadrant3 = false;

/**
extern "C" int init(int d_lev);
extern "C" int connect_to_server( char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
**/
int main(){
	init();
	while(start){
		char server_addr[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
		connect_to_server(server_addr, 1024);
		char serverMessage[24] = {'P','l','e','a','s','e'};
		send_to_server(serverMessage);
		char message[24];
		receive_from_server(message);
		printf("%s", message);
		if (message == '1234563v'){
			quadrant1 = true;
		}
	}
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
			turnLeft(60,60);
			quadrant3=false;
			}
		else if (error==666 && quadrant3==true){
			sleep1(0,250000);
			getError();
			if(error < 0){
			turnRight(-70, 70);
			}
			else{
			turnLeft(-70,70);
			}
			sleep1(0,250000);
			printf("print\n");
			quadrant3=false;
		}
		else if(error == 666){
			turnLeft(-70,-70);
			quadrant3=false;
		}
		else if (error == 420){
			turnLeft(70,70);
			sleep1(0,250000);
			printf("white Line \n");
			quadrant3=true;
			}
		else if (error > 0){
			turnLeft(20,50);
			quadrant3=false;

		} else if (error < 0){
			turnRight(50,20);
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
	}
//		printf("Error = %d\n", error);
	if( blackCount == 320){
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
	}
	return error;

}

