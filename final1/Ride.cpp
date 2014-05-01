///////////////////////////////////////////////////////////
//Ride class contains functions for describing people    //
//from People class' (People.h) interaction with building//
//as well as retrieving the file name of ride image      //
///////////////////////////////////////////////////////////
#include"ride.h"

//constructor for Ride class
Ride::Ride(char* f) //f= file name for bathroom image
{
    ride_img=f;
}

//returns the file name referring to the image of the ride for use in top down view of park
char* Ride::get_img()
{
    return ride_img;
}

//functions below not currently in use. can be defined and implemented if animated people are added to the top down view of park
void Ride::enter()
{
    
}

void Ride::exit()
{

}


