/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ride class holds the file name for the image representing it in the gui of top down view of park as well as functions   //
//that can be used to expand on the People class (People.h) interaction with the park									   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef RIDE_H
#define RIDE_H
#include<iostream>
#include<string.h>
using namespace std;

class Ride
{
    public:

        Ride(char* f="ride_img.png");	//constructor
        void enter();					//function can be used to define how often people from People class enter the ride
        void exit();					//function can be used to define how often people from People class exit the ride
        char* get_img();				//returns the file name of the bathroom image

    private:

            char* ride_img;			//variable holds file name of image for ride
};
#endif
