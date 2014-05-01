/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//The Building class is instantiated in a 2D vector in the Park class (Park.h) and each building class holds a value allowing it to represent  //
//one type of building to be displayed in the top down view of the park. It instantiates classes for types of buildings that it can represent: //
// Shop (shop.h), BRoom (bRoom.h) ( a bathroom), Vendor (vendor.h), Ride (ride.h). it contains functions allowing other classes and functions  //
// to modify which type of building the class represents and these types of buildings are represented as enumerated integers.				   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BUILDING_H
#define BUILDING_H

#include "shop.h"
#include "bRoom.h"
#include "vendor.h"
#include "ride.h"
#include "RollerCoaster.h"
#include <iostream>
#include <string.h>
#include "Finances.h"
using namespace std;

//Building class is instantiated in a 2D vector in Park class (Park.h)
class Building
{
    public:
        Building(int p,Finances *);	//constructor which passes in: p=type of property it represents and a pointer to the Finances class instantiated
        							// in the Park class
        Finances *F1;				//variable holds pointer to Finances class instantiated in Park class
        RollerCoaster R1;			//instantiates the RollerCoaster class (RollerCoaster.h) which is used to enter the building rollercoaster screen
        							// during game play
        //the following are classes that are also the types of properties the building class can represent
        Shop sBuild;				
        BRoom bBuild;
        Vendor vBuild;
        Ride rBuild;
		
		//the enumeration is used to make clear which type of property the building class represents at the current state of the game
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
        void set_property(int);		//function accepts an integer represented by the previous enumeration allowing functions and other classes 	
        							// to set which type of property the building class represents
        int get_property();			//allows other functions and classes to detect which type of property the building class is currently representing
    private:
        int property;				//variable holds a value representing which type of property the building class is currently representing
        


};
#endif
