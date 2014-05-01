//RollerCoaster Class
//This holds everything having to do with the RollerCoaster interface.


#ifndef ROLLERCOASTER_H
#define ROLLERCOASTER_H
 
#include <iostream>
#include "Rating.h"
#include "Finances.h"
#include "TrackPiece.h"
#include "Button.h"
#include "Menu.h"
#include "Cart.h"
#include <string>
#include <vector>
#include "SDL/SDL.h"
using namespace std;

class RollerCoaster{

private:
	//All of these surfaces load in all the PNGs that will be used in the drawing
	SDL_Surface *screen;						//The screen that everything will be drawn to
	SDL_Surface *backG;						//The Grass on the ground
	SDL_Surface *backSky;						//The sky
	SDL_Surface *cartPNG;						//The cart
	SDL_Surface *highlightedTrackPNG;				//The highlighted trackpiece
	SDL_Surface *track1PNG;						//Four different color
	SDL_Surface *track2PNG;						//trackpieces to represent the
	SDL_Surface *track3PNG;						//different types of track
	SDL_Surface *track4PNG;
	SDL_Surface *cloud1PNG;						//Different clouds that are in the sky
	SDL_Surface *cloud2PNG;
	SDL_Surface *cloud3PNG;
	SDL_Surface *cloud4PNG;
	int PNGHheight;							//PNGheights that are needed for drawing rotated tracks
	int PNGheight;
	SDL_Surface *menuBackPNG;					//Can be drawn as the back of the menu -- not used
	SDL_Surface *blankPNG;						//A white button -- used to show that the button is clicked
	SDL_Surface *button0PNG;					//All 10 buttons
	SDL_Surface *button1PNG;
	SDL_Surface *button2PNG;
	SDL_Surface *button3PNG;
	SDL_Surface *button4PNG;
	SDL_Surface *button5PNG;
	SDL_Surface *button6PNG;
	SDL_Surface *button7PNG;
	SDL_Surface *button8PNG;
	SDL_Surface *button9PNG;
	int peopleOnRide;						//The people on ride and maximum people on ride
	int maxPeopleOnRide;
	int connected;							//not used -- says that the tracks are connected
	int cursorType;
	int currOffsetX, currOffsetY, lastOffsetX,lastOffsetY;		//Offsets
	int trackAdd;							//type of track currently being added
	int dragStatus;							//Controls the dragging of the screen
	int lastDragX,lastDragY;					
	int nStations;
	int currTrack;
	int OperationStatus;						//open or closed
	Menu *mainMenu;
	Finances *F1;
	string name;
	int nCarts;							//nCarts -- 1,2 or 3
	vector<int> cloudVec;						//vector of clouds that are in the sky
	vector<int> speedVec;						//speed and angle measurements at each frame - used to measure ratings
	vector<double> angleVec;
	vector<SDL_Surface *> myVec;					//holds all the buttons to pass into the menu
	vector<Cart *> carts;
	vector<TrackPiece> track;					//the trackpieces
	vector<TrackPiece> cbTrack;
	vector<TrackPiece> bottomTrack;
	vector<Uint16> clicks;						//holds info about user clicks
	Rating rating;							//ratings of the coaster
	int exitInterface;						//used to leave the while loop
	int selectTrack(double,double);					//tells what track you picked
	int addTrack(double,double,double,double);			//adds a track to the track vector
	double distance(double,double,double,double);			//calculates the distance between two points
	void setupClouds();						//generates where the clouds should be
	void sell();							//sells coaster
	void checkPlace(Cart *);					//makes sure Cart is in the right place -- called by play
	int updateSpeed(Cart *,int,int);				//changes the speed of the cart
	int getBroken();						//says if the coaster is broken up or not
	void parseTrackInfo(double,double,double,double,double,double); //tells what to do with adding the track
	void menuChanges(int);						//based on button clicks, updates variables
	void placeStation();						//place station piece
	void parseInfo(double,double);					//parses what to do with a click
	void parseDrag(Uint16, Uint16,int);				//controls drag
	void drawMenu();						
	void drawCurrent(int);						//draws current picture
	void play(int);							//plays and rates the rollerCoaster -- argument allows for no animation (ie it will only rate it
public:
	int worth;
	void setFinances(Finances *);					//lets you pass a pointer to the finances to the rollercoaster so you can buy/sell stuff
	RollerCoaster();
	void rateCoaster();
	void load(int,int);						//loads rollercoaster from file
	void displayInterface(int,int);					//allows editing and playing of rollerCoaster
};
#endif
