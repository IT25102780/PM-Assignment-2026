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
void initializeMap()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            if(i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1)
            {
                map[i][j] = '#';
            }
            else
            {
                map[i][j] = ' ';
            }

            hiddenTrap[i][j] = 0;
        }
    }
}

void placePlayers()
{
    players[0].row = 1;
    players[0].col = 1;
    map[1][1] = players[0].symbol;

    if(playerCount >= 2)
    {
        players[1].row = 13;
        players[1].col = 13;
        map[13][13] = players[1].symbol;
    }

    if(playerCount == 3)
    {
        players[2].row = 1;
        players[2].col = 13;
        map[1][13] = players[2].symbol;
    }
}

void printMap()
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c ", map[i][j]);
        }

        printf("\n");
    }

    printf("\n");

    for(int i = 0; i < playerCount; i++)
    {
        printf("Player %d (%s)\n", i + 1, players[i].name);
        printf("Health : %d\n", players[i].health);
        printf("Score  : %d\n", players[i].score);
        printf("Keys   : %d\n\n", players[i].keys);
    }
}

