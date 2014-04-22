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
		double x,y;			//position in pixels
		double length,width,angle;	//meters,meters,radians
		double angleSpeed;		//radians/s
		double speed;			//meters/s
		double direction;		//radians
		int hertz;			//per second
		void increment();
		void draw(int, int);
		int currTrack;
		double distTrack;
	private:
		SDL_Surface *screen;
};

#endif
