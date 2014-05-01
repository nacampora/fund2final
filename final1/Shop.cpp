////////////////////////////////////////////////////////////
//Shop class contains functions for describing people     //
//from People class' (People.h) interaction with building,//
//contains function for determining what people will buy  //
//as well as retrieving the file name of shop image  	  //
////////////////////////////////////////////////////////////
#include "shop.h"

//constructor for Shop class
Shop::Shop(int sh,int n,int l,int m,int h,char* f)//accepts variables for costs of items within the shop, time in shop, and file name of shop image
{
    time = 30;
    shop_cost = sh;
    null_price = n;
    low_price = l;
    med_price = m;
    high_price = h;
    shop_img = f;
}

//returns the file name referring to the image of the shop for use in top down view of park
char* Shop::get_img()
{
    return shop_img;
}

//functions below not currently in use. can be defined and implemented if animated people are added to the top down view of park
void Shop::enter()
{

}

void Shop::exit()
{

}


