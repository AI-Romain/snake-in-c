#include <windows.h>
#include <stdio.h>
#include <conio.h> /* getch() and kbhit() */
#include <stdlib.h>

#define HEIGTH 25
#define WIDTH 50

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
int render(void);
int input(void);
struct Position getFoodLocation();

// Default snake pos
int XSnakeHeadPos = WIDTH / 2;
int YSnakeHeadPos = HEIGTH / 2;

/* struct Position Map[WIDTH][HEIGTH]; */

struct Position SnakePos[100] = {
    {
        WIDTH / 2, /// default head pos
        HEIGTH / 2,
    }};

int snakeSize = 1;
int score = 0;

struct Position getFoodLocation()
{
    struct Position location;

    location.x = rand() % WIDTH + 1;
    location.y = rand() % HEIGTH + 1;

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
}
void addSnakeBody()
{
    snakeSize++;
    // Add the new position to the end of the array
    SnakePos[snakeSize].x = SnakePos[0].x;
    SnakePos[snakeSize].y = SnakePos[0].y;
}

/* void generateMap()
{
    int x;
    int y;

    for (y = 0; y <= HEIGTH; y++)
    {
        for (x = 0; x <= WIDTH; x++)
        {

        }
    }
} */

void updateSnake(void)
{

    if (foodLocation.x == SnakePos[0].x && foodLocation.y == SnakePos[0].y)
    {
        updateFood();
        addSnakeBody();
    }

    SnakePos[snakeSize] = SnakePos[0];
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
}

void gameLoop()
{
    render();
    input();
    updateSnake();
}

int main()
{
    updateFood();

    while (1)
    {
        gameLoop();
        Sleep(300);
    }
    return 1;
}

void renderScore()
{
    printf("Score : %d", (sizeof(SnakePos) / sizeof(SnakePos[0])));
}

int render()
{
    int x;
    int y;

    system("cls");
    for (y = 0; y <= HEIGTH; y++)
    {
        for (x = 0; x <= WIDTH; x++)
        {

            int isSnake = 0;

            for (int i = 0; i < snakeSize; i++)
            {
                if (x == SnakePos[i].x && y == SnakePos[i].y)
                {
                    if (!SnakePos[i].x || !SnakePos[i].y)
                        continue;
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
    renderScore();
    return 1;
}

int input(void)
{
    if (!kbhit())
        return 0;

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
    }
}
