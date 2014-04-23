#ifndef MENU_H
#define MENU_H

#include <iostream>
using namespace std;

#include "Button.h"
#include <vector>
class Menu{

private:
	vector <Button> b;
	vector <double> rect;
	double x,y;
	int ratio;
	int buttonSize;
	void addButton();	
	SDL_Surface *s;
public:
	Menu(SDL_Surface *,double,double,int,int);
	vector<double> findPlace(int,int);
	int buttonClicked(double,double);
	void toggle(int);
	int getState(int);
	void move(double, double);
	void draw(SDL_Surface *,vector<SDL_Surface *>);
	vector<double> menuBox();
};

#endif
