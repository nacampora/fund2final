//FILE NOT CURRENTLY USED IN ROLLER COASTER PROJECT

#include <iostream>
using namespace std;

#include "RollerCoaster.h"

int main(void){
	SDL_Surface* screen = NULL;
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode( 1300, 650, 32, SDL_SWSURFACE ); 
	RollerCoaster R1(screen,"First Roller Coaster");
	R1.displayInterface();
}
