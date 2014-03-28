#ifndef
#define

#inclue<math.h>
#include<vector.h>
#include<iostream>
#inclue "gridSquare.h"
#include "person.h"//temporary name

using namespace std;

class Park
{
    public:
        Park(double m=0,int p=0,int nR=0,int nS=0,int nV=0,int nB=0,int nP=0);

        person();
        void event();

        double money;
        int popularity;

    private:
        gridsquare grid;
        gridsquare vector< vector<grid> >;

        int get_num_rides();
        int get_num_shops();
        int get_num_vendors();
        int get_brooms();
        int get_num_people();
};

#endif
