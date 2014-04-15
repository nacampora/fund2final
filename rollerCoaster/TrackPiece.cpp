
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
using namespace std;

#include "TrackPiece.h"

TrackPiece::TrackPiece(double x1,double y1,double x2,double y2,int track){
	startX=x1;
	startY=y1;
	endX=x2;
	endY=y2;
	trackType=track;
}

void TrackPiece::drawPiece(SDL_Surface *s,int offsetX,int offsetY){
	lineRGBA(s,startX-offsetX,startY+offsetY,endX-offsetX,endY+offsetY,255,255,255,255);
}
