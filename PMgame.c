#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 15
#define COLS 15
#define MAX_PLAYERS 3

char map[ROWS][COLS];
int hiddenTrap[ROWS][COLS];

typedef struct
{
    char name[30];
    int row;
    int col;
    int score;
    int health;
    int keys;
    char symbol;

} Player;

Player players[MAX_PLAYERS];
int playerCount;

int main()
{
    srand(time(NULL));

    gameMenu();

    initializeMap();

    placePlayers();

    printMap();

    return 0;
}

