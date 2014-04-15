#ifndef FORCE_H
#define FORCE_H

#include <iostream>
using namespace std;

class Force {
	public:
		Force(int,double,double,double,int);
		int side;
		double placement;
		double ang;
		double force;
		int remaining;
		void printOut();
};

#endif
