#ifndef ROLLERCOASTER_H
#define ROLLERCOASTER_H
 
#include <iostream>
#include "Rating.h"
#include "TrackPiece.h"
#include "Button.h"
#include "Menu.h"
#include <string>
#include <vector>
#include "SDL/SDL.h"
using namespace std;

class RollerCoaster{

private:

	int connected;
	int cursorType;
	int currOffsetX, currOffsetY, lastOffsetX,lastOffsetY;
	int trackAdd;
	int dragStatus;
	int lastDragX,lastDragY;
	int nStations;
	Menu *mainMenu;
	string name;
	SDL_Surface *screen;
	int OperationStatus;
	vector<TrackPiece> track;
	vector<Uint16> clicks;
	Rating rating;
	int currTrack;
	string getName();
	void parseTrackInfo(double,double,double,double,double,double);
	void menuChanges(int);
	void setName(string);
	void rateCoaster();
	void placeStation();
	void selectTrack(double,double);
	void addTrack(double,double,double,double);
	void removeTrack();
	void autoComplete();
	void parseInfo(Uint16, Uint16);
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
