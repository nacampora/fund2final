#ifndef PARK_H
#define PARK_H

#include<math.h>
#include<vector>
#include<iostream>
#include "gridSquare.h"
//#include "person.h"//temporary name

using namespace std;

class Park
{
    public:
        Park(double m=0,int p=0,int nR=0,int nS=0,int nV=0,int nB=0,int nP=0);

        //person people;
        void event();

        double money;
        int popularity;

    private:
         vector< vector<gridSquare> > grid;

        int get_num_rides();
        int get_num_shops();
        int get_num_vendors();
        int get_brooms();
        int get_num_people();
};

#endif
