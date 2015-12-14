/*==============================================================================
| Filename: PA6.c
| Programmer: Kenneth Eversole
| Class: Cpts 121 Fall 2015 Lab Section 10
| Programming Assignment 6: Basic Game of Battleship
| Date: November 1, 2015
+------------------------------------------------------------------------------
| Description: This contains the nesscary function for the game to run properly,
including the main "game" function battleship();
==============================================================================*/
#include "PA6.h"

/**
* Function name : battleship()
* Date Created  : November 5, 2015
* Usage         : battleship();
* Definition    : This function acts as the main function of the program.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void battleship()
{
	//for the moving of the curser and color
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w0ldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	FILE *data_game = NULL;
	Boards human_board[10][10];
	Boards computer_board[10][10];

	int human_board_hits[10][10] = { -1 };

	Ai data = { .seek_or_destroy = 0, .DTargets = (COORD){ -1, -1 } };

	Coordinate target;


	int	totalship_health_human = 17;
	int totalship_health_computer = 17;
	int player = 0;
	int i = 0, ch = 0;
	int shot = 0;
	int option = 0;
	int end_game = 1;
	int esc = 1;
	int k = 0;
	int j = 0;


	Info ships[NUMSHIPS] = { { 'c', 5, 5, 5, "Carrier" },
	{ 'b', 4, 4, 4, "Battleship" },
	{ 'r', 3, 3, 3, "Cruiser" },
	{ 's', 3, 3, 3, "Submarine" },
	{ 'd', 2, 2, 2, "Destroyer" } };




	Stats game_stats_human = { 0, 0 };
	Stats game_stats_computer = { 0, 0 };


	game_play_board();
	print_attributes(ships);
	print_title();

	init_game_board(human_board);
	init_game_board(computer_board);

	print_human_board(human_board);
	print_computer_board(computer_board);

	data_game = fopen("data.dat", "w");


	//sets up Dtargets
	for (i = 0; i < 102; i++)
	{

		data.DTargets[i] = (COORD){ -1, -1 };



	}


	//sets up human_board_hits
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			human_board_hits[i][j] = -1;
		}


	}




	//selection of placement
	textbox(1);

	option = _getch() - 0x30;

	switch (option)
	{
		//secret
	case 0:
		printf("TEST");
		break;

	case 1:


		placeships_m(human_board, ships);

		break;
	case 2:
		placeships_r(human_board, ships);

		break;

	}
	system("cls");
	game_play_board();
	print_attributes(ships);
	print_title();

	printf("\n");


	//loadingbar();

	placeships_r(computer_board, ships);


	print_human_board(human_board);
	print_computer_board(computer_board);


	player = rand() % 2;

	do
	{
		print_human_board(human_board);
		print_computer_board(computer_board);

		switch (player)
		{
			//human turn
		case 0:


			textbox(20);


			do
			{



				target = findtarget(computer_board);
				shot = checkshot(computer_board, target, ships);
				if (shot == 0)
				{
					fprintf(data_game, "MISS - HUMAN\n", &data_game);

					game_stats_human.numMisses += 1;
				}
				if (shot == 1)
				{
					fprintf(data_game, "HIT - HUMAN\n", &data_game);
					game_stats_human.numHits += 1;
					totalship_health_computer -= 1;

					print_attributes(ships);
				}
			} while (shot == 2);

			print_computer_board(computer_board);
			player = !player;


			break;

		case 1:


			Sleep(1000);
			textbox(21);


			//needs to be worked on.
			print_attributes(ships);


			print_human_board(human_board);
			print_computer_board(computer_board);

			//AI//computer_ai(target_comp, human_board, highest_value, data_game, total_p, carrier_p, battleship_p, sub_p, cruiser_p, destroyer_p, is_ship_hit, human_health);
			computer_ai(human_board, ships, &data, &game_stats_computer, human_board_hits, data_game);

			//could be done better, but I am tired... #nosleepclub
			totalship_health_human = ships[0].health + ships[1].health + ships[2].health + ships[3].health + ships[4].health;



			Sleep(1000);

			player = !player;
			break;
		}

		if (totalship_health_computer == 0)
		{
			fprintf(data_game, "HUMAN WINS!\n", &data_game);
			end_game = 0;
		}
		if (totalship_health_human == 0)
		{
			fprintf(data_game, "COMPUTER WINS!\n", &data_game);
			end_game = 0;

		}
	} while (end_game);

	system("cls");

	//default
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;

	//computer loses
	if (totalship_health_computer == 0)
	{
		SetConsoleTextAttribute(Consolehandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		SetConsoleCursorPosition(Consolehandle, (COORD){ 48, 19 });
		printf("YOU WIN!");
		SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
	}
	if (totalship_health_human == 0)
	{
		SetConsoleTextAttribute(Consolehandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		SetConsoleCursorPosition(Consolehandle, (COORD){ 48, 19 });
		printf("YOU LOSE!");
		SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
	}
	fclose(data_game);
}

/**
* Function name : print_title ()
* Date Created  : November 9, 2015
* Usage         : print_title();
* Definition    : This function prints the title "Battleship" to the screen.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void print_title()
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w0ldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	//default console colors
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;

	SetConsoleTextAttribute(Consolehandle, 10);

	for (int i = 0; i < 17; i++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 18, 2 + i });
		switch (i)
		{
		case 0: printf("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
			break;
		case 1: printf("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
			break;
		case 2: printf("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
			break;
		case 3: printf("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
			break;
		case 4: printf("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
			break;
		}
	}
	SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
	SetConsoleCursorPosition(Consolehandle, (COORD){ 40, 26 });

}

/**
* Function name : game_rules()
* Date Created  : November 9, 2015
* Usage         : game_rules();
* Definition    : This function prints out the rules of the game.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void game_rules()
{
	int i = 0;

	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < 17; i++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 22, 18 + i });
		switch (i)
		{
		case 0: printf("RULES OF THE GAME:");
			break;
		case 1: printf("1. This is a two player game.");
			break;
		case 2: printf("2. Player 1 is you and Player 2 is the computer.");
			break;
		case 3: printf("3. Player 1 will be prompted if user wants to ");
			break;
		case 4: printf("   manually input coordinates for the game board or have");
			break;
		case 5: printf("   the computer randomly generate a game board");
			break;
		case 6: printf("4. There are five types of ships to be placed by longest ");
			break;
		case 7: printf("   length to theshortest; [c] Carrier has 5 cells, ");
			break;
		case 8:	printf("   [b] Battleship has 4 cells, [r] Cruiser has 3 cells,");
			break;
		case 9: printf("   [s] Submarine has 3 cells, [d] Destroyer has 2 cells");
			break;
		case 10: printf("5. The computer randomly selects which player goes first");
			break;
		case 11: printf("6. The game begins as each player tries to guess the ");
			break;
		case 12: printf("   location of the shipsof the opposing player's game board;");
			break;
		case 13: printf("   [*] hit and [m] miss");
			break;
		case 14: printf("7. First player to guess the location of all ships wins");
			break;

		}
	}



}

/**
* Function name : game_menu_board()
* Date Created  : November 10, 2015
* Usage         : game_menu_board();
* Definition    : This function prints out the board that will used for the menus.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void game_menu_board()
{
	HANDLE Output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coordinates = { 200, 100 };
	SetConsoleScreenBufferSize(Output, Coordinates);
	SMALL_RECT Coordinates2 = { 0, 0, 100, 43 };
	SetConsoleWindowInfo(Output, TRUE, &Coordinates2);


	//colors
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w0ldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;



	//default color
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;

	//sets color to gray
	SetConsoleTextAttribute(Consolehandle, 8);

	printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");

	SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

}

/**
* Function name : game_play_board()
* Date Created  : November 10, 2015
* Usage         : game_playboard();
* Definition    : This function prints out the game board that use use for the actual game.
*					The reason for this is because there are lines that are added.
* Pre-condition : NONE
* Post-condition: NONE
*/
void game_play_board()
{
	HANDLE Output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Coordinates = { 200, 100 };
	SetConsoleScreenBufferSize(Output, Coordinates);
	SMALL_RECT Coordinates2 = { 0, 0, 100, 43 };
	SetConsoleWindowInfo(Output, TRUE, &Coordinates2);

	//colors
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w0ldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;



	//default color
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;

	//sets color to gray
	SetConsoleTextAttribute(Consolehandle, 8);


	printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCE\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA		\xBA                                 \xBA                                 \xBA               \xBA\n"
		"\xBA               \xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xBA		\xBA                                                                   \xBA               \xBA\n"
		"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");

	SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

}

/**
* Function name : game_menu()
* Date Created  : November 11, 2015
* Usage         : game_menu();
* Definition    : This function creates the game menu inside the game.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
int game_menu()
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int choice = 0, i = 0;



	for (i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 35, 26 + i });
		switch (i)
		{

		case 0: printf("[1]. Print game rules\n");
			break;
		case 1: printf("[2]. Start a game of Battleship\n");
			break;
		case 2: printf("[3]. FAQ");
			break;
		case 3: printf("[4]. Exit\n");
			break;
		case 4: printf("[SELECTION]: ");
			break;
		}
	}
	SetConsoleCursorPosition(Consolehandle, (COORD){ 48, 30 });
	choice = _getch() - 0x30;

	return choice;
}


/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void print_attributes(Info ships[])
{

	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w0ldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	int i = 0, j = 0;

	SetConsoleCursorPosition(Consolehandle, (COORD){ 6, 6 });
	printf("HUMAN");
	SetConsoleCursorPosition(Consolehandle, (COORD){ 90, 6 });
	printf("CPU");
	SetConsoleCursorPosition(Consolehandle, (COORD){ 28, 13 });
	printf("YOUR BOARD");
	SetConsoleCursorPosition(Consolehandle, (COORD){ 62, 13 });
	printf("CPU BOARD");


	//default
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;
	SetConsoleCursorPosition(Consolehandle, (COORD){ 3, 16 });
	printf("[SHIPS SUNK]");
	SetConsoleCursorPosition(Consolehandle, (COORD){ 87, 16 });
	printf("[SHIPS SUNK]");
	//human ships
	for (i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 5, 18 + i });
		switch (i)
		{

		case 0:
			if (ships[0].health == 0)
			{


				printf("SUNK");




			}
			else
			{


				SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("ccccc", ships[i].symbol);
				SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);


			}
			break;
		case 1:

			if (ships[1].health == 0)
			{
				printf("SUNK");

			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, 8 | FOREGROUND_INTENSITY);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			break;
		case 2:
			if (ships[2].health == 0)
			{
				printf("SUNK");

			}
			else
			{


				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			break;
		case 3:
			if (ships[3].health == 0)
			{
				printf("SUNK");

			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, CYAN | FOREGROUND_INTENSITY);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}
			}
			break;
		case 4:
			if (ships[4].health == 0)
			{
				printf("SUNK");

			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, 12 | FOREGROUND_INTENSITY);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			break;
		}
	}






	//computer ships
	for (i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 90, 18 + i });
		switch (i)
		{

		case 0:
			if (ships[0].computer_health == 0)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("c");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}

			}
			else
			{

				for (j = 0; j < ships[i].length; j++)
				{

					printf("?");
				}
			}
			break;
		case 1:

			if (ships[1].computer_health == 0)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, 8 | FOREGROUND_INTENSITY);
					printf("b");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}

			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{

					printf("?");
				}
			}
			break;
		case 2:
			if (ships[2].computer_health <= 0)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("r");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}

			}
			else
			{


				for (j = 0; j < ships[i].length; j++)
				{

					printf("?");
				}
			}
			break;
		case 3:
			if (ships[3].computer_health <= 0)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, CYAN | FOREGROUND_INTENSITY);
					printf("s", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}

			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{
					printf("?");
				}
			}
			break;
		case 4:
			if (ships[4].computer_health <= 0)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, 12 | FOREGROUND_INTENSITY);
					printf("d");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}

			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{

					printf("?");
				}
			}
			break;
		}
	}
	SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

}

/**
* Function name : faq()
* Date Created  : November 11, 2015
* Usage         : faq();
* Definition    : This function crates a faq to give information about the game to the user.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void faq()
{
	int i = 0;
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);

	for (i = 0; i < 5; i++)
	{

		SetConsoleCursorPosition(Consolehandle, (COORD){ 25, 26 + i });
		switch (i)
		{
		case 0: printf("This game was built by Kenneth Eversole with help");
			break;
		case 1: printf("from Sean Williams to understand windows.h");
			break;
		}
	}


}

//from Andy's code, modified to fit my code
/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void init_game_board(Boards board[][10])
{
	int row_index = 0, col_index = 0;

	// rows
	for (row_index = 0; row_index < ROWS; row_index++)
	{
		// columns
		for (col_index = 0; col_index < COLS; col_index++)
		{
			board[row_index][col_index].symbol = '~';
			board[row_index][col_index].position.row = row_index;
			board[row_index][col_index].position.column = col_index;
		}
	}
}

//From Andy's code, super modified though
/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void print_human_board(Boards board[][10])
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w0ldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	int row_index = 0, col_index = 0, i = 0;


	//default
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;


	// rows
	for (row_index = 0; row_index < ROWS; row_index++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 25, 16 });
		printf("0 1 2 3 4 5 6 7 8 9");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 22, 17 + row_index });

		i = 0;
		printf(" %d", i + row_index);
		//set color to blue
		SetConsoleTextAttribute(Consolehandle, 1 | FOREGROUND_INTENSITY);
		// columns
		for (col_index = 0; col_index < COLS; col_index++)
		{
			;
			switch (board[row_index][col_index].symbol)
			{
			case '~':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

				break;
			case 'c':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case 'd':
				SetConsoleTextAttribute(Consolehandle, 12 | FOREGROUND_INTENSITY);
				break;
			case 'r':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case 's':
				SetConsoleTextAttribute(Consolehandle, CYAN | FOREGROUND_INTENSITY);
				break;
			case 'b':
				SetConsoleTextAttribute(Consolehandle, 8 | FOREGROUND_INTENSITY);
				break;
			case 'X':
				SetConsoleTextAttribute(Consolehandle, 15);
				break;
			case '*':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			}


			printf(" %c", board[row_index][col_index].symbol);

			//printf(" %c", board[row_index][col_index].symbol);

			SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

		}

		putchar('\n');


	}

	SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void placeships(Boards board[][10], Info ships, Coordinate position, int direction)
{
	int i = 0;

	for (i = 0; i < ships.length; i++)
	{
		if (direction == HORIZONTAL)
		{

			board[position.row][position.column + i].symbol = ships.symbol;

		}
		else
		{
			board[position.row + i][position.column].symbol = ships.symbol;
		}
	}
}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void placeships_r(Boards board[][10], Info ships[])
{
	Coordinate position;
	int direction = 0;
	int i = 0;
	srand((unsigned int)time(NULL));
	for (i = 0; i < NUMSHIPS; i++)
	{

		do
		{
			direction = rand() % 2;
			position = generateposition(direction, ships[i].length);

		} while (!checkposition(board, position, direction, ships[i].length));

		placeships(board, ships[i], position, direction);
	}
}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
Coordinate generateposition(int direction, int length)
{
	Coordinate position;

	if (direction == HORIZONTAL)
	{
		position.row = rand() % 10;
		position.column = rand() % (10 - length + 1);
	}
	else
	{
		position.row = rand() % (10 - length + 1);
		position.column = rand() % 10;
	}

	return position;
}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void print_computer_board(Boards board[][10])
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD w0ldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	int row_index = 0, col_index = 0, i = 0;


	//default
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;



	// rows
	for (row_index = 0; row_index < ROWS; row_index++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 59, 16 });
		printf("0 1 2 3 4 5 6 7 8 9");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 56, 17 + row_index });

		i = 0;
		printf(" %d", i + row_index);
		//set color to blue
		SetConsoleTextAttribute(Consolehandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		// columns
		for (col_index = 0; col_index < COLS; col_index++)
		{

			switch (board[row_index][col_index].symbol)
			{
			case '*':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf(" *");
				break;
			case 'X':
				SetConsoleTextAttribute(Consolehandle, 15 | FOREGROUND_INTENSITY);
				printf(" X");
				break;
			case 'c':
			case 'd':
			case 'r':
			case 's':
			case 'b':
			case '~':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf(" ~");
				break;

			}
			SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);


		}
		putchar('\n');


	}

	SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
int checkposition(Boards board[][10], Coordinate position, int direction, int length)
{
	int i = 0;


	for (i = 0; i < length; i++)
	{

		if (board[position.row][position.column].symbol != '~')
		{
			return 0;
		}
		switch (direction)
		{
		case HORIZONTAL:
			position.column++;
			break;
		case VERTICAL:
			position.row++;
			break;
		}

	}

	return 1;


}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
int checkshot(Boards board[][10], Coordinate target, Info ships[])
{

	int shot = 2;
	switch (board[target.row][target.column].symbol)
	{
		/* miss */
	case '~':
		board[target.row][target.column].symbol = 'X';
		shot = 0;
		textbox(7);
		break;

		/* hit */
	case 'c':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		ships[0].computer_health--;
		textbox(6);
		break;
	case 'b':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		ships[1].computer_health--;
		textbox(6);
		break;
	case 'r':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		ships[2].computer_health--;
		textbox(6);
		break;
	case 's':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		ships[3].computer_health--;
		textbox(6);
		break;
	case 'd':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		ships[4].computer_health--;
		textbox(6);

		if (board[target.row][target.column].symbol != '~')
		{
			shot = -1;
		}

	}
	return shot;
}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
Coordinate findtarget(Boards board[][10])
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Consolehandle, (COORD){ 59, 17 });
	Coordinate target = { 0 };
	int direction = -1;
	int r = 17, c = 59;
	char k = '\0';
	int esc = 0;

	do
	{
		esc = 1;
		switch (k = _getch())
		{

		case 'w':
			if (r > 17)
			{
				SetConsoleCursorPosition(Consolehandle, (COORD){ c, r -= 1 });
				board[target.row -= 1][target.column];
			}

			break;
		case 's':
			if (r < 26)
			{
				SetConsoleCursorPosition(Consolehandle, (COORD){ c, r += 1 });
				board[target.row += 1][target.column];
			}
			break;
		case 'a':
			if (c > 59)
			{
				SetConsoleCursorPosition(Consolehandle, (COORD){ c -= 2, r });
				board[target.row][target.column -= 1];
			}
			break;
		case 'd':
			if (c < 77)
			{
				SetConsoleCursorPosition(Consolehandle, (COORD){ c += 2, r });
				board[target.row][target.column += 1];
			}
			break;
		case 'r':

			direction = 1;
			break;
		case 'e':
		case '\n':
			esc = 0;



			break;
		}





	} while (esc);
	return target;
}

/**
* Function name : placeships_m()
* Date Created  : November 18, 2015
* Usage         : placeships_m();
* Definition    : This function allows the player to manually place their ships.
*
* Pre-condition : A selection to manually place their ships.
* Post-condition: NONE
*/
void placeships_m(Boards board[][10], Info ships[])
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Consolehandle, (COORD){ 25, 17 });
	textbox(2);
	Coordinate position = { 0 };
	int flag = 0, i = 0, j = 1;
	int direction = 0;
	int r = 17, c = 25;

	char k = '\0';
	short esc = 1;

	for (flag = 0; flag < 5; flag++)
	{

		esc = 1;

		do
		{

			switch (k = _getch())
			{

			case 'w':

				if (r > 17)
				{
					SetConsoleCursorPosition(Consolehandle, (COORD){ c, r -= 1 });
					board[position.row -= 1][position.column];
				}

				break;
			case 's':
				if (r < 26)
				{
					SetConsoleCursorPosition(Consolehandle, (COORD){ c, r += 1 });
					board[position.row += 1][position.column];
				}
				break;
			case 'a':
				if (c > 25)
				{
					SetConsoleCursorPosition(Consolehandle, (COORD){ c -= 2, r });
					board[position.row][position.column -= 1];
				}
				break;
			case 'd':
				if (c < 42)
					SetConsoleCursorPosition(Consolehandle, (COORD){ c += 2, r });
				board[position.row][position.column += 1];
				break;
			case 'r':
				SetConsoleCursorPosition(Consolehandle, (COORD){ 25, 17 });
				direction = !direction;
				if (direction)
				{

					textbox(3);

				}
				else
				{

					textbox(4);

				}

				break;
			case 'e':


				if (checkposition(board, position, direction, ships[flag].length))
				{

					placeships(board, ships[flag], position, direction);
					esc = 0;
					print_human_board(board);
				}
				else
				{

					textbox(5);
				}


				break;
			}


		} while (esc);




	}
}

/**
* Function name : textbox ()
* Date Created  : November 18, 2015
* Usage         : textbox();
* Definition    : This function is what displays the chatter messages to the user.
*
* Pre-condition : input has to be 0 or greater
* Post-condition: NONE
*/
void textbox(int option)

{

	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);


	switch (option)
	{

	case 0:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 19, 41 });
		break;

	case 1:

		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 40, 35 });
		int i = 0;
		for (i = 0; i < 3; i++)
		{
			SetConsoleCursorPosition(Consolehandle, (COORD){ 40, 35 + i });
			switch (i)
			{

			case 0: printf("[1]. Manual Placement\n");
				break;
			case 1: printf("[2]. Random Placement\n");
				break;
			case 2: printf("[SELECTION]: ");
				break;
			}
		}

		break;

		//manual placement directions
	case 2:

		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 25, 35 });
		for (i = 0; i < 4; i++)
		{
			SetConsoleCursorPosition(Consolehandle, (COORD){ 25, 35 + i });
			switch (i)
			{
			case 0:
				printf("        [HOW TO PLACE SHIPS MANUALLY]");
				break;
			case 1:
				printf("[1] Use W,A,S,D to move around the board.");
				break;
			case 2:
				printf("[2] Then use the R key to rotate the ship.");
				break;
			case 3:
				printf("[3] Finally press the E key to to finalize the placement.");
				break;
			}
		}
		SetConsoleCursorPosition(Consolehandle, (COORD){ 25, 17 });

		break;
		//vertical
	case 3:

		clearscreen();

		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		for (i = 0; i < 3; i++)
		{
			SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 + i });
			switch (i)
			{
			case 0:
				printf("[SHIP ORIENTATION]");
				break;
			case 1:
				printf("");
				break;

			case 2:
				printf("    VERTICAL");
				break;


			}

		}

		break;
		//horizontail
	case 4:

		clearscreen();

		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		for (i = 0; i < 3; i++)
		{
			SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 + i });
			switch (i)
			{
			case 0:
				printf("[SHIP ORIENTATION]");
				break;
			case 1:
				printf("");
				break;

			case 2:
				printf("   HORIZONTIAL");
				break;


			}
		}

		break;
	case 5:

		clearscreen();

		SetConsoleCursorPosition(Consolehandle, (COORD){ 35, 35 });
		for (i = 0; i < 3; i++)
		{
			SetConsoleCursorPosition(Consolehandle, (COORD){ 35, 35 + i });
			switch (i)
			{
			case 0:
				printf("            [ERROR]");
				break;
			case 1:
				printf("");
				break;

			case 2:
				printf("PLEASE CHOOSE A NEW SPOT/DIRECTION");
				break;



			}
		}

		break;
	case 6:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[SHOT RESULT]");

		SetConsoleCursorPosition(Consolehandle, (COORD){ 48, 37 });
		printf("HIT!");
		break;
	case 7:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[SHOT RESULT]");

		SetConsoleCursorPosition(Consolehandle, (COORD){ 48, 37 });
		printf("MISS!");
		break;
		//carrier sunk
	case 8:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("COMPUTER'S CARRIER SUNK!");
		break;
		//battleship sunk
	case 9:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("COMPUTER'S BATTLESHIP SUNK!");
		break;
		//crusier sunk
	case 10:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("COMPUTER'S CRUSIER SUNK!");
		break;
		//submarine sunk
	case 11:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("COMPUTER'S SUBMARINE SUNK!");
		break;
		//destroyer sunk
	case 12:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("COMPUTER'S DESTROYER SUNK!");
		break;
		//computer hit
	case 13:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[COMPUTER'S SHOT]");

		SetConsoleCursorPosition(Consolehandle, (COORD){ 48, 37 });
		printf("HIT!");
		break;

		//computer miss
	case 14:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[COMPUTER'S SHOT]");

		SetConsoleCursorPosition(Consolehandle, (COORD){ 48, 37 });
		printf("MISS!");
		break;
		//human carrier sunk
	case 15:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("YOUR CARRIER HAS BEEN SUNK!");
		break;
		//human battleship sunk
	case 16:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("YOUR BATTLESHIP HAS BEEN SUNK!");
		break;
		//human crusier sunk
	case 17:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("YOUR CRUSIER HAS BEEN SUNK!");
		break;
		//human submarine sunk
	case 18:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 44, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("YOUR SUBMARINE HAS BEEN SUNK!");
		break;
		//human destroyer sunk
	case 19:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[SHIP DEAD]");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 37, 37 });
		printf("YOUR DESTROYER HAS BEEN SUNK!");
		break;
	case 20:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[YOUR TURN]");

		break;
	case 21:
		clearscreen();
		SetConsoleCursorPosition(Consolehandle, (COORD){ 43, 35 });
		printf("[COMPUTER'S TURN]");
		break;






	}

}

/**
* Function name : clearscreen ()
* Date Created  : November 18, 2015
* Usage         : clearscreen();
* Definition    : This function clears the textbox region of the board.
*
* Pre-condition : NONE
* Post-condition: NONE
*/
void clearscreen()
{
	TCHAR charc = { ' ' };
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cCharsWritten;
	DWORD dwConSize = 65;
	int num = 0;
	cCharsWritten = num;
	SetConsoleCursorPosition(Consolehandle, (COORD){ 19, 35 });
	FillConsoleOutputCharacter(Consolehandle, charc, dwConSize, (COORD){ 19, 35 }, &cCharsWritten);

	FillConsoleOutputCharacter(Consolehandle, charc, dwConSize, (COORD){ 19, 36 }, &cCharsWritten);

	FillConsoleOutputCharacter(Consolehandle, charc, dwConSize, (COORD){ 19, 37 }, &cCharsWritten);

	FillConsoleOutputCharacter(Consolehandle, charc, dwConSize, (COORD){ 19, 38 }, &cCharsWritten);

	FillConsoleOutputCharacter(Consolehandle, charc, dwConSize, (COORD){ 19, 39 }, &cCharsWritten);

	FillConsoleOutputCharacter(Consolehandle, charc, dwConSize, (COORD){ 19, 40 }, &cCharsWritten);

}

void computer_ai(Boards board[][10], Info ships[], Ai *data, Stats *game_stats_computer, int human_board_hits[][10], FILE *data_game)
{
	int	carrier_p[10][10] =
	{
		{ 2, 3, 4, 5, 6, 6, 5, 4, 3, 2 },
		{ 3, 4, 5, 6, 7, 7, 6, 5, 4, 3 },
		{ 4, 5, 6, 7, 8, 8, 7, 6, 5, 4 },
		{ 5, 6, 7, 8, 9, 9, 8, 7, 6, 5 },
		{ 6, 7, 8, 9, 10, 10, 9, 8, 7, 6 },
		{ 6, 7, 8, 9, 10, 10, 9, 8, 7, 6 },
		{ 5, 6, 7, 8, 9, 9, 8, 7, 6, 5 },
		{ 4, 5, 6, 7, 8, 8, 7, 6, 5, 4 },
		{ 3, 4, 5, 6, 7, 7, 6, 5, 4, 3 },
		{ 2, 3, 4, 5, 6, 6, 5, 4, 3, 2 }, };


	int battleship_p[10][10] =
	{
		{ 2, 3, 4, 5, 5, 5, 5, 4, 3, 2 },
		{ 3, 4, 5, 5, 6, 6, 5, 5, 4, 3 },
		{ 4, 5, 5, 6, 7, 7, 6, 5, 5, 4 },
		{ 5, 5, 6, 7, 8, 8, 7, 6, 5, 5 },
		{ 5, 6, 7, 8, 8, 8, 8, 7, 6, 5 },
		{ 5, 6, 7, 8, 8, 8, 8, 7, 6, 5 },
		{ 5, 5, 6, 7, 8, 8, 7, 6, 5, 5 },
		{ 4, 5, 5, 6, 7, 7, 6, 5, 5, 4 },
		{ 3, 4, 5, 5, 6, 6, 5, 5, 4, 3 },
		{ 2, 3, 4, 5, 5, 5, 5, 4, 3, 2 }, };

	int sub_p[10][10] =
	{
		{ 2, 3, 4, 4, 4, 4, 4, 4, 3, 2 },
		{ 3, 4, 5, 5, 5, 5, 5, 5, 4, 3 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 3, 4, 5, 5, 5, 5, 5, 5, 4, 3 },
		{ 2, 3, 4, 4, 4, 4, 4, 4, 3, 2 }, };

	int cruiser_p[10][10] =
	{
		{ 2, 3, 4, 4, 4, 4, 4, 4, 3, 2 },
		{ 3, 4, 5, 5, 5, 5, 5, 5, 4, 3 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 4, 5, 6, 6, 6, 6, 6, 6, 5, 4 },
		{ 3, 4, 5, 5, 5, 5, 5, 5, 4, 3 },
		{ 2, 3, 4, 4, 4, 4, 4, 4, 3, 2 }, };


	int destroyer_p[10][10] =
	{
		{ 2, 3, 3, 3, 3, 3, 3, 3, 3, 2 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 3, 4, 4, 4, 4, 4, 4, 4, 4, 3 },
		{ 2, 3, 3, 3, 3, 3, 3, 3, 3, 2 }, };



	int total_p[10][10] = { 0 };
	int h = 0;
	int i = 0;
	int j = 0;
	int m = 0;
	int l = 0;
	int k = 0;
	int z = 0;
	int p = 0;
	int exit = 0;
	int threshhold = 0;
	int target_location = 0;
	int fire = 0;
	int dtargets_index = 0;
	int dtargets_size = 0;
	int does_exist = 0;



	//used to find total amount of a probability
	int hist[35] = { 0 };

	//the number of targets
	int found = 0;

	COORD targets[100] = { -1, -1 };

	if (data->seek_or_destroy == 0)
	{

		//think mode
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{

				//what are these again?
				//what is the problem going on here
				total_p[i][j] = ((is_dead(Carrier, ships, game_stats_computer) == 1 ? 0 : carrier_p[i][j])) +
					((is_dead(Battleship, ships, game_stats_computer) == 1 ? 0 : battleship_p[i][j])) +
					((is_dead(Cruiser, ships, game_stats_computer) == 1 ? 0 : cruiser_p[i][j])) +
					((is_dead(Submarine, ships, game_stats_computer) == 1 ? 0 : sub_p[i][j])) +
					((is_dead(Destroyer, ships, game_stats_computer) == 1 ? 0 : destroyer_p[i][j]));

				//if miss it decrements the field
				if (human_board_hits[i][j] == 0)
				{
					for (k = 0; k < 5; k++)
					{
						for (l = (j - ships[k].length < 0 ? 0 : j - ships[k].length); l < (j + ships[k].length>9 ? 9 - ships[k].length : 0); l++)
						{
							for (m = 0; m < ships[k].length; m++)
							{
								total_p[i][j - ships[k].length]--;
							}
						}
						for (l = (i - ships[k].length < 0 ? 0 : i - ships[k].length); l < (i + ships[k].length>9 ? 9 - ships[k].length : 0); l++)
						{
							for (m = 0; m < ships[k].length; m++)
							{
								total_p[i - ships[k].length][j]--;
							}
						}
					}
				}
			}
		}

		//find the amount of targets
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (total_p[i][j] < 0)
				{
					total_p[i][j] = 0;
				}
				hist[total_p[i][j]]++;
			}


		}

		for (h = 34; exit == 0 && h > 0; h--)
		{
			found += hist[h];
			if (found >= 15)
			{
				exit = 1;
			}

		}

		threshhold = h;
		found = 0;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (total_p[i][j] >= threshhold)
				{
					//Find an attack point for liberty prime mode.
					targets[found] = (COORD){ i, j };
					found++;
				}
			}
		}



		//ai fire
		do
		{
			target_location = rand() % found;
			checkshot_comp(board, targets[target_location], human_board_hits, ships);

		} while (checkshot_comp(board, targets[target_location], human_board_hits, ships) == 2);

		//prime mode
		if (ai_first_shot(board, targets[target_location], game_stats_computer, human_board_hits, ships, data_game))
		{
			//set dindex to 0
			dtargets_index = 0;
			//determines the base attack point
			data->seek_or_destroy = 1;

			//North
			if ((targets[target_location].Y >= 0) && (human_board_hits[targets[target_location].Y - 1][targets[target_location].X] == -1))
			{
				data->DTargets[dtargets_index].Y = targets[target_location].Y - 1;
				data->DTargets[dtargets_index++].X = targets[target_location].X;
			}
			//South
			if ((targets[target_location].Y <= 9) && (human_board_hits[targets[target_location].Y + 1][targets[target_location].X] == -1))
			{
				data->DTargets[dtargets_index].Y = targets[target_location].Y + 1;
				data->DTargets[dtargets_index++].X = targets[target_location].X;
			}
			//West
			if ((targets[target_location].X >= 0) && (human_board_hits[targets[target_location].Y][targets[target_location].X - 1] == -1))
			{
				data->DTargets[dtargets_index].Y = targets[target_location].Y;
				data->DTargets[dtargets_index++].X = targets[target_location].X - 1;
			}
			//East
			if ((targets[target_location].X <= 9) && (human_board_hits[targets[target_location].Y][targets[target_location].X + 1] == -1))
			{
				data->DTargets[dtargets_index].Y = targets[target_location].Y;
				data->DTargets[dtargets_index++].X = targets[target_location].X + 1;
			}


		}
		else
		{
			data->seek_or_destroy = 0;
			board[targets[target_location].Y][targets[target_location].X].symbol = 'X';
			human_board_hits[targets[target_location].Y][targets[target_location].X] = 0;

		}






	}



	//target has been found...time to kill(LIBERTY PRIME MODE)
	else
	{
		do
		{
			target_location = rand() % 5;
		} while (data->DTargets[target_location].X == -1);

		if (ai_fire(board, data, target_location, game_stats_computer, human_board_hits, data_game, ships))
		{
			//determines the number of elements that represent vaild targets
			while (data->DTargets[dtargets_size].X != -1)
			{

				dtargets_size++;
			}

			//North
			if ((data->DTargets[target_location].Y >= 0) && (human_board_hits[data->DTargets[target_location].Y - 1][data->DTargets[target_location].X] == -1))
			{

				//shifts data->DTargets over to put a free spot in the front.
				does_exist = 0;
				for (z = 0; z < dtargets_size; z++)
				{
					if (((data->DTargets[z].Y -1) == data->DTargets[target_location].Y - 1) && (data->DTargets[z].X == data->DTargets[target_location].X))
					{
						does_exist = 1;
					}
				}


				if (!does_exist)
				{
					for (z = dtargets_size; z > 0; z--)
					{

						data->DTargets[z] = data->DTargets[z - 1];

					}
					
						data->DTargets[0].Y = data->DTargets[target_location].Y - 1;
						data->DTargets[0].X = data->DTargets[target_location].X;
						dtargets_size++;
					
				}
			}
			//South
			if ((data->DTargets[target_location].Y <= 9) && (human_board_hits[data->DTargets[target_location].Y + 1][data->DTargets[target_location].X] == -1))
			{
				//shifts data->DTargets over to put a free spot in the front.
				does_exist = 0;
				for (z = 0; z < dtargets_size; z++)
				{
					if (((data->DTargets[z].Y + 1) == data->DTargets[target_location].Y + 1) && (data->DTargets[z].X == data->DTargets[target_location].X))
					{
						does_exist = 1;
					}
				}

				if (!does_exist)
				{
					for (z = dtargets_size; z > 0; z--)
					{

						data->DTargets[z] = data->DTargets[z - 1];

					}
					
						data->DTargets[0].Y = data->DTargets[target_location].Y + 1;
						data->DTargets[0].X = data->DTargets[target_location].X;
						dtargets_size++;
					
				}
			}
			//West
			if ((data->DTargets[target_location].X >= 0) && (human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X - 1] == -1))
			{
				//shifts data->DTargets over to put a free spot in the front.
				does_exist = 0;
				for (z = 0; z < dtargets_size; z++)
				{
					if ((data->DTargets[z].Y == data->DTargets[target_location].Y) && ((data->DTargets[z].X - 1) == data->DTargets[target_location].X - 1))
					{
						does_exist = 1;
					}
				}


				if (!does_exist)
				{
					for (z = dtargets_size; z > 0; z--)
					{

						data->DTargets[z] = data->DTargets[z - 1];

					}

					
						data->DTargets[0].Y = data->DTargets[target_location].Y;
						data->DTargets[0].X = data->DTargets[target_location].X - 1;
						dtargets_size++;
					
				}
			}
			//East
			if ((data->DTargets[target_location].X <= 9) && (human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X + 1] == -1))
			{
				//shifts data->DTargets over to put a free spot in the front.
				does_exist = 0;
				for (z = 0; z < dtargets_size; z++)
				{
					if ((data->DTargets[z].Y == data->DTargets[target_location].Y) && ((data->DTargets[z].X + 1)== data->DTargets[target_location].X + 1))
					{
						does_exist = 1;
					}
				}


				if (!does_exist)
				{
					for (z = dtargets_size; z > 0; z--)
					{

						data->DTargets[z] = data->DTargets[z - 1];

					}
					
						data->DTargets[0].Y = data->DTargets[target_location].Y;
						data->DTargets[0].X = data->DTargets[target_location].X + 1;
						dtargets_size++;
					
				}
			}


		}




		//checks if there is still a chance to hit a ship. If yes it will continue to kill (LIBERTY PRIME!)
		is_dead(5, ships, game_stats_computer);
		if (game_stats_computer->numHits == 0)
		{
			data->seek_or_destroy = 0;
		}
		else
		{
			data->seek_or_destroy = 1;
		}

	}
}

/*
This function does a whole lot of useful stuff
1. it fires at a target
2. Determines the out come of that shot
3. If it is a hit, it will change values accordingly
4. Writes to the file

*/

int ai_fire(Boards board[][10], Ai *data, int target_location, Stats *game_stats_computer, int human_board_hits[][10], FILE *data_game, Info ships[])
{




	int shot = 2;
	
		switch (board[data->DTargets[target_location].Y][data->DTargets[target_location].X].symbol)
		{
			/* miss */
		case '~':
			shot = 0;
			human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X] = 0;
			fprintf(data_game, "MISS - COMPUTER\n", &data_game);
			board[data->DTargets[target_location].Y][data->DTargets[target_location].X].symbol = 'X';
			textbox(14);
			break;


			/* hit */
		case 'c':
			game_stats_computer->numHits++;
			human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X] = 1;
			fprintf(data_game, "HIT - COMPUTER\n", &data_game);
			board[data->DTargets[target_location].Y][data->DTargets[target_location].X].symbol = '*';
			ships[0].health--;
			shot = 1;
			textbox(13);


			break;
		case 'b':
			game_stats_computer->numHits++;
			human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X] = 1;
			fprintf(data_game, "HIT - COMPUTER\n", &data_game);
			board[data->DTargets[target_location].Y][data->DTargets[target_location].X].symbol = '*';
			ships[1].health--;
			shot = 1;
			textbox(13);

			break;

		case 'r':
			game_stats_computer->numHits++;
			human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X] = 1;
			fprintf(data_game, "HIT - COMPUTER\n", &data_game);
			board[data->DTargets[target_location].Y][data->DTargets[target_location].X].symbol = '*';
			ships[2].health--;
			shot = 1;
			textbox(13);

			break;

		case 's':
			game_stats_computer->numHits++;
			human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X] = 1;
			fprintf(data_game, "HIT - COMPUTER\n", &data_game);
			board[data->DTargets[target_location].Y][data->DTargets[target_location].X].symbol = '*';
			ships[3].health--;
			shot = 1;
			textbox(13);
			break;

		case 'd':
			game_stats_computer->numHits++;
			human_board_hits[data->DTargets[target_location].Y][data->DTargets[target_location].X] = 1;
			fprintf(data_game, "HIT - COMPUTER\n", &data_game);
			board[data->DTargets[target_location].Y][data->DTargets[target_location].X].symbol = '*';
			ships[4].health--;
			shot = 1;
			textbox(13);
			break;

		case 'X':
		case '*':
		
			break;
		}

	

	return shot;
}


//This determines if a ship is dead

int is_dead(int option, Info ships[], Stats *game_stats_computer)
{
	int i = 0;

	switch (option)
	{
	case Carrier:
		if (ships[0].health == 0)
		{

			game_stats_computer->numHits -= ships[0].length;
			return 1;

		}
		break;
	case Battleship:
		if (ships[1].health == 0)
		{

			game_stats_computer->numHits -= ships[1].length;
			return 1;

		}
		break;
	case Cruiser:
		if (ships[2].health == 0)
		{

			game_stats_computer->numHits -= ships[2].length;
			return 1;

		}
		break;
	case Submarine:
		if (ships[3].health == 0)
		{

			game_stats_computer->numHits -= ships[3].length;
			return 1;

		}
		break;
	case Destroyer:
		if (ships[4].health == 0)
		{

			game_stats_computer->numHits -= ships[4].length;
			return 1;

		}
		break;
	case 5:

		for (option = 0; option < NUMSHIPS; option++)
		{
			switch (option)
			{
			case 0:
				if (ships[0].health == 0)
				{

					game_stats_computer->numHits = game_stats_computer->numHits - ships[0].length;
					return 1;

				}
				break;
			case 1:
				if (ships[1].health == 0)
				{
					game_stats_computer->numHits = game_stats_computer->numHits - ships[1].length;
					return 1;

				}
				break;
			case 2:
				if (ships[2].health == 0)
				{

					game_stats_computer->numHits = game_stats_computer->numHits - ships[2].length;
					return 1;

				}
				break;
			case 3:
				if (ships[3].health == 0)
				{

					game_stats_computer->numHits = game_stats_computer->numHits - ships[3].length;
					return 1;

				}
				break;
			case 4:
				if (ships[4].health == 0)
				{

					game_stats_computer->numHits = game_stats_computer->numHits - ships[4].length;
					return 1;

				}
				break;
			}
		}
	}
	return 0;
}

void loadingbar()
{
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);


	int h = 0;
	for (h = 0; h < 10000; h++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 40, 35 });
		printf("Loading Boards");
		SetConsoleCursorPosition(Consolehandle, (COORD){ 55, 35 });
		printf("%d%%", h / 100);


	}
	clearscreen();

}

int checkshot_comp(Boards board[][10], COORD targets, int human_board_hits[][10], Info ships[])
{




	int shot = 2;
	switch (board[targets.Y][targets.X].symbol)
	{
		/* miss */
	case '~':
		shot = 0;



		break;


		/* hit */
	case 'c':

		shot = 1;


		break;
	case 'b':

		shot = 1;

		break;

	case 'r':

		shot = 1;

		break;

	case 's':

		shot = 1;

		break;

	case 'd':


		shot = 1;

		break;

	case 'X':
	case '*':
	default:

		break;
	}
	return shot;
}

int ai_first_shot(Boards board[][10], COORD targets, Stats *game_stats_computer, int human_board_hits[][10], Info ships[], FILE *data_game)
{

	int shot = 0;

	switch (board[targets.Y][targets.X].symbol)
	{
		/* miss */
	case '~':
		shot = 0;

		human_board_hits[targets.Y][targets.X] = 0;
		fprintf(data_game, "MISS - COMPUTER\n", &data_game);
		board[targets.Y][targets.X].symbol = 'X';
		textbox(14);
		break;


		/* hit */
	case 'c':
		game_stats_computer->numHits++;
		human_board_hits[targets.Y][targets.X] = 1;
		fprintf(data_game, "HIT - COMPUTER\n", &data_game);
		ships[0].health--;
		board[targets.Y][targets.X].symbol = '*';
		shot = 1;
		textbox(13);


		break;
	case 'b':
		game_stats_computer->numHits++;
		human_board_hits[targets.Y][targets.X] = 1;
		fprintf(data_game, "HIT - COMPUTER\n", &data_game);
		board[targets.Y][targets.X].symbol = '*';
		ships[1].health--;
		shot = 1;
		textbox(13);

		break;

	case 'r':
		game_stats_computer->numHits++;
		human_board_hits[targets.Y][targets.X] = 1;
		fprintf(data_game, "HIT - COMPUTER\n", &data_game);
		board[targets.Y][targets.X].symbol = '*';
		ships[2].health--;
		shot = 1;
		textbox(13);

		break;

	case 's':
		game_stats_computer->numHits++;
		human_board_hits[targets.Y][targets.X] = 1;
		fprintf(data_game, "HIT - COMPUTER\n", &data_game);
		board[targets.Y][targets.X].symbol = '*';
		ships[3].health--;
		shot = 1;
		textbox(13);
		break;

	case 'd':
		game_stats_computer->numHits++;
		ships[4].health--;
		human_board_hits[targets.Y][targets.X] = 1;
		fprintf(data_game, "HIT - COMPUTER\n", &data_game);
		board[targets.Y][targets.X].symbol = '*';
		shot = 1;
		textbox(13);
		break;

	case 'X':
	case '*':




		break;
	}


	return shot;
}