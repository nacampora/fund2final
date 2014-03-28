#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include "building.h"
#include<string.h>

class gridSquare
{
    public:
        gridSquare(int p=0);
        building build;
        double purchase();
        void display();
        string get_property();

    private:

};
#endif
