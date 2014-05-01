#include <iostream>
using namespace std;

#include "RollerCoaster.h"

int main(void){
	SDL_Surface* screen = NULL;
	SDL_Init( SDL_INIT_EVERYTHING );
	RollerCoaster R1;
	R1.displayInterface(1,1);
	R1.rateCoaster();
}
