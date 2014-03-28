#ifndef
#define

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

        display();
    private:
        int property;
        enum
        {
            grass=0,
            path,
            ride,
            shop,
            bRoom,
            vendor
        };
};
#endif
