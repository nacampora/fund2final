#include <iostream>
using namespace std;

#include "Button.h"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

Button::Button(double x,double y,int s){
	cornerX=x;
	cornerY=y;
	size=s;
	checked=0;
}

void Button::toggle(){
	if(checked==0){
		checked=1;
	}else{
		checked=0;
	}
}

void Button::draw(SDL_Surface *s){
	rectangleRGBA(s,cornerX,cornerY,cornerX+size,cornerY+size,255,255,255,255);
	if(checked==1){
		lineRGBA(s,cornerX,cornerY,cornerX+size,cornerY+size,255,255,255,255);
		lineRGBA(s,cornerX+size,cornerY,cornerX,cornerY+size,255,255,255,255);
	}	
}

int Button::getSize(){
	return size;
}

void Button::move(double x1,double y1){
	cornerX=x1;
	cornerY=y1;
}

int Button::getState(){
	return checked;
}
