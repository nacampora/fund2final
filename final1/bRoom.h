/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BRoom class holds the file name for the image representing it in the gui of top down view of park as well as functions   //
//that can be used to expand on the People class (People.h) interaction with the park									   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef BROOM_H
#define BROOM_H
#include<iostream>
#include<string.h>
using namespace std;

class BRoom
{
    public:
        BRoom(int t=10,char* b="bRoom_img.png");	//constructor passes in: t= time people spend in bathroom, and file name for image of bathroom
        void enter();								//function can be used to define how often people from People class enter the bathroom
        void exit();								//function can be used to define how often people from People class exit the bathroom
        char* get_img();							//returns the file name of the bathroom image

        private:

            int time_inside;						//variable describes how long people from People class will spend in bathroom
            char* bRoom_img;						//variable holds file name of image for bathroom
};
#endif
