///////////////////////////////////////////////////////////
//Bathroom class contains functions for describing people//
//from People class' (People.h) interaction with building//
//as well as retrieving the file name of bathroom image  //
///////////////////////////////////////////////////////////

#include"bRoom.h"
//constructor for BRoom class
BRoom::BRoom(int t,char* b) //t= time people spend inside bathroom, b= file name for bathroom image
{
    time_inside = t;
    bRoom_img = b;
}

//returns the file name referring to the image of the bathroom for use in top down view of park
char* BRoom::get_img()
{
    return bRoom_img;
}
//functions below not currently in use. can be defined and implemented if animated people are added to the top down view of park
void BRoom::enter()
{

}

void BRoom::exit()
{

}


