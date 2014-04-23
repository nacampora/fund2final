#include <iostream>
using namespace std;

#include "Menu.h"
#include "global.cpp"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include <vector>

Menu::Menu(SDL_Surface *screen,double X,double Y,int nButtons,int buttonS){
	s=screen;
	x=X;
	y=Y;
	ratio=5;
	buttonSize=buttonS;
	for(int F=0;F<nButtons;F++){
		addButton();
	}
	int sz = b.size();
	int col=0;
	while(col*col*ratio<=sz-1){
		col++;
	}
	int row = ((int) (sz/col)+1);
	if(sz % col == 0){
		row--;
	}
	rect.push_back(x);
	rect.push_back(y);
	rect.push_back(x+(col+1)*buttonS/2 + col*buttonS);
	rect.push_back(y+(row+1)*buttonS/2 + row*buttonS);
}

vector<double> Menu::findPlace(int element,int total){
	int col=0;
	while(col*col*ratio<=total-1){
		col++;
	}
	int column = (element) % col;
	int row = ((int) (element) / col);
	double y1 = y + (row+1)*(buttonSize/2) + (row)*buttonSize;
	double x1 = x + (column+1)*(buttonSize/2) + (column)*buttonSize;
	vector<double> point;
	point.push_back(x1);
	point.push_back(y1);
	return point;
}

vector<double> Menu::menuBox(){
	return rect;		
}

void Menu::addButton(){
	Button button(0,0,buttonSize);
	b.push_back(button);
	vector<double> point;
	int s = b.size(),count=0;
	for(vector<Button>::iterator it=b.begin(); it!=b.end(); it++){
		point = findPlace(count,s);
		it->move(point[0],point[1]);
		point.clear();
		count++;
	} 
}

void Menu::draw(SDL_Surface *screen,vector<SDL_Surface *> background){
//	rectangleRGBA(s,rect[0],rect[1],rect[2],rect[3],155,155,155,155);
	SDL_Rect offset;
	offset.x=rect[0];
	offset.y=rect[1];
	SDL_Rect rec;
	rec.x=rec.y=0;
	rec.w=(rect[2]-rect[0]);
	rec.h=(rect[3]-rect[1]);
//	SDL_BlitSurface(background[0],&rec,screen,&offset);
	int count = 0;
	for(vector<Button>::iterator it=b.begin(); it!=b.end(); it++){
		count++;
		offset.x=it->cornerX;
		offset.y=it->cornerY;
		if(it->getState()==1){
			SDL_BlitSurface(background[0],NULL,screen,&offset);
		}
		SDL_BlitSurface(background[count],NULL,screen,&offset);
//		it->draw(screen,count);
	}
}

void Menu::move(double x1,double y1){
	double changeX=x1-x;
	double changeY=y1-y;
	rect[0]=rect[0]+changeX;
	rect[1]=rect[1]+changeY;
	rect[2]=rect[2]+changeX;
	rect[3]=rect[3]+changeY;
	x=x1;
	y=y1;
	for(vector<Button>::iterator it=b.begin(); it!=b.end(); it++){
		it->move((it->cornerX)+changeX,(it->cornerY)+changeY);		
	}	
}

int Menu::buttonClicked(double x1,double y1){
	if(isInsideBox(rect[0],rect[1],rect[2],rect[3],x1,y1)==0){
		return -2;
	}else{
		for(int F=0;F<b.size();F++){
			vector<double> pos = findPlace(F,b.size());
			if(isInsideBox(pos[0],pos[1],pos[0]+buttonSize,pos[1]+buttonSize,x1,y1)==1)
				return F;
		}
		return -1;
	}
}

void Menu::toggle(int a){
	if(a>-1){
		b[a].toggle();
	}
}

int Menu::getState(int a){
	if(a>-1 && a<b.size()){
		return b[a].getState();
	}else{
		return -1;
	}
}
