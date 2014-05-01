//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Park.h is instantiated in class CApp in CApp.h. it instantiates the classes: Finances (Finances.h), Time (Time.h), People(People.h), and Building     //
//(building.h) contains variables that define size of the top down view of the park. the size of the park determines the size of the gui window that    //
// opens when game begins. 																																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARK_H
#define PARK_H

#include<math.h>
#include<vector>
#include<iostream>
#include "building.h"
#include"Finances.h"
#include"Time.h"
#include "People.h"

using namespace std;

using namespace std;

//Class Park is instantiated under class CApp (CApp.h)
class Park
{
    public:
        Park(int xgs=26,int ygs=13,int men=0);//constructor xgs=x size of park grid, ygs= y size of park grid, men=which menu is open(initialized to no open menus)

        
        //void event();
        
        int get_Xgridsize();				//returns the x size of park grid
        int get_Ygridsize();				//returns the y size of park grid
        int get_menu();						//returns which menu is open
        void set_menu(int);					//allows functions and classes to set which menu is open represented by the integer value passed in
        									//menus are as follows: 0= no menu, 1= buy building menu on left side of screen, 2= buy building menu on right side of 
        									//screen 3=buy building menu with option to build roller coaster on left side of screen, 4= buy building menu with
        									//option to build roller coaster on right side of screen, 5=main menu
        vector< vector<Building> > grid;	//a 2D vector that represents the top down view of the park, Building (building.h) instantiated in Park constructor, 
        									//Building contains information as to which type of building is displayed on specific grid square in the top down view 
        Finances F1;						//instantiates Finances Class (Finances.h) which holds information about how much money the player has to use in buying
        									//buildings and buying pieces for rollercoasters 

        Time T1;							//instantiates Time Class (Time.h) which contains information about how much time has passed in the game world
        People P1;							//instantiates People class (People.h) which contains information about the people that virtually inhabit the park
        									//the people spend money at the different buildings built in the park which is reflected in the Finances class

    private:

        int menu;							//variable holds the value representing which type of menu is open in the top down view of park
        int XgridSize;						//variable holds the x size of park grid
        int YgridSize;						//variable holds the y size of the park grid
};

#endif
