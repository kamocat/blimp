#include <stdlib.h>
#include "SDL/SDL.h"
#include <stdio.h>
#include <time.h>
//#include "windows.h"

SDL_Surface *screen;
// Entry point
int main(int argc, char *argv[]){
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
	int exit = 0;
	while(!exit){
//		Sleep(50);
		nanosleep(&req, (struct timespec *)NULL);	
		while(SDL_PollEvent(&event)){  
			switch(event.type){  
				case SDL_KEYDOWN:
				/* handle keyboard stuff here */                            
				break;

				case SDL_QUIT:
				break;
				case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
					if ( ( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) {
						int v = -event.jaxis.value/260;
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
							printf("Left:   %d \n", v);
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
							printf("Right:  %d \n", v);
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
					
					/*
					if(event.jbutton.button == 0){
						printf("%s\n", "A");
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
						printf("Down:   %s\n", "LB");
					}
					if(event.jbutton.button == 5){
						printf("Up:     %s\n", "RB");
					}
					if(event.jbutton.button == 6){
						printf("%s\n", "Down Select");
						select = 1;
					}
					if(event.jbutton.button == 7){
						printf("%s\n", "Down Start");
						start = 1;
					}
					/*if(event.jbutton.button == 9){
						printf("%s\n", "Left Joy Stick");
					}*/
					if(event.jbutton.button == 8){
						printf("%s\n", "xbox Button");
						exit = 1;	
					}
					/*if(event.jbutton.button == 10){
						printf("%s\n", "Right Joy Stick");
					}*/
					if(select == 1 && start == 1){
						exit = 1;
					}
					
				break;
				case SDL_JOYBUTTONUP:
					/*if(event.jbutton.button == 0){
						printf("%s\n", "A");
					}
					if(event.jbutton.button == 1){
						printf("%s\n", "B");
					}
					if(event.jbutton.button == 2){
						printf("%s\n", "X");
					}
					if(event.jbutton.button == 3){
						printf("%s\n", "Y");
					}
					if(event.jbutton.button == 4){
						printf("%s\n", "LB");
					}
					if(event.jbutton.button == 5){
						printf("%s\n", "RB");
					}	*/
					if(event.jbutton.button == 6){
						printf("%s\n", "Up Select");
						select = 0;
					}
					if(event.jbutton.button == 7){
						printf("%s\n", "Up Start");
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
	return 1;
}
