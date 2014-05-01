//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OnRender() Called in CApp.cpp in OnExecute() function. contains conditions for displaying and positions for displaying all//
//SDL surfaces for the top down view of the park as well as the main GUI window that the game is run in						//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CApp.h"
using namespace std;
void CApp::OnRender() {
    if(Begin==true)
    {
		//for loops run through each grid square in top down view of park to determine what type of building should be displayed in each grid square
        for(int i=0;i<(Pmap.get_Ygridsize()*50);i+=50)
        {
            for(int j=0;j<(Pmap.get_Xgridsize()*50);j+=50)
            {
            	//unselected by user grass image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_grassB)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Grass, j, i, 0, 0, 50, 50);
                }
                //selected by user (highlighted) grass image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_grassY)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Grass, j, i, 0, 100, 50, 150);
                }
                //unselected by user path image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_pathB)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Path, j, i, 0, 0, 50, 50);
                }
                //selected by user (highlighted) path image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_pathY)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Path, j, i, 0, 100, 50, 150);
                }
                //unselected by user vendor image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_vendorB)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Vendor, j, i, 0, 0, 50, 50);
                }
                //selected by user (highlighted) vendor image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_vendorY)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Vendor, j, i, 0, 100, 50, 150);
                }
                //unselected by user ride image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_rideB)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Ride, j, i, 0, 0, 50, 50);
                }
                //selected by user (highlighted) ride image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_rideY)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Ride, j, i, 0, 100, 50, 150);
                }
                //unselected by user shop image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_shopB)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Shop, j, i, 0, 0, 50, 50);
                }
                //selected by user (highlighted) shop image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_shopY)
                {
                        CSurface::OnDraw(Surf_Display, Surf_Shop, j, i, 0, 100, 50, 150);
                }
                //unselected by user bathroom image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_bRoomB)
                {
                        CSurface::OnDraw(Surf_Display, Surf_BRoom, j, i, 0, 0, 50, 50);
                }
                //selected by user (highlighted) bathroom image
                if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_bRoomY)
                {
                        CSurface::OnDraw(Surf_Display, Surf_BRoom, j, i, 0, 100, 50, 150);
                }
                //menu for buying shops displayed at top left corner of screen (displays when grid square is selected by user)
                if(Pmap.get_menu()==1)
                {
                    CSurface::OnDraw(Surf_Display, Surf_Menu,0 ,0 , 0, 0, 130, 200);
                }
                //menu for buying shops displayed at top right corner of screen (displays when grid square is selected by user)
                if(Pmap.get_menu()==2)
                {
                   CSurface::OnDraw(Surf_Display, Surf_Menu,Pmap.get_Xgridsize()*50-130 ,0 , 0, 0, 130, 200);
                }
                //menu for buying shops and editing a roller coaster at top right corner of screen (displays when ride building is selected by user)
                if(Pmap.get_menu()==3)
                {
                   CSurface::OnDraw(Surf_Display, Surf_RMenu,0 ,0 , 0, 0, 130, 200);
                }
                //menu for buying shops and editing a roller coaster at top left corner of screen (displays when ride building is selected by user)
                if(Pmap.get_menu()==4)
                {
                   CSurface::OnDraw(Surf_Display, Surf_RMenu,Pmap.get_Xgridsize()*50-130 ,0 , 0, 0, 130, 200);
                }
                //main menu image displays when open main menu icon is clicked, displays finances, in game time and options to save and close game
                if(Pmap.get_menu()==5)
                {
                   CSurface::OnDraw(Surf_Display, Surf_MMenu,(((Pmap.get_Xgridsize()*50)/2)-355/2) ,(((Pmap.get_Ygridsize()*50)/2)-318/2) , 0, 0, 413, 368);
                }
                //always draw this: main GUI for game
                CSurface::OnDraw(Surf_Display, Surf_Gear,Pmap.get_Xgridsize()*50-25 ,0 , 0, 0, 25, 25);
            }
        }
    }
    else
    {
        CSurface::OnDraw(Surf_Display,Surf_Begin,0,0);
    }
	//move all active surfaces to GUI
    SDL_Flip(Surf_Display);
}
