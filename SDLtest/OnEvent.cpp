#include "CApp.h"
#include<math.h>
#include<fstream>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnExit() {
    Running = false;
}

void CApp::mainmenu(int mX,int mY)
{
    int x=((Pmap.get_Xgridsize()*50)/2)-(355/2);
    int y=(((Pmap.get_Ygridsize()*50)/2)-318/2);
    //if press red x button at top right of menu
    if((mX>x+320)&&mX<(x+345)&&mY>(y+10)&&mY<(y+34))
    {
        SDL_FreeSurface( parkEntranceFeeText );
        SDL_FreeSurface( currentLoanText );
        SDL_FreeSurface( balanceText );
    //run through grid checking if any squares are higlighted
        for(int i=0;i<Pmap.get_Ygridsize();i++)
        {
            for(int j=0;j<Pmap.get_Xgridsize();j++)
            {
                if(Pmap.grid[i][j].get_property()%2==1)//if square is highlighted
                {
                    if(i*50>150||j*50>200)//if highlighted square not in upper left corner
                    {
                        Pmap.set_menu(1);//close menu and reopen previously opened menu(in upper left corner)
                    }
                    else//if highlihgted square is in upper left corner
                    {
                        Pmap.set_menu(2);//close main menu and reopen previously opened menu (on upper right corner)
                    }
                }
            }
        }
        if(Pmap.get_menu()==5)//if the main menu is still open after checking for old menus to re-open
        {
            Pmap.set_menu(0);//close main menu
        }
    }//end of if(clicked on close menu button)
    else if(mX>x+313&&mX<x+340&&mY>y+53&&mY<y+68)
    {
        Pmap.F1.increaseEntranceFee();
    }
    else if(mX>x+313&&mX<x+340&&mY>y+74&&mY<y+91)
    {
        Pmap.F1.decreaseEntranceFee();
    }
    else if(mX>x+313&&mX<x+340&&mY>y+95&&mY<y+111)
    {
        Pmap.F1.increaseLoan();
    }
    else if(mX>x+313&&mX<x+340&&mY>y+117&&mY<y+132)
    {
        Pmap.F1.decreaseLoan();
    }
    else if(mX>x&&mX<x+106&&mY>y+213&&mY<y+316)
    {
        ofstream file("saved_game.txt");
        if(file.is_open())
        {
            for(int i=0;i<Pmap.get_Ygridsize();i++)
            {
                for(int j=0;j<Pmap.get_Xgridsize();j++)
                {
                    //if any squares on the board are highlighted at save, save as unhighlighted version
                    if(Pmap.grid[i][j].get_property()%2==1)
                    {
                        file << (Pmap.grid[i][j].get_property()-1);
                        file << " ";
                    }
                    else//otherwise save the square as is
                    {
                        file << Pmap.grid[i][j].get_property();
                        file << " ";
                    }
                }
                file << "\n";
            }
            file.close();
        }
    }
    else if(mX>x+139&&mX<x+242&&mY>y+213&&mY<y+316)
    {
        Running = false;
    }
}

int CApp::buymenu(int mX,int mY)
{

    int xSquare=0;
    int ySquare=0;
    for(int i=0;i<Pmap.get_Ygridsize();i++)
    {
        for(int j=0;j<Pmap.get_Xgridsize();j++)
        {
            if(Pmap.grid[i][j].get_property()%2==1)
            {
                 xSquare=j;
                 ySquare=i;
            }
        }
    }
    if(Pmap.get_menu()==1||Pmap.get_menu()==3)
    {
        if(mX>0&&mX<37&&mY>0&&mY<37)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_bRoomY);
            Pmap.set_menu(1);
            return 1;
        }
        else if(mX>0&&mX<37&&mY>39&&mY<75)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_rideY);
            Pmap.set_menu(3);
            return 1;
        }
        else if(mX>0&&mX<37&&mY>79&&mY<114)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_vendorY);
            Pmap.set_menu(1);
            return 1;
        }
        else if(mX>42&&mX<77&&mY>0&&mY<37)
        {
            Pmap.F1.sellShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_grassY);
            Pmap.set_menu(1);
            return 1;
        }
        else if(mX>42&&mX<77&&mY>39&&mY<75)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_pathY);
            Pmap.set_menu(1);
            return 1;
        }
        else if(mX>42&&mX<77&&mY>79&&mY<114)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_shopY);
            Pmap.set_menu(1);
            return 1;
        }
    }//end of if (menu on left open)
    else//if menu on right open
    {
        if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+37&&mY>0&&mY<37)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_bRoomY);
            Pmap.set_menu(2);
            return 1;
        }
        else if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+37&&mY>39&&mY<75)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_rideY);
            Pmap.set_menu(4);
            return 1;
        }
        else if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+37&&mY>79&&mY<114)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_vendorY);
            Pmap.set_menu(2);
            return 1;
        }
        else if(mX>Pmap.get_Xgridsize()*50-130+42&&mX<Pmap.get_Xgridsize()*50-130+77&&mY>0&&mY<37)
        {
            Pmap.F1.sellShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_grassY);
            Pmap.set_menu(2);
            return 1;
        }
        else if(mX>Pmap.get_Xgridsize()*50-130+42&&mX<Pmap.get_Xgridsize()*50-130+77&&mY>39&&mY<75)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_pathY);
            Pmap.set_menu(2);
            return 1;
        }
        else if(mX>Pmap.get_Xgridsize()*50-130+42&&mX<Pmap.get_Xgridsize()*50-130+77&&mY>79&&mY<114)
        {
            Pmap.F1.buyShop();
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_shopY);
            Pmap.set_menu(2);
            return 1;
        }
    }//end of if (menu on right open)
    return 0;
}

void CApp::coastermenu(int mX,int mY)
{
    int xSquare=0;
    int ySquare=0;
    for(int i=0;i<Pmap.get_Ygridsize();i++)
    {
        for(int j=0;j<Pmap.get_Xgridsize();j++)
        {
            if(Pmap.grid[i][j].get_property()%2==1)
            {
                 xSquare=j;
                 ySquare=i;
            }
        }
    }
    if(Pmap.get_menu()==3)
    {
       if(mX>0&&mX<76&&mY>119&&mY<140)
        {
            Pmap.grid[ySquare][xSquare].R1.displayInterface(xSquare,ySquare);
        }
    }
    if(Pmap.get_menu()==4)
    {
        if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+76&&mY>119&&mY<140)
        {
            Pmap.grid[ySquare][xSquare].R1.displayInterface(xSquare,ySquare);
        }
    }


}

void CApp::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void CApp::OnLButtonDown(int mX, int mY) {
    if(Begin==false)//if in start screen
    {
        int num=0;
        if(mX>921&&mX<1254&&mY>508&&mY<620)//if user presses "load" button
        {
            ifstream myfile ("saved_game.txt");
            if (myfile.is_open())
            {
                for(int i=0;i<Pmap.get_Ygridsize();i++)
                {
                    for(int j=0; j<Pmap.get_Xgridsize();j++)
                    {
                        myfile >> num;
                        Pmap.grid[i][j].set_property(num);//reading one character from file to array
                    }
                }
                myfile.close();
            for(int k=0;k<Pmap.get_Ygridsize();k++)
            {
                for(int l=0;l<Pmap.get_Xgridsize();l++)
                {
                    Pmap.grid[k][l].R1.load(l,k);
                }
            }
                Begin=true;

            }
            else
            {
                return;
            }
        }
        if(mX>921&&mX<1254&&mY>358&&mY<472)//if user presses "new game" button
        {
           Begin=true;
        }
    }//end of if (Begin==false)

    else//else in the top down view of park
    {
        int clicked=0;
        int xSquare=floor(mX/50)*50;//determines an integer number that coorisponds with a x value in the 2D grid vector of vectors
        int ySquare=floor(mY/50)*50;//determines an integer number that coorisponds with a Y value in the 2D grid vector of vectors
        if(Pmap.get_menu()==5)//if the main menu is already open
        {
            //determine what actions to take depending on where user has clicked
            mainmenu(mX,mY);
        }

        else if(((mX>((Pmap.get_Xgridsize()*50)-25))&&mY<25)&&Pmap.get_menu()!=5)//if clicked on open main menu icon (top right corner of screen)//if main menu is not open
        {
            prep_finances();
            Pmap.set_menu(5);//open main menu
            apply_surface( ((Pmap.get_Xgridsize()*50)/2)-(355/2)+222, (((Pmap.get_Ygridsize()*50)/2)-318/2)+57, parkEntranceFeeText, Surf_Display );
            apply_surface( ((Pmap.get_Xgridsize()*50)/2)-(355/2)+222, (((Pmap.get_Ygridsize()*50)/2)-318/2)+100, currentLoanText, Surf_Display );
            apply_surface( ((Pmap.get_Xgridsize()*50)/2)-(355/2)+222, (((Pmap.get_Ygridsize()*50)/2)-318/2)+141, balanceText,Surf_Display );
            //apply_surface( 100, 400, dateText, Surf_Display );
        }
        else if(Pmap.get_menu()!=5)//as long as main menu isnt open, allow clicking on other parts of screen
        {
            if(Pmap.get_menu()==3||Pmap.get_menu()==4)
            {
                coastermenu(mX,mY);//determine if user clicked the edit coaster button
            }

            if(Pmap.get_menu()>0&&Pmap.get_menu()<5)//if the highlighted square menu is open
            {
                clicked=buymenu(mX,mY);//determine what action to take based on where user clicks
            }

            if(clicked!=1)
            {
                for(int i=0;i<Pmap.get_Ygridsize();i++)
                {
                    for(int j=0;j<Pmap.get_Xgridsize();j++)
                    {
                        if((i!=ySquare/50)||(j!=xSquare/50))//if not same square as clicked
                        {
                            if(Pmap.grid[i][j].get_property()%2==1)//if square is highlighted
                            {
                                Pmap.grid[i][j].set_property(Pmap.grid[i][j].get_property()-1);//set to unhighlighted
                            }
                        }
                    }
                }
                if(Pmap.grid[ySquare/50][xSquare/50].get_property()%2==0)//if square is unhighlighted when clicked
                {
                    //specialized menu for ride
                    if(Pmap.grid[ySquare/50][xSquare/50].get_property()==Pmap.grid[0][0].enum_rideB)
                    {
                        Pmap.grid[ySquare/50][xSquare/50].set_property(Pmap.grid[ySquare/50][xSquare/50].get_property()+1);
                        //set menu at upper left corner unless clicked in that area then upper right corner
                        if(xSquare>130||ySquare>200)
                        {
                            Pmap.set_menu(3);
                        }
                        else
                        {
                            Pmap.set_menu(4);
                        }
                    }
                    else//if not a rollercoaster square that was selected
                    {
                        //change square to highlighted version
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


                }//end of if square is unhighlighted when clicked
                else if(Pmap.grid[ySquare/50][xSquare/50].get_property()%2==1)//if square is highlighted when clicked
                {
                    //unhighlight square and close menu
                    Pmap.grid[ySquare/50][xSquare/50].set_property(Pmap.grid[ySquare/50][xSquare/50].get_property()-1);
                    Pmap.set_menu(0);
                }
            }
        }//end of else main menu isnt open
    }//end of else referring to being in top down view of park
}

/*void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    if(Pmap.get_menu()==5)
    {
        switch(sym)
        {
            case SDLK_1:
            {

                ofstream file("saved_game.txt");
                if(file.is_open())
                {
                    for(int i=0;i<Pmap.get_Ygridsize();i++)
                    {
                        for(int j=0;j<Pmap.get_Xgridsize();j++)
                        {
                            //if any squares on the board are highlighted at save, save as unhighlighted version
                            if(Pmap.grid[i][j].get_property()%2==1)
                            {
                                file << (Pmap.grid[i][j].get_property()-1);
                                file << " ";
                            }
                            else//otherwise save the square as is
                            {
                                file << Pmap.grid[i][j].get_property();
                                file << " ";
                            }

                        }
                        file << "\n";
                    }
                    file.close();
                }
                break;
            }
            case SDLK_2:
                Running = false;
                break;
            case SDLK_3:
                for(int i=0;i<Pmap.get_Ygridsize();i++)
                {
                    for(int j=0;j<Pmap.get_Xgridsize();j++)
                    {
                        if(Pmap.grid[i][j].get_property()%2==1)//if square is highlighted
                        {
                            if(i*50>150||j*50>200)
                            {
                               Pmap.set_menu(1);
                            }
                            else
                            {
                                Pmap.set_menu(2);
                            }
                        }
                    }
                    if(Pmap.get_menu()==5)
                    {
                        Pmap.set_menu(0);
                    }
                }
                break;
            default:
                break;
        }
    }
    else
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
                case SDLK_1:
                    //sell
                    Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_grassY);
                break;

                case SDLK_2:
                    OnKeyDown(SDLKey sym_2, SDLMod mod_2, Uint16 unicode_2)
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
                    }

                    Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_pathY);

                break;

                case SDLK_3:
                    Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_bRoomY);

                break;

                case SDLK_4:
                    Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_vendorY);

                break;

                case SDLK_5:
                    Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_shopY);

                break;

                case SDLK_6:
                    Pmap.grid[y][x].set_property(Pmap.grid[0][0].enum_rideY);
                    if(x*50>130||y*50>200)
                    {
                        Pmap.set_menu(3);
                    }
                    else
                    {
                        Pmap.set_menu(4);
                    }


                break;

                case SDLK_7:
                    if(Pmap.get_menu()==3||Pmap.get_menu()==4)
                    {
                        //enter editing ride function
                    }
                break;

                case SDLK_8:

                break;

                case SDLK_9:

                break;

                case SDLK_0:

                break;

                default:

                break;
            }
        }
    }
}*/

void CApp::prep_finances()
{
    SDL_Color textColor = { 0, 0, 0 };
    TTF_Font *font = NULL;
    int parkEntranceFeeInt = Pmap.F1.getParkEntranceFee();
    ostringstream convert1;
    convert1 << parkEntranceFeeInt;
    string str1 = convert1.str();
    const char * parkEntranceFee = str1.c_str();

    int currentLoanInt = Pmap.F1.getCurrentLoan();
    ostringstream convert2;
    convert2 << currentLoanInt;
    string str2 = convert2.str();
    const char * currentLoan = str2.c_str();

    int balanceInt = Pmap.F1.getBalance();
    ostringstream convert3;
    convert3 << balanceInt;
    string str3 = convert3.str();
    const char * balance = str3.c_str();
}
