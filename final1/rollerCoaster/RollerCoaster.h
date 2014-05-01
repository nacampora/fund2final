#ifndef ROLLERCOASTER_H
#define ROLLERCOASTER_H
 
#include <iostream>
#include "Rating.h"
//#include "Finances.h"
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
	SDL_Surface *screen;
	SDL_Surface *backG;
	SDL_Surface *backSky;
	SDL_Surface *cartPNG;
	SDL_Surface *trackPNG;
	int PNGheight;
	SDL_Surface *menuBackPNG;
	SDL_Surface *blankPNG;
	SDL_Surface *button0PNG;
	SDL_Surface *button1PNG;
	SDL_Surface *button2PNG;
	SDL_Surface *button3PNG;
	SDL_Surface *button4PNG;
	SDL_Surface *button5PNG;
	SDL_Surface *button6PNG;
	SDL_Surface *button7PNG;
	int peopleOnRide;
	int maxPeopleOnRide;
	int connected;
	int cursorType;
	int currOffsetX, currOffsetY, lastOffsetX,lastOffsetY;
	int trackAdd;
	int dragStatus;
	int lastDragX,lastDragY;
	int nStations;
	int currTrack;
	int OperationStatus;
	int rideEntranceFee;
	Menu *mainMenu;
//	Finances *F1;
	string name;
	int nCarts;
	vector<SDL_Surface *> myVec;
	vector<Cart *> carts;
	vector<TrackPiece> track;
	vector<Uint16> clicks;
	Rating rating;
	string getName();
	int selectTrack(double,double);
	int addTrack(double,double,double,double);
	int getRideEntranceFee();
	double distance(double,double,double,double);
	void increaseRideEntranceFee();
	void decreaseRideEntranceFee();
	void checkPlace(Cart *);
	void updateSpeed(Cart *,int,int);
	void parseTrackInfo(double,double,double,double,double,double);
	void menuChanges(int);
	void setName(string);
	void rateCoaster();
	void placeStation();
	void parseInfo(double,double);
	void parseDrag(Uint16, Uint16,int);
	void drawMenu();
	void drawCurrent();
	void play();
public:
	int worth;
	RollerCoaster(SDL_Surface *,string);
	void displayInterface();	
};
#endif