#include "RollerCoaster.h"
#include "Button.cpp"
#include "Menu.cpp"
#include "global.cpp"
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
using namespace std;

int windowHeight=500;

RollerCoaster::RollerCoaster(SDL_Surface *r,string s){
	trackAdd=1;		//Type of track you are using
	name = s;		//Name the RollerCoaster
	OperationStatus=0;	//Initially closed
	currTrack=-1;		//There are no tracks, so the track being edited is set to -1
	connected=1;
	track.clear();
	screen=r;
	mainMenu = new Menu(r,20,20,5,20);
	mainMenu->toggle(0);
	mainMenu->toggle(1);
	currOffsetX=0;
	currOffsetY=0;
	cursorType=0;
	dragStatus=0;
	lastDragX=lastDragY=lastOffsetX=lastOffsetY=0;
	clicks.push_back(10);
	clicks.push_back(12);
	nStations=0;
}

string RollerCoaster::getName(){
	return name;
}

void RollerCoaster::setName(string s){
	name=s;
}

void RollerCoaster::rateCoaster(){
	//Going to have to do with play -- play without animation and measure values.
}

void RollerCoaster::selectTrack(double x0, double y0){	

	int ellipse_offset=5;		//if you click inside of an elipse drawn around the track piece,
	int found = 0;			//you will select that piece.  Could run into problems with a small
	int count = 0;			//line next to a big one.  Fix when able to see better.
	for(vector<TrackPiece>::iterator it=track.begin(); it!=track.end();it++){
		int x1=it->startX;
		int y1=it->startY;
		int x2=it->endX;
		int y2=it->endY;
		double length = distance(x1,y1,x2,y2);
		double part1 = distance(x1,y1,x0,y0);
		double part2 = distance(x2,y2,x0,y0);
		double totDist = part1+part2;
		if(totDist-length>ellipse_offset){
			currTrack=count;
		}
		count++;
	}
}

void RollerCoaster::addTrack(double x1,double y1,double x2,double y2){
	TrackPiece T;
	T.trackType = trackAdd;
	T.startX = x1;
	T.startY = y1;
	T.endX = x2;
	T.endY = y2;
	track.push_back(T);
	if(trackAdd!=1 && nStations==0){
		nStations=1;
	}
	if(trackAdd==1 && nStations==1){
		TrackPiece R;
		T.trackType=0;
		T.startX=track[track.size()-1].endX;
		T.startY=track[track.size()-1].endY;
		T.endX=x1;
		T.endY=y1;
		track.push_back(R);
		nStations=2;
	}
}

void RollerCoaster::removeTrack(){
	int count=0;
	for(vector<TrackPiece>::iterator it = track.begin();it != track.end(); it++){
		if(currTrack==count){
			track.erase(it);
		}
		count++;
	}
}

void RollerCoaster::autoComplete(){

}

void RollerCoaster::drawCurrent(){
	SDL_FillRect(screen,NULL, 0x000000); 
	mainMenu->draw();
	for(vector<TrackPiece>::iterator it = track.begin();it!=track.end();it++){
		it->drawPiece(screen,currOffsetX,currOffsetY);
	}
}

void RollerCoaster::play(){

}

void RollerCoaster::menuChanges(int a){
	
/*
These changes are handlers for when a menu item is toggled: it will be a large case structure
with one case per button
Button list:
0) Connected building vs regular line building
1) Station
2) Chain
3) ShootOff
4) Select track instead of building it
*/
	switch(a){
		case 0: 
			connected=(connected==1?0:1);
			mainMenu->toggle(0);
			clicks.clear();
			break;
		case 1:
			if(track.size()==0){
				cout << "Place the station before you add other track types" << endl;
			}else if(nStations==2){
				cout << "You already have two stations" << endl;
			}else{
				if(mainMenu->getState(1)==0){
					trackAdd=1;
					if(mainMenu->getState(2)==1)
						mainMenu->toggle(2);
					if(mainMenu->getState(3)==1)
						mainMenu->toggle(3);
				}else{
					trackAdd=0;
				}
				mainMenu->toggle(a);
			}
			break;
		case 2:
			if(track.size()==0){
				cout << "Place the station before you add other track types" << endl;
			}else if(nStations==2){
				cout << "You already have two stations" << endl;
			}else{
				if(mainMenu->getState(2)==0){
					trackAdd=2;
					if(mainMenu->getState(1)==1)
						mainMenu->toggle(1);
					if(mainMenu->getState(3)==1)
						mainMenu->toggle(3);
				}else{
					trackAdd=0;
				}
				mainMenu->toggle(a);
			}
			break;
		case 3:
			if(track.size()==0){
				cout << "Place the station before you add other track types" << endl;
			}else if(nStations==2){
				cout << "You already have two stations" << endl;
			}else{
				if(mainMenu->getState(3)==0){
					trackAdd=3;
					if(mainMenu->getState(1)==1)
						mainMenu->toggle(1);
					if(mainMenu->getState(2)==1)
						mainMenu->toggle(2);
				}else{
					trackAdd=0;
				}
				mainMenu->toggle(a);
			}
			break;
		case 4:
			if(mainMenu->getState(4)==0){
				cursorType=1;
				mainMenu->toggle(4);
			}else{
				cursorType=0;
				mainMenu->toggle(4);
			}
		default:
			break;
	}
}

void RollerCoaster::parseTrackInfo(double x1,double y1,double x2,double y2,double x,double y){
	if(trackAdd==1){
		y2=windowHeight;
		y1=windowHeight;
		y=windowHeight;
	}
	if(connected==0){
		addTrack(x1,y1,x2,y2);
		clicks.clear();
	}else{
		addTrack(x1,y1,x2,y2);
		clicks.clear();
		parseInfo(x-currOffsetX,y+currOffsetY);
	}

}

void RollerCoaster::parseInfo(Uint16 x,Uint16 y){
	int a = mainMenu->buttonClicked(x,y);
	if(a>-2){
		if(a>-1){
			menuChanges(a);
		}
	}else{
		x+=currOffsetX;
		y-=currOffsetY;
		if(cursorType==0){
			clicks.push_back((double) x);
			clicks.push_back((double) y);
			if(clicks.size()==4){
				parseTrackInfo(clicks[0],clicks[1],clicks[2],clicks[3],x,y);
			}
		}
	}
	drawCurrent();
	SDL_Flip( screen ); 

}

void RollerCoaster::parseDrag(Uint16 x,Uint16 y,int type){
	if(cursorType==1){
		if(type==SDL_MOUSEBUTTONDOWN){
			dragStatus=1;
			lastDragX=x;
			lastDragY=y;
			lastOffsetX=currOffsetX;
			lastOffsetY=currOffsetY;
		}else if(type==SDL_MOUSEMOTION){
			if(dragStatus==1){
				int xDiff=x-lastDragX;
				int yDiff=y-lastDragY;
				currOffsetX = lastOffsetX - xDiff;
				currOffsetY = lastOffsetY + yDiff;
				if(currOffsetY < 0){
					currOffsetY=0;
				}
				if(currOffsetX < 0){
					currOffsetX=0;
				}
			}
		}else if(type==SDL_MOUSEBUTTONUP){
			dragStatus=0;
		}
	}
	drawCurrent();
	SDL_Flip( screen ); 		
}

void RollerCoaster::displayInterface(){
	int done=0;
	drawCurrent();
	SDL_Flip(screen);
	while(done==0){
		SDL_Event test_event;
		while(SDL_PollEvent(&test_event)){
			Uint16 x = test_event.button.x;
			Uint16 y = test_event.button.y;
			switch(test_event.type){
				case SDL_MOUSEBUTTONDOWN:
					{
						parseDrag(x,y,SDL_MOUSEBUTTONDOWN);
						if(test_event.button.button==SDL_BUTTON_LEFT){
							parseInfo(x,y);
						}else{
							done=1;
						}
						break;
					}
				case SDL_MOUSEBUTTONUP:
					{
						parseDrag(x,y,SDL_MOUSEBUTTONUP);
						break;
					}
				case SDL_MOUSEMOTION:
					{
						parseDrag(x,y,SDL_MOUSEMOTION);
						break;
					}
				default:
					break;
					done=1;
			}
		}
	}					
	SDL_Quit(); 

}
