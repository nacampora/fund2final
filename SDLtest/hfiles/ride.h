#ifndef RIDE_H
#define RIDE_H

using namespace std;
class ride
{
    public:

        ride(int p=0,int s=0,string f="ride_img.bmp");
        void enter();
        void exit();

    private:

            int popularity;
            int scariness;
            string ride_img;
};
#endif
