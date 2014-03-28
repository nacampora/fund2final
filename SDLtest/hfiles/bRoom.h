#ifndef BROOM_H
#define BROOM_H

class bRoom
{
    public:
        bRoom(int t=10,string b="bRoom_img.bmp");
        void enter();
        void exit();

        private:

            int time_inside;
            string bRoom_img;
};
#endif
