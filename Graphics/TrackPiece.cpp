
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
using namespace std;

#include "TrackPiece.h"
#define base 15
#define width 1300
#define height 650
double dist(double x1,double y1,double x2,double y2){
	return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}
TrackPiece::TrackPiece(double x1,double y1,double x2,double y2,int track){
	startX=x1;
	startY=y1;
	endX=x2;
	endY=y2;
	trackType=track;
}


double TrackPiece::findAngle(){
	double d= dist(startX,startY,endX,endY);
	double ang;
	double xdist=endX-startX;
	double ydist=startY-endY;
	if(xdist>=0 && ydist>=0){
		ang=asin(ydist/d);
	}else if(xdist<0 && ydist>=0){
		ang=(M_PI/2)-asin(ydist/d)+M_PI/2;
	}else if(xdist<0 && ydist<0){
		ang=asin(-ydist/d)+M_PI;
	}else if(xdist>=0 && ydist <0){
		ang=M_PI/2-asin(-ydist/d)+3*M_PI/2;
	}else{
		ang=0;
	}
	return ang;
}

void TrackPiece::drawPiece(SDL_Surface *s,SDL_Surface *tr,int offsetX,int offsetY){
	if(startY>height){
		startY=startY-65535;
	}
	if(endY>height){
		endY=endY-65535;
	}
	SDL_Rect offset;
	offset.x=startX-offsetX;
	offset.y=startY+offsetY;
	double d = dist(startX,startY,endX,endY);
	int nPieces=(int)(d/base);
	double left = d-nPieces*base;
	double ang=findAngle();
	if(ang>0 && ang<M_PI/2){
		offset.y-=base*sin(ang);
	}else if(ang>=M_PI/2 && ang<M_PI){
		offset.x-=base*sin(ang-M_PI/2);
		offset.y-=base*cos(ang-M_PI/2);
	}else if(ang>=M_PI && ang < M_PI*3/2){
		offset.x-=base*cos(ang-M_PI);
	}
	double ix=offset.x;
	double iy=offset.y;
	for(int F=1;F<=nPieces;F++){
		SDL_Surface *rotatedImg=rotozoomSurface(tr,ang*360/(2*M_PI),1.0,0);
		if(offset.x>0 && offset.x<width && offset.y>0 && offset.y < height){
			SDL_BlitSurface(rotatedImg,NULL,s,&offset);
		}
		if(F<nPieces){
			offset.x=F*base*cos(ang)+ix;
			offset.y=-F*base*sin(ang)+iy;
		}else{
			if(left>base-1){
				offset.x=F*base*cos(ang)+ix;
				offset.y=-F*base*sin(ang)+iy;
			}
		}
	}
	SDL_Surface *rotatedImg=rotozoomSurface(tr,ang*360/(2*M_PI),1.0,0);
	if(offset.x>0 && offset.x<width && offset.y>0 && offset.y < height){
		SDL_BlitSurface(rotatedImg,NULL,s,&offset);
	}
//	lineRGBA(s,ix,iy,offset.x,offset.y,155,155,155,155);	
	
}
