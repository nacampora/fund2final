#include "Force.h"
#include <iostream>
using namespace std;

Force::Force(int sd, double place, double a, double f,int time){
	side=sd;
	placement=place;
	ang=a;
	force=f;
	remaining=time;
}

void Force::printOut(){
	cout << side << endl << placement << endl << ang << endl << force << endl << remaining << endl;
}
