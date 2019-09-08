#define PDC_DLL_BUILD 1
#define WINCOLORS 1
#define PROMPTCOLORS 2
#define ESCAPE 27
#define WINDOWTEXT 3


#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include <iostream>
#include <fstream>

using namespace std;


////////////////////////////////          Function Prototypes            ///////////////////////////////////////////////
void quitPrompt(void);
bool confirm(void);
void saveFile(void);
bool savePrompt(void);
void setupWindow(void);
void inputHandling(void);


//******************************            Main Function                  *********************************************
int main(void)
{
	setupWindow();

	inputHandling();

	quitPrompt();




		
	


	

	/////////////////////Save file code goes here
	
	
	
		
		mvaddstr(((num_rows / 2)-2), ((num_cols / 2) - 12), "Your file has been saved!!" );
	}
	
	mvaddstr(((num_rows/2)), ((num_cols/2)-12), "press any key to exit");
	response = getch();
	endwin();

}











///////////////////////////////////////////              Window setup function              ////////////////////////////////////////
void windowSetup(void){

WINDOW* main_window = nullptr;
int num_cols = 0;
int num_rows = 0;

//SETUP


//initialize our window
main_window = initscr();

//start colors
start_color();


init_pair(WINCOLORS, COLOR_BLUE, COLOR_WHITE);// Blue text on a white screen for regular Window Colors

init_pair(PROMPTCOLORS, COLOR_WHITE, COLOR_RED);// White text on a red screen for Prompt Colors

init_pair(WINDOWTEXT, COLOR_WHITE, COLOR_BLUE);// White text on a blue background for Window Text

bkgd(COLOR_PAIR(WINCOLORS));// Initialize the background with WINCOLORS


//resize our window
resize_term(0, 0);
getmaxyx(main_window, num_rows, num_cols);
resize_term(num_rows - 1, num_cols - 1);
getmaxyx(main_window, num_rows, num_cols);

//turn keyboard echo
noecho();

//turn on keypad input
keypad(main_window, TRUE);
curs_set(2);

//add Welcome String to the screen
mvaddstr(2, 2, "Welcome to the Airth Text Editor");


//creates the border around the perimeter of the window
for (int i = 0; i < num_cols; i++)
{
	//top row
	mvaddch(0, i, ACS_BLOCK);


	//bottom row

	mvaddch(num_rows - 1, i, ACS_BLOCK);

}

for (int i = 0; i < num_rows; i++)
{
	//left column
	mvaddch(i, 0, ACS_BLOCK);

	//right column
	mvaddch(i, num_cols - 1, ACS_BLOCK);
}

//Footer message
wattron(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT

mvaddstr(num_rows-1, 3, "ESC = Quit Program | CTRL+S = Save | CTRL+L = Load");

wattroff(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS


//mvaddstr(num_rows - 2, 3, "ESC = Quit Program | CTRL+S = Save | CTRL+L = Load");

//sets cursor initial position
wmove(main_window, 3, 3);

}
//////////////////////////////////////////              exit prompt function              ///////////////////////////////////
	void exitPrompt(void)
	{
		wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

		mvaddstr(num_rows - 2, num_cols - 45, "Are you sure you want to quit?");

		wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS



	}











///////////////////////////////////////            Save prompt function goes here               ////////////////////////////////////
	void savePrompt(void) {

		wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

		mvaddstr(num_rows - 2, num_cols - 45, "Would you like to save your file? Y or N");

		wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

		if (confirm()) {
			saveFile();
		}
	}




///////////////////////////////////////            Save file function goes here               ////////////////////////////////////
	void saveFile(void){
		
		mvaddstr(((num_rows / 2) - 2), ((num_cols / 2) - 12), "Your file has been saved!!");

	}


//////////////////////////////////////               Confirm function goes here                /////////////////////////////////////
	bool confirm(void) {
		switch (getch()) {

		case 'y' || 'Y':
			return 1;
			break;

		case 'n' || 'N':
			return 0;
			break;

		default:
			confirm();
		}
	}


	}

		

		
		//changes color to promptcolors
		wattroff(main_window, COLOR_PAIR(PROMPTCOLORS));

	
		\
///////////////////////////         Quit prompt function goes here           //////////////////////////


void quitPrompt(void) {
			//changes color for prompt
			wattron(main_window, COLOR_PAIR(PROMPTCOLORS));

			//exit prompt print
			mvaddstr(num_rows - 2, num_cols - 45, "Are you sure you want to quit? y or n");

			//changes color to wincolors
			wattroff(main_window, COLOR_PAIR(PROMPTCOLORS));

			if (confirm) {
				saveprompt();
				mvaddstr(((num_rows / 2)), ((num_cols / 2) - 12), "press any key to exit");
				response = getch();
				endwin();
			}
			else {
				inputHandling();
			}
			
			//calls save function
			



//////////////////////////           Input Handler function goes here            //////////////////////////////
			void inputHandling(void) {

				//This is where the input characters get handled
				int input = getch();

				
				while (input != ESCAPE) {

					waddch(main_window, input);
					input = getch();

				}
			}