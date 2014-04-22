#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include "SDL/SDL.h"
using namespace std;

class Button{
private:
	int checked;
	int size;
public:
	Button(double,double,int=10);
	double cornerX,cornerY;
	void draw(SDL_Surface *,int);
	void toggle();
	int getState();
	void move(double,double);
	int getSize();
};

#endif
