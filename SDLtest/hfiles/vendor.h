#ifndef VENDOR_H
#define VENDOR_H
#include<string>
#include<iostream>
using namespace std;
class vendor
{
    public:

        vendor(int n=0,int l=5,int h=10,int t=10,string f="vendor_img.bmp");
        int random_buy();
        void enter();
        void exit();
    private:
        string vendor_img;
        int null_price;
        int low_price;
        int high_price;
        int time_inside;

};
#endif
