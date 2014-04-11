#include "hfiles\building.h"

Building::Building(int p)
{

    property=p;
    file = "grass_img.png";
}

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
}

int Building::get_property()
{
    return property;
}

void Building::set_property(int p)
{
    property=p;
}

