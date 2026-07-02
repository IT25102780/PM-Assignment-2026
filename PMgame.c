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

void initializeMap();
void printMap();
void placePlayers();
void gameMenu();

int main()
{
    srand(time(NULL));

    gameMenu();

    initializeMap();

    placePlayers();

    printMap();

    return 0;
}

void gameMenu()
{
    int choice;

    printf("\n====================================\n");
    printf("   QUEST FOR THE LOST TREASURE\n");
    printf("====================================\n");

    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf("\nStarting New Game...\n");
            break;

        case 2:
            printf("\nLoading Game...\n");
            break;

        case 3:
            printf("\nThank you for playing.\n");
            exit(0);

        default:
            printf("\nInvalid choice.\n");
            exit(0);
    }

    printf("\nEnter number of players (1-3): ");
    scanf("%d", &playerCount);

    if(playerCount < 1 || playerCount > 3)
    {
        printf("Invalid number of players.\n");
        exit(0);
    }

    for(int i = 0; i < playerCount; i++)
    {
        printf("Enter Player %d Name: ", i + 1);
        scanf("%s", players[i].name);

        players[i].score = 0;
        players[i].health = 100;
        players[i].keys = 0;
        players[i].symbol = '1' + i;
    }
}

