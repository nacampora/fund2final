/////////////////////////////////////////////////////////////////////////////////////////////////////
//function OnInit() called in CApp.cpp and initializes all surfaces to be used in top down view of //
//park. function returns false if any of the surfaces do not find the file they refer to which 	   //
//then prevents the game from running.															   //
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CApp.h"

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
	//surface for main GUI of top down view of park
    if((Surf_Display = SDL_SetVideoMode((Pmap.get_Xgridsize()*50), (Pmap.get_Ygridsize()*50), 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
	//loads image of grass tile
    if((Surf_Grass = CSurface::OnLoad("grass_img.png")) == NULL) {
        return false;
    }
    //loads image of ride building
    if((Surf_Ride = CSurface::OnLoad(Pmap.grid[0][0].rBuild.get_img())) == NULL) {
        return false;
    }
    //loads image of vendor building
    if((Surf_Vendor = CSurface::OnLoad(Pmap.grid[0][0].vBuild.get_img())) == NULL) {
        return false;
    }
    //loads image of bRoom building
    if((Surf_BRoom = CSurface::OnLoad(Pmap.grid[0][0].bBuild.get_img())) == NULL) {
        return false;
    }
    //loads image of shop building
    if((Surf_Shop = CSurface::OnLoad(Pmap.grid[0][0].sBuild.get_img())) == NULL) {
        return false;
    }
    //loads image of path tile
    if((Surf_Path = CSurface::OnLoad("path_img.png")) == NULL) {
        return false;
    }
    //loads image of menu for buying properties
    if((Surf_Menu = CSurface::OnLoad("menu_img.gif")) == NULL){
        return false;
    }
    //loads image of menu for buying properties and entering roller coaster building aspect of game
    if((Surf_RMenu = CSurface::OnLoad("rmenu_img.gif")) == NULL){
        return false;
    }
    //loads image of main menu which displays finances, in game time, and allows for saving and exiting game
    if((Surf_MMenu = CSurface::OnLoad("mainmenua_img.gif")) == NULL){
        return false;
    }
    //loads image of icon for opening main menu
    if((Surf_Gear = CSurface::OnLoad("gear_img.png")) == NULL){
        return false;
    }
    //loads image of opening screen of game with load and new game options
    if((Surf_Begin = CSurface::OnLoad("loadscreen_img.png")) == NULL){
        return false;
    }
    
    //if any of the surfaces do not initialize properly
    if( init() == false )
    {
        return 1;
    }
	// if all surfaces initialize properly
    return true;
}
