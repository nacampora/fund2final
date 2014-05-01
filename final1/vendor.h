/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Vendor class holds the file name for the image representing it in the gui of top down view of park, functions            //
//that can be used to expand on the People class (People.h) interaction with the park, and potential costs for items       //
//that can be sold within the vendor								   													   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VENDOR_H
#define VENDOR_H
#include<string>
#include<iostream>
#include <stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;

class Vendor
{
    public:

        Vendor(int n=0,int l=5,int h=10,int t=10,char* f="vendor_img.png");
        int random_buy();				//function for determining what item a person will buy from the vendor
        void enter();					//function can be used to define how often people from People class enter the vendor
        void exit();					//function can be used to define how often people from People class exit the vendor
        char* get_img();				//returns the file name of the shop image
    private:
        char* vendor_img;				//contains file name of vendor image for top down view of park
        //following variables contain prices for vendor and time spent in the vendor by people
        int null_price;
        int low_price;
        int high_price;
        int time_inside;

};
#endif
