//Cart Class
//
//This is the actual RollerCoaster car that is drawn to the screen.
//

#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include "SDL/SDL.h"
using namespace std;

class Cart{
	public:
		Cart(double,double,int length,int width,SDL_Surface *);
		int ppm;			//pixels per meter
		double x,y,lastx,lasty;		//position in pixels
		double length,width,angle;	//meters,meters,radians
		double angleSpeed;		//radians/s
		double speed;			//meters/s
		double direction;		//radians
		int hertz;			//per second
		double fixedX,fixedY;
		void increment();
		void draw(int, int,SDL_Surface *,SDL_Surface *);
		int currTrack;
		double distTrack;		//These are the current track, and distance along the tracks of the cart, and each of the wheels.
		int fwCurrTrack;
		double fwDistTrack;
		int swCurrTrack;
		double swDistTrack;
	private:
		SDL_Surface *screen;
};

#endif
