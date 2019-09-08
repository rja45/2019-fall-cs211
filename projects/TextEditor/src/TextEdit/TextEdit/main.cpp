#define PDC_DLL_BUILD 1
#define PDC_WIDE 1
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


////////////////////////////////          Function Prototypes            ////////////////////////////////
bool confirm(void);



//******************************            Main Function                  *******************************
int main(void){

//////////////////////////////////          This is where the window is built      ////////////////////////

	WINDOW* main_window = nullptr;

	int num_cols = 0;
	int num_rows = 0;
	int cursx = 0;
	int cursy = 0;

	

	//initialize our window
	resize_term(2000, 2000);
	main_window=initscr();	
		//initscr();
		
cbreak();
keypad(main_window, TRUE);
//raw();
//wrefresh(main_window);
//immedok(main_window, true);


//turn off keyboard echo
		noecho();

	
		
		//curs_set(2);

	//start colors
	start_color();
	init_pair(WINCOLORS, COLOR_BLUE, COLOR_WHITE);// Blue text on a white screen for regular Window Colors

	init_pair(PROMPTCOLORS, COLOR_WHITE, COLOR_RED);// White text on a red screen for Prompt Colors

	init_pair(WINDOWTEXT, COLOR_WHITE, COLOR_BLUE); //White text on a blue background for Window Text

	bkgd(COLOR_PAIR(WINCOLORS));// Initialize the background with WINCOLORS


		//resize our window
		
		getmaxyx(main_window, num_rows, num_cols);
		refresh();
		//resize_term(num_rows - 1, num_cols - 1);
		//getmaxyx(main_window, num_rows, num_cols);
		

		//creates the border around the perimeter of the window
		
		wborder(main_window, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK,
			ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
		
		
		

		//add Welcome String to the screen
		wattron(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT

		mvaddstr(0, 3, "Welcome to the Airth Text Editor!");

		wattroff(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS

		//Footer message
		wattron(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT

		mvaddstr(num_rows - 1, 3, "ESC - Quit | F1 - Save File | F2 - Load File | F3 - New File");

		wattroff(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS

	


	//sets cursor initial position
	wmove(main_window, 1, 3);

	///////////////////////         This is where the input characters get handled           /////////////////

	bool quit = false;
	int input = wgetch(main_window);

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
			}
				break;

		case KEY_F(1):
			wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvaddstr(num_rows - 2, num_cols - 45, "Would you like to save your file? Y or N");

			wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			refresh();
			if (confirm()) {
				wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT
				mvaddstr(((num_rows / 2) - 2), ((num_cols / 2) - 12), "Your file has been saved!!");
				wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			}
			break;

		case KEY_F(2):
			wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvaddstr(num_rows - 2, num_cols - 45, "Would you like to load a file? Y or N");

			wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			refresh();
			break;

		case KEY_F(3):
			wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvaddstr(num_rows - 2, num_cols - 45, "Would you like to make a new file?");

			wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
			refresh();
			break;

		case KEY_RESIZE:

				//getmaxyx(stdscr, num_rows, num_cols);
				resize_term(0, 0);
				getmaxyx(stdscr, num_rows, num_cols);
				wresize(main_window,num_rows, num_cols);
				//resize_term(0, 0);
				//Make border
				wborder(main_window, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);
				//Header message
				wattron(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT
				mvaddstr(0, 3, "Welcome to the Airth Text Editor!");
				wattroff(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS
				//Footer message
				wattron(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT
				mvaddstr(num_rows - 1, 3, "ESC = Quit Program | CTRL+S = Save | CTRL+L = Load");
				wattroff(main_window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS				
				//wmove(main_window, 3, 3);
				//refresh();
				wrefresh(main_window);
				//wmove(main_window, 3, 3);
				input = NULL;
				break;

		case KEY_COMMAND:
			wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT
			mvaddstr(((num_rows / 2) - 2), ((num_cols / 2) - 12), "Your thing has f8!!");
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

	void resizeWin(WINDOW* window, int* rows, int* cols) {
		//resize_term(0, 0);
		getmaxyx(window, *rows, *cols);
		resize_term(*rows - 1, *cols - 1);
		getmaxyx(window, *rows, *cols);


		//creates the border around the perimeter of the window
		for (int i = 0; i < *cols; i++)
		{
			//top row
			mvaddch(0, i, ACS_DIAMOND);


			//bottom row
			mvaddch(*rows - 1, i, ACS_BLOCK);

		}

		for (int i = 0; i < *rows; i++)
		{
			//left column
			mvaddch(i, 0, ACS_BLOCK);

			//right column
			mvaddch(i, *cols - 1, ACS_BLOCK);
		}



		//add Welcome String to the screen
		wattron(window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT

		mvaddstr(0, 3, "Welcome to the Airth Text Editor!");

		wattroff(window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS



		//Footer message
		wattron(window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR FOR PROMPT

		mvaddstr(*rows - 1, 3, "ESC = Quit Program | CTRL+S = Save | CTRL+L = Load");

		wattroff(window, COLOR_PAIR(WINDOWTEXT)); //CHANGES COLOR BACK TO WINCOLORS

	}
	