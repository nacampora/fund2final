#ifndef GLOBAL_CPP
#define GLOBAL_CPP

#include <math.h>
int isInsideBox(double x1,double y1,double x2,double y2, double x, double y){
	int xmax,xmin,ymax,ymin;
	if(x1>x2){
		xmax=x1;
		xmin=x2;
	}else{
		xmax=x2;
		xmin=x1;
	}
	if(y1>y2){
		ymax=y1;
		ymin=y2;
	}else{
		ymax=y2;
		ymin=y1;
	}
	if(x<xmin || x>xmax || y<ymin || y>ymax){
		return 0;
	}else{
		return 1;
	}
}

double distance(double x1,double y1,double x2,double y2){
	return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}

#endif
