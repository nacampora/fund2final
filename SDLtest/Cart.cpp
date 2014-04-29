#include "hfiles/Cart.h"
#include <iostream>
#include "SDL/SDL.h"
//#include "SDL/SDL_gfxPrimitives.h"
#include <math.h>
#include "SDL/SDL_rotozoom.h"
using namespace std;


Cart::Cart(double x1,double y1,int w,int l,SDL_Surface *s){
	fixedX=0;
	fixedY=0;
	distTrack=0;
	currTrack=0;
	fwCurrTrack=0;
	swCurrTrack=0;
	hertz = 20;
	width=w;
	length=l;
	screen=s;
	angle=0;
	x=x1;
	y=y1;
	angleSpeed=0;
	speed=0;
	direction=0;
	ppm=1;
}

void Cart::increment(){
	angle+=angleSpeed/hertz;
	x+=ppm*speed*cos(direction);
	y-=ppm*speed*sin(direction);
}


void Cart::draw(int Ox,int Oy,SDL_Surface *s,SDL_Surface *cartPNG){
	double savex = x;
	double savey = y;
	x = fixedX-Ox;
	y = fixedY+Oy;
	SDL_Rect offset;
	offset.x=x-length*sin(angle)/2-width*cos(angle)/2;
	offset.y=y-length*cos(angle)/2+width*sin(angle)/2;
	if(angle>0 && angle<M_PI/2){
		offset.y-=width*sin(angle);
	}else if(angle>=M_PI/2 && angle<M_PI){
		offset.y-=2*length*cos(angle-M_PI/2);
		offset.y-=width*sin(angle-M_PI/2)/2;
		offset.x-=2*length*sin(angle-M_PI/2);
	}else if(angle>=M_PI && angle < M_PI*3/2){
		offset.x-=2*length*cos(angle-M_PI);
		offset.x-=width*sin(angle-M_PI)/1.66;
		offset.y-=width*cos(angle-M_PI)/1.66;
	}else if(angle>=M_PI*3/2 && angle<=2*M_PI){
		offset.x-=length*cos(angle-3*M_PI/2);
	}
	if(angle<=M_PI || angle>=3*M_PI/2){
		offset.x-=5*cos(angle+M_PI/2);
		offset.y+=5*sin(angle+M_PI/2);
	}else{
		offset.x+=8*cos(angle+M_PI/2);
		offset.y-=8*sin(angle+M_PI/2);
	}
	SDL_Surface *rotatedImg=rotozoomSurface(cartPNG,angle*360/(2*M_PI),1.0,0);
	SDL_BlitSurface(rotatedImg,NULL,s,&offset);
/*	lineRGBA(screen,x-length*sin(angle)/2-width*cos(angle)/2,y-length*cos(angle)/2+width*sin(angle)/2,x-length*sin(angle)/2+width*cos(angle)/2,y-length*cos(angle)/2-width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x-length*sin(angle)/2+width*cos(angle)/2,y-length*cos(angle)/2-width*sin(angle)/2,x+length*sin(angle)/2+width*cos(angle)/2,y+length*cos(angle)/2-width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x+length*sin(angle)/2+width*cos(angle)/2,y+length*cos(angle)/2-width*sin(angle)/2,x+length*sin(angle)/2-width*cos(angle)/2,y+length*cos(angle)/2+width*sin(angle)/2,255,255,255,255);
	lineRGBA(screen,x+length*sin(angle)/2-width*cos(angle)/2,y+length*cos(angle)/2+width*sin(angle)/2,x-length*sin(angle)/2-width*cos(angle)/2,y-length*cos(angle)/2+width*sin(angle)/2,255,255,255,255);
*/
	x=savex;
	y=savey;
}

