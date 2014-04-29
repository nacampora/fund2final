///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nicholas Acampora:
//The following functions are declared in the CApp.h file, which is the top level class of the program. There are functions to
//control the basic operations of the game:
//functions for initializing all sdl surfaces, looping the game while running, updating based on each loop of game, updating gui
//on each loop of game, removing all data from memory, closing game.
//main function is also included in this .cpp file.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "CApp.h"
//constructor initializes all SDL surfaces to the null pointer. they are later assigned files in the function OnInit()
CApp::CApp() {
    screen = NULL;
    Surf_Display = NULL;//gui window
    Surf_Grass = NULL;//grass tiles for top down park view
    Surf_Path = NULL;//path tiles for top down park view
    Surf_Ride = NULL;//tiles for ride building in top down park view
    Surf_Shop = NULL;//tiles for shop building in top down park view
    Surf_BRoom = NULL;//tiles for bathroom building in top down park view
    Surf_Vendor = NULL;//tiles for food vendor building in top down park view
    Surf_Menu = NULL;//menu display that appears when tile is selected in top down view
    Surf_RMenu = NULL;//menu display that appears when a rollercoaster tyle is selected in top down display
    Surf_MMenu = NULL;//menu displays when main menu icon is pressed
    Surf_Gear = NULL;//icon to press to display main menu
    Surf_Begin = NULL;//load and new game opening screen of game

    Running = true;//initializes game to running
    Begin = false;//initializes game to start on Surf_Begin
}

//called from main() controls all main operations of game. allows game to begin and loops through updates based on input and
//number of times through loop. cleans up data from memory when game ends and closes program when game is ended.
int CApp::OnExecute() {
    if(OnInit() == false) {//returns true if all sdl surfaces initialize properly and false if not, causing game to end
        return -1;
    }

    SDL_Event Event;//declares variable that holds input from user

//while loop loops while running variable is set to true. is set to true in constructor and false when user presses
//red exit button on GUI
    while(Running) {
        while(SDL_PollEvent(&Event)) {//loops and checks for user input and asssigns it to variable event
            OnEvent(&Event);//when user input occurs, game changes based on user input in this function
        }
        if(Begin==false)
        {

        }
        OnLoop();//updates game based on number of times through loop
        OnRender();//updates GUI graphics each loop
    }

    OnCleanup();//cleans memory to prevent memory leaks when game ends

    return 0;//ends program
}

//main function initializes a variable of class CApp and starts game
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();//calls function to begin game and loop until game is finished
}
