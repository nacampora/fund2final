#include "Cart.h"
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


void Cart::draw(){
	
	lineRGBA(screen,x-length*sin(angle)/2-width*cos(angle)/2,y-length*cos(angle)/2+width*sin(angle)/2,x-length*sin(angle)/2+width*cos(angle)/2,y-length*cos(angle)/2-width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x-length*sin(angle)/2+width*cos(angle)/2,y-length*cos(angle)/2-width*sin(angle)/2,x+length*sin(angle)/2+width*cos(angle)/2,y+length*cos(angle)/2-width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x+length*sin(angle)/2+width*cos(angle)/2,y+length*cos(angle)/2-width*sin(angle)/2,x+length*sin(angle)/2-width*cos(angle)/2,y+length*cos(angle)/2+width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x+length*sin(angle)/2-width*cos(angle)/2,y+length*cos(angle)/2+width*sin(angle)/2,x-length*sin(angle)/2-width*cos(angle)/2,y-length*cos(angle)/2+width*sin(angle)/2,255,255,255,255);
}

void Cart::m(){
	angleSpeed=.3;
	while(angle<=M_PI/2){
		draw();
		SDL_Flip(screen);
		SDL_Delay(100);
		increment();
	}
	SDL_Delay(5000);
}




