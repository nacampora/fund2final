////////////////////////////////////////////////////////
// OnLoop() called in CApp.cpp in OnExecute() function//
// is used to keep track of in game time  			  //
////////////////////////////////////////////////////////
#include "CApp.h"
#include <ctime>
#include "Time.h"


void CApp::OnLoop() {
		//compares the current time to initial time, if not equal, increments the in game hour (so that one second is equivalent to one in game hour)
	    if (current_time!=time(0)) {
			Pmap.T1.incrementHour();
			current_time = time(0);
		}
		
//following code not currently used in current game state:

	/*SDL_Color textColor = { 0, 0, 0 };
	TTF_Font *font = NULL;
	font = TTF_OpenFont( "arial.ttf", 28 );
	const char* date = Pmap.T1.getDate();
	dateText = TTF_RenderText_Solid( font, date , textColor );
	apply_surface( 100, 10, dateText, Surf_MMenu );*/
}
