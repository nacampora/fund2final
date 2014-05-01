////////////////////////////////////////////////////////////////////////////////////////
//Park.cpp contains function for obtaining the menu that is open in the top down view //
//of the park as well as the x and y size of the park grid. constructor instantiates  //
//the Building class (building.h)													  //
////////////////////////////////////////////////////////////////////////////////////////
#include "Park.h"
using namespace std;
//constructor for park Class (Park.h)
Park::Park(int xgs,int ygs,int men)
{
    menu=men;						//initializes the menu that is open in the top down view of the park
	XgridSize=xgs;					//initializes the x size of the park grid
    YgridSize=ygs;					//initializes the y size of the park grid
    vector<Building> a;				//temporary vector of Building classes
    for(int i=0;i<XgridSize;i++)
    {
        Building build(0,&F1);		//instantiates the class Building (building.h), passes in the type of property the specific building represents
        							//as well as a pointer to the Finances class instantiated in the Park.h Park class
        a.push_back(build);
    }
    for(int j=0;j<YgridSize;j++)
    {

        grid.push_back(a);			//creates a 2D vector of the Building classes
    }

}
//returns which menu is open in top down view of park
int Park::get_menu()
{
    return menu;
}

//allows functions and member classes to set which menu is open in top down view of park
//allows functions and classes to set which menu is open represented by the integer value passed in
//menus are as follows: 0= no menu, 1= buy building menu on left side of screen, 2= buy building menu on right side of 
//screen 3=buy building menu with option to build roller coaster on left side of screen, 4= buy building menu with
void Park::set_menu(int m)
{
    menu=m;
}

//returns x size of park grid
int Park::get_Xgridsize()
{
    return XgridSize;
}

//returns y size of park grid
int Park::get_Ygridsize()
{
    return YgridSize;
}


//commented out functions not currently used
/*
//returns the number of roller coasters currently in the park
int Park::get_num_rides()
{
    int numRide=0;
    for(int i=0;i<YgridSize;i++)
    {
        for(int j=0;j<XgridSize;j++)
        {
            if(grid[i][j].get_property()==grid[i][j].enum_rideB||grid[i][j].enum_rideY)
            {
                numRide++;
            }
        }
    }
    return numRide;
}

//returns the number of shops currently in the park
int Park::get_num_shops()
{
    int numShop=0;
    for(int i=0;i<YgridSize;i++)
    {
        for(int j=0;j<XgridSize;j++)
        {
            if(grid[i][j].get_property()==grid[i][j].enum_shopB||grid[i][j].enum_shopY)
            {
                numShop++;
            }
        }
    }
    return numShop;
}

*/
