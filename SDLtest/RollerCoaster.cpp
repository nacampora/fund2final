#include "hfiles\RollerCoaster.h"
//#include "Finances.h"
#include <iostream>
#include <string>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include <sstream>
#include <fstream>
#define CW 100
#define CH 50
#define W1 20
#define W2 80
#define base 15
using namespace std;

int windowHeight=500;

//RollerCoaster::RollerCoaster(SDL_Surface *r,string s,Finances *F){
RollerCoaster::RollerCoaster(){
//	F1=F;
	SDL_Surface *r=SDL_SetVideoMode(1300,650,32,SDL_SWSURFACE);
	nCarts=0;
	rideEntranceFee=1;
	trackAdd=1;		//Type of track you are using
	//name = s;		//Name the RollerCoaster
	OperationStatus=0;	//Initially closed
	currTrack=-1;		//There are no tracks, so the track being edited is set to -1
	connected=1;
	track.clear();
	screen=r;
	int nBut=8;
	mainMenu = new Menu(r,20,20,nBut,30);
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
	backSky=IMG_Load("images/Sky.png");
	backG=IMG_Load("images/Ground.png");
	cartPNG=IMG_Load("images/Cart.png");
	trackPNG=IMG_Load("images/track2.png");
	PNGheight=20;
	menuBackPNG=IMG_Load("red.png");
	blankPNG=IMG_Load("images/Blank.png");
	button0PNG=IMG_Load("images/Connected-Track.png");
	button1PNG=IMG_Load("images/Station.png");
	button2PNG=IMG_Load("images/Chain.png");
	button3PNG=IMG_Load("images/Chain.png");
	button4PNG=IMG_Load("images/Drag.png");
	button5PNG=IMG_Load("images/Erase.png");
	button6PNG=IMG_Load("images/Play.png");
	button7PNG=IMG_Load("images/Stop.png");
	myVec.push_back(blankPNG);
	myVec.push_back(button0PNG);
	myVec.push_back(button1PNG);
	myVec.push_back(button2PNG);
	myVec.push_back(button3PNG);
	myVec.push_back(button4PNG);
	myVec.push_back(button5PNG);
	myVec.push_back(button6PNG);
	myVec.push_back(button7PNG);
	exitInterface=0;
	peopleOnRide=0;
	maxPeopleOnRide=4;
}

void RollerCoaster::increaseRideEntranceFee(){
	rideEntranceFee++;
}

void RollerCoaster::decreaseRideEntranceFee(){
	rideEntranceFee--;
}

int RollerCoaster::getRideEntranceFee(){
	return rideEntranceFee;
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

double RollerCoaster::distance(double x1,double y1,double x2,double y2){
	return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}


int RollerCoaster::selectTrack(double x0, double y0){
	int offset=10;
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
		if(totDist-length<ellipse_offset){
			return count;
		}
		count++;
	}
	return -1;
}

		//	int RollerCoaster::addTrack(double x1,double y1,double x2,double y2,Finances *F1){
int RollerCoaster::addTrack(double x1,double y1,double x2,double y2){
	TrackPiece T;
	T.trackType = trackAdd;
	T.startX = x1;
	T.startY = y1;
	T.endX = x2;
	T.endY = y2;
/*	if(T.trackType==1){
		F1->buyStation();
		worth+=F1->stationPrice;
	}else{
		if(abs(tan(T.findAngle())>1)){
			F1->buySteep();
			worth+=F1->steepPrice;
		}else{
			F1->buyGradual();
			worth+=F1->gradualPrice;
		}
	}	*/
	if(trackAdd==1 && nStations==0){
		if(x2>x1){
			track.clear();
			T.startX=10;
			track.push_back(T);
		}else{
			return 0;
		}
	}else if(trackAdd!=1 && nStations==0){
		nStations=1;

		track.push_back(T);
	}else if(trackAdd==1 && nStations==1){
		if(x2>x1){
			T.startX=x1;
			T.startY=T.endY=y1;
			T.endX=x1+track[0].endX-track[0].startX;
			track.push_back(T);
			nStations=2;
		}
	}else{
		track.push_back(T);
	}
	return 1;
}

void RollerCoaster::drawCurrent(){
	SDL_BlitSurface(backSky,NULL,screen,NULL);
	SDL_Rect off;
	off.x=0;
	off.y=windowHeight-30+currOffsetY;
	SDL_BlitSurface(backG,NULL,screen,&off);
	for(int i=track.size()-1;i>=0;i--){
		track[i].drawPiece(screen,trackPNG,currOffsetX,currOffsetY,PNGheight);
		for(int F=0;F<nCarts;F++){
			if(carts[F]->currTrack==i){
				carts[F]->draw(currOffsetX,currOffsetY,screen,cartPNG);
			}
		}
	}
	mainMenu->draw(screen,myVec);
}

void RollerCoaster::checkPlace(Cart *myCart){
	for(int F=0;F<1;F++){
	double dist = distance(track[myCart->currTrack].startX,track[myCart->currTrack].startY,track[myCart->currTrack].endX,track[myCart->currTrack].endY);
	double ang = track[myCart->currTrack].findAngle();
	ang+=3*M_PI/2;
	double x1=myCart->x+CH*cos(ang)/2;
	double y1=myCart->y-CH*sin(ang)/2;
	double w1=W1;
	double w2=W2;
	ang-=3*M_PI/2;
	double x2=x1+(myCart->width)*((w1/100)-.5)*cos(ang);
	double y2=y1-(myCart->width)*((w1/100)-.5)*sin(ang);
	double x3=x1+(myCart->width)*((w2/100)-.5)*cos(ang);
	double y3=y1-(myCart->width)*((w2/100)-.5)*sin(ang);
	double distMiddle= distance(track[myCart->currTrack].startX,track[myCart->currTrack].startY,x1,y1);
	double ratio=distMiddle/dist;
	myCart->distTrack=ratio;
	double distFirst= distance(track[myCart->fwCurrTrack].startX,track[myCart->fwCurrTrack].startY,x2,y2);
	double distF = distance(track[myCart->fwCurrTrack].startX,track[myCart->fwCurrTrack].startY,track[myCart->fwCurrTrack].endX,track[myCart->fwCurrTrack].endY);
	double fratio=distFirst/distF;
	if(fratio>1){
		myCart->fwCurrTrack++;
		myCart->currTrack=myCart->fwCurrTrack;
		myCart->fixedX=track[myCart->currTrack].startX+(CW/2-CW*W1/100+dist*(fratio-1))*cos(track[myCart->currTrack].findAngle());
		myCart->x=myCart->fixedX+CH*cos(track[myCart->currTrack].findAngle()+M_PI/2)/2;
		myCart->fixedX=myCart->x;
		myCart->fixedY=track[myCart->currTrack].startY-(CW/2-CW*W1/100+dist*(fratio-1))*sin(track[myCart->currTrack].findAngle());
		myCart->y=myCart->fixedY-CH*sin(track[myCart->currTrack].findAngle()+M_PI/2)/2;
		myCart->fixedY=myCart->y;
		checkPlace(myCart);
		break;
	}else if(fratio<0){

	}else{
		myCart->fwDistTrack=fratio;
		myCart->currTrack=myCart->fwCurrTrack;
	}
	double distSec= distance(track[myCart->swCurrTrack].startX,track[myCart->swCurrTrack].startY,x3,y3);
	double distS = distance(track[myCart->swCurrTrack].startX,track[myCart->swCurrTrack].startY,track[myCart->swCurrTrack].endX,track[myCart->swCurrTrack].endY);
	double sratio=distSec/distS;
	if(sratio>1){
		myCart->swCurrTrack++;
		checkPlace(myCart);
		break;
	}else{
		myCart->swDistTrack=sratio;
	}
	double fwX=track[myCart->fwCurrTrack].startX+distFirst*cos(track[myCart->fwCurrTrack].findAngle());
	double fwY=track[myCart->fwCurrTrack].startY-distFirst*sin(track[myCart->fwCurrTrack].findAngle());
	double swX=track[myCart->swCurrTrack].startX+distSec*cos(track[myCart->swCurrTrack].findAngle());
	double swY=track[myCart->swCurrTrack].startY-distSec*sin(track[myCart->swCurrTrack].findAngle());
	TrackPiece t(fwX,fwY,swX,swY,0);
	double a=t.findAngle();
	myCart->angle=a;
	myCart->direction=track[myCart->fwCurrTrack].findAngle();
	dist = distance(track[myCart->currTrack].startX,track[myCart->currTrack].startY,track[myCart->currTrack].endX,track[myCart->currTrack].endY);
	myCart->x=track[myCart->currTrack].startX+(myCart->distTrack)*dist*cos(track[myCart->currTrack].findAngle())+CH*cos(track[myCart->currTrack].findAngle()+M_PI/2)/2;
	myCart->y=track[myCart->currTrack].startY-(myCart->distTrack)*dist*sin(track[myCart->currTrack].findAngle())-CH*sin(track[myCart->currTrack].findAngle()+M_PI/2)/2;
	int m=fwX+(CW/2-CW*W1/100)*cos(myCart->angle)+CH*cos(myCart->angle+M_PI/2)/2;
	int n=fwY-(CW/2-CW*W1/100)*sin(myCart->angle)-CH*sin(myCart->angle+M_PI/2)/2;
	myCart->fixedX=m;
	myCart->fixedY=n;
	}
}

void RollerCoaster::updateSpeed(Cart *myCart,int x1,int y1){
	if(track[myCart->currTrack].trackType==1 || track[myCart->currTrack].trackType==2){
		myCart->speed=10;
	}else{
		if(myCart->speed>0){
			myCart->speed+=(myCart->y-y1)/15;
		}else{
			myCart->speed+=(y1-myCart->y)/15;
		}
	}
}

void RollerCoaster::play(){
	int w=CW;
	int h=CH;
	nCarts = (track[0].endX-track[0].startX)/(w+10);
	carts.clear();
	for(int F=0;F<nCarts;F++){
		Cart *myCart = new Cart(10+w/2+F*(w+5),windowHeight-h/2,w,h,screen);
		myCart->fixedX=myCart->x;
		myCart->fixedY=myCart->y;
		myCart->draw(currOffsetX,currOffsetY,screen,cartPNG);
		myCart->speed=.15;
		carts.push_back(myCart);
	}
	SDL_Flip(screen);
	SDL_Delay(500);
	int stop=0;
	int countDown=0;
	int countDownVal=5;
	while(stop==0){
		SDL_Event test_event;
		while(SDL_PollEvent(&test_event)){
			Uint16 x = test_event.button.x;
			Uint16 y = test_event.button.y;
			double xd=(double) x;
			double yd=(double) y;
			switch(test_event.type){
				case SDL_MOUSEBUTTONDOWN:
					int a = mainMenu->buttonClicked(xd,yd);
					if(a==7){
						stop=1;
						break;
					}
			}
		}
		for(int F=0;F<nCarts;F++){
			carts[F]->lastx = carts[F]->x;
			carts[F]->lasty = carts[F]->y;
		}
		if(carts[nCarts-1]->x>300){
			currOffsetX=carts[nCarts-1]->fixedX-300-(nCarts<5?nCarts*50:250);
		}else{
			currOffsetX=0;
		}
		currOffsetY=-carts[nCarts-1]->fixedY+windowHeight-(nCarts<6?nCarts*50:250);
		if(currOffsetY<0){
			currOffsetY=0;
		}
		double averageSpeed=0;
		for(int F=0;F<nCarts;F++){
			updateSpeed(carts[F],carts[F]->lastx,carts[F]->lasty);
			averageSpeed+=carts[F]->speed;
		}
		averageSpeed=averageSpeed/nCarts;
		for(int F=0;F<nCarts;F++){
			carts[F]->speed=averageSpeed;
		}
		for(int F=0;F<nCarts;F++){
			carts[F]->increment();
			updateSpeed(carts[F],carts[F]->lastx,carts[F]->lasty);
			checkPlace(carts[F]);
			drawCurrent();
		}
		SDL_Flip(screen);
		SDL_Delay(50);
		if(carts[0]->currTrack==track.size()-1){
			countDown=1;
		}
		if(countDown==1){
			countDownVal--;
		}
		if(countDownVal<0){
			stop=1;
			SDL_Delay(1000);
		}
	}
	carts.clear();
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
					if(connected==0){
						connected=1;
						mainMenu->toggle(0);
					}
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
				if(mainMenu->getState(5)==1){
					mainMenu->toggle(5);
				}
			}else{
				cursorType=0;
				mainMenu->toggle(4);
			}
			break;
		case 5:
			if(mainMenu->getState(5)==0){
				cursorType=2;
				mainMenu->toggle(5);
				if(mainMenu->getState(4)==1){
					mainMenu->toggle(4);
				}
			}else{
				cursorType=0;
				mainMenu->toggle(5);
			}
			break;
		case 6:
			if(nStations==2){
				play();
			}else{
				cout << "Not Enough Stations" << endl;
			}
			break;
		case 7:
			exitInterface=1;
		default:
			break;
	}
}

void RollerCoaster::parseTrackInfo(double x1,double y1,double x2,double y2,double x,double y){
	if(nStations==0 && trackAdd==1){
		y2=windowHeight;
		y1=windowHeight;
		y=windowHeight;
	}
	double d = distance(x1,y1,x2,y2);
	int nPieces=d/base+1;
	int a=0;
	a=addTrack(x1,y1,x2,y2);
	double ang=track[track.size()-1].findAngle();
	x2=x1+nPieces*base*cos(ang);
	y2=y1-nPieces*base*sin(ang);
	track[track.size()-1].endX=x2;
	track[track.size()-1].endY=y2;
	x=x2;
	y=y2;
	if(a==1){
		clicks.clear();
	}else{
		double temp0=clicks[0];
		double temp1=clicks[1];
		clicks.clear();
		clicks.push_back(temp0);
		clicks.push_back(temp1);
	}
	if(connected==1 && a==1){
		int s=track.size();
		parseInfo(x-currOffsetX,y+currOffsetY);
	}
	if(nStations==2){
		track[track.size()-1].endX=track[track.size()-1].startX+track[0].endX-track[0].startX;
	}
}

void RollerCoaster::parseInfo(double x,double y){
	int a = mainMenu->buttonClicked(x,y);
	if(a>-2){
		if(a>-1){
			menuChanges(a);
		}
	}else{
		x+=currOffsetX;
		y-=currOffsetY;
		if(cursorType==0 && nStations!=2){
			clicks.push_back((double) x);
			clicks.push_back((double) y);
			if(clicks.size()==4){
				parseTrackInfo(clicks[0],clicks[1],clicks[2],clicks[3],x,y);
			}
		}else if(cursorType==2){
			int a = selectTrack(x,y);
			if((a>0 || track.size()==1) && (track[track.size()-1].trackType!=1 || a==track.size()-1)){
				if(track.size()==1){
					nStations=0;
				}else if(track[track.size()-1].trackType==1){
					nStations=1;
				}
				int count=0;
				for(vector<TrackPiece>::iterator it=track.begin(); it!=track.end(); it++){
					if(count==a){
						track.erase(it);
						break;
					}
					count++;
				}
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
				if(currOffsetY < 0)
					currOffsetY=0;
				if(currOffsetX < 0)
					currOffsetX=0;
			}
		}else if(type==SDL_MOUSEBUTTONUP){
			dragStatus=0;
		}
		drawCurrent();
		SDL_Flip( screen );
	}
}

void RollerCoaster::load(int xCo,int yCo){
	track.clear();
	string s = "Coasters/RollerCoaster";
	ostringstream convert;
	convert << xCo;
	string stringxCo = convert.str();
	ostringstream convert1;
	convert1 << yCo;
	string stringyCo = convert1.str();
	string txt = ".txt";
	s=s+stringxCo+stringyCo+txt;
	const char *fileName=s.c_str();
	ifstream file (fileName);
	if(file.is_open()){
		int length;
		file >> length;
		for(int F=0;F<length;F++){
			int trackT;
			TrackPiece T;
			file >> T.startX;
			file >> T.startY;
			file >> T.endX;
			file >> T.endY;
			file >> T.trackType;
			track.push_back(T);
		}
	}
	if(track.size()>2 && track[track.size()-1].trackType==1)
    {
        nStations=2;
    }
    else if(track.size()>0 && track[0].trackType==1){
        nStations=1;
    }
    else{
        nStations=0;
    }
}

void RollerCoaster::displayInterface(int xCo,int yCo){
	drawCurrent();
	SDL_Flip(screen);
	while(exitInterface==0){
		SDL_Event test_event;
		while(SDL_PollEvent(&test_event)){
			Uint16 x = test_event.button.x;
			Uint16 y = test_event.button.y;
			double xd=(double) x;
			double yd=(double) y;
			switch(test_event.type){
				case SDL_MOUSEBUTTONDOWN:
					{
						parseDrag(x,y,SDL_MOUSEBUTTONDOWN);
						if(test_event.button.button==SDL_BUTTON_LEFT){
							parseInfo(xd,yd);
						}else{
							exitInterface=1;
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
			}
		}

	}
	string s = "Coasters/RollerCoaster";
	ostringstream convert;
	convert << xCo;
	string stringxCo = convert.str();
	ostringstream convert1;
	convert1 << yCo;
	string stringyCo = convert1.str();
	string txt = ".txt";
	s=s+stringxCo+stringyCo+txt;
	const char *fileName=s.c_str();
	ofstream file(fileName);
	if(file.is_open()){
		file << track.size();
		file << " ";
		for(vector<TrackPiece>::iterator it = track.begin();it!= track.end();it++){
			file << it->startX;
			file << " ";
			file << it->startY;
			file << " ";
			file << it->endX;
			file << " ";
			file << it->endY;
			file << " ";
			file << it->trackType;
			file << " ";
		}
		file.close();
	}
	exitInterface=0;
}
