//Button Class
//
//This is the class that controls the Buttons that are inside the menu.
//Each button has basic checkbox functionality, but depending on the button some are used differently
#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include "SDL/SDL.h"
using namespace std;

class Button{
private:
	int checked;	//if the button is clicked or not
	int size;	//size of the button in pixels
public:
	Button(double,double,int=10);
	double cornerX,cornerY;
	void draw(SDL_Surface *,int);
	void toggle();
	int getState();			//returns checked
	void move(double,double);	//can move a button to a spot, never used in this projet
	int getSize();			//returns size
};

#endif
