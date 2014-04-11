#include "hfiles/shop.h"

Shop::Shop(int sh,int n,int l,int m,int h,string f)
{
    time = 30;
    shop_cost = sh;
    null_price = n;
    low_price = l;
    med_price = m;
    high_price = h;
    shop_img = f;
}

void Shop::enter()
{

}

void Shop::exit()
{

}

string Shop::get_img()
{
    return shop_img;
}
