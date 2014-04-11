#ifndef RIDE_H
#define RIDE_H
#include<iostream>
#include<string.h>
using namespace std;

class Ride
{
    public:

        Ride(string f="ride_img.png");
        void enter();
        void exit();
        string get_img();

    private:

            string ride_img;
};
#endif
