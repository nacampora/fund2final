//Menu Class
//This menu is filled with n number of check boxes that can have different PNGs loaded in.

#ifndef MENU_H
#define MENU_H

#include <iostream>
using namespace std;

#include "Button.h"
#include <vector>
class Menu{

private:
	vector <Button> b;		//buttons of the menu
	vector <double> rect;
	double x,y;
	int ratio;			//ratio of height to width of menu, automatically forms the menu based on this ratio
	int buttonSize;
	void addButton();		//never actually used in this project, still good to have	
	SDL_Surface *s;	
	int isInsideBox(double,double,double,double,double,double);		//for checking what button was clicked
public:
	Menu(SDL_Surface *,double,double,int,int);
	vector<double> findPlace(int,int);
	int buttonClicked(double,double);		//tells which button was clicked.  -1 if no button but on the menu, -2 if not on menu at all.
	void toggle(int);			//toggles button n
	int getState(int);			//gets State of button n
	void move(double, double);
	void draw(SDL_Surface *,vector<SDL_Surface *>);		//draws the menu
	vector<double> menuBox();
};

#endif
