/*==============================================================================
| Filename: PA6.h
| Programmer: Kenneth Eversole
| Class: Cpts 121 Fall 2015 Lab Section 10
| Programming Assignment 6: Basic Game of Battleship
| Date: November 1, 2015
+------------------------------------------------------------------------------
| Description: This contains the structs, libraries, defined constants
|	and prototypes for the program to run.
==============================================================================*/

//guard code
#ifndef PA6_H
#define PA6_h

//libraries 
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include <conio.h>


//defined constants
#define _CRT_SECURE_NO_WARNINGS
#define HOW_TO_PLAY 1
#define START_NEW_GAME 2
#define FAQ 3
#define EXIT_GAME 4


//Useful stuff
#define ROWS 10
#define COLS 10
#define NUMSHIPS 5


//arrow keys
#define key_left 0x25
#define key_up  0x26
#define key_right  0x27
#define key_down  0x28
#define key_escape  0x1B

//ships
#define Carrier 0
#define Battleship 1
#define Cruiser 2
#define Submarine 3
#define Destroyer 4


//colors
#define MAGENTA 5
#define CYAN 3
#define DARKGRAY 8
//boolean
#define TRUE 1
#define FALSE 0

typedef struct info
{
	char   symbol;
	short  length;
	short  health;
	short computer_health;
	char   *name;

} Info;

typedef struct stats
{
	int	numHits;
	int	numMisses;
} Stats;

typedef struct coordinate 
{
	int row;
	int column;
} Coordinate;

typedef struct boards 
{
	char       symbol;
	Coordinate position;
} Boards;


//AI thoughts 
typedef  struct ai
{
	int seek_or_destroy;
	COORD DTargets[101];
}Ai;

typedef enum rotation
{
	HORIZONTAL,
	VERTICAL

} Rotation;


//prototypes 
int checkposition(Boards board[][10], Coordinate position, int direction, int length);
int checkshot(Boards board[][10], Coordinate target, Info ships[]);
int game_menu();
void print_title();
void game_menu_board();
void game_play_board();
void game_rules();
void print_attributes(Info ships[]);
void faq();
void battleship();
void print_human_board(Boards board[][10]);
void print_computer_board(Boards board[][10]);
void init_game_board(Boards board[][10]);
void placeships(Boards board[][10], Info ships, Coordinate  position, int direction);
void placeships_r(Boards board[][10], Info ships[]);
void placeships_m(Boards board[][10], Info ships[]);
void textbox(int option);
void clearscreen(); 
void computer_ai(Boards board[][10], Info ships[], Ai *data, Stats *game_stats_computer, int human_board_hits[][10], FILE *data_game);
int is_dead(int option, Info ships[], Stats *game_stats_computer);
int checkshot_comp(Boards board[][10], COORD targets,  int human_board_hits[][10], Info ships[]);
int ai_fire(Boards board[][10], Ai *data, int target_location, Stats *game_stats_computer, int human_board_hits[][10], FILE *data_game, Info ships[]);
int random(int min, int max);

int ai_first_shot(Boards board[][10], COORD targets, Stats *game_stats_computer, int human_board_hits[][10], Info ships[], FILE *data_game);

void loadingbar();
//help found online
Coordinate generateposition(int direction, int length);
Coordinate findtarget(Boards board[][10]);
Coordinate findcoord(Boards board[][10]);

//structs and handles
HANDLE wHnd; /* write (output) handle */
HANDLE rHnd; /* read (input handle */

//guard code
#endif PA6_H