///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Nicholas Acampora:
//The following functions are declared in the CApp.h file, which is the top level class of the program. There are functions to
//control the basic operations of the game:
//functions for initializing all sdl surfaces, looping the game while running, updating based on each loop of game, updating gui
//on each loop of game, removing all data from memory, closing game.
//main function is also included in this .cpp file.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<ctime>
#include "CApp.h"
//constructor initializes all SDL surfaces to the null pointer. they are later assigned files in the function OnInit()
CApp::CApp() {
    screen = NULL;
    Surf_Display = NULL;					//gui window
    Surf_Grass = NULL;						//grass tiles for top down park view
    Surf_Path = NULL;						//path tiles for top down park view
    Surf_Ride = NULL;						//tiles for ride building in top down park view
    Surf_Shop = NULL;						//tiles for shop building in top down park view
    Surf_BRoom = NULL;						//tiles for bathroom building in top down park view
    Surf_Vendor = NULL;						//tiles for food vendor building in top down park view
    Surf_Menu = NULL;						//menu display that appears when tile is selected in top down view
    Surf_RMenu = NULL;						//menu display that appears when a rollercoaster tyle is selected in top down display
    Surf_MMenu = NULL;						//menu displays when main menu icon is pressed
    Surf_Gear = NULL;						//icon to press to display main menu
    Surf_Begin = NULL;						//load and new game opening screen of game
    MenuPNG=IMG_Load("mainmenua_img.gif");	//loads main menu surface for use in updating display of finances in top down view of the roller Coaster park
   //the following initialize text surfaces for use in displaying the users finances and the date  on the main menu in the top down view of the park
    parkEntranceFeeText = NULL;
    currentLoanText = NULL;
    balanceText = NULL;
    dateText = NULL;
    font = NULL;							//initializes the font to be used in displaying text surfaces
	current_time= time(0);					//initializes the time used in the park (displayed on the main menu) to 0
    Running = true;							//initializes game to running
    Begin = false;							//initializes game to start on Surf_Begin
}

//called from main() controls all main operations of game. allows game to begin and loops through updates based on input and
//number of times through loop. cleans up data from memory when game ends and closes program when game is ended.
int CApp::OnExecute() {
    if(OnInit() == false) {//returns true if all sdl surfaces initialize properly and false if not, causing game to end
        return -1;
    }

    SDL_Event Event;//declares variable that holds input from user

	SDL_WM_SetCaption( "RollerCoaster Tycoon", NULL );
    
        
//while loop loops while running variable is set to true. is set to true in constructor and false when user presses
//red exit button on GUI
    while(Running) {
        while(SDL_PollEvent(&Event)) {	//loops and checks for user input and asssigns it to variable event
            OnEvent(&Event);			//when user input occurs, game changes based on user input in this function
        }

		OnRender();						//updates GUI graphics each loop
        OnLoop();						//updates game based on number of times through loop
    }

    OnCleanup();						//cleans memory to prevent memory leaks when game ends

    return 0;							//ends program
}

//main function initializes a variable of class CApp and starts game
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();			//calls function to begin game and loop until game is finished
}

//the follwing function is used for loading the text surfaces into the game to be displayed on the main menu in the top down view of the park
//the function returns the loaded surface
SDL_Surface* CApp:: load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}


//the following function is used to initialize the text surfaces for display on the main menu in the top down view of the park
//the function returns true if the surface is properly initialized and false if not
bool CApp::init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    //screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    /*if( screen == NULL )
    {
        return false;
    }*/

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    //SDL_WM_SetCaption( "Finances", NULL );

    //If everything initialized fine
    return true;
}

bool CApp::load_files()
{

    //Open the font
    font = TTF_OpenFont( "arial.ttf", 28 );

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}
