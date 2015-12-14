/*==============================================================================
| Filename: main.c
| Programmer: Kenneth Eversole
| Class: Cpts 121 Fall 2015 Lab Section 10
| Programming Assignment 6: Basic Game of Battleship
| Date: November 1, 2015
+------------------------------------------------------------------------------
| Description: Unilike most programs, main.c here is used as as the 
|	"bridge" or main menu function of the game.
==============================================================================*/

#include "PA6.h"
/**
* Function name : main()
* Date Created  : November 5, 2015
* Usage         : main();
* Definition    : This function creates the main menu of the game.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
int main()
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(TEXT("Battleship by Kenneth Eversole"));

	int menu_choice = 0, option = 0;
	srand((unsigned int)time(NULL));

	do
	{
		game_menu_board();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 18, 18 });
		print_title();

		SetConsoleCursorPosition(Consolehandle, (COORD){ 40, 26 });
		// Prints menu on the screen 
		option = game_menu();

		switch (option)
		{
		case HOW_TO_PLAY:
			// Prints to the screen the rules of the game  
			system("cls");
			game_menu_board();
			print_title();
			SetConsoleCursorPosition(Consolehandle, (COORD){ 35, 26 });
			game_rules();
			system("pause");
			system("cls");
			menu_choice = TRUE;
			break;

		case START_NEW_GAME:
			// Plays a new game
			system("cls");
			battleship();
			SetConsoleCursorPosition(Consolehandle, (COORD){ 36, 37 });
			system("pause");
			system("cls");
			menu_choice = TRUE;
			break;

		case FAQ:
			// FAQ about the dev
			system("cls");
			game_menu_board();
			print_title();
			faq();
			system("pause");
			system("cls");
			menu_choice = TRUE;
			break;
		case EXIT_GAME:
			// Exits out from the game 
			system("cls");
			SetConsoleCursorPosition(Consolehandle, (COORD){ 35, 21 });
			printf("Goodbye! Play again another time!\n");
			menu_choice = FALSE;
			break;
		}

	} while (menu_choice);

	SetConsoleCursorPosition(Consolehandle, (COORD){ 35, 22 });
	return 0;
}