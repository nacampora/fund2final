#include "CApp.h"

void CApp::OnCleanup() {
    SDL_FreeSurface(Surf_Grass);
    SDL_FreeSurface(Surf_Path);
    SDL_FreeSurface(Surf_BRoom);
    SDL_FreeSurface(Surf_Vendor);
    SDL_FreeSurface(Surf_Ride);
    SDL_FreeSurface(Surf_Shop);
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}
