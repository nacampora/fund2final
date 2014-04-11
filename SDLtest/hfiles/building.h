#ifndef BUILDING_H
#define BUILDING_H

#include"shop.h"
#include"bRoom.h"
#include"vendor.h"
#include "ride.h"

class Building
{
    public:
        Building(int p=0);

        Shop sBuild;
        BRoom bBuild;
        Vendor vBuild;
        Ride rBuild;

        void display();

        enum {
            enum_grassB=0,
            enum_grassY,
            enum_pathB,
            enum_pathY,
            enum_rideB,
            enum_rideY,
            enum_shopB,
            enum_shopY,
            enum_bRoomB,
            enum_bRoomY,
            enum_vendorB,
            enum_vendorY
        };
        void set_property(int);
        int get_property();
    private:
        string file; //temporary variable
        int property;

};
#endif
