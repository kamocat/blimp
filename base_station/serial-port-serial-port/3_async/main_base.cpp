#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include <time.h>
#include <iostream>
#include <boost/thread.hpp>
//#include "SimpleSerial.h"

#include "BufferedAsyncSerial.h"

using namespace std;
using namespace boost;
 
void sleep_2(unsigned int mseconds);
void *threadCode(void *data);

int start_tx = 254;
int exit_i;
int left_i;
int right_i;
int servo_i;
char send_string[6];
int debug;


int main(int argc, char *argv[]){
	long n; 
	int m;
	n = 0;
	pthread_t thread;

	debug = 0;

	left_i = 127;
	right_i = 127;
	servo_i = 1;
	printf("Main: creating thread\n");
	int rc = pthread_create(&thread, NULL , threadCode, (void *)n );
	if (rc){
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	exit_i = 0;
	printf("Main: loop\n");
	while(exit_i == 0){
		sleep_2 (10000);
		//char send_string[3];
		//char left_h
		//char right_h
		//char servo_h
		//sleep(10);
		printf("Main:   %d\t%d\t%d\t%d\n",start_tx, left_i,right_i,servo_i);
		m=sprintf(send_string,"%c%c%c%c\n",start_tx,left_i,right_i,servo_i);
		//printf("%s",m);

		//n=sprintf (buffer, "%c%c%c\n",a,b,c);

		try{
			BufferedAsyncSerial serial("/dev/ttyUSB2",9600);
			serial.writeString(send_string);
			this_thread::sleep(posix_time::seconds(2));
			std::string s = serial.readStringUntil("\r\n");
			cout<<"\t\t\t\t\tReceived : " << s <<" : end"<<endl;
			
			serial.close();
		}
		catch(boost::system::system_error& e){
			cout<<"Error: "<<e.what()<<endl;
		return 1;
	}



	}
	printf("exiting\n");
	pthread_exit(NULL);
}


void *threadCode(void *data){
	int select = 0, start = 0;

	int milisec = 50;
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec*1000000L;


	if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
	printf("The names of the joysticks are:\n");
	int i =0;       
	for( i=0; i < SDL_NumJoysticks(); i++ ) 
	{
		printf("    %s\n", SDL_JoystickName(i));
	}
	SDL_Joystick *joystick;
	SDL_Event event;
	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	printf("With %i joysticks", SDL_JoystickNumAxes(joystick));
	exit_i = 0;
	while(!exit_i){
//		Sleep(50);
		nanosleep(&req, (struct timespec *)NULL);	
		while(SDL_PollEvent(&event)){  
			switch(event.type){  
				/*case SDL_KEYDOWN:
				/* handle keyboard stuff here                            
				break;*/

				/*case SDL_QUIT:
				break;*/
				case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
					/*if ( ( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) {*/
					if(true){
						int v1 = event.jaxis.value;
						int v = -v1/260;
						/*printf("%d\t%d \n",event.jaxis.value ,v);*/
						if(v > 127){
							v = 127;
						}else if(v < -127){
							v = -127;
						}
						/*printf("%d:\t%d \n",event.jaxis.axis, v);*/
						
						/*
						if(event.jaxis.axis == 0){
							/* Left-right for joystick one 
							/*printf("%d \n", event.jaxis.value);
							printf("%d \n", v);
						}
						*/
						if(event.jaxis.axis == 1){
							/* Up-Down movement code goes here for left Joystick */
							if(debug == 1){
								printf("Thread: Left:\t%d\t%d\n",v1, v);
							}
							left_i = v+127;
						}
						/*
						if(event.jaxis.axis == 2){
							/* Up-Down movement code goes here for left Joystick 
							printf("%d \n", v);
						}

						if(event.jaxis.axis == 3){
							/* Up-Down movement code goes here for left Joystick 
							printf("%d \n", v);
						}
						*/
						if(event.jaxis.axis == 4){
							/* Up-Down movement code goes here for left Joystick*/ 
							if(debug == 1){
								printf("Thread: Right:\t%d\t%d\n",v1, v);
							}
							right_i = v+127;
						}
						/*
						if(event.jaxis.axis == 5){
							/* Up-Down movement code goes here for left Joystick 
							printf("%d \n", v);
						}*/

					}
				break;
				case SDL_JOYHATMOTION:  /* Handle Hat Motion */
					/*if ( event.jhat.value & SDL_HAT_UP ){
						printf("Up\n");
					}
					if ( event.jhat.value & SDL_HAT_LEFT ){
						printf("Left\n");
					}
					if ( event.jhat.value & SDL_HAT_RIGHT ){
						printf("Right\n");
					}
					if ( event.jhat.value & SDL_HAT_DOWN ){
						printf("Down\n");
					}
					if ( event.jhat.value & SDL_HAT_CENTERED ){
						printf("Centered\n");
					}*/
				break;
				case SDL_JOYBUTTONDOWN:
					
					
					if(event.jbutton.button == 0){
						printf("%s\n", "debug");
						debug = !debug;
					}
					/*
					if(event.jbutton.button == 1){
						printf("%s\n", "B");
					}
					if(event.jbutton.button == 2){
						printf("%s\n", "X");
					}*/
					if(event.jbutton.button == 3){
						printf("%s\n", "Y");
						left_i = 127;
						right_i = 127;
						servo_i = 1;
					}
					if(event.jbutton.button == 4){
						if(debug == 1){
							printf("Thread: Down:   %s\n", "LB");
						}
						servo_i = 1;
					}
					if(event.jbutton.button == 5){
						if(debug == 1){
							printf("Thread: Up:     %s\n", "RB");
						}
						servo_i = 3;
					}
					if(event.jbutton.button == 6){
						if(debug == 1){
							printf("Thread: %s\n", "Down Select");
						}
						select = 1;
					}
					if(event.jbutton.button == 7){
						if(debug == 1){
							printf("Thread: %s\n", "Down Start");
						}
						start = 1;
					}
					/*if(event.jbutton.button == 9){
						printf("%s\n", "Left Joy Stick");
					}*/
					if(event.jbutton.button == 8){
						if(debug == 1){
							printf("Thread: %s\n", "xbox Button");
						}
						exit_i = 1;	
					}
					/*if(event.jbutton.button == 10){
						printf("%s\n", "Right Joy Stick");
					}*/
					if(select == 1 && start == 1){
						exit_i = 1;
					}
					
				break;
				case SDL_JOYBUTTONUP:
					/*if(event.jbutton.button == 0){
						printf("%s\n", "A");
						debug = 0;
					}
					
					if(event.jbutton.button == 1){
						printf("%s\n", "B");
					}
					if(event.jbutton.button == 2){
						printf("%s\n", "X");
					}
					if(event.jbutton.button == 3){
						printf("%s\n", "Y");
					}*/
					if(event.jbutton.button == 4){
						if(debug == 1){
							printf("Thread: Up:     %s\n", "LB");
						}
						servo_i = 2;
					}
					if(event.jbutton.button == 5){
						if(debug == 1){
							printf("Thread: Up:     %s\n", "RB");
						}
						servo_i = 2;
					}
					if(event.jbutton.button == 6){
						if(debug == 1){
							printf("Thread: %s\n", "Up Select");
						}
						select = 0;
					}
					if(event.jbutton.button == 7){
						if(debug == 1){
							printf("Thread: %s\n", "Up Start");
						}
						start = 0;
					}/*
					if(event.jbutton.button == 8){
						printf("%s\n", "Left Joy Stick");
					}
					if(event.jbutton.button == 9){
						printf("%s\n", "Right Joy Stick");
					}
					if(event.jbutton.button == 10){
						printf("%s\n", "Right Joy Stick");
					}
					*/
				break;
				
			}
		}
	}

}


 
void sleep_2(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

