#ifndef
#define

class bRoom
{
    public:

        bRooom(int t=10,b="bRoom_img.bmp");
        void enter();
        void exit();

        private:

            int time_inside;
            string bRoom_img;
};
#endif
