#ifndef
#define

class shop();
    public:
        shop(int n=0,l=10,mo=15,mt=20,h=40,f="shop_img.bmp");
        int random_buy();
        void enter();
        void exit();
    private:
        int null_price;
        int low_price;
        int med_one_price;
        int med_two_price;
        int high_price;
        string shop_img;
#endif
