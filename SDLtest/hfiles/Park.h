#ifndef PARK_H
#define PARK_H

#include<math.h>
#include<vector>
#include<iostream>
#include "building.h"

using namespace std;
//#include "person.h"//temporary name

using namespace std;

class Park
{
    public:
        Park(double m=0,int p=0, int xgs=26,int ygs=10,int men=0);//constructor

        //person people;
        void event();

        double money;
        int popularity;
        int get_Xgridsize();
        int get_Ygridsize();
        int get_menu();
        void set_menu(int);
        vector< vector<Building> > grid;
    private:

        int menu;
        int XgridSize;
        int YgridSize;
        int get_num_rides();
        int get_num_shops();
        int get_num_vendors();
        int get_brooms();
        int get_num_people();
};

#endif
