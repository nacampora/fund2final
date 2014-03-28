#ifndef SHOP_H
#define SHOP_H

#include<iostream>
#include<string.h>
using namespace std;

class shop{
    public:
        shop(int n=0,int l=10,int mo=15,int mt=20,int h=40,string f="shop_img.bmp");
        int random_buy();
        void enter();
        void exit();
    private:
        int null_price;
        int low_price;
        int med_one_price;
        int med_two_price;
        int high_price;
        string shop_img;
};
#endif
