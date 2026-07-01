#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 15
#define COLS 15
#define MAX_PLAYERS 3

char map[ROWS][COLS];
int hiddenTrap[ROWS][COLS];

int main()
{
    srand(time(NULL));

    gameMenu();

    initializeMap();

    placePlayers();

    printMap();

    return 0;
}

