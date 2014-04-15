#ifndef CART_H
#define CART_H

#include "Force.h"
#include <iostream>
#include "SDL/SDL.h"
using namespace std;

class Cart{
	public:
		Cart(double,double,int length,int width,SDL_Surface *);
		double x,y;
		double length,width,angle;
		double angleSpeed;
		double speed;
		double direction;
		void addForce(Force);
		void applyForces();
		void printForces();
		void draw();
	private:
		vector<Force> forceVec = new vector<Force>;
		SDL_Surface *screen;
};

#endif
