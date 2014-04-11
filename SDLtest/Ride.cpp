#include"hfiles/ride.h"

Ride::Ride(string f)
{
    ride_img=f;
}

void Ride::enter()
{
    //move over to frankies stuff
}

void Ride::exit()
{

}

string Ride::get_img()
{
    return ride_img;
}
