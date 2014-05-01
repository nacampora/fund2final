#ifndef SHOP_H
#define SHOP_H

#include<iostream>
#include<string.h>
using namespace std;

class Shop{
    public:
        Shop(int sh=0,int n=0,int l=10,int m=20,int h=40,string f="shop_img.png");
        //int random_buy();
        void enter();
        void exit();
        string get_img();

    private:
        int time;
        int shop_cost;
        int null_price;
        int low_price;
        int med_price;
        int high_price;
        string shop_img;
};
#endif
