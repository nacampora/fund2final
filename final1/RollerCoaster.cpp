//RollerCoaster member functions

#include "RollerCoaster.h"
#include "Finances.h"
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
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

RollerCoaster::RollerCoaster(){
	srand(time(NULL));
	setupClouds();
	SDL_Surface *r=SDL_SetVideoMode(1300,650,32,SDL_SWSURFACE);
	nCarts=0;
	trackAdd=1;		//Type of track you are using
	OperationStatus=0;	//Initially closed
	currTrack=-1;		//There are no tracks, so the track being edited is set to -1
	connected=1;
	track.clear();
	screen=r;
	int nBut=10;	//10 buttons
	mainMenu = new Menu(r,20,20,nBut,30);	//This is the menu
	mainMenu->toggle(1);
	currOffsetX=0;
	currOffsetY=0;
	cursorType=0;
	dragStatus=0;						//Lots of variables initialized
	lastDragX=lastDragY=lastOffsetX=lastOffsetY=0;
	clicks.push_back(10);
	clicks.push_back(12);
	nStations=0;
	backSky=IMG_Load("images/Sky.png");				//Loads lots of PNGs
	backG=IMG_Load("images/Ground.png");
	cartPNG=IMG_Load("images/Cart.png");
	track1PNG=IMG_Load("images/Track1.png");
	track2PNG=IMG_Load("images/Track4.png");
	track3PNG=IMG_Load("images/Track5.png");
	track4PNG=IMG_Load("images/Track2.png");
	highlightedTrackPNG=IMG_Load("images/Track3.png");
	PNGHheight=10;
	PNGheight=10;
	cloud1PNG=IMG_Load("images/Cloud1.png");
	cloud2PNG=IMG_Load("images/Cloud2.png");
	cloud3PNG=IMG_Load("images/Cloud3.png");
	cloud4PNG=IMG_Load("images/Cloud4.png");
	blankPNG=IMG_Load("images/Blank.png");
	button0PNG=IMG_Load("images/Exit-Square.png");
	button1PNG=IMG_Load("images/Station.png");
	button2PNG=IMG_Load("images/Chain.png");
	button3PNG=IMG_Load("images/Boost.png");
	button4PNG=IMG_Load("images/Drag.png");
	button5PNG=IMG_Load("images/Erase.png");
	button6PNG=IMG_Load("images/Highlighted-Track.png");
	button7PNG=IMG_Load("images/Sell.png");
	button8PNG=IMG_Load("images/Play.png");
	button9PNG=IMG_Load("images/Stop.png");
	myVec.push_back(blankPNG); 
	myVec.push_back(button0PNG);
	myVec.push_back(button1PNG);
	myVec.push_back(button2PNG);
	myVec.push_back(button3PNG);
	myVec.push_back(button4PNG);
	myVec.push_back(button5PNG);
	myVec.push_back(button6PNG);
	myVec.push_back(button7PNG);
	myVec.push_back(button8PNG);
	myVec.push_back(button9PNG);
	exitInterface=0;
	peopleOnRide=0;				//more variables beiong set
	maxPeopleOnRide=4;
	currTrack=-1;
	worth=0;
}


void RollerCoaster::setFinances(Finances * F){
	F1=F;
}


void RollerCoaster::setupClouds(){
	for(int F = 0;F<500; F++){
		int x = rand() % 400000;
		int y = -1000 - rand() % 2000;
		int num = rand() % 4;
		cloudVec.push_back(x);
		cloudVec.push_back(y);
		cloudVec.push_back(num);		//randomly generated clouds
	}
}


void RollerCoaster::rateCoaster(){
	if(getBroken()==0 && nStations==2){
		play(0);			//plays without animation
	}
	rating.excitement=0;	
	rating.intensity=0;
	rating.deadliness=0;
	rating.length=0;	
	rating.speed=0;
	double totSpeed;
	for(int F=0;F<track.size();F++){
		rating.length+=distance(track[F].startX,track[F].startY,track[F].endX,track[F].endY);
	}
	for(int F=0;F<speedVec.size();F++){
		totSpeed+=speedVec[F];
		if(F>0){
			double angle1=angleVec[F-1];				//measures:
			double angle2=angleVec[F];				//excitement -- good attribute, average speed divided by 20.  Higher speed is good
			double diff1=angle2-angle1;				//intensity -- bad attribute, average angleChange * speed / 1000, sharp turns are bad
			double diff2=angle1-angle2;				//deadliness -- 1 or 0.  You die if deadliness = 1, aka intensity > 100
			double diff;						//length of coaster
			if(diff1>diff2){					//highest speed
				diff=diff1;
			}else{
				diff=diff2;
			}
			if(diff>M_PI){
				diff=M_PI-(diff-M_PI);
			}
			rating.intensity+=speedVec[F]*diff*.1;
		}
		if(speedVec[F]>rating.speed){
			rating.speed=speedVec[F];
		}
	}
	if(speedVec.size()>0){
		rating.excitement = totSpeed/(speedVec.size());
		rating.intensity*1000/(speedVec.size());
	}
	if(rating.intensity>100){
		rating.deadliness=1;
	}
	rating.excitement/=20;
//	cout << rating.excitement << " " << rating.intensity << " " << rating.length << " " << rating.speed << " " << rating.deadliness << endl;
}

double RollerCoaster::distance(double x1,double y1,double x2,double y2){
	return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}


int RollerCoaster::selectTrack(double x0, double y0){	
	int offset=10;
	int ellipse_offset=5;		//if you click inside of an elipse drawn around the track piece,
	int found = 0;			//you will select that piece.  Could run into problems with a small
	int count = 0;			//line next to a big one.  Oh well.
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

void RollerCoaster::sell(){
	track.clear();				//lets you sell the coaster, sets appropriate variables
	F1->sellCoaster(worth);
	worth=0;
	nStations=0;
	clicks.clear();
	clicks.clear();			//if you deleted all the tracks.
	clicks.push_back(10);
	clicks.push_back(windowHeight);
	trackAdd=1;
	if(mainMenu->getState(1)==0){
		mainMenu->toggle(1);
	}
	if(mainMenu->getState(2)==1){
		mainMenu->toggle(2);
	}
	if(mainMenu->getState(3)==1){
		mainMenu->toggle(3);
	}
	exitInterface=1;		//takes you out of the interface;
}

		//	int RollerCoaster::addTrack(double x1,double y1,double x2,double y2,Finances *F1){
int RollerCoaster::addTrack(double x1,double y1,double x2,double y2){
	if(distance(x1,y1,x2,y2)<CW/2+1){
		return 0;
	}					//adds a track depending on the two points it connects and the type of coaster
	TrackPiece T;				//This function became a little convaluted because of all the different possible cases
	T.trackType = trackAdd;
	T.startX = x1;				//First an instance of the track under consideration is created.
	T.startY = y1;
	T.endX = x2;
	T.endY = y2;
	if(trackAdd==1 && nStations==0){		//if you are adding the first station
		if(x2>x1){
			track.clear();			//lets you add onto the station
			T.startX=10;
			track.push_back(T);
			currTrack=track.size()-1;
		}else{
			return 0;
		}
	}else if(trackAdd!=1 && nStations==0){		//if you are adding the first track after the first station
		nStations=1;
		if(currTrack<track.size()-1){
			track.insert(track.begin()+currTrack+1,T);		//you insert into the vector if you are add a track to the middle
			currTrack++;
		}else{
			track.push_back(T);
			currTrack=track.size()-1;
		}
	}else if(trackAdd==1 && nStations==1){					//adding the second station.  automatically sets the length of this piece,
		int broken=getBroken();						//you dont get to choose
		if(x2>x1 && currTrack==track.size()-1 && broken==0){
			T.startX=x1;
			T.startY=T.endY=y1;
			T.endX=x1+track[0].endX-track[0].startX+500;
			if(currTrack<track.size()-1){
				track.insert(track.begin()+currTrack+1,T);
				currTrack++;
			}else{
				track.push_back(T);
				currTrack=track.size()-1;
			}
			nStations=2;
		}else{
			return 0;
		}
	}else{
		if(currTrack<track.size()-1){				//default case.  for all tracks not yet dealt with in above case
			track.insert(track.begin()+currTrack+1,T);
			currTrack++;
		}else{
			track.push_back(T);
			currTrack=track.size()-1;
		}
	}
	if(T.trackType==1){
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
	}	
	return 1; 
}

void RollerCoaster::drawCurrent(int drawCarts){			//draws the current screen.
	SDL_Rect off;		//offset for the background sky.  Changes based on how high up you are.  The PNG is really tall, so by
	off.x=0;			//setting it at the correct offset it gets darker higher up.
	off.y=-5000+currOffsetY;
	if(off.y>0){
		off.y=0;
	}
	SDL_BlitSurface(backSky,NULL,screen,&off);
	off.x=0;
	off.y=windowHeight-30+currOffsetY;		//set up the ground -- only appears if you are at the bottom
	SDL_BlitSurface(backG,NULL,screen,&off);
	for(int F=0; F<cloudVec.size(); F+=3){
		int xVal = cloudVec[F]-currOffsetX;
		int yVal = cloudVec[F+1]+currOffsetY;
		if(yVal>-200 && yVal<900 && xVal>-200 && xVal<1500){
			SDL_Rect r1;
			r1.x=xVal;
			r1.y=yVal;
			switch(cloudVec[F+2]){
				case 0:							//clouds -- 4 different cloud PNGs
					SDL_BlitSurface(cloud1PNG,NULL,screen,&r1);
					break;
				case 1:
					SDL_BlitSurface(cloud2PNG,NULL,screen,&r1);
					break;
				case 2:
					SDL_BlitSurface(cloud3PNG,NULL,screen,&r1);
					break;
				case 3:
					SDL_BlitSurface(cloud4PNG,NULL,screen,&r1);
					break;
			}
		}
	}
	int count=track.size()-1;
	for(int i=track.size()-1;i>=0;i--){		//iterates backwards through the track to draw it
		if(drawCarts==1){
			for(int F=0;F<nCarts;F++){
				if(i==carts[F]->currTrack){					//draws the cart along with the track it is on, so that it can appear
					carts[F]->draw(currOffsetX,currOffsetY,screen,cartPNG);	//behind tracks when it needs to 
				}
			}
		}
		SDL_Surface *trackPNG;
		if(track[i].trackType==0){
			trackPNG=track1PNG;
		}else if(track[i].trackType==1){
			trackPNG=track2PNG;
		}else if(track[i].trackType==2){
			trackPNG=track3PNG;
		}else if(track[i].trackType==3){
			trackPNG=track4PNG;
		}
		if(count==currTrack){
			if(drawCarts==0){
				track[i].drawPiece(screen,highlightedTrackPNG,currOffsetX,currOffsetY,PNGHheight);
			}else{												//draws the pieces.
				track[i].drawPiece(screen,trackPNG,currOffsetX,currOffsetY,PNGHheight);
			}
		}else{
			track[i].drawPiece(screen,trackPNG,currOffsetX,currOffsetY,PNGheight);
		}
		count--;
	}
	mainMenu->draw(screen,myVec);		//draw menu
}

void RollerCoaster::checkPlace(Cart *myCart){		//Most confusing function.  This sets up the position of the cart based on a few factors: the angle of the cart,
	for(int F=0;F<1;F++){				//the track it is currently on, how far along the track it is, and where its wheels are.
	myCart->angle=1.2345;
	double dist = distance(track[myCart->currTrack].startX,track[myCart->currTrack].startY,track[myCart->currTrack].endX,track[myCart->currTrack].endY);
	double ang = track[myCart->currTrack].findAngle();
	ang+=3*M_PI/2;
	double x1=myCart->x+CH*cos(ang)/2;		//The x,y coordinates of the cart are the actual center of the cart, so these few lines figure out where the 
	double y1=myCart->y-CH*sin(ang)/2;		//corners of the cart are, and puts that info into x2,y2 and x3,y3
	double w1=W1;
	double w2=W2;
	ang-=3*M_PI/2;
	double x2=x1+(myCart->width)*((w1/100)-.5)*cos(ang);
	double y2=y1-(myCart->width)*((w1/100)-.5)*sin(ang);
	double x3=x1+(myCart->width)*((w2/100)-.5)*cos(ang);
	double y3=y1-(myCart->width)*((w2/100)-.5)*sin(ang);
	double distMiddle= distance(track[myCart->currTrack].startX,track[myCart->currTrack].startY,x1,y1);	//where the cart is
	double ratio=distMiddle/dist;		//ratio is the ratio of cart distance from the beginning of the track to track length
	myCart->distTrack=ratio;		//distTrack -- how far along the track is, is a ratio, it tells the percent progress along the track
	double distFirst= distance(track[myCart->fwCurrTrack].startX,track[myCart->fwCurrTrack].startY,x2,y2);
	double distF = distance(track[myCart->fwCurrTrack].startX,track[myCart->fwCurrTrack].startY,track[myCart->fwCurrTrack].endX,track[myCart->fwCurrTrack].endY);
	double fratio=distFirst/distF;
	if(fratio>1){				//fratio is the same as ratio but for the first wheel (the one on the left), when that number is > 1 the cart moves to the next track
		myCart->fwCurrTrack++;
		myCart->currTrack=myCart->fwCurrTrack; 
/*
here is the first appearance of fixedX and fixedY.  These are a little confusing, they are slightly different than x,y because x,y says where the cart is, while fixedX,fixedY
describe where the cart should be drawn.  This is necessary because the actual position of the cart at a change in gradient would look terrible, so a fix  is necessary, but
if x,y is updated to fixedX,fixedY, that screws everything up.
*/

		myCart->fixedX=track[myCart->currTrack].startX+(CW/2-CW*W1/100+dist*(fratio-1))*cos(track[myCart->currTrack].findAngle());	
		myCart->x=myCart->fixedX+CH*cos(track[myCart->currTrack].findAngle()+M_PI/2)/2;
		myCart->fixedX=myCart->x;
		myCart->fixedY=track[myCart->currTrack].startY-(CW/2-CW*W1/100+dist*(fratio-1))*sin(track[myCart->currTrack].findAngle());
		myCart->y=myCart->fixedY-CH*sin(track[myCart->currTrack].findAngle()+M_PI/2)/2;
		myCart->fixedY=myCart->y;
		checkPlace(myCart);		//since there has been a big change we rerun this function
		break;
	}else if(fratio<0){
		
	}else{
		myCart->fwDistTrack=fratio;
		myCart->currTrack=myCart->fwCurrTrack;
	}
	double distSec= distance(track[myCart->swCurrTrack].startX,track[myCart->swCurrTrack].startY,x3,y3);		//same deal as distFirst but with the wheel on the right
	double distS = distance(track[myCart->swCurrTrack].startX,track[myCart->swCurrTrack].startY,track[myCart->swCurrTrack].endX,track[myCart->swCurrTrack].endY);
	double sratio=distSec/distS;
	if(sratio>1){				//if sratio is bigger than 1 the second wheel changes trackpiece.
		myCart->swCurrTrack++;
		checkPlace(myCart);		//since there has been a big change we rerun this function
		break;
	}else{
		myCart->swDistTrack=sratio;
	}
	double fwX=track[myCart->fwCurrTrack].startX+distFirst*cos(track[myCart->fwCurrTrack].findAngle());	//where the first and seccond wheels should appear.
	double fwY=track[myCart->fwCurrTrack].startY-distFirst*sin(track[myCart->fwCurrTrack].findAngle());
	double swX=track[myCart->swCurrTrack].startX+distSec*cos(track[myCart->swCurrTrack].findAngle());
	double swY=track[myCart->swCurrTrack].startY-distSec*sin(track[myCart->swCurrTrack].findAngle());
	TrackPiece t(fwX,fwY,swX,swY,0);		//a trackpiece is instantiated because this class needs access to the findAngle function.
	double a=t.findAngle();
	myCart->angle=a;
	myCart->direction=track[myCart->fwCurrTrack].findAngle();		//makes sure the rollercoaster will increment in the correct direction.
	dist = distance(track[myCart->currTrack].startX,track[myCart->currTrack].startY,track[myCart->currTrack].endX,track[myCart->currTrack].endY);
	myCart->x=track[myCart->currTrack].startX+(myCart->distTrack)*dist*cos(track[myCart->currTrack].findAngle())+CH*cos(track[myCart->currTrack].findAngle()+M_PI/2)/2;	//position of the cart
	myCart->y=track[myCart->currTrack].startY-(myCart->distTrack)*dist*sin(track[myCart->currTrack].findAngle())-CH*sin(track[myCart->currTrack].findAngle()+M_PI/2)/2;
	int m=fwX+(CW/2-CW*W1/100)*cos(myCart->angle)+CH*cos(myCart->angle+M_PI/2)/2;	//fixed position of the cart for graphics.
	int n=fwY-(CW/2-CW*W1/100)*sin(myCart->angle)-CH*sin(myCart->angle+M_PI/2)/2;
	myCart->fixedX=m;
	myCart->fixedY=n;
	}
	if(myCart->angle==1.2354){
		SDL_Delay(2000);		//for debugging purposes.
	}
}

int RollerCoaster::updateSpeed(Cart *myCart,int x1,int y1){
	if(track[myCart->currTrack].trackType==1 || track[myCart->currTrack].trackType==2){		//if you are on a track or station, speed is 10
		myCart->speed=10;
	}else if(track[myCart->currTrack].trackType==3){		//if you are on a shootOff section the speed goes up towards a threshold of 400
		if(myCart->speed>400){
			myCart->speed=400;
		}else{
			myCart->speed+=4;
		}
	}else{
		if(myCart->speed>0){				//if you are on a regular trackpiece the speedChange depends on the yChange
			myCart->speed+=(myCart->y-y1)/20;
		}else{
			myCart->speed+=(y1-myCart->y)/20;
		}
	}
	if(myCart->speed<1.8){		//stop playing if the rollerCoaster stops.
		return 1;
	}
	return 0;
}

void RollerCoaster::play(int wait){		//argument wait will make the animation work if set to 1
	speedVec.clear();		//these two vecs take measurements for rating purposes
	angleVec.clear();
	int w=CW;
	int h=CH;	
	nCarts = (track[0].endX-track[0].startX)/(w+10);	//checks how many carts it can fit on the station
	if(nCarts>3){
		nCarts=3;	//cap of 3 set for number of carts to avoid lag.
	}
	carts.clear();				//clear and then set up a vetor of carts
	for(int F=0;F<nCarts;F++){
		Cart *myCart = new Cart(10+w/2+F*(w+5),windowHeight-h/2,w,h,screen);
		myCart->fixedX=myCart->x;
		myCart->fixedY=myCart->y;
		if(wait==1){
			myCart->draw(currOffsetX,currOffsetY,screen,cartPNG);
		}
		myCart->speed=.15;
		carts.push_back(myCart);
	}
	SDL_Flip(screen);
	SDL_Delay(500);
	int stop=0;
	int countDown=0;
	int countDownVal=5;		//initializes variables
	while(stop==0){		//end loop if stop is 1
		SDL_Event test_event;
		while(SDL_PollEvent(&test_event)){
			Uint16 x = test_event.button.x;
			Uint16 y = test_event.button.y;
			double xd=(double) x;
			double yd=(double) y;
			switch(test_event.type){
				case SDL_MOUSEBUTTONDOWN:
					int a = mainMenu->buttonClicked(xd,yd);
					if(a==9){
						stop=wait==1?1:0;		//lets you use the 9th menu button -- stop
						break;
					}
			}
		}
		for(int F=0;F<nCarts;F++){
			carts[F]->lastx = carts[F]->x;
			carts[F]->lasty = carts[F]->y;
		}
		double averageSpeed=0;			//the average speed feature makes the train speed the average of the carts, so the graphics are smoother
		for(int F=0;F<nCarts;F++){
			updateSpeed(carts[F],carts[F]->lastx,carts[F]->lasty);	//updates all the speeds then calcs the average
			averageSpeed+=carts[F]->speed;
		}
		averageSpeed=averageSpeed/nCarts;
		for(int F=0;F<nCarts;F++){
			carts[F]->speed=averageSpeed;
		}
		if(carts[nCarts-1]->x>300){
			currOffsetX=carts[nCarts-1]->fixedX-300-(nCarts<5?nCarts*50:250);		//sets the offset to the first cart so the animation follows the cart
		}else{
			currOffsetX=0;
		}
		currOffsetY=-carts[nCarts-1]->fixedY+windowHeight-(nCarts<6?nCarts*50:250);
		if(currOffsetY<0){
			currOffsetY=0;
		}
		for(int F=0;F<nCarts;F++){
			carts[F]->increment();		//increments cart position based on speed.
			if(stop==0){
				stop=updateSpeed(carts[F],carts[F]->lastx,carts[F]->lasty);
				if(stop==1 && wait==1){
					SDL_Delay(1000);	//pauses for 1 second then stops animation if rollerCoaster runs out of speed
				}
			}
			checkPlace(carts[F]);
			if((carts[F]->currTrack)>track.size()-1 && wait==1){
				SDL_Delay(1000);
				stop=1;
			}
			if(wait==1){
				drawCurrent(1);
			}
		}
		if(wait==1){
			SDL_Flip(screen);
			SDL_Delay(50);
		}
		if(carts[0]->currTrack==track.size()-1){
			countDown=1;
		}
		if(countDown==1){
			countDownVal--;		//this makes it so that the animation does not abruptly stop
		}
		if(countDownVal<0){
			stop=1;
			if(wait==1){
				SDL_Delay(1000);
			}
		}
		speedVec.push_back(carts[0]->speed);
		angleVec.push_back(carts[0]->angle);
	}
	carts.clear();
	drawCurrent(0);
	SDL_Flip(screen);
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
	int broken=getBroken();
	switch(a){
		case 0: 
			exitInterface=1;		//quits interface
			break;
		case 1:
			if(track.size()==0){
				cout << "Place the station before you add other track types" << endl;
			}else if(nStations==2 && broken==0){
				cout << "You already have two stations" << endl;
			}else{
				if(mainMenu->getState(1)==0){			//Buttons 1,2, and 3 are linked because they describe track types.
					trackAdd=1;				//if one is pressed the other two are not.
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
			}else if(nStations==2 && broken==0){
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
			}else if(nStations==2 && broken==0){
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
				if(mainMenu->getState(5)==1){		//Buttons 4,5, and 6 are linked because they describe cursor type
					mainMenu->toggle(5);
				}
				if(mainMenu->getState(6)==1){
					mainMenu->toggle(6);
				}
			}else{
				cursorType=0;
				mainMenu->toggle(4);
			}
			break;
		case 5:			//the fifth case
			if(mainMenu->getState(5)==0){
				cursorType=2;
				mainMenu->toggle(5);
				if(mainMenu->getState(4)==1){
					mainMenu->toggle(4);
				}
				if(mainMenu->getState(6)==1){
					mainMenu->toggle(6);
				}
			}else{
				cursorType=0;
				mainMenu->toggle(5);
			}
			break;
		case 8:
			if(nStations==2){
				play(1);		//plays the rollerCoaster animation
			}else{
				cout << "Not Enough Stations" << endl;			//In case there is not a station to play the roller coaster
			}
			break;
		case 7:
			sell();		//sells the coaster
			break;
		case 6:
			if(mainMenu->getState(6)==0){
				cursorType=3;
				mainMenu->toggle(6);
				if(mainMenu->getState(5)==1){
					mainMenu->toggle(5);
				}
				if(mainMenu->getState(4)==1){
					mainMenu->toggle(4);
				}
			}else{
				cursorType=0;
				mainMenu->toggle(6);
			}
			break;
		default:
			break;
	}
}

void RollerCoaster::parseTrackInfo(double x1,double y1,double x2,double y2,double x,double y){
	if(nStations==0 && trackAdd==1){
		y2=windowHeight;
		y1=windowHeight;	//if you are putting a station it will be level
		y=windowHeight;
	}
	double d = distance(x1,y1,x2,y2);
	int nPieces=d/base+1;
	int a=0;
	a=addTrack(x1,y1,x2,y2);			//you are adding the track here
	double ang=track[currTrack].findAngle();
	x2=x1+nPieces*base*cos(ang);
	y2=y1-nPieces*base*sin(ang);
	if(a==1){
		track[currTrack].endX=x2;	
		track[currTrack].endY=y2;
	}
	int fixed=0;
	if(currTrack<track.size()-1){
		if(distance(track[currTrack+1].startX,track[currTrack+1].startY,track[currTrack].endX,track[currTrack].endY)<25){	//This is the functionality that lets you
			fixed=1;													//reconnect tracks.  If you are bridging
			track[currTrack].endX=track[currTrack+1].startX;								//a gap in the tracks, and you click within
			track[currTrack].endY=track[currTrack+1].startY;								//25 pixels of the end of the gap, it will
			currTrack=track.size()-1;											//fix it so that it lies up the tracks
			clicks.clear();
			clicks.push_back(track[track.size()-1].endX);
			clicks.push_back(track[track.size()-1].endY);
			int broken=getBroken();
			if(nStations==2 && broken==0){
				if(mainMenu->getState(1)==0){
					mainMenu->toggle(1);
				}
				if(mainMenu->getState(2)==1){
					mainMenu->toggle(2);
				}
				if(mainMenu->getState(3)==1){
					mainMenu->toggle(3);
				}
			
			}
		}
	}
	x=x2;
	y=y2;
	if(a==1){
		if(fixed==0)
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
		if(fixed==0){
			parseInfo(x-currOffsetX,y+currOffsetY);
		}
	}
	if(nStations==2){
		track[track.size()-1].endX=track[track.size()-1].startX+track[0].endX-track[0].startX+500;	//sets the length of the second station 
	}
}

int RollerCoaster::getBroken(){		//tests to see if there are gaps in the track
	int broken=0;
	if(track.size()>1){
	for(int i=0;i<track.size()-2;i++){
		if(distance(track[i].endX,track[i].endY,track[i+1].startX,track[i+1].startY)>10){
			broken=1;
		}
	}
	}
	return broken;
}

void RollerCoaster::parseInfo(double x,double y){	//parses the information of each click.
	int a = mainMenu->buttonClicked(x,y);
	if(a>-2){
		if(a>-1){
			menuChanges(a);
		}
	}else{
		x+=currOffsetX;
		y-=currOffsetY;
		if((cursorType==0 && nStations!=2) || (cursorType==0 && getBroken()==1 && currTrack!=track.size()-1)){
			clicks.push_back((double) x);
			clicks.push_back((double) y);
			if(clicks.size()==4){			//if youre adding a track, then it will call parseTrackInfo
				parseTrackInfo(clicks[0],clicks[1],clicks[2],clicks[3],x,y);
			}
		}else if(cursorType==2){		//erase a track
			int a = selectTrack(x,y);
			if((a>0 || track.size()==1)){
				if(track.size()==1){
					nStations=0;
				}							//if statements that will update the number of stations
				if(track.size()>2 && track[track.size()-1].trackType==1){
					nStations=2;
				}else{
					nStations=1;
				}
				int count=0;
				for(vector<TrackPiece>::iterator it=track.begin(); it!=track.end(); it++){
					if(count==a){
						track.erase(it);	//erase the correct track
						break;
					}
					count++;
				}
			}
			clicks.clear();
			clicks.push_back(track[track.size()-1].endX);
			clicks.push_back(track[track.size()-1].endY);
			currTrack=track.size()-1;
			if(track.size()==0){
				clicks.clear();			//if you deleted all the tracks.
				clicks.push_back(10);
				clicks.push_back(windowHeight);
				trackAdd=1;
				if(mainMenu->getState(1)==0){
					mainMenu->toggle(1);
				}
				if(mainMenu->getState(2)==1){
					mainMenu->toggle(2);
				}
				if(mainMenu->getState(3)==1){
					mainMenu->toggle(3);
				}
			}
		}else if(cursorType==3){	//this is to change what track you are adding onto.
			int a = selectTrack(x,y);
			if(a>-1){
				clicks.clear();
				clicks.push_back(track[a].endX);
				clicks.push_back(track[a].endY);
				currTrack=a;
			}
		}
	}
	drawCurrent(0);
	SDL_Flip( screen );
}

void RollerCoaster::parseDrag(Uint16 x,Uint16 y,int type){
	if(cursorType==1){
		if(type==SDL_MOUSEBUTTONDOWN){				//This makes it so that you can drag the screen.  Originally we had it so that the screen would update every
			dragStatus=1;					//mouse movement but it got to slow with the addition of more tracks that we took it out.
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
			drawCurrent(0);
			SDL_Flip( screen ); 		
		}
		if(currOffsetY>5000){
			currOffsetY=5000;		//upper limit
		}
	}
}

void RollerCoaster::load(int xCo,int yCo){
	track.clear();				//Load in from a file.  The track vector, the worth, and nStations need to be loaded in. 
	string s = "Coasters/RollerCoaster";
	ostringstream convert;
	convert << xCo;
	string stringxCo = convert.str();
	ostringstream convert1;
	convert1 << yCo;			//the name of the file is based on its address in the 2d vector of the park
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
		file >> worth;
		file >> nStations;
		int a;
		file >> a;
		clicks.push_back(a);
		file >> a;
		clicks.push_back(a);
	}
	if(track.size()>2 && track[track.size()-1].trackType==1){
		nStations=2;
	}else if(track.size()>0 && track[0].trackType==1){
		nStations=1;
	}else{
		nStations=0;
	}
}

void RollerCoaster::displayInterface(int xCo,int yCo){
	drawCurrent(0);						//sort of the 'main' of this class.  It has a while loop that continually updates the screen.
	SDL_Flip(screen);
	while(exitInterface==0){
		SDL_Event test_event;
		while(SDL_PollEvent(&test_event)){		//parses mouseClicks
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
	string s = "Coasters/RollerCoaster";		//saves to a file when you exit the while loop.  this is literally the exact opposit of the load function.
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
		file << worth;
		file << " ";
		file << nStations;
		file << " ";
		file << clicks[0];
		file << " ";
		file << clicks[1];
		file.close();
	}
	exitInterface=0;
	rateCoaster(); 	//rates coaster as you leave.
}
