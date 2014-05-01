//////////////////////////////////////////////////////////////////////////////
//Building.cpp contains functions to allow other functions and classes to   //
//detect and change which type of property the Building class is currently  //
// representing in the top down view of the Park							//
//////////////////////////////////////////////////////////////////////////////
#include "building.h"

Building::Building(int p,Finances *F)
{
	R1.setFinances(F);	
    property=p;
    
}

//returns which type of property the Building Class is currently representing
int Building::get_property()
{
    return property;
}

//accepts integer value to change which type of property the Building class is currently representing
void Building::set_property(int p)
{
    property=p;
}

//following function not currently used
/*
void Building::display()
{
    if(property==enum_rideB) file=rBuild.get_img();
    if(property==enum_rideY) file=rBuild.get_img();
    if(property==enum_bRoomB) file=bBuild.get_img();
    if(property==enum_bRoomY) file=bBuild.get_img();
    if(property==enum_grassB) file="grass_img.png";
    if(property==enum_grassY) file="grass_img.png";
    if(property==enum_pathB) file="path_img.png";
    if(property==enum_pathY) file="path_img.png";
    if(property==enum_shopB) file=sBuild.get_img();
    if(property==enum_shopY) file=sBuild.get_img();
    if(property==enum_vendorB) file=vBuild.get_img();
    if(property==enum_vendorY) file=vBuild.get_img();
}*/
