
#include <iostream>
using namespace std;

#include "hfiles/Button.h"
#include "SDL/SDL.h"
//#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include <string>
#include <stdlib.h>
#include <sstream>
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

void Button::draw(SDL_Surface *s,int buttonNum){
	//rectangleRGBA(s,cornerX,cornerY,cornerX+size,cornerY+size,255,255,255,255);
	SDL_Surface *button;
	string r="buttons/button";
	string w=".png";
	stringstream ss;
	ss << 1;
	string str=ss.str();
	string tot = r+str+w;
	button=IMG_Load("tot");
	SDL_Rect offset;
	offset.x=cornerX;
	offset.y=cornerY;
	SDL_BlitSurface(button,NULL,s,NULL);
	/*if(checked==1){
		lineRGBA(s,cornerX,cornerY,cornerX+size,cornerY+size,255,255,255,255);
		lineRGBA(s,cornerX+size,cornerY,cornerX,cornerY+size,255,255,255,255);
	}*/
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
