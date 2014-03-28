#ifndef
#define

class vendor
{
    public:

        vendor(int n=0,int l=5,int h=10,t=10,f="vendor_img.bmp");
        int random_buy();
        void enter();
        void exit();
    private:
        string vendor_img="vendor_img.bmp";
        int null_price;
        int low_price;
        int high_price;
        int time_inside;

};
#endif
