#define PDC_DLL_BUILD 1

#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(void)
{
	WINDOW* main_window = nullptr;
	int num_cols = 0;
	int num_rows = 0;

	//SETUP
	

	//initialize our window
	main_window = initscr();

	//start colors
	start_color();

	// Blue text on a white screen
	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	bkgd(COLOR_PAIR(1)); 


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
	mvaddstr(2, 2, "Welcome to the Airth Text Editor. Press ESC to exit.");


	//MAIN PROGRAM LOGIC GOES HERE

		//This is where the input characters get handled

	

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
	mvaddstr(num_rows - 2, 3, "ESC = Quit Program | CTRL+S = Save | CTRL+L = Load");


	wmove(main_window, 3, 3);

		
	
int input = getch();

while (input != 27) {


	waddch(main_window, input);


	//pause for user input
	input = getch();
}
	
	//end curses mode
	endwin();

}