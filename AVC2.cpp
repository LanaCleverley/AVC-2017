#include "E101.h" 

int move(int error);
int getError();
int turnLeft(int leftMotor, int rightMotor);
int turnRight(int leftMotor, int rightMotor);


int main(){
	init();
	while(true){
		move(getError());
	}
}

int move(int error){
		int turn;

		//int error = getError();
		sleep1(0,50000);

		if(error > 0){
			turn = (int)((double)error/8000*50+50);
			turnLeft(15,50);

		} else if (error < 0){
			turn = (int)((double)error/8000*50+50);
			turnRight(50, 15);

		} else if(error == 0) {
			turnLeft(15,15);
		}
		else if(error == 66666){
			turnLeft(-15,-15);
		}
		return 0;
}

int turnLeft(int leftMotor, int rightMotor){

	set_motor(1,- leftMotor);
	set_motor(2,- rightMotor);
	return 0;
}

int turnRight(int leftMotor, int rightMotor){
	set_motor(1,- leftMotor);
	set_motor(2,- rightMotor);
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
		if(pixel > 100){ // if the pixel is white
			array[count]=1;
		}
		else{
			array[count]=0;
	  	}
	//	printf("%d", array[count]);

    		count=count+1;
	}
	//	printf("\n");
	for(int i=0; i<320; i++){
		if(array[i]==1){
			error=error+(i-160.5)/2;
		}
		else if (array[i]==0){
			blackCount++;
		}
	}

//		printf("Error = %d\n", error);
	if( blackCount == 320){
		error = 66666;
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
