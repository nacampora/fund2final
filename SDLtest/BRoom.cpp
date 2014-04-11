#include"hfiles/bRoom.h"

BRoom::BRoom(int t,string b)
{
    time_inside = t;
    bRoom_img = b;
}

void BRoom::enter()
{

}

void BRoom::exit()
{

}

string BRoom::get_img()
{
    return bRoom_img;
}
