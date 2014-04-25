#include <iostream>
#include "SDL/SDL.h"
#include "Cart.h"
using namespace std;

int main(void){
	SDL_Surface* screen = NULL;
	SDL_Init( SDL_INIT_EVERYTHING );
	screen = SDL_SetVideoMode( 1200, 600, 32, SDL_SWSURFACE );
	Cart c1(500,300,200,100,screen);
	c1.m();
	SDL_Flip(screen);
	SDL_Delay(2000);
	SDL_Quit();

}
