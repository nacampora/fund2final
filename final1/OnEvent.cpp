//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//OnEvent() Function called in CApp.cpp in OnExecute() function. This function contains functions for making in game decisions based on 	//
//the users input, based mainly on mouse clicks for the top down view of the park. function mainmenu() performs actions for when the main 	//
//menu is open, allowing users to adjust their finances (by accessing the Finance class: Finance.h), saving the game (which writes to a file//
//and exiting the game. The buymenu() function performs actions when one of the buy building menus is open, allowing the user to buy 		//
//different types of buildings by accessing the Building class( building.h) and changing its property variable. the coastermenu() function 	//
//allows the user to enter the roller coaster building screen by accessing the RollerCoaster class (RollerCoaster.h). The prep_finances		//
//function readies the text surfaces that are displayed on top of the main menu when it is open and controlls the updating of the text while//
//user input is recieved in the main menu. All of these functions are called within the OnLButtonDown() function which is accessed from 	//
//the function OnEvent based on the recognition that the left mouse key was clicked by pre-defined SDL functions and libraries. All in-game //
//decisions are based off of the x and y coordinates of the mouse click.																	//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CApp.h"
#include<math.h>
#include<fstream>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

//accessed from CApp.cpp in OnExecute() function
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);//
}

//sets "game running" variable to false to initialize the end game process. this causes the program to exit the while loop in OnExecute() in CApp.cpp
void CApp::OnExit() {
    Running = false;
}

// changes game based on mouse clicks while main menu is open, allowing the user to adjust their finances, save game, and exit game, called from
//OnLButtonDown()
void CApp::mainmenu(int mX,int mY)						//inputs x and y coordinate of mouse click
{
    int x=((Pmap.get_Xgridsize()*50)/2)-(355/2);		//finds the x center of the GUI and assigns to the variable x
    int y=(((Pmap.get_Ygridsize()*50)/2)-318/2);		//finds the y center of the GUI and assigns to the variable y
    //if press red x button at top right of menu
    if((mX>x+320)&&mX<(x+345)&&mY>(y+10)&&mY<(y+34))	//if location of the close main menu button in relation to center of GUI is clicked by user
    {

        
    	//run through grid checking if any squares are higlighted
        for(int i=0;i<Pmap.get_Ygridsize();i++)
        {
            for(int j=0;j<Pmap.get_Xgridsize();j++)
            {
                if(Pmap.grid[i][j].get_property()%2==1)				//if square is highlighted (selected by user click)
                {
                    if(i*50>150||j*50>200)							//if highlighted square not in upper left corner
                    {
                        Pmap.set_menu(1);							//close main menu and reopen previously opened buy menu(in upper left corner)
                    }
                    else											//if highlihgted (selected by user click) square is in upper left corner
                    {
                        Pmap.set_menu(2);							//close main menu and reopen previously opened buy menu (on upper right corner)
                    }
                }
            }
        }
        if(Pmap.get_menu()==5)								//if the main menu is still open after checking for old menus to re-open
        {
            Pmap.set_menu(0);								//close main menu
        }
    }//end of if(clicked on close menu button)
    
    //if user clicks on button to increase park entrance fee in main menu
    else if(mX>x+313&&mX<x+340&&mY>y+53&&mY<y+68)		//location of increase park entrance fee button
    {
        Pmap.F1.increaseEntranceFee();					//calls function in Finance class
        prep_finances();								//updates text surfaces displayed in main menu
    }
    //if user clicks on button to decrease park entrace fee in main menu
    else if(mX>x+313&&mX<x+340&&mY>y+74&&mY<y+91)		//location of decrease park entrace fee button
    {
        Pmap.F1.decreaseEntranceFee();					//calls function in Finance class
        prep_finances();								//updates text surfaces displayed in main menu
    }
    //if user clicks on button to increase their loan in main menu
    else if(mX>x+313&&mX<x+340&&mY>y+95&&mY<y+111)		//location of increase loan button
    {
        Pmap.F1.increaseLoan();							//calls function in Finance class
        prep_finances();								//updates text surfaces displayed in main menu
    }
    //if user clicks on button to decrease their loan in main menu
    else if(mX>x+313&&mX<x+340&&mY>y+117&&mY<y+132)		//location of decrease loan button
    {
        Pmap.F1.decreaseLoan();							//calls function in Finance class
        prep_finances();								//updates text surfaces displayed in main menu
    }
    //if user clicks on button to save game state
    else if(mX>x&&mX<x+106&&mY>y+213&&mY<y+316)			//location of save button
    {
        ofstream file("saved_game.txt");				//open save file for writing to
        if(file.is_open())								//if file is successfully opened
        {
        	//run through 2D vector of Park to identify types of buildings and locations in park
            for(int i=0;i<Pmap.get_Ygridsize();i++)
            {
                for(int j=0;j<Pmap.get_Xgridsize();j++)
                {
                    //if any squares on the board are highlighted at save, save as unhighlighted version
                    if(Pmap.grid[i][j].get_property()%2==1)
                    {
                        file << (Pmap.grid[i][j].get_property()-1);		//write to file the building type
                        file << " ";
                    }
                    //otherwise save the square as is
                    else				
                    {
                        file << Pmap.grid[i][j].get_property();			//write to file the building type
                        file << " ";
                    }
                }
                file << "\n";
            }
            //following code saves the in game time as well as the different finance values of current game to file
            file << Pmap.T1.hour;
            file << " ";
            file << Pmap.T1.day;
            file << " ";
            file << Pmap.T1.month;
            file << " ";
            file << Pmap.T1.year;
            file << " ";
            file << Pmap.F1.getBalance();
            file << " ";
            file << Pmap.F1.getParkEntranceFee();
            file << " ";
            file << Pmap.F1.getCurrentLoan();
            
            file.close();												//close file
        }
    }
    //if user clicks end game button in main menu
    else if(mX>x+139&&mX<x+242&&mY>y+213&&mY<y+316)						//location of end game button
    {
        Running = false;												//set "game running" variable to false
    }
}

//function called in OnLButtonDown() when the buy menus are open, allowing users to buy different types of property based on the location of the 
//grid square they have selected. this is identified by finding which grid square is currently "highlighted" and determining which property to change
//it to based on the x and y location of the users click
int CApp::buymenu(int mX,int mY)
{
	//variables for saving which square is currently selected "highlighted" by user
    int xSquare=0;
    int ySquare=0;
    //runs through 2D vector of buildings 
    for(int i=0;i<Pmap.get_Ygridsize();i++)
    {
        for(int j=0;j<Pmap.get_Xgridsize();j++)
        {
        	//if a grid square is selected, when modded with two, it will equal one based on the enum values in the Building class which represent
        	//which type of building a particular square is
            if(Pmap.grid[i][j].get_property()%2==1)
            {
            	//saves the location of the selected grid square
                 xSquare=j;
                 ySquare=i;
            }
        }
    }
    //if the buy menu on the left side of the screen is open
    if(Pmap.get_menu()==1||Pmap.get_menu()==3)
    {
    	//if user clicks on the bathroom button
        if(mX>0&&mX<37&&mY>0&&mY<37)		//location of buy bathroom button
        {
            Pmap.F1.buyShop();				//calls function in Finance class
            // changes the type of building the selected square is to a bathroom building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_bRoomY);	
            Pmap.set_menu(1);				//keeps the buy menu open
            return 1;
        }
        //if the user clicks on the buy ride button
        else if(mX>0&&mX<37&&mY>39&&mY<75)	//location of buy ride button
        {
            Pmap.F1.buyShop();				//calls function in Finance class
            // changes the type of building the selected square is to a ride building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_rideY);
            Pmap.set_menu(3);				//keeps the buy menu open
            return 1;
        }
        //if the user clicks on the buy vendor button
        else if(mX>0&&mX<37&&mY>79&&mY<114)	//location of buy vendor button
        {
            Pmap.F1.buyShop();				//calls function in Finance class
            // changes the type of building the selected square is to a vendor building			
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_vendorY);
            Pmap.set_menu(1);				//keeps the buy menu open
            return 1;
        }
        //if the user clicks on the sell building button
        else if(mX>42&&mX<77&&mY>0&&mY<37)	//location of sell building button
        {
            Pmap.F1.sellShop();				//calls function in Finance class
            // changes the type of building the selected square is to a grass building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_grassY);
            Pmap.set_menu(1);				//keeps the buy menu open
            return 1;
        }
        //if the user clicks on the buy path button
        else if(mX>42&&mX<77&&mY>39&&mY<75)	//location of buy path button
        {
            Pmap.F1.buyShop();				//calls function in Finance class
            // changes the type of building the selected square is to a path building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_pathY);
            Pmap.set_menu(1);				//keeps the buy menu open
            return 1;
        }
        //if the user clicks on the buy shop button
        else if(mX>42&&mX<77&&mY>79&&mY<114)	//location of buy shop button
        {
            Pmap.F1.buyShop();				//calls function in Finance class
            // changes the type of building the selected square is to a path building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_shopY);
            Pmap.set_menu(1);				//keeps the buy menu open
            return 1;
        }
    }//end of if (menu on left open)
    
    else//if buy building menu on right open
    {
    	//if user clicks on the buy bathroom button
        if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+37&&mY>0&&mY<37)		//location of buy bathroom button
        {
            Pmap.F1.buyShop();																	//calls function in Finance class
            // changes the type of building the selected square is to a bathroom building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_bRoomY);
            Pmap.set_menu(2);																	//keeps the buy menu open
            return 1;
        }
        //if user clicks on the buy ride button
        else if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+37&&mY>39&&mY<75)//location of buy bathroom button
        {
            Pmap.F1.buyShop();																	//calls function in Finance class
            // changes the type of building the selected square is to a ride building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_rideY);
            Pmap.set_menu(4);																	//keeps the buy menu open
            return 1;
        }
        //if user clicks on the buy vendor button
        else if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+37&&mY>79&&mY<114)//location of buy bathroom button
        {
            Pmap.F1.buyShop();																	//calls function in Finance class
            // changes the type of building the selected square is to a vendor building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_vendorY);
            Pmap.set_menu(2);																	//keeps the buy menu open
            return 1;
        }
        //if user clicks on the sell building button
        else if(mX>Pmap.get_Xgridsize()*50-130+42&&mX<Pmap.get_Xgridsize()*50-130+77&&mY>0&&mY<37)//location of sell building button
        {
            Pmap.F1.sellShop();																	//calls function in Finance class
            // changes the type of building the selected square is to a grass building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_grassY);
            Pmap.set_menu(2);																	//keeps the buy menu open
            return 1;
        }
        //if user clicks on the buy path button
        else if(mX>Pmap.get_Xgridsize()*50-130+42&&mX<Pmap.get_Xgridsize()*50-130+77&&mY>39&&mY<75)//location of buy path button
        {
            Pmap.F1.buyShop();																	//calls function in Finance class
            // changes the type of building the selected square is to a path building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_pathY);
            Pmap.set_menu(2);																	//keeps the buy menu open
            return 1;
        }
        //if user clicks on the buy shop button
        else if(mX>Pmap.get_Xgridsize()*50-130+42&&mX<Pmap.get_Xgridsize()*50-130+77&&mY>79&&mY<114)//location of buy shop button
        {
            Pmap.F1.buyShop();																	//calls function in Finance class
            // changes the type of building the selected square is to a shop building
            Pmap.grid[ySquare][xSquare].set_property(Pmap.grid[ySquare][xSquare].enum_shopY);
            Pmap.set_menu(2);																	//keeps the buy menu open
            return 1;
        }
    }//end of if (menu on right open)
    return 0;
}

//if selected grid square is a ride building
void CApp::coastermenu(int mX,int mY)
{
    int xSquare=0;
    int ySquare=0;
    //determines which grid square is selected
    for(int i=0;i<Pmap.get_Ygridsize();i++)
    {
        for(int j=0;j<Pmap.get_Xgridsize();j++)
        {
            if(Pmap.grid[i][j].get_property()%2==1)
            {
            	//location of selected grid square in 2D array of buildings
                 xSquare=j;
                 ySquare=i;
            }
        }
    }
    //if ride and buy shop menu is open on left side of screen
    if(Pmap.get_menu()==3)
    {
    	//if user clicks on build roller coaster button
       if(mX>0&&mX<76&&mY>119&&mY<140)//location of build roller coaster button
        {
        	//calls function in RollerCoaster class (RollerCoaster.h) to display roller coaster editing screen and functionality
            Pmap.grid[ySquare][xSquare].R1.displayInterface(xSquare,ySquare);
        }
    }
    //if ride and buy shop menu is open on right side of screen
    if(Pmap.get_menu()==4)
    {
    	//if user clicks on build roller coaster button
        if(mX>Pmap.get_Xgridsize()*50-130&&mX<Pmap.get_Xgridsize()*50-130+76&&mY>119&&mY<140)//location of build roller coaster button
        {
        	//calls function in RollerCoaster class (RollerCoaster.h) to display roller coaster editing screen and functionality
            Pmap.grid[ySquare][xSquare].R1.displayInterface(xSquare,ySquare);
        }
    }


}

// function is used to add text surfaces on top of main menu when it is open
void CApp::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

//function is called when user input is the left mouse button, is used to determine action taken in game based on x and y coordinates of click
void CApp::OnLButtonDown(int mX, int mY) {
    if(Begin==false)//if in start screen
    {
        int num=0;
        if(mX>921&&mX<1254&&mY>508&&mY<620)						//if user presses "load" button
        {
            ifstream myfile ("saved_game.txt");					//opens save file for input
            if (myfile.is_open())								//if save file is open
            {
            	//run through the data representing the types of buildings in the park
                for(int i=0;i<Pmap.get_Ygridsize();i++)
                {
                    for(int j=0; j<Pmap.get_Xgridsize();j++)
                    {
                        myfile >> num;							//read data from save file into temporary variable
                        Pmap.grid[i][j].set_property(num);		//reading one character from file to array to re-build saved park
                    }
                }
                //following code re-loads the values of in game time and user money from save file
                myfile >> num;
                Pmap.T1.hour = num;
                myfile >> num;
                Pmap.T1.day = num;
                myfile >> num;
                Pmap.T1.month = num;
                myfile >> num;
                Pmap.T1.year = num;
                myfile >> num;
                Pmap.F1.setBalance(num);
                myfile >> num;
                Pmap.F1.setParkEntranceFee(num);
                myfile >> num;
                Pmap.F1.setCurrentLoan(num);
                myfile.close();									//close save file
                
                //runs through each grid square in 2D array of buildings
		        for(int k=0;k<Pmap.get_Ygridsize();k++)
		        {
		            for(int l=0;l<Pmap.get_Xgridsize();l++)
		            {
		                Pmap.grid[k][l].R1.load(l,k);			//loads any previously built rollercoasters to that square
		            }
		        }
		            Begin=true;

            }
            
            else												//if file not successfully opened
            {
                return;
            }
        }
        if(mX>921&&mX<1254&&mY>358&&mY<472)						//if user presses "new game" button
        {
        	//run through each grid square in 2D array of buildings
        	for(int i=0; i<Pmap.get_Ygridsize();i++)
        	{
        		for(int j=0; j<Pmap.get_Xgridsize();j++)
        		{
        			//following code concatonates a string that represents the file name of the saved roller coaster files and then deletes those files
        			string s = "Coasters/RollerCoaster";
					ostringstream convert;
					convert << j;
					string stringxCo = convert.str();
					ostringstream convert1;
					convert1 << i;
					string stringyCo = convert1.str();
					string txt = ".txt";
					s=s+stringxCo+stringyCo+txt;
					const char *fileName=s.c_str();
					remove(fileName);							//deletes saved roller coaster file
				}
			}
           Begin=true;
        }
    }//end of if (Begin==false)

    else//else in the top down view of park
    {
        int clicked=0;//if the user clicked on a menu item
        int xSquare=floor(mX/50)*50;//determines an integer number that coorisponds with a x value in the 2D grid vector of vectors
        int ySquare=floor(mY/50)*50;//determines an integer number that coorisponds with a Y value in the 2D grid vector of vectors
        if(Pmap.get_menu()==5)//if the main menu is already open
        {
            //determine what actions to take depending on where user has clicked
            mainmenu(mX,mY);
        }

        else if(((mX>((Pmap.get_Xgridsize()*50)-25))&&mY<25)&&Pmap.get_menu()!=5)//if clicked on open main menu icon (top right corner of screen)
        //if main menu is not open
        {
        	Pmap.set_menu(5);								//open main menu
			prep_finances();								//prepares and displays the finances and in game time to the main menu
            //apply_surface( 100, 400, dateText, Surf_Display );
        }
        else if(Pmap.get_menu()!=5)							//as long as main menu isnt open, allow clicking on other parts of screen
        {
            if(Pmap.get_menu()==3||Pmap.get_menu()==4)
            {
                coastermenu(mX,mY);							//determine if user clicked the edit coaster button
            }

            if(Pmap.get_menu()>0&&Pmap.get_menu()<5)		//if the highlighted square menu is open
            {
                clicked=buymenu(mX,mY);						//determine what action to take based on where user clicks
            }

            if(clicked!=1)									// if user did not click on a menu item
            {
                for(int i=0;i<Pmap.get_Ygridsize();i++)
                {
                    for(int j=0;j<Pmap.get_Xgridsize();j++)
                    {
                        if((i!=ySquare/50)||(j!=xSquare/50))//if not same square as clicked
                        {
                            if(Pmap.grid[i][j].get_property()%2==1)//if square is highlighted
                            {
                                Pmap.grid[i][j].set_property(Pmap.grid[i][j].get_property()-1);//set to unhighlighted
                            }
                        }
                    }
                }
                if(Pmap.grid[ySquare/50][xSquare/50].get_property()%2==0)//if square is unhighlighted when clicked
                {
                    //specialized menu for ride
                    if(Pmap.grid[ySquare/50][xSquare/50].get_property()==Pmap.grid[0][0].enum_rideB)
                    {
                        Pmap.grid[ySquare/50][xSquare/50].set_property(Pmap.grid[ySquare/50][xSquare/50].get_property()+1);
                        //set menu at upper left corner unless clicked in that area then upper right corner
                        if(xSquare>130||ySquare>200)
                        {
                            Pmap.set_menu(3);
                        }
                        else
                        {
                            Pmap.set_menu(4);
                        }
                    }
                    else//if not a rollercoaster square that was selected
                    {
                        //change square to highlighted version
                        Pmap.grid[ySquare/50][xSquare/50].set_property(Pmap.grid[ySquare/50][xSquare/50].get_property()+1);
                        //set menu at upper left corner unless clicked in that area then upper right corner
                        if(xSquare>130||ySquare>200)
                        {
                            Pmap.set_menu(1);
                        }
                        else
                        {
                            Pmap.set_menu(2);
                        }
                    }


                }//end of if square is unhighlighted when clicked
                
                else if(Pmap.grid[ySquare/50][xSquare/50].get_property()%2==1)//if square is highlighted when clicked
                {
                    //unhighlight square and close menu
                    Pmap.grid[ySquare/50][xSquare/50].set_property(Pmap.grid[ySquare/50][xSquare/50].get_property()-1);
                    Pmap.set_menu(0);
                }
            }
        }//end of else main menu isnt open
        
    }//end of else referring to being in top down view of park
    
}//end of OnLButtonDown function

//function displays the in game time and finances to the main menu when it is open
void CApp::prep_finances()
{
				//frees previous text surfaces
				SDL_FreeSurface( parkEntranceFeeText );
				SDL_FreeSurface( currentLoanText );
				SDL_FreeSurface( balanceText );
	            SDL_Color textColor;									//determines text color
				TTF_Font *font = NULL;									//initializes first font
				TTF_Font *font2 = NULL;									//initializes second font
				font = TTF_OpenFont( "arial.ttf", 28 );					//loads first font
				font2 = TTF_OpenFont( "arial.ttf", 16 );				//loads second font
				int parkEntranceFeeInt = Pmap.F1.getParkEntranceFee();	//assigns value from Finances class
				ostringstream convert1;									//intializes variable for converted value
				convert1 << parkEntranceFeeInt;							//converts value from Finance class
				string str1 = convert1.str();							//converts value from Finance class			
				const char * parkEntranceFee = str1.c_str();			//converts value from Finance class

				int currentLoanInt = Pmap.F1.getCurrentLoan();			//assigns value from Finances class
				ostringstream convert2;									//intializes variable for converted value
				convert2 << currentLoanInt;								//converts value from Finance class
				string str2 = convert2.str();							//converts value from Finance class	
				const char * currentLoan = str2.c_str();				//converts value from Finance class

				int balanceInt = Pmap.F1.getBalance();					//assigns value from Finances class
				ostringstream convert3;									//intializes variable for converted value
				convert3 << balanceInt;									//converts value from Finance class
				string str3 = convert3.str();							//converts value from Finance class	
				const char * balance = str3.c_str();					//converts value from Finance class	
				const char* date = Pmap.T1.getDate();					//assigns value from Time class
				
				

				//Render the text
				textColor = {255, 255, 255};
				dateText = TTF_RenderText_Solid( font2, date , textColor );
				textColor = {0, 0, 0};
				parkEntranceFeeText = TTF_RenderText_Solid( font, parkEntranceFee , textColor );
				currentLoanText = TTF_RenderText_Solid( font, currentLoan , textColor );
				balanceText = TTF_RenderText_Solid( font, balance , textColor );

            //refresh main menu and apply new text surfaces to main menu 
            SDL_BlitSurface(MenuPNG,NULL,Surf_MMenu,NULL);
            apply_surface( 222, 57, parkEntranceFeeText, Surf_MMenu );
            apply_surface( 222, 100, currentLoanText, Surf_MMenu );
            apply_surface( 222, 141, balanceText,Surf_MMenu);
            apply_surface( 138, 15, dateText, Surf_MMenu );
}
