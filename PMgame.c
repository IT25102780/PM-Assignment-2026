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

    int movesMade;
    int treasuresFound;
    int trapsTriggered;
    int damageTaken;
    int healthPacksUsed;
    int keysCollected;
    int doorsUnlocked;

} Player;

char map[SIZE][SIZE];
int hiddenTrap[SIZE][SIZE];

#define MAX_PLAYERS 3
Player players[MAX_PLAYERS];
int playerCount;


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
    int i;

    do
    {
        printf("Enter Number of Players (1-3): ");
        scanf("%d",&playerCount);

    }while(playerCount<1 || playerCount>3);

    for(i=0;i<playerCount;i++)
    {
        printf("Enter Player %d Name: ",i+1);
        scanf("%s",players[i].name);

        players[i].health=100;
        players[i].score=0;
        players[i].keys=0;

        players[i].symbol='1'+i;

        players[i].movesMade=0;
        players[i].treasuresFound=0;
        players[i].trapsTriggered=0;
        players[i].damageTaken=0;
        players[i].healthPacksUsed=0;
        players[i].keysCollected=0;
        players[i].doorsUnlocked=0;
    }
}

//Random Player Placement
void placePlayers()
{
    int r, c;
    int i;

    for(i = 0; i<playerCount; i++)
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

    for(i = 0; i<playerCount; i++)
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
    int k;
    int playerFound;

    printf("\n");

    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            playerFound = 0;

            for(k = 0; k < playerCount; k++)
            {
                if(players[k].health > 0 &&
                   players[k].row == i &&
                   players[k].col == j)
                {
                    printf("%c ", players[k].symbol);

                    playerFound = 1;

                    break;
                }
            }

            if(!playerFound)
            {
                printf("%c ", map[i][j]);
            }
        }

        printf("\n");
    }

    printPlayerInfo();
    printRecentLog();
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

//Door Handling Function
int handleDoor(int playerIndex, int row, int col)
{
    if(map[row][col] == 'D')
    {
        if(players[playerIndex].keys > 0)
        {
            players[playerIndex].keys--;

	    players[playerIndex].doorsUnlocked++;

            map[row][col] = ' ';

            printf("Door unlocked!\n");

            return 1;
        }
        else
        {
            printf("Need a key to open this door!\n");

            return 0;
        }
    }

    return 1;
}

//Process Tile Effects
void processTile(int playerIndex)
{
    int r = players[playerIndex].row;
    int c = players[playerIndex].col;

    /* Trap */
    if(hiddenTrap[r][c] == 1)
    {
        players[playerIndex].health -= 20;

        if(players[playerIndex].health < 0)
            players[playerIndex].health = 0;

	players[playerIndex].trapsTriggered++;
	players[playerIndex].damageTaken += 20;
        hiddenTrap[r][c] = 0;

        printf("Trap triggered! -20 HP\n");
    }

    /* Treasure */
    if(map[r][c] == 'T')
    {
        players[playerIndex].score += 10;
	players[playerIndex].treasuresFound++;

        map[r][c] = ' ';

        printf("Treasure collected! +10 Score\n");
    }

    /* Health Pack */
    if(map[r][c] == 'H')
    {
        players[playerIndex].health += 20;

        if(players[playerIndex].health > 100)
            players[playerIndex].health = 100;

	players[playerIndex].healthPacksUsed++;
        map[r][c] = ' ';

        printf("Health Pack used! +20 HP\n");
    }

    /* Key */
    if(map[r][c] == 'K')
    {
        players[playerIndex].keys++;
	players[playerIndex].keysCollected++;

        map[r][c] = ' ';

        printf("Key collected!\n");
    }
}

//Single Step Movement 
void performMove(int playerIndex, char move)
{
    int newRow = players[playerIndex].row;
    int newCol = players[playerIndex].col;

    switch(move)
    {
        case 'W':
        case 'w':
            newRow--;
            break;

        case 'S':
        case 's':
            newRow++;
            break;

        case 'A':
        case 'a':
            newCol--;
            break;

        case 'D':
        case 'd':
            newCol++;
            break;

        default:
            printf("Invalid move character skipped!\n");
            return;
    }

    if(!isValidMove(newRow, newCol))
    {
        printf("Move blocked!\n");
        return;
    }

    if(!handleDoor(playerIndex, newRow, newCol))
    {
        return;
    }

    players[playerIndex].row = newRow;
    players[playerIndex].col = newCol;

    processTile(playerIndex);
}

//Move Player Function
void movePlayer(int playerIndex)
{
    char moves[50];

    if(players[playerIndex].health <= 0)
    {
        printf("%s is eliminated.\n",
               players[playerIndex].name);

        return;
    }

    printf("\n%s's Turn\n",
           players[playerIndex].name);

    printf("Enter up to 4 moves (WASD): ");
    scanf("%s", moves);

    if(strlen(moves) > 4)
    {
        printf("More than 4 moves entered. Turn cancelled!\n");
        return;
    }

    int i;

    for(i = 0; i < strlen(moves); i++)
    {
        performMove(playerIndex, moves[i]);
	players[playerIndex].movesMade++;
    }
}

//Remaining Treasures Function
int remainingTreasures()
{
    int i, j;
    int count = 0;

    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            if(map[i][j] == 'T')
            {
                count++;
            }
        }
    }

    return count;
}

//End Game Check
int allPlayersDead()
{
    if(players[0].health <= 0 &&
       players[1].health <= 0)
    {
        return 1;
    }

    return 0;
}

//Save Game Function
void saveGame()
{
    FILE *fp;

    fp = fopen("savegame.dat", "wb");

    if(fp == NULL)
    {
        printf("Save failed!\n");
        return;
    }

    fwrite(players, sizeof(Player), 2, fp);
    fwrite(map, sizeof(map), 1, fp);
    fwrite(hiddenTrap, sizeof(hiddenTrap), 1, fp);

    fclose(fp);

    printf("Game Saved Successfully!\n");
}

//Lode Game Function
int loadGame()
{
    FILE *fp;

    fp = fopen("savegame.dat", "rb");

    if(fp == NULL)
    {
        return 0;
    }

    fread(players, sizeof(Player), 2, fp);
    fread(map, sizeof(map), 1, fp);
    fread(hiddenTrap, sizeof(hiddenTrap), 1, fp);

    fclose(fp);

    printf("Game Loaded Successfully!\n");

    return 1;
}

//Apply HP Bonus
void applyHPBonus()
{
    int i;

    for(i = 0; i < 2; i++)
    {
        if(players[i].health > 0)
        {
            players[i].score += players[i].health / 2;
        }
    }
}

//Sort Scores
void sortPlayers(Player ranking[])
{
    int i, j;

    Player temp;

    for(i = 0; i < 1; i++)
    {
        for(j = 0; j < 1 - i; j++)
        {
            if(ranking[j].score < ranking[j + 1].score)
            {
                temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}

//Leaderboard
void showScores()
{
    Player ranking[2];

    ranking[0] = players[0];
    ranking[1] = players[1];

    applyHPBonus();

    ranking[0] = players[0];
    ranking[1] = players[1];

    sortPlayers(ranking);

    printf("\n");
    printf("================================\n");
    printf("FINAL LEADERBOARD\n");
    printf("================================\n");

    printf("1. %s : %d\n",
           ranking[0].name,
           ranking[0].score);

    printf("2. %s : %d\n",
           ranking[1].name,
           ranking[1].score);

    if(ranking[0].score == ranking[1].score)
    {
        printf("\nResult : TIE GAME!\n");
    }
    else
    {
        printf("\nWinner : %s\n",
               ranking[0].name);
    }
}

//Save Prompt
void askSave()
{
    char choice;

    printf("\nSave Game? (Y/N): ");
    scanf(" %c", &choice);

    if(choice == 'Y' || choice == 'y')
    {
        saveGame();
    }
}

//Game Loop
void gameLoop()
{
    while(1)
    {
        printMap();

        movePlayer(0);

        movePlayer(1);

        if(remainingTreasures() == 0)
        {
            printf("\nAll treasures collected!\n");
            break;
        }

        if(allPlayersDead())
        {
            printf("\nAll players eliminated!\n");
            break;
        }

        askSave();
    }
}

//New Game
void newGame()
{
    initializeMap();

    initializePlayers();

    placePlayers();

    gameLoop();
}

//Main Menu
int main()
{
    int choice;

    srand(time(NULL));

    printf("=================================\n");
    printf(" QUEST FOR THE LOST TREASURE\n");
    printf("=================================\n");

    printf("1. New Game\n");
    printf("2. Load Game\n");

    printf("Enter Choice : ");
    scanf("%d", &choice);

    if(choice == 2)
    {
        if(loadGame())
        {
            gameLoop();
        }
        else
        {
            printf("No Save File Found!\n");
            newGame();
        }
    }
    else
    {
        newGame();
    }

    showScores();

    return 0;
}

