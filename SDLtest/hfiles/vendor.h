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

        Vendor(int n=0,int l=5,int h=10,int t=10,string f="vendor_img.png");
        int random_buy();
        void enter();
        void exit();
        string get_img();
    private:
        string vendor_img;
        int null_price;
        int low_price;
        int high_price;
        int time_inside;

};
#endif
