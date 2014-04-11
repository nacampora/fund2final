#include "CApp.h"
using namespace std;
void CApp::OnRender() {
    for(int i=0;i<(Pmap.get_Ygridsize()*50);i+=50)
    {
        for(int j=0;j<(Pmap.get_Xgridsize()*50);j+=50)
        {
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_grassB)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Grass, j, i, 0, 0, 50, 50);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_grassY)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Grass, j, i, 0, 100, 50, 150);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_pathB)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Path, j, i, 0, 0, 50, 50);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_pathY)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Path, j, i, 0, 100, 50, 150);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_vendorB)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Vendor, j, i, 0, 0, 50, 50);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_vendorY)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Vendor, j, i, 0, 100, 50, 150);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_rideB)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Ride, j, i, 0, 0, 50, 50);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_rideY)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Ride, j, i, 0, 100, 50, 150);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_shopB)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Shop, j, i, 0, 0, 50, 50);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_shopY)
            {
                    CSurface::OnDraw(Surf_Display, Surf_Shop, j, i, 0, 100, 50, 150);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_bRoomB)
            {
                    CSurface::OnDraw(Surf_Display, Surf_BRoom, j, i, 0, 0, 50, 50);
            }
            if(Pmap.grid[i/50][j/50].get_property()==Pmap.grid[i/50][j/50].enum_bRoomY)
            {
                    CSurface::OnDraw(Surf_Display, Surf_BRoom, j, i, 0, 100, 50, 150);
            }
            if(Pmap.get_menu()==1)
            {
                CSurface::OnDraw(Surf_Display, Surf_Menu,0 ,0 , 0, 0, 130, 200);
            }
            if(Pmap.get_menu()==2)
            {
               CSurface::OnDraw(Surf_Display, Surf_Menu,Pmap.get_Xgridsize()*50-130 ,0 , 0, 0, 130, 200);
            }

        }
    }

    SDL_Flip(Surf_Display);
}
