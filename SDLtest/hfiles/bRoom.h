#ifndef BROOM_H
#define BROOM_H
#include<iostream>
#include<string.h>
using namespace std;

class BRoom
{
    public:
        BRoom(int t=10,string b="bRoom_img.png");
        void enter();
        void exit();
        string get_img();

        private:

            int time_inside;
            string bRoom_img;
};
#endif
