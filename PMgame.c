#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 15

#define WALLS 30
#define TREASURES 12
#define HEALTHPACKS 5
#define KEYS 3
#define DOORS 3
#define TRAPS 10

typedef struct
{
    char name[50];
    int row;
    int col;
    int score;
    int health;
    int keys;
    char symbol;
} Player;

char map[SIZE][SIZE];
int hiddenTrap[SIZE][SIZE];

Player players[2];

//Empty Map Initialization
void initializeEmptyMap()
{
    int i, j;

    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            map[i][j] = ' ';
            hiddenTrap[i][j] = 0;
        }
    }
}

//Boder Walls
void createBorderWalls()
{
    int i;

    for(i = 0; i < SIZE; i++)
    {
        map[0][i] = '#';
        map[SIZE - 1][i] = '#';

        map[i][0] = '#';
        map[i][SIZE - 1] = '#';
    }
}

//Random Empty Cell Generator
void getRandomEmptyCell(int *r, int *c)
{
    do
    {
        *r = rand() % SIZE;
        *c = rand() % SIZE;

    } while(map[*r][*c] != ' ');
}

//Place Interior Walls
void placeWalls()
{
    int count = 0;
    int r, c;

    while(count < WALLS)
    {
        getRandomEmptyCell(&r, &c);

        map[r][c] = '#';
        count++;
    }
}

//Place Treasures
void placeTreasures()
{
    int count = 0;
    int r, c;

    while(count < TREASURES)
    {
        getRandomEmptyCell(&r, &c);

        map[r][c] = 'T';
        count++;
    }
}

//Place Health Packs
void placeHealthPacks()
{
    int count = 0;
    int r, c;

    while(count < HEALTHPACKS)
    {
        getRandomEmptyCell(&r, &c);

        map[r][c] = 'H';
        count++;
    }
}

//Place Keys
void placeKeys()
{
    int count = 0;
    int r, c;

    while(count < KEYS)
    {
        getRandomEmptyCell(&r, &c);

        map[r][c] = 'K';
        count++;
    }
}

//Place Doors
void placeDoors()
{
    int count = 0;
    int r, c;

    while(count < DOORS)
    {
        getRandomEmptyCell(&r, &c);

        map[r][c] = 'D';
        count++;
    }
}

//Place Hidden Traps
void placeTraps()
{
    int count = 0;
    int r, c;

    while(count < TRAPS)
    {
        do
        {
            r = rand() % SIZE;
            c = rand() % SIZE;

        } while(map[r][c] != ' ' ||
                hiddenTrap[r][c] == 1);

        hiddenTrap[r][c] = 1;
        count++;
    }
}

//Create Complete Map
void initializeMap()
{
    initializeEmptyMap();

    createBorderWalls();

    placeWalls();
    placeTreasures();
    placeHealthPacks();
    placeKeys();
    placeDoors();
    placeTraps();
}




//Player Struct Initialization
void initializePlayers()
{
    printf("Enter Player 1 Name: ");
    scanf("%s", players[0].name);

    printf("Enter Player 2 Name: ");
    scanf("%s", players[1].name);

    players[0].health = 100;
    players[0].score = 0;
    players[0].keys = 0;
    players[0].symbol = '1';

    players[1].health = 100;
    players[1].score = 0;
    players[1].keys = 0;
    players[1].symbol = '2';
}

//Random Player Placement
void placePlayers()
{
    int r, c;
    int i;

    for(i = 0; i < 2; i++)
    {
        do
        {
            r = rand() % SIZE;
            c = rand() % SIZE;

        } while(map[r][c] != ' ');

        players[i].row = r;
        players[i].col = c;
    }
}

//Print Player Information
void printPlayerInfo()
{
    int i;

    printf("\n=====================================\n");

    for(i = 0; i < 2; i++)
    {
        printf("Player %c (%s)\n",
               players[i].symbol,
               players[i].name);

        printf("HP: %d  Score: %d  Keys: %d\n",
               players[i].health,
               players[i].score,
               players[i].keys);

        printf("-------------------------------------\n");
    }
}

//Print Map
void printMap()
{
    int i, j;
    int playerFound;

    printf("\n");

    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            playerFound = 0;

            if(players[0].health > 0 &&
               players[0].row == i &&
               players[0].col == j)
            {
                printf("%c ", players[0].symbol);
                playerFound = 1;
            }

            else if(players[1].health > 0 &&
                    players[1].row == i &&
                    players[1].col == j)
            {
                printf("%c ", players[1].symbol);
                playerFound = 1;
            }

            if(!playerFound)
            {
                printf("%c ", map[i][j]);
            }
        }

        printf("\n");
    }

    printPlayerInfo();
}

//Update Main Function
int main()
{
    srand(time(NULL));

    initializeMap();

    initializePlayers();

    placePlayers();

    printMap();

    return 0;
}




//IsValidMove()
int isValidMove(int row, int col)
{
    if(row < 0 || row >= SIZE)
        return 0;

    if(col < 0 || col >= SIZE)
        return 0;

    if(map[row][col] == '#')
        return 0;

    return 1;
}









