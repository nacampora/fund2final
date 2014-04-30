#include "CApp.h"

void CApp::OnCleanup() {
    SDL_FreeSurface(Surf_Grass);
    SDL_FreeSurface(Surf_Path);
    SDL_FreeSurface(Surf_BRoom);
    SDL_FreeSurface(Surf_Vendor);
    SDL_FreeSurface(Surf_Ride);
    SDL_FreeSurface(Surf_Shop);
    SDL_FreeSurface(Surf_Menu);
    SDL_FreeSurface(Surf_MMenu);
    SDL_FreeSurface(Surf_RMenu);
    SDL_FreeSurface(Surf_Gear);
    SDL_FreeSurface(Surf_Begin);
    SDL_FreeSurface( parkEntranceFeeText );
    SDL_FreeSurface( currentLoanText );
    SDL_FreeSurface( balanceText );
    SDL_FreeSurface( dateText );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();
    SDL_Quit();
}
