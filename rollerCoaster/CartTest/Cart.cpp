#include "Cart.h"
#include "Force.h"
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <math.h>
using namespace std;


Cart::Cart(double x1,double y1,int w,int l,SDL_Surface *s){
	hertz = 20;
	width=w;
	length=l;
	screen=s;
	angle=0;
	x=x1;
	y=y1;
	angleSpeed=0;
	speed=0;
	direction=0;
	ppm=100;
}

void Cart::increment(){
	angle+=angleSpeed/hertz;
	x+=ppm*speed*cos(direction);
	y+=ppm*speed*sin(direction);
}

void Cart::addForce(Force f){
	forceVec.push_back(f);
}

void Cart::applyForces(){
	for(vector<Force>::iterator it=forceVec.begin(); it!=forceVec.end(); it++){
		(it->remaining)--;
		if(it->remaining==0){
			forceVec.erase(it);
			it--;
			continue;
		}
		
			
	}
}

void Cart::printForces(){
	for(vector<Force>::iterator it=forceVec.begin(); it!=forceVec.end();it++){
		it->printOut();
	}
}

void Cart::draw(){
	lineRGBA(screen,x-length*sin(angle)/2-width*cos(angle)/2,y-length*cos(angle)/2+width*sin(angle)/2,x-length*sin(angle)/2+width*cos(angle)/2,y-length*cos(angle)/2-width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x-length*sin(angle)/2+width*cos(angle)/2,y-length*cos(angle)/2-width*sin(angle)/2,x+length*sin(angle)/2+width*cos(angle)/2,y+length*cos(angle)/2-width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x+length*sin(angle)/2+width*cos(angle)/2,y+length*cos(angle)/2-width*sin(angle)/2,x+length*sin(angle)/2-width*cos(angle)/2,y+length*cos(angle)/2+width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x+length*sin(angle)/2-width*cos(angle)/2,y+length*cos(angle)/2+width*sin(angle)/2,x-length*sin(angle)/2-width*cos(angle)/2,y-length*cos(angle)/2+width*sin(angle)/2,255,255,255,255);
}

void Cart::m(){
	speed=1;
	angleSpeed=1;
	for(int F=0;F<6;F++){
		draw();
		SDL_Flip(screen);
		SDL_Delay(500);
		increment();
	}
}




