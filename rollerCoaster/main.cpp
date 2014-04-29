#include <iostream>
using namespace std;

#include "RollerCoaster.h"

int main(void){
	SDL_Surface* screen = NULL;
	SDL_Init( SDL_INIT_EVERYTHING );
//	screen = SDL_SetVideoMode( 1300, 650, 32, SDL_SWSURFACE ); 
	RollerCoaster R1;
	R1.displayInterface(1,1);
	remove ("dir/file1");
	remove ("dir/file2");
	remove ("dir/file3");
}
