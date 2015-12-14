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
	HANDLE Consolehandle = GetStdHandle(STD_OUTPUT_HANDLE);
	FILE *data_game = NULL;
	Boards human_board[10][10];
	Boards computer_board[10][10];



	Coordinate target;
	Coordinate target_comp = { 0 };

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




	int computer_health[5] = { 0, 0, 0, 0, 0 };
	int human_health[5] = { 0, 0, 0, 0, 0 };
	int is_ship_hit = 0;

	int	totalship_health_human = 17;
	int totalship_health_computer = 17;
	int player = 0;
	int i = 0, ch = 0;
	int shot = 0;
	int option = 0;
	int end_game = 1;


	Info ships[NUMSHIPS] = { { 'c', 5, "Carrier" },
	{ 'b', 4, "Battleship" },
	{ 'r', 3, "Cruiser" },
	{ 's', 3, "Submarine" },
	{ 'd', 2, "Destroyer" } };



	Stats game_stats_human = { 0, 0 };
	Stats game_stats_computer = { 0, 0 };


	game_play_board();
	print_attributes(ships, human_health, computer_health);
	print_title();

	init_game_board(human_board);
	init_game_board(computer_board);

	print_human_board(human_board);
	print_computer_board(computer_board);

	data_game = fopen("data.dat", "w");



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
	print_attributes(ships, human_health, computer_health);
	print_title();

	printf("\n");


	loadingbar();

	placeships_r(computer_board, ships);


	print_human_board(human_board);
	print_computer_board(computer_board);


	player = rand() % 2;

	do
	{

		switch (player)
		{
			//human turn
		case 0:

		{

			target = findtarget(computer_board);
			shot = checkshot(computer_board, target, computer_health);
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

				print_attributes(ships, human_health, computer_health);
			}
		} while (shot == -1);

		print_computer_board(computer_board);
		player = !player;

		break;

		case 1:


			print_attributes(ships, human_health, computer_health);
			print_human_board(human_board);
			print_computer_board(computer_board);

			//AI
			computer_ai(target_comp, human_board, data_game, carrier_p, battleship_p, sub_p, cruiser_p, destroyer_p, is_ship_hit, human_health);
			



			system("pause");

			player = !player;
			break;
		}

		if (totalship_health_computer == 0)
		{

			end_game = 0;
		}
		if (totalship_health_human == 0)
		{
			end_game = 0;

		}
	} while (end_game);


	system("cls");

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
		case 1: printf("[2]. Start a game of BattleShip\n");
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
void print_attributes(Info ships[], int human_health[], int computer_health[])
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
	printf("HUMAN BOARD");
	SetConsoleCursorPosition(Consolehandle, (COORD){ 62, 13 });
	printf("CPU BOARD");


	//default
	GetConsoleScreenBufferInfo(Consolehandle, &csbiInfo);
	w0ldColorAttrs = csbiInfo.wAttributes;


	//human ships
	for (i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(Consolehandle, (COORD){ 5, 18 + i });
		switch (i)
		{

		case 0:
			if (human_health[0] == 5)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_RED);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			else
			{

				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			break;
		case 1:

			if (human_health[1] == 4)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_RED);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			break;
		case 2:
			if (human_health[2] == 3)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, CYAN);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
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
		case 3:
			if (human_health[3] == 3)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
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
		case 4:
			if (human_health[4] == 2)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, MAGENTA);
					printf("%c", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);
				}
			}
			else
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, MAGENTA | FOREGROUND_INTENSITY);
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
			if (computer_health[0] == 5)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("c");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}
				textbox(8);
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

			if (computer_health[1] == 4)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf("b");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}
				textbox(9);
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
			if (computer_health[2] == 3)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, CYAN | FOREGROUND_INTENSITY);
					printf("r");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}
				textbox(10);
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
			if (computer_health[3] == 3)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("s", ships[i].symbol);
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}
				textbox(11);
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
			if (computer_health[4] == 2)
			{
				for (j = 0; j < ships[i].length; j++)
				{
					SetConsoleTextAttribute(Consolehandle, MAGENTA | FOREGROUND_INTENSITY);
					printf("d");
					SetConsoleTextAttribute(Consolehandle, w0ldColorAttrs);

				}
				textbox(12);
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
				SetConsoleTextAttribute(Consolehandle, MAGENTA | FOREGROUND_INTENSITY);
				break;
			case 'r':
				SetConsoleTextAttribute(Consolehandle, CYAN | FOREGROUND_INTENSITY);
				break;
			case 's':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case 'b':
				SetConsoleTextAttribute(Consolehandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			}

			printf(" %c", board[row_index][col_index].symbol);

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
				SetConsoleTextAttribute(Consolehandle, DARKGRAY | FOREGROUND_INTENSITY);
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
int checkshot(Boards board[][10], Coordinate target, int computer_health[])
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
		computer_health[0] += 1;
		textbox(6);
		break;
	case 'b':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		computer_health[1] += 1;
		textbox(6);
		break;
	case 'r':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		computer_health[2] += 1;
		textbox(6);
		break;
	case 's':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		computer_health[3] += 1;
		textbox(6);
		break;
	case 'd':
		board[target.row][target.column].symbol = '*';
		shot = 1;
		computer_health[4] += 1;
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



void computer_ai(Coordinate target_comp, Boards board[][10], FILE *data_game, int	carrier_p[][10], int battleship_p[][10], int sub_p[10][10], int cruiser_p[][10], int destroyer_p[][10], int is_ship_hit, int human_health[])
{

	int total_p[10][10] = { 0, 0 };
	int i = 0, j = 0, r = 0, c = 0;
	int target_value = 0;
	int highest_value = 0;
	int temp_target = 0;
	int flag = 1;
	int shot = 2;
	int targetflag = 1;
	int escape = 1;


	if (!is_ship_hit || escape)
	{
		//finds the total prob across all shiptypes
		for (i = 0; i < 10; i++)
		{

			for (j = 0; j < 10; j++)
			{

				total_p[i][j] = (destroyer_p[i][j] + cruiser_p[i][j] + sub_p[i][j] + battleship_p[i][j] + carrier_p[i][j]);

			}
		}

		//finds the highest value in the array minus 1
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (total_p[i][j] > highest_value)
				{
					highest_value = total_p[i][j] - 1;
				}
			}
		}


		//finds a random target from the array within those possible values
		do
		{
			do
			{
				c = rand() % 9;
				r = rand() % 9;
				target_value = total_p[r][c];

				if (target_value >= highest_value)
				{
					targetflag = 0;
				}

			} while (targetflag);

			target_comp.row = r;
			target_comp.column = c;


			shot = checkshot_comp(board, target_comp, human_health);
			if (shot == 0 || shot == 1)
			{

				flag = 0;
			}

		} while (flag);


		//this will be the action part. I.E. if the shot misses it will subtract everything by one in the sqaures vertically and horizontally from the shot.
		//miss
		if (shot == 0)
		{

			//carrier
			carrier_p[r][c] = 0;
			carrier_p[r + 1][c] -= 1;
			carrier_p[r - 1][c] -= 1;
			carrier_p[r][c + 1] -= 1;
			carrier_p[r][c - 1] -= 1;

			//battleship
			battleship_p[r][c] = 0;
			battleship_p[r + 1][c] -= 1;
			battleship_p[r - 1][c] -= 1;
			battleship_p[r][c + 1] -= 1;
			battleship_p[r][c + 1] -= 1;

			//sub
			sub_p[r][c] = 0;
			sub_p[r + 1][c] -= 1;
			sub_p[r - 1][c] -= 1;
			sub_p[r][c + 1] -= 1;
			sub_p[r][c - 1] -= 1;



			//crusier
			cruiser_p[r][c] = 0;
			cruiser_p[r + 1][c] -= 1;
			cruiser_p[r - 1][c] -= 1;
			cruiser_p[r][c + 1] -= 1;
			cruiser_p[r][c - 1] -= 1;

			//destroyer
			destroyer_p[r][c] = 0;
			destroyer_p[r + 1][c] -= 1;
			destroyer_p[r - 1][c] -= 1;
			destroyer_p[r][c + 1] -= 1;
			destroyer_p[r][c - 1] -= 1;

			escape = 0;

		}

		if (shot == 1)
		{
			is_ship_hit = 1;
		}

		escape = 0;
	
		
	}
	
	computer_ai_hit(target_comp, board, data_game, is_ship_hit, human_health, r, c);
	


}

int checkshot_comp(Boards board[][10], Coordinate target_comp, int human_health[])
{
	int shot = 2;
	switch (board[target_comp.row][target_comp.column].symbol)
	{
		/* miss */
	case '~':
		shot = 0;
		break;

		/* hit */
	case 'c':

		shot = 1;
		human_health[0] += 1;

		break;
	case 'b':

		shot = 1;
		human_health[1] += 1;

		break;
	case 'r':
		human_health[2] += 1;
		shot = 1;

		break;
	case 's':
		human_health[3] += 1;
		shot = 1;


		break;
	case 'd':
		human_health[4] += 1;
		shot = 1;


		break;
	case 'X':
	case '*':
	default:



		break;
	}
	return shot;
}

void computer_ai_hit(Coordinate target_comp, Boards board[][10], FILE *data_game, int is_ship_hit, int human_health[], int r, int c)
{
	int temp_target = 0;
	if (is_ship_hit == 1)
	{

		//checks if ship is dead
		switch (board[r][c].symbol)
		{
			/* hit */
		case 'c':


			if (human_health[0] == 5);
			{
				is_ship_hit = 0;
			}
			break;
		case 'b':

			if (human_health[1] == 4);
			{
				is_ship_hit = 0;
			}
			break;
		case 'r':


			if (human_health[2] == 3);
			{
				is_ship_hit = 0;
			}
			break;
		case 's':


			if (human_health[3] == 3);
			{
				is_ship_hit = 0;
			}
			break;
		case 'd':

			if (human_health[4] == 2);
			{
				is_ship_hit = 0;
			}

		}


		//finds next part of the ship
		temp_target = rand() % 3;
		switch (temp_target)
		{


		case 0:
			target_comp.row = r + 1;
			target_comp.column = c;

			break;
		case 1:

			target_comp.row = r - 1;
			target_comp.column = c;
			break;
		case 2:

			target_comp.row = r;
			target_comp.column = c + 1;
			break;
		case 3:
			target_comp.row = r;
			target_comp.column = c - 1;
			break;
		}
		is_ship_hit = checkshot_comp(board, target_comp, human_health);

	}

	


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