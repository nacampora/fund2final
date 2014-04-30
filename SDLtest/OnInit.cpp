#include "CApp.h"

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    /*if((screen = SDL_SetVideoMode( 1300, 650, 32, SDL_SWSURFACE ))==NULL);
    {
        return false;
    }*/

    if((Surf_Display = SDL_SetVideoMode((Pmap.get_Xgridsize()*50), (Pmap.get_Ygridsize()*50), 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    if((Surf_Grass = CSurface::OnLoad("grass_img.png")) == NULL) {
        return false;
    }
    if((Surf_Ride = CSurface::OnLoad("ride_img.png")) == NULL) {
        return false;
    }
    if((Surf_Vendor = CSurface::OnLoad("vendor_img.png")) == NULL) {
        return false;
    }
    if((Surf_BRoom = CSurface::OnLoad("bRoom_img.png")) == NULL) {
        return false;
    }
    if((Surf_Shop = CSurface::OnLoad("shop_img.png")) == NULL) {
        return false;
    }
    if((Surf_Path = CSurface::OnLoad("path_img.png")) == NULL) {
        return false;
    }
    if((Surf_Menu = CSurface::OnLoad("menu_img.gif")) == NULL){
        return false;
    }
    if((Surf_RMenu = CSurface::OnLoad("rmenu_img.gif")) == NULL){
        return false;
    }
    if((Surf_MMenu = CSurface::OnLoad("mainmenua_img.gif")) == NULL){
        return false;
    }
    if((Surf_Gear = CSurface::OnLoad("gear_img.png")) == NULL){
        return false;
    }
    if((Surf_Begin = CSurface::OnLoad("loadscreen_img.png")) == NULL){
        return false;
    }
    if( init() == false )
    {
        return 1;
    }

    return true;
}
