//Button Class Member Functions

#include <iostream>
using namespace std;

#include "Button.h"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include <string>
#include <stdlib.h>
#include <sstream>
Button::Button(double x,double y,int s){
	cornerX=x;	
	cornerY=y;	//places the button and sets its variables
	size=s;
	checked=0;
}

void Button::toggle(){
	if(checked==0){
		checked=1;		//changes state of checked
	}else{
		checked=0;
	}
}


void Button::draw(SDL_Surface *s,int buttonNum){
	SDL_Surface *button;
	string r="buttons/button";
	string w=".png";
	stringstream ss;
	ss << 1;
	string str=ss.str();
	string tot = r+str+w;
	button=IMG_Load("tot");
	SDL_Rect offset;							//This function draws the buttons
	offset.x=cornerX;							//It is not used because the menu
	offset.y=cornerY;							//draws the buttons
	SDL_BlitSurface(button,NULL,s,NULL); 
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
