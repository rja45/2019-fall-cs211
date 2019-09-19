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
#define LEFT_ARROW 260
#define	RIGHT_ARROW 261
#define UP_ARROW 259
#define DOWN_ARROW 258
#define BACKSPACE 8
#define NEWLINE 10


//Header Files
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


////////////////////////////////          Function Prototypes            ////////////////////////////////
bool confirm(void);


//******************************            Main Function                  *******************************
int main(int argc, char* argv[])
{

	//////////////////////////////////          This is where the window is built      ////////////////////////
		//create variables
	int term_cols = 120;
	int term_rows = 30;
	int win_cols = 0;
	int win_fcol = 0;
	int win_frow = 0;
	int win_rows = 0;
	int curs_x = 0;
	int curs_y = 0;
	int screen_y = 0;
	int screen_x = 0;
	int output_ledge = 0;
	int output_redge = 0;
	int output_bedge = 0;
	int output_tedge = 0;
	int vector_y = 0;
	int vector_x = 0;
	string filename;
	char fname;
	char fileChar;
	char c;
	ifstream inFile;
	vector< vector <int> > buffer;


	//initialize the terminal
	initscr();

	//Resize the terminal for initial size
	getmaxyx(stdscr, term_rows, term_cols);
	resize_term(term_rows, term_cols);

	//initialize the window dimensions
	win_cols = term_cols - 4;
	win_fcol = 2;
	win_frow = 2;
	win_rows = term_rows - 4;
	output_redge = win_cols;
	output_ledge = win_fcol;
	output_bedge = win_rows;
	output_tedge = win_frow;

	//initialize the main window
	WINDOW* main_window = newwin(win_rows, win_cols, win_frow, win_fcol);


	//Set input characteristics	
	cbreak();
	keypad(main_window, true);
	//Set Scrolling
	//scrollok(main_window, true);
	//wsetscrreg(main_window, win_rows, win_cols);



	//Set cursor visibility
	curs_set(2);


	//turn off keyboard echo
	noecho();



	//color initializations
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


	//Terminal text at the top and bottom of the window	
	attron(COLOR_PAIR(TERMTEXT));
	mvprintw(0, 3, "Welcome to the Airth Text Editor!");
	mvprintw(term_rows - 1, 3, "ESC - Quit | CTRL+S -Save File | CTRL+L -Load File | CTRL+N -New File");
	attroff(COLOR_PAIR(TERMTEXT));


	//create buffer vectors to same size as window cols and rows.
	buffer.resize(300);
	for (int i = 0; i < 300; i++)
	{
		buffer[i].resize(600);
	}
	

	if (argc >= 2)
	{

		inFile.open(argv[1]);

		if (!inFile.is_open())
		{
			attron(COLOR_PAIR(TERMTEXT));
			//
			mvprintw(term_rows - 1, term_cols - 45, "                                           ");
			//
			attroff(COLOR_PAIR(TERMTEXT));

			attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

			mvprintw(term_rows - 1, term_cols - 45, "File loading has failed");

			attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS	

			attron(COLOR_PAIR(TERMTEXT));

			mvprintw(term_rows - 1, term_cols - 45, "                                           ");

			attroff(COLOR_PAIR(TERMTEXT));

			refresh();

		}

		if (inFile.good())
		{
			int copy_y = 0;
			int copy_x = 0;

			for (int i = 0; i < buffer.size(); i++)
			{
				{
					for (int j = 0; j < buffer[i].size(); j++)
					{
						buffer[i][j] = ' ';
					}
				}
			}


			while (!inFile.eof())
			{
				inFile.get(fileChar);

				if (fileChar == 10)
				{
					buffer[copy_y][copy_x] = fileChar;
					copy_y++;
					copy_x = 0;
				}
				else
				{
					buffer[copy_y][copy_x] = fileChar;
					copy_x++;
				}


			}

			attron(COLOR_PAIR(TERMTEXT));

			mvprintw(term_rows - 1, term_cols - 45, "                                           ");

			attroff(COLOR_PAIR(TERMTEXT));

			attron(COLOR_PAIR(PROMPTCOLORS));

			//exit prompt print
			mvprintw(term_rows - 1, term_cols - 40, "Your file has been loaded!");

			attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

			refresh();

			getch();


		}
	}
	//if there is no file to load upon startup, the vector is initialized with all spaces
	else
	{
		//initialize buffer vector with a space/blank in every position
		for (int i = 0; i < buffer.size(); i++)
		{
			{
				for (int j = 0; j < buffer[i].size(); j++)
				{
					buffer[i][j] = ' ';
				}
			}
		}
	}


		//print out the buffer to the screen based on window size
		for (int i = output_tedge; i < output_bedge; i++)
		{

			for (int j = output_ledge; j < output_redge; j++)
			{
				mvwaddch(main_window, screen_y, screen_x, buffer[i][j]);
				screen_x++;
			}
			screen_x = 0;
			screen_y++;
		}
		screen_y = 0;
		screen_x = 0;

		//sets cursor initial position	
		wmove(main_window, curs_y, curs_x);

		refresh();
		wrefresh(main_window);

		///////////////////////         This is where the input characters get handled           /////////////////
			//set whether user wants to quit
		bool quit = false;
		int input;

		//this loop checks the quit bool after every key input

		while (!quit) {

			input = wgetch(main_window);
			vector_y = curs_y + output_tedge;
			vector_x = curs_x + output_ledge;



			//if the terminal is resized, the terminal window is all redrawn to the new dimensions
			if (is_termresized() == true)
			{

				clear();
				//getyx(main_window, curs_y, curs_x);
				resize_term(0, 0);
				//getmaxyx(stdscr, term_rows, term_cols);

				//win_cols = term_cols - 4;
				//win_fcol = 2;
				//win_frow = 2;
				//win_rows = term_rows - 4;
				//wresize(main_window, win_cols, win_rows);

				//creates the BLUE border around the perimeter of the terminal
				border(ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK,
					ACS_BLOCK, ACS_BLOCK, ACS_BLOCK, ACS_BLOCK);

				//add Welcome String to the screen
				attron(COLOR_PAIR(TERMTEXT)); //CHANGES COLOR FOR PROMPT
				mvprintw(0, 3, "Welcome to the Airth Text Editor!");
				mvprintw(term_rows - 1, 3, "ESC - Quit | CTRL+S -Save File | CTRL+L -Load File | CTRL+N -New File");
				attroff(COLOR_PAIR(TERMTEXT)); //CHANGES COLOR BACK TO WINCOLORS

				//get new window edges
				output_redge = win_cols - 1;
				output_bedge = win_rows - 1;

				//re-print all text from the buffer onto the screen with the new dimensions
				for (int i = output_tedge; i < output_bedge; i++)
				{

					for (int j = output_ledge; j < output_redge; j++)
					{
						mvwaddch(main_window, screen_y, screen_x, buffer[i][j]);
						screen_x++;
					}
					screen_y++;
				}
				screen_y = 0;
				screen_x = 0;

				wmove(main_window, curs_y, curs_x);

				refresh();
				wrefresh(main_window);




			}
			//getyx(main_window, curs_y, curs_x);



			switch (input) {
			case (ESCAPE):
				//changes color for prompt
				attron(COLOR_PAIR(PROMPTCOLORS));
				//exit prompt print
				mvprintw(term_rows - 1, term_cols - 40, "Are you sure you want to quit?");



				attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

				attron(COLOR_PAIR(TERMTEXT));

				quit = confirm();

				mvprintw(term_rows - 1, term_cols - 45, "                                        ");

				if (!quit)
				{
					break;
				}

				attroff(COLOR_PAIR(TERMTEXT));

				//changes color for prompt
				attron(COLOR_PAIR(PROMPTCOLORS));

				mvprintw(term_rows - 1, term_cols - 45, "Would you like to save your file? Y or N");


				attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS



				if (confirm()) {
					//changes color for prompt
					attron(COLOR_PAIR(PROMPTCOLORS));

					//exit prompt print
					mvprintw(term_rows - 1, term_cols - 40, "Your file has been saved!");

					attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

					attron(COLOR_PAIR(TERMTEXT));

					input = wgetch(main_window);

					mvprintw(term_rows - 1, term_cols - 45, "                                           ");

					attroff(COLOR_PAIR(TERMTEXT));

					break;

				}
				else
				{
					attron(COLOR_PAIR(PROMPTCOLORS));

					mvprintw(term_rows - 1, term_cols - 40, "Your file has not been saved!");

					attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

					attron(COLOR_PAIR(TERMTEXT));

					input = wgetch(main_window);

					mvprintw(term_rows - 1, term_cols - 45, "                                           ");

					attroff(COLOR_PAIR(TERMTEXT));

					break;
				}

				wrefresh(main_window);
				break;

			case (SAVE):
				wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

				mvprintw(term_rows - 2, term_cols - 45, "Would you like to save your file? Y or N");

				wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
				wrefresh(main_window);
				if (confirm()) {
					wattron(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT
					mvprintw(((term_rows / 2) - 2), ((term_cols / 2) - 12), "Your file has been saved!!");
					wattroff(main_window, COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
				}
				break;

			case (LOAD):
				attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

				mvprintw(term_rows - 1, term_cols - 45, "Would you like to load a file? Y or N");

				attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

				if (confirm())
				{
					attron(COLOR_PAIR(TERMTEXT));

					mvprintw(term_rows - 1, term_cols - 45, "                                           ");

					attroff(COLOR_PAIR(TERMTEXT));

					attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

					mvprintw(term_rows - 1, term_cols - 45, "What is the name of the .txt file?");

					attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

					attron(COLOR_PAIR(TERMTEXT));

					mvprintw(0, term_cols - 40, "                                           ");

					attroff(COLOR_PAIR(TERMTEXT));

					refresh();

					attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

					wmove(stdscr, 0, term_cols - 40);

					c = getch();

					while (c != 10)
					{
						filename.push_back(c);
						addch(c);
						c = getch();
					}

					char fname[30];
					strncpy_s(fname, filename.c_str(), sizeof(filename));







					attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS				




					;


					inFile.open(fname);


					if (!inFile.is_open())
					{
						attron(COLOR_PAIR(TERMTEXT));
						//
						mvprintw(term_rows - 1, term_cols - 45, "                                           ");
						//
						attroff(COLOR_PAIR(TERMTEXT));

						attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

						mvprintw(term_rows - 1, term_cols - 45, "File loading has failed");

						attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS	

						attron(COLOR_PAIR(TERMTEXT));

						mvprintw(term_rows - 1, term_cols - 45, "                                           ");

						attroff(COLOR_PAIR(TERMTEXT));

						memset(fname, 0, sizeof(fname));

						filename.clear();

						refresh();

						break;
					}

					if (inFile.good())

					{
						int copy_y = 0;
						int copy_x = 0;

						for (int i = 0; i < buffer.size(); i++)
						{
							{
								for (int j = 0; j < buffer[i].size(); j++)
								{
									buffer[i][j] = ' ';
								}
							}
						}


						while (!inFile.eof())
						{
							inFile.get(fileChar);

							if (fileChar == 10)
							{
								buffer[copy_y][copy_x] = fileChar;
								copy_y++;
								copy_x = 0;
							}
							else
							{
								buffer[copy_y][copy_x] = fileChar;
								copy_x++;
							}


						}

						attron(COLOR_PAIR(TERMTEXT));

						mvprintw(term_rows - 1, term_cols - 45, "                                           ");

						attroff(COLOR_PAIR(TERMTEXT));

						attron(COLOR_PAIR(PROMPTCOLORS));

						//exit prompt print
						mvprintw(term_rows - 1, term_cols - 40, "Your file has been loaded!");

						attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

						refresh();

						getch();


					}


				}
				else
				{
					attron(COLOR_PAIR(TERMTEXT));

					//exit prompt print
					mvprintw(term_rows - 1, term_cols - 45, "                                      ");

					attroff(COLOR_PAIR(TERMTEXT)); //CHANGES COLOR BACK TO WINCOLORS

				}


				getch();

				attron(COLOR_PAIR(TERMTEXT));

				mvprintw(term_rows - 1, term_cols - 45, "                                           ");

				attroff(COLOR_PAIR(TERMTEXT));
				break;

			case (NEW_FILE):
				attron(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR FOR PROMPT

				mvprintw(term_rows, term_cols - 45, "Would you like to make a new file? Y or N");

				attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS
				break;


			case (KEY_LEFT):

				//if cursor is at left edge, with more to display, the text shifts rightward and cursor doesn't move.
				if (curs_x == 0 && output_ledge > 0)
				{
					output_ledge--;
					output_redge--;
					break;
				}
				//if the cursor is at the left edge, with nothing more to display, nothing happens
				else if (curs_x == 0 && output_ledge == 0)
				{
					break;
				}
				//in all other cases, the cursor moves left.
				else
				{
					curs_x--;
					break;
				}


			case (KEY_RIGHT):

				//if cursor is at right edge, with more to display, the text shifts leftward and cursor doesn't move.
				if (curs_x == win_cols - 1 && output_redge < buffer[curs_y].size() - 1)
				{
					output_redge++;
					output_ledge++;
					break;
				}
				//if cursor is at the right edge, with nothing more to display, characters are created and displayed
				else if (curs_x == win_cols - 1 && output_redge == buffer[curs_y].size() - 1)
				{
					buffer[curs_y].push_back(' ');
					output_redge++;
					output_ledge++;
					break;
				}
				//in all other cases, the cursor moves rightward in the window
				else
				{
					curs_x++;
					break;
				}



			case (KEY_UP):
				//if cursor is at the top edge, with more to display, the text shifts downward and cursor doesn't move.
				if (curs_y == 0 && output_tedge > 0) {
					output_tedge--;
					output_bedge--;
					break;
				}
				//if cursor is at the top edge, with nothing more to display, nothing happens.
				else if (curs_y == 0 && output_tedge == 0)
				{
					break;
				}
				//in all other cases, the cursor moves upward in the window.
				else
				{
					curs_y--;
					break;
				}


			case (KEY_DOWN):
				//if cursor is at the bottom edge, with more to display, the text shifts upward and the cursor doesn't move. 
				if (curs_y == win_rows - 1 && curs_y < buffer.size() - 1)
				{
					output_tedge++;
					output_bedge++;
					break;
				}
				//if cursor is at the bottom edge, with nothing more to display, a row is created and initialized and the text moves up, cursor doesn't move.
				else if (curs_y == win_rows - 1 && output_tedge == buffer.size() - 1)
				{
					buffer.push_back(vector <int>(600));
					for (int i = 0; i < buffer[win_cols].size(); i++)
					{
						buffer[curs_y][i] = ' ';
					}
					output_tedge++;
					output_bedge++;
					break;
				}
				//in all other cases, the cursor moves downward in the window
				else
				{
					curs_y++;
					break;
				}


			case BACKSPACE:
				//if cursor is not near edge of window, the cursor moves left one position and overwrites value with ' '.
				if (curs_x > 0)
				{
					curs_x--;
					buffer[vector_y][vector_x] = ' ';
					break;
				}

				//if cursor is at the left edge, the text shifts rightward and the new character under the cursor gets overwritten with ' '. 
				else if (curs_x == 0 && output_ledge > 0)
					output_ledge--;
				output_redge--;

				for (int i = output_tedge; i < output_bedge; i++)
				{

					for (int j = output_ledge; j < output_redge; j++)
					{
						mvwaddch(main_window, screen_y, screen_x, buffer[i][j]);
						screen_x++;
					}
					screen_y++;
				}
				screen_y = 0;
				screen_x = 0;
				buffer[vector_y][vector_x] = ' ';
				break;

			case (NEWLINE):
				//if cursor is at the bottom edge, with more to display, the text shifts upward and the cursor doesn't move. 
				if (curs_y == win_rows - 1 && curs_y < buffer.size() - 1)
				{
					output_tedge++;
					output_bedge++;

					break;
				}
				//if cursor is at the bottom edge, with nothing more to display, a row is created and initialized and the text moves up, cursor doesn't move.
				else if (curs_y == win_rows - 1 && output_tedge == buffer.size() - 1)
				{
					buffer.push_back(vector <int>(600));
					for (int i = 0; i < buffer[win_cols].size(); i++)
					{
						buffer[curs_y][i] = ' ';
					}
					output_tedge++;
					output_bedge++;
					break;
				}
				//in all other cases, the cursor moves downward in the window
				else
				{
					curs_y++;
					break;
				}



			default:
				//if cursor is at the right edge and there is more to display, the character is inserted and the text moves leftward and the cursor doesn't move.
				if (curs_x == win_cols - 1 && output_redge < buffer[curs_y].size())
				{
					buffer[vector_y][vector_x] = input;
					output_redge++;
					output_ledge++;
					break;
				}
				//if the cursor is at the right edge and there is nothing more to display, the new character gets added to the end of the vector and the text shifts leftward.
				else if (output_redge == buffer[curs_y].size() - 1)
				{
					buffer[vector_y].push_back(input);
					output_redge++;
					output_ledge++;
					break;
				}
				//in all other cases, the character gets input and the cursor moves rightward.
				else
				{
					vector_y = curs_y + output_tedge;
					vector_x = curs_x + output_ledge;
					buffer[vector_y][vector_x] = input;
					curs_x++;
					break;
				}

			}



			for (int i = output_tedge; i < output_bedge; i++)
			{

				for (int j = output_ledge; j < output_redge; j++)
				{
					mvwaddch(main_window, screen_y, screen_x, buffer[i][j]);
					screen_x++;
				}
				screen_x = 0;
				screen_y++;
			}
			screen_y = 0;
			screen_x = 0;

			wmove(main_window, curs_y, curs_x);

			wrefresh(main_window);

			refresh();
		}



		//changes color for prompt
		attron(COLOR_PAIR(PROMPTCOLORS));


		//any key to exit prompt
		mvprintw(term_rows - 1, term_cols - 45, "Press any key to escape");


		attroff(COLOR_PAIR(PROMPTCOLORS)); //CHANGES COLOR BACK TO WINCOLORS

		wrefresh(main_window);
		wgetch(main_window);
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


//for (int i = 0; i < buffer.size(); i++) 
//{
	//for (int j = 0; j < buffer[i].size(); j++)
	//{
		//if (buffer[i][j] > 0 && buffer[i][j] < 256)
		//{
		//	mvwaddch(main_window, i, j, buffer[i][j]);
		//}
	//}
//}