#include"hfiles/vendor.h"
#include<time.h>

Vendor::Vendor(int n,int l,int h,int t,string f)
{
    vendor_img=f;
    null_price=n;
    low_price=l;
    high_price=h;
    time_inside=t;
    srand(time(NULL));
}

int Vendor::random_buy()
{
    int rand_buy=rand()%3;
    if(rand_buy==0) return null_price;
    else if(rand_buy==1) return low_price;
    else if(rand_buy==2) return high_price;
    else return null_price;

}

void Vendor::enter()
{

}

void Vendor::exit()
{

}

string Vendor::get_img()
{
    return vendor_img;
}
