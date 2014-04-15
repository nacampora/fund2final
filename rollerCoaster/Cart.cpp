#include "Cart.h"
#include "Force.h"
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <math.h>
using namespace std;


Cart::Cart(double x1,double y1,int w,int l,SDL_Surface *s){
	width=w;
	length=l;
	screen=s;
	ang=0;
	x=x1;
	y=y1;
	angleSpeed=0;
	speed=0;
	direction=0;
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
	lineRGBA(screen,x,y,x+width*cos(ang),y-width*sin(ang),255,255,255,255);
	lineRGBA(screen,x,y,x+length*sin(ang),y+length*cos(ang),255,255,255,255);
	lineRGBA(screen,x+length*sin(ang),y+length*cos(ang),x+length*sin(ang)+width*cos(ang),y-width*sin(ang)+length*cos(ang),255,255,255,255);
	lineRGBA(screen,x+length*sin(ang)+width*cos(ang),y-width*sin(ang)+length*cos(ang),x,y,255,255,255,255);
}






	
