#include "hfiles\Park.h"
using namespace std;
Park::Park(double m,int p,int xgs,int ygs,int men)
{
    menu=men;
    money=m;
    popularity=p;
    XgridSize=xgs;
    YgridSize=ygs;
    vector<Building> a;
    for(int i=0;i<XgridSize;i++)
    {
        Building build;
        a.push_back(build);
    }
    for(int j=0;j<YgridSize;j++)
    {

        grid.push_back(a);
    }

}
void Park::event()
{

}

int Park::get_menu()
{
    return menu;
}

void Park::set_menu(int m)
{
    menu=m;
}
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
int Park::get_num_vendors()
{
    int numVendor=0;
    for(int i=0;i<YgridSize;i++)
    {
        for(int j=0;j<XgridSize;j++)
        {
            if(grid[i][j].get_property()==grid[i][j].enum_vendorB||grid[i][j].enum_vendorY)
            {
                numVendor++;
            }
        }
    }
    return numVendor;
}
int Park::get_brooms()
{
    int numBRooms=0;
    for(int i=0;i<YgridSize;i++)
    {
        for(int j=0;j<XgridSize;j++)
        {
            if(grid[i][j].get_property()==grid[i][j].enum_bRoomB||grid[i][j].enum_bRoomY)
            {
                numBRooms++;
            }
        }
    }
    return numBRooms;
}
int Park::get_num_people()
{

}

int Park::get_Xgridsize()
{
    return XgridSize;
}

int Park::get_Ygridsize()
{
    return YgridSize;
}
