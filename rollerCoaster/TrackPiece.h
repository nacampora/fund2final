#ifndef TRACKPIECE_H
#define TRACKPIECE_H

#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
using namespace std;

class TrackPiece{

public:
	TrackPiece(double=0,double=0,double=1,double=1,int=0);		// Default Constructor
	double startX;		//Coordinates of track piece
	double startY;
	double endX;
	double endY;
	double trackType;		//Regular, Station, Chain, Shootoff
	void drawPiece(SDL_Surface *,int,int);
};
#endif
