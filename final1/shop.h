/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Shop class holds the file name for the image representing it in the gui of top down view of park, functions              //
//that can be used to expand on the People class (People.h) interaction with the park, and potential costs for items       //
//that can be sold within the shop									   													   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SHOP_H
#define SHOP_H

#include<iostream>
#include<string.h>
using namespace std;

class Shop{
    public:
        Shop(int sh=0,int n=0,int l=10,int m=20,int h=40,char* f="shop_img.png");//constructor initializes costs of items within shop as well as file name
        //int random_buy(); 		//function for determining what item a person will buy from the shop
        void enter();				//function can be used to define how often people from People class enter the shop
        void exit();				//function can be used to define how often people from People class exit the shop
        char* get_img();			//returns the file name of the shop image

    private:
    	//variables for costs of items within the shop as well as time spent in the shop before leaving
        int time;					//time spent in shop
        int shop_cost;
        int null_price;
        int low_price;
        int med_price;
        int high_price;
        char* shop_img;			//variable holds file name of shop image for use in top down view of park
};
#endif
