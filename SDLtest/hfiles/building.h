#ifndef BUILDING_H
#define BUILDING_H

#include"shop.h"
#include"bRoom.h"
#include"vendor.h"
#include "ride.h"

class building
{
    public:
        building();
        shop sBuild;
        bRoom bBuild;
        vendor vBuild;
        ride rBuild;

        void display();
    private:
        int property;
        enum
        {
            enum_grass=0,
            enum_path,
            enum_ride,
            enum_shop,
            enum_bRoom,
            enum_vendor
        };
};
#endif
