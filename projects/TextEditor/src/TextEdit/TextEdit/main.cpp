//Define global variables
#define PDC_DLL_BUILD 1
#define PDC_WIDE 1
#define WINCOLORS 1
#define PROMPTCOLORS 2
#define TERMCOLORS 3
#define TERMTEXT 4
#define ESCAPE 27
#define SAVE ctrl('s')
#define LOAD ctrl('l')
#define NEW_FILE ctrl('n')
#define ctrl(x)           ((x) & 0x1f)


//Header Files
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


////////////////////////////////          Function Prototypes            ////////////////////////////////
bool confirm(void);


void draw_centered(WINDOW* win, int max_y, int max_x, string text);


//******************************            Main Function                  *******************************
int main(void) {

	//////////////////////////////////          This is where the window is built      ////////////////////////

		//create variables
	int term_cols = 0;
	int term_rows = 0;
	int curs_x = 0;
	int curs_y = 0;
	vector <string> inputbuffer;

	//initialize the terminal
	initscr();

	//Resize for initial size
	resize_term(30, 120);
	getmaxyx(stdscr, term_rows, term_cols);


	//initialize the main window
	WINDOW* main_window = newwin((term_rows - 4), (term_cols - 4), 2, 2);

	//Set input
	nl();

	//cbreak();	

	keypad(stdscr, true);

	//keypad(main_window, true);

	//raw();

	//Set Scrolling

	scrollok(main_window, true);

	wsetscrreg(main_window, term_rows - 4, term_cols - 4);

	//Set cursor visibility
	curs_set(2);

	//turn off keyboard echo
	noecho();


	if (can_change_color) {

		//start colors
		start_color();

		// Black text on a white screen for regular Window Colors
		init_pair(WINCOLORS, COLOR_BLACK, COLOR_WHITE);

		// White text on a red screen for Prompt Colors
		init_pair(PROMPTCOLORS, COLOR_WHITE, COLOR_RED);

		// Blue border and white inserior for the Terminal Colors
		init_pair(TERMCOLORS, COLOR_BLUE, COLOR_WHITE);

		// White text to contrast with Blue Terminal border text.
		init_pair(TERMTEXT, COLOR_WHITE, COLOR_BLUE);

		// Initialize the background with WINCOLORS
		wbkgd(main_window, COLOR_PAIR(WINCOLORS));

		//Initialize the Terminal Colors
		bkgd(COLOR_PAIR(TERMCOLORS));
	}
	else {
		use_default_colors();
	}

	//creates the BLUE border around the perimeter of the terminal


	border(ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK,
		ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);








	//add Welcome String to the screen
	attron(COLOR_PAIR(TERMTEXT)); //CHANGES COLOR FOR PROMPT

	mvaddstr(0, 3, "Welcome to the Airth Text Editor!");

	//attroff( COLOR_PAIR(TERMCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

	//Footer message
	//attron(COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT

	mvaddstr(term_rows - 1, 3, "ESC - Quit | CTRL+S -Save File | CTRL+L -Load File | CTRL+N -New File");

	attroff(COLOR_PAIR(TERMTEXT)); //CHANGES COLOR BACK TO WINCOLORS

	refresh();
	//wrefresh(main_window);


//sets cursor initial position
//wmove(main_window, 3, 3);
//wrefresh(main_window);

///////////////////////         This is where the input characters get handled           /////////////////
//set whether user wants to quit
	bool quit = false;

	//get input from keyboard

	char input = wgetch(main_window);

	while (!quit) {

		switch (input) {
		case ESCAPE:
			//changes color for prompt
			attron(COLOR_PAIR(PROMPTCOLORS));
			//exit prompt print
			mvaddstr(term_rows - 1, term_cols - 40, "Are you sure you want to quit?");

			quit = confirm();

			attron(COLOR_PAIR(TERMCOLORS));

			border(ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK,
				ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);

			attroff(COLOR_PAIR(TERMCOLORS));

			mvaddstr(term_rows - 1, term_cols - 45, "Would you like to save your file? Y or N");

			attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

			attron(COLOR_PAIR(TERMCOLORS));

			border(ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK,
				ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);

			attroff(COLOR_PAIR(TERMCOLORS));

			if (confirm()) {
				clear();
				attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT
				mvaddstr(((term_rows / 2) - 2), ((term_cols / 2) - 12), "Your file has been saved!!");
				attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			}
			break;

		case SAVE:
			wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvaddstr(term_rows - 2, term_cols - 45, "Would you like to save your file? Y or N");

			wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			wrefresh(main_window);
			if (confirm()) {
				wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT
				mvaddstr(((term_rows / 2) - 2), ((term_cols / 2) - 12), "Your file has been saved!!");
				wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			}
			break;

		case LOAD:
			attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvaddstr(term_rows - 2, term_cols - 45, "Would you like to load a file? Y or N");

			attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			//wrefresh(main_window);
			break;

		case NEW_FILE:
			attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvaddstr(term_rows, term_cols - 45, "Would you like to make a new file? Y or N");

			attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			//refresh(main_window);
			break;

		case KEY_RESIZE:

			//getmaxyx(stdscr, num_rows, num_cols);
			//resize_term(0, 0);				
			//wresize(main_window,num_rows, num_cols);
			//resize_term(0, 0);
			//Make border
			//wborder(main_window, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
			//Header message
			//wattron(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT
			//mvaddstr(0, 3, "Welcome to the Airth Text Editor!");
			//wattroff(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS
			//Footer message
			//wattron(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT
			//mvaddstr(num_rows - 1, 3, "ESC = Quit Program | CTRL+S = Save | CTRL+L = Load");
			//wattroff(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS				
			//wmove(main_window, 3, 3);
			//refresh();
			//wrefresh(main_window);
			//wmove(main_window, 3, 3);
			input = NULL;
			break;


		case KEY_LEFT:

			getyx(main_window, curs_y, curs_x);
			move(curs_y, curs_x - 1);
			//refresh();
			getch();
			break;



		default:

			waddch(main_window, input);
			input = wgetch(main_window);
			break;
		}






	}

	char response = getch();
	endwin();

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

void windowResize(WINDOW* win, int rows, int cols) {

	resize_window(win, (rows - 4), (cols - 4));

}