
#include <stdio.h>
#include "E101.h" 
#include <time.h>

int move(int error);
int getError();
int doQuad4();
int turnLeft(int leftMotor, int rightMotor);
int turnRight(int leftMotor, int rightMotor);
int aracheck = 0;
int gate = 0;
bool quadrant1 = false;
bool quadrant2 = false;
bool quadrant3 = false;
bool quadrant4 = false;
int getsensor(int side);

/**
extern "C" int init(int d_lev);
extern "C" int connect_to_server( char server_addr[15], int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
**/
int getSensor(int side){
	int x;
	for(int i=0; i<5; i++){
		x = x+read_analog(side);
	}
	x = x/5;
	return x;
}

int main(){
	init();
	char server_addr[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(server_addr, 1024);
	char serverMessage[24] = {'P','l','e','a','s','e',' ','w','o','r','k'};
	send_to_server(serverMessage);
	char message[24];
	receive_from_server(message);
	printf("%s", message);
	send_to_server(message);
	
	quadrant1 = true;
	
	
	while(quadrant1){
		move(getError());
	}
	while(quadrant2){
		move(getError());
		}
	while(quadrant4){
		doQuad4();
	}	
}	

/**
 * right = 0
 * left = 2
 * front =1
 * */


int move(int error){
	//	printf("quadrant 3 %d\n",quadrant3);
		if(error==0){               // if the AV is on the line exactly
			turnLeft(60,60);    // drive straight forward
			quadrant3=false;    //leave quadrant 3 set to false, as it is not in quadrant 3 yet
			}
		else if (error==666 && quadrant3==true){   //if all pixels read are black, and it is in quadrant 3
			sleep1(0,250000);                  //wait 1/4 of a second 
			getError();                        //Get the current error value
			if(error < 0){                     // Check if the current error value is less than 0
			turnRight(-60, 60);                // if the error is less than 0, turn right 
			sleep1(0,500000);                  // sleep for 1/2 of a second
			}
			else{				//if the error is greater than 0
			turnLeft(-50,50);   //turn left
			}
			sleep1(0,500000);   //sleep for 1/2 of a second
 			//printf("print\n");
			quadrant3=false;    // set quadrant 3 to be false
		}
		else if(error == 666){		// if every pixel reading is black
			turnLeft(-50,-50);		//go backwards at motorspeed 50
			quadrant3=false;		//set quadrant 3 to be false
			printf("Back\n");
		}
		else if (error == 420){		//if every pixel reading is white
			turnLeft(40,40);		//go straight ahead at motor speed 30
			sleep1(0,250000);
			//printf("white Line \n");
			quadrant3=true;			//set quadrant 3 to true; AV is now in quad 3
			}
		else if (error > 0){		//if the error value is greater than 0
			turnLeft(25,55);		//turn left to find the line
			quadrant3=false;		//set quadrant 3 to be false

		} else if (error < 0){		//if the error is less than 0
			turnRight(55,25);		//turn right to find the line
			quadrant3=false;		//set quadrant 3 to be false
		} 
		
		if((getSensor(2)>300) && (getSensor(0)>300) && gate>1200){
			quadrant4=true;
			quadrant1=false;
			quadrant2=false;
			quadrant3=false;
			printf("Quad4\n");
			}
		
		gate++;
		printf("%d\n",gate);
		return 0;
}

/**
right = 0
left = 2
front = 1
*/
int doQuad4(){
	int Left = getSensor(2);
	int Right = getSensor(0);
	int Front = getSensor(1);
	if(Left<Right){
		turnRight(50, 25);
	}
	if(Left>Right){
		turnLeft(50,25);
	}
	return 0;
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
			array[count]=1; //set the value in the array to 1
		}
		else{					//else, if the pixel is black
			array[count]=0;		//set the value in the array to 0
	  	}
    		count++;			//implement the counter so this is done for every pixel accros the image
	}
	for(int i=0; i<320; i++){			//for every value in the array
		if(array[i]==1){				//if the value read in the array is = 1, and therefore white
			error=error+(i-160.5)/4;	//set the error value to the previous error value, plus 1/4 of the position of the value in the array minus half of the array.
			whiteCount++;				//implement the white count to count how many white pixels there are
			//printf("1");
		}
		else if (array[i]==0){		//otherwise if the pixel is black
			blackCount++;			//implement balck count to count how many black pixels there are
			//printf("0");
		}

	}
	//printf("\n");
	if( blackCount == 320){		//if there are more than 320 black pixels
		error = 666;			// set error to 666
	}
	if( whiteCount > 310 ){		//if the white count is greater than 310
		if (quadrant1){			//if it is in quadrant 1
			quadrant1 = false;	//set quadrant 1 to false
			quadrant2 = true; 	//set quadrant 2 to true
		}
		
		else if (quadrant2){	//if quadrant 2 is already true
			error = 420;		//set error to 420
		}
	}
	return error;

}

