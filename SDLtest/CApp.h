////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nicholas Acampora:
//This class is the top level of the roller coaster tycoon game. It has functions to control the basic operations of the game.
//functions for initializing all sdl surfaces, looping the game while running, updating based on each loop of game, updating gui
//on each loop of game, removing all data from memory, closing game.
//contains Park class which contains function and classes for the operation of the top down view of the park
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _CAPP_H_
    #define _CAPP_H_

#include "SDL/SDL.h"

#include "CEvent.h"
#include "CSurface.h"

#include "hfiles/Park.h"

class CApp : public CEvent {
    private:
        bool            Running;// true or false based on whether or not the game is running correctly. when false, the program
        //cleans up all memory and ends


//the following SDL surfaces are pointers to all of the images displayed in the GUI. files are assigned to the images in
//OnInit.cpp
        SDL_Surface*    Surf_Display;//gui window
        SDL_Surface*    Surf_Grass;//grass tiles for top down park view
        SDL_Surface*    Surf_Path;//path tiles for top down park view
        SDL_Surface*    Surf_Ride;//tiles for ride building in top down park view
        SDL_Surface*    Surf_Shop;//tiles for shop building in top down park view
        SDL_Surface*    Surf_BRoom;//tiles for bathroom building in top down park view
        SDL_Surface*    Surf_Vendor;//tiles for food vendor building in top down park view
        SDL_Surface*    Surf_Menu;//menu display that appears when tile is selected in top down view
    public:
        CApp();//constructor initializes all SDL surfaces and the "bool running" variable

        int OnExecute();//contains while loop which contains functions for all main parts of game

    public:
        Park Pmap;//second level class that conatins variables and functions that control the top down view of the park

        bool OnInit();//function that assigns files to all SDL surfaces. returns true if all surfaces initialize, false if one
        //or more surfaces do not initialize (usually because file can't be found)

        void OnEvent(SDL_Event* Event);//function that controls actions when user provides input
            void OnLButtonDown(int, int);//on left click of mouse, controls game response based on location of mouse on screen
            void OnKeyDown(SDLKey, SDLMod, Uint16);//when keyboard input is provided, controls game response based on key pressed
            void OnExit();//when red x button is pressed, removes sdl spaces from memory and exits

        void OnLoop();//updates state of game each iteration of controlling while loop in function OnExecute

        void OnRender();//implements changes to game gui window

        void OnCleanup();//deletes all data in memory space before program ens to prevent memory leaks
};

#endif
