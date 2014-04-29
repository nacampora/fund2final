/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Finances.h"
#include "Time.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;

SDL_Surface *image = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *parkEntranceFeeText = NULL;
SDL_Surface *currentLoanText = NULL;
SDL_Surface *balanceText = NULL;
SDL_Surface *dateText = NULL;
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
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

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Finances", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    image = load_image( "Finances.png" );
    background = load_image( "sky.JPG" );

    //Open the font
    font = TTF_OpenFont( "arial.ttf", 28 );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( image );
    SDL_FreeSurface( parkEntranceFeeText );
    SDL_FreeSurface( currentLoanText );
    SDL_FreeSurface( balanceText );
    SDL_FreeSurface( dateText );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    
    Finances F1;

    int parkEntranceFeeInt = F1.getParkEntranceFee();
    ostringstream convert1;
    convert1 << parkEntranceFeeInt;
    string str1 = convert1.str();
    const char * parkEntranceFee = str1.c_str();
       
    int currentLoanInt = F1.getCurrentLoan();
    ostringstream convert2;
    convert2 << currentLoanInt;
    string str2 = convert2.str();
    const char * currentLoan = str2.c_str();
   
    int balanceInt = F1.getBalance();
    ostringstream convert3;
    convert3 << balanceInt;
    string str3 = convert3.str();
    const char * balance = str3.c_str();
    
//    const char * parkEntranceFee="5";
//    const char * currentLoan="1000";
//    const char * balance="10000";

    Time T1;
    const char* date = T1.getDate();
    cout << date << endl;
    
    //Render the text
    dateText = TTF_RenderText_Solid( font, date , textColor );
    parkEntranceFeeText = TTF_RenderText_Solid( font, parkEntranceFee , textColor );
    currentLoanText = TTF_RenderText_Solid( font, currentLoan , textColor );
    balanceText = TTF_RenderText_Solid( font, balance , textColor );

    //If there was an error in rendering the text
    if( image == NULL )
    {
        return 1;
    }

    //Apply the surface to the screen
    apply_surface( 0, 0, background, screen );
    apply_surface( 0, 0, image, screen );
    apply_surface( 330, 85, parkEntranceFeeText, screen );
    apply_surface( 330, 145, currentLoanText, screen );
    apply_surface( 330, 205, balanceText, screen );
    apply_surface( 100, 400, dateText, screen );

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }



    //IF (USER CLICKS UP ON THE FINANCE BUTTON) {
    //    F1.increaseLoan();
    //} else if (USER CLICKS ON THE DOWN FINANCE BUTTON) {
    //    F1.decreaseLoan();
    //}

    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
    }

    //Free surfaces and font then quit SDL_ttf and SDL
    clean_up();

    return 0;
}
