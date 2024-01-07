#include <windows.h>
#include <stdio.h>
#include <conio.h> /* getch() and kbhit() */
#include <stdlib.h>
#include <time.h>

#define HEIGTH 25
#define WIDTH 50

enum GameState
{
    inMenu = 2,
    Playing = 1,
    GameOver = 0
};

enum GameState gameState = inMenu;

struct Cases
{
    char Snake;
    char SnakeHead;
    char Food;
    char Border;
};

struct Cases c = {
    'o', // Snake
    'O', // Snake Head
    'D', // Food
    '#'  // Border
};

struct Position
{
    int x;
    int y;
};

// Prototypes des fonctions
void render(void);
void renderGameOverScreen(void);
void renderGameOverScreen(void);
void triggerGameOver(void);


char *gameOverScreenText =
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                 /$$$$$$                                           /$$$$$$                                    \n"
    "                /$$__  $$                                         /$$__  $$                                   \n"
    "               | $$  \\__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$       | $$  \\ $$ /$$    /$$  /$$$$$$   /$$$$$$   \n"
    "               | $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$      | $$  | $$|  $$  /$$/ /$$__  $$ /$$__  $$    \n"
    "               | $$|_  $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$      | $$  | $$ \\  $$/$$/ | $$$$$$$$| $$  \\__/\n"
    "               | $$  \\ $$ /$$__  $$| $$ | $$ | $$| $$_____/      | $$  | $$  \\  $$$/  | $$_____/| $$        \n"
    "               |  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$      |  $$$$$$/   \\  $/   |  $$$$$$$| $$         \n"
    "                \\______/  \\_______/|__/ |__/ |__/ \\_______/       \\______/     \\_/     \\_______/|__/    \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "            Presse Enter to start a new game !                                                                \n"
    "            Presse x to quit.                                                                                 \n"
    "                                                                                                              \n";
char *mainMenuScreenText =
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "             /$$$$$$                      /$$                        /$$$$$$                                          \n"
    "            /$$__  $$                    | $$                       /$$__  $$                                         \n"
    "           | $$  \\__/ /$$$$$$$   /$$$$$$ | $$   /$$  /$$$$$$       | $$  \\__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$      \n"
    "           |  $$$$$$ | $$__  $$ |____  $$| $$  /$$/ /$$__  $$      | $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$       \n"
    "            \\____  $$| $$  \\ $$  /$$$$$$$| $$$$$$/ | $$$$$$$$      | $$|_  $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$   \n"
    "            /$$  \\ $$| $$  | $$ /$$__  $$| $$_  $$ | $$_____/      | $$  \\ $$ /$$__  $$| $$ | $$ | $$| $$_____/     \n"
    "           |  $$$$$$/| $$  | $$|  $$$$$$$| $$ \\  $$|  $$$$$$$      |  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$      \n"
    "            \\______/ |__/  |__/ \\_______/|__/  \\__/ \\_______/       \\______/  \\_______/|__/ |__/ |__/ \\_______/\n"
    "                                                                                                              \n"
    "                                                                                                              \n"
    "            Presse Enter to start playing !                                                                   \n"
    "            Presse x to quit.                                                                                 \n"
    "                                                                                                              \n";

// Default snake pos
int XSnakeHeadPos = WIDTH / 2;
int YSnakeHeadPos = HEIGTH / 2;

/* struct Position Map[WIDTH][HEIGTH]; */

struct Position SnakePos[(HEIGTH - 1) * (WIDTH - 1)] = {
    {
        WIDTH / 2, /// default head pos
        HEIGTH / 2,
    }};

int snakeSize = 1;
int score = 0;

struct Position getFoodLocation()
{
    struct Position location;

    srand(time(NULL));
    location.x = rand() % (WIDTH);
    location.y = rand() % (HEIGTH);

    return location;
}

enum Direction
{
    North,
    South,
    East,
    West,
};

enum Direction snakeDirection = North;

struct Position foodLocation;

void updateFood()
{
    foodLocation = getFoodLocation();
    score++;
}

void triggerGameOver()
{
    foodLocation = getFoodLocation();
    score = 0;

    for (int i = snakeSize; i >= 1; i--)
    {
        SnakePos[i] = (struct Position){0, 0};
    }
    SnakePos[0].x = WIDTH / 2;
    SnakePos[0].y = HEIGTH / 2;

    snakeDirection = North;

    snakeSize = 1;
    gameState = GameOver;
}
void addSnakeBody()
{
    snakeSize++;
    // Add the new position to the end of the array
    SnakePos[snakeSize].x = SnakePos[0].x;
    SnakePos[snakeSize].y = SnakePos[0].y;
}

void updateSnake(void)
{

    if (
        SnakePos[0].x <= 0 ||
        SnakePos[0].x >= WIDTH ||
        SnakePos[0].y >= HEIGTH ||
        SnakePos[0].y <= 0)
    {
        triggerGameOver();
    }

    if (foodLocation.x == SnakePos[0].x && foodLocation.y == SnakePos[0].y)
    {
        updateFood();
        addSnakeBody();
    }

    for (int i = snakeSize; i >= 1; i--)
    {
        SnakePos[i] = SnakePos[i - 1];
    }

    switch (snakeDirection)
    {
    case North:
        SnakePos[0].y--;
        break;
    case South:
        SnakePos[0].y++;
        break;
    case East:
        SnakePos[0].x++;
        break;
    case West:
        SnakePos[0].x--;
        break;
    }

    for (int i = 1; i <= snakeSize; i++)
    {
        if (SnakePos[i].x == SnakePos[0].x && SnakePos[i].y == SnakePos[0].y)
        {
            triggerGameOver();
            break;
        }
    }
}

void gameLoop()
{
    render();
    input();

    if (gameState == Playing)
        updateSnake();
}

int main()
{
    updateFood();

    while (1)
    {
        gameLoop();
        Sleep(50);
    }
    return 1;
}

void renderScore()
{
    printf("Score : %d", score);
}

void renderGameOverScreen()
{
    printf(gameOverScreenText);
}
void renderMainMenuScreen()
{
    printf(mainMenuScreenText);
}
void renderPlayScreen()
{
    int x;
    int y;

    for (y = 0; y <= HEIGTH; y++)
    {
        for (x = 0; x <= WIDTH; x++)
        {

            int isSnake = 0;

            for (int i = 0; i < snakeSize; i++)
            {
                if (x == SnakePos[i].x && y == SnakePos[i].y)
                {
                    i == 0 ? printf(" %c", c.SnakeHead) : printf(" %c", c.Snake);
                    isSnake = 1;
                }
            }

            if (isSnake == 1)
                continue;

            if (x == foodLocation.x && y == foodLocation.y)
            {
                printf(" %c", c.Food);
            }
            else
            {
                if (y == 0 || y == HEIGTH || x == 0 || x == WIDTH)
                {
                    printf(" %c", c.Border);
                }
                else
                {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
    printf("\nPresse x to quit.                                                                                 \n");
}

void render()
{

    system("cls");

    switch (gameState)
    {
    case inMenu:
        renderMainMenuScreen();
        break;
    case GameOver:
        renderGameOverScreen();
        break;

    case Playing:
        renderPlayScreen();
        renderScore();
        break;
    }
}

void input(void)
{
    if (!kbhit())
        return;

    switch (getch())
    {
    case 'w':
        if (snakeDirection != South)
            snakeDirection = North;
        break;
    case 's':
        if (snakeDirection != North)
            snakeDirection = South;
        break;
    case 'a':
        if (snakeDirection != East)
            snakeDirection = West;
        break;
    case 'd':
        if (snakeDirection != West)
            snakeDirection = East;
        break;
    case 'x':
        exit(EXIT_SUCCESS);
        break;
    case 13: // correspond to the ENTER key
        if (gameState != Playing)
        {
            gameState = Playing;
        }
        break;
    }
}
