#define PDC_DLL_BUILD 1
#define WINCOLORS 1
#define PROMPTCOLORS 2
#define ESCAPE 27


#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include <iostream>
#include <fstream>

using namespace std;


////////////////////////////////          Function Prototypes            ///////////////////////////////////////////////
bool confirm(void);


//******************************            Main Function                  *********************************************
int main(void) {


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
	mvaddstr(num_rows - 2, 3, "ESC = Quit Program | CTRL+S = Save | CTRL+L = Load");

	//sets cursor initial position
	wmove(main_window, 3, 3);


	///////////////////////////////////////           This is where the input characters get handled           ///////////////////////////

	int input = getch();
	bool quit = false;

	while (!quit) {

		switch (input) {
		case ESCAPE:
			//changes color for prompt
			wattron(main_window, COLOR_PAIR(PROMPTCOLORS));

			//exit prompt print
			mvaddstr(num_rows - 2, num_cols - 45, "Are you sure you want to quit?");

			//changes color to wincolors
			wattroff(main_window, COLOR_PAIR(PROMPTCOLORS));
			quit = confirm();

			wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvaddstr(num_rows - 2, num_cols - 45, "Would you like to save your file? Y or N");

			wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

			if (confirm()) {
				clear();
				wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT
				mvaddstr(((num_rows / 2) - 2), ((num_cols / 2) - 12), "Your file has been saved!!");
				wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

				break;

		default:
			waddch(main_window, input);
			input = getch();
			break;
			}




		}

		char response = getch();
		endwin();

	}

}

bool confirm(void) {
	char answer = getch();
	switch (answer) {

	case 'y':
		return true;
		break;
	case 'Y':
		return true;
		break;

	case 'n': 
		return false;
		break;

	case 'N':
		return false;
		break;

	default:
		confirm();
	}


}










