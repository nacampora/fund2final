#include "CApp.h"
#include<math.h>

void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnExit() {
    Running = false;
}

void CApp::OnLButtonDown(int mX, int mY) {
    int xSquare=floor(mX/50)*50;
    int ySquare=floor(mY/50)*50;
    for(int i=0;i<Pmap.get_Ygridsize();i++)
    {
        for(int j=0;j<Pmap.get_Xgridsize();j++)
        {
            if((i!=ySquare/50)||(j!=xSquare/50))
            {
                if(Pmap.grid[i][j].get_property()%2==1)
                {
                    Pmap.grid[i][j].set_property(Pmap.grid[i][j].get_property()-1);
                }
            }
        }
    }
    if(Pmap.grid[ySquare/50][xSquare/50].get_property()%2==0)
    {
        Pmap.grid[ySquare/50][xSquare/50].set_property(Pmap.grid[ySquare/50][xSquare/50].get_property()+1);
        //set menu at upper left corner unless clicked in that area then upper right corner
        if(xSquare>130||ySquare>200)
        {
            Pmap.set_menu(1);
        }
        else
        {
            Pmap.set_menu(2);
        }

    }
    else if(Pmap.grid[ySquare/50][xSquare/50].get_property()%2==1)
    {
        Pmap.grid[ySquare/50][xSquare/50].set_property(Pmap.grid[ySquare/50][xSquare/50].get_property()-1);
        Pmap.set_menu(0);
    }

}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    int x = 0;
    int y = 0;
    int menu_open=0;

     for(int i=0;i<Pmap.get_Ygridsize();i++)
    {
        for(int j=0;j<Pmap.get_Xgridsize();j++)
        {
                if(Pmap.grid[i][j].get_property()%2==1)
                {
                    x=j;
                    y=i;
                    menu_open = 1;
                }
        }
    }

    if(menu_open==1)
    {
        switch (sym)
        {
            case SDLK_0:
                //sell
                Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_grassB);
            break;

            case SDLK_1:
                /*OnKeyDown(SDLKey sym_2, SDLMod mod_2, Uint16 unicode_2)
                {
                    switch(sym_2)
                    {
                        case SDLK_y:
                            Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_path)
                        break;

                        case SDLK_n:

                        break;

                        default;

                        break;
                    }
                }*/

                Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_pathB);

            break;

            case SDLK_2:
                Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_rideB);

            break;

            case SDLK_3:
                Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_shopB);

            break;

            case SDLK_4:
                Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_bRoomB);

            break;

            case SDLK_5:
                Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_vendorB);

            break;

            case SDLK_6:

            break;

            case SDLK_7:

            break;

            case SDLK_8:

            break;

            case SDLK_9:

            break;

            default:

            break;
        }
    }
}
