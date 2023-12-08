#include <windows.h>
#include <stdio.h>
#include <conio.h> /* getch() and kbhit() */
#include <stdlib.h>

#define HEIGTH 25
#define WIDTH 50

// Prototypes des fonctions
int render(void);
int input(void);

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

// Default snake pos
int XSnakeHeadPos = WIDTH / 2;
int YSnakeHeadPos = HEIGTH / 2;

struct Position SnakePos[] = {
    {
        WIDTH / 2, /// default head pos
        HEIGTH / 2,
    },
    {
        (WIDTH / 2), /// default head pos
        (HEIGTH / 2) - 1,
    },
};

int score = 0;

enum Direction
{
    North,
    South,
    East,
    West,
};

enum Direction snakeDirection = North;

void updateSnake(void)
{
    SnakePos[sizeof(SnakePos) / sizeof(SnakePos[0]) - 1] = SnakePos[0];
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
    while (1)
    {
        gameLoop();
        Sleep(300);
    }
    return 1;
}

void drawScore()
{
    printf("Score : %d", score);
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
            for (int i = 0; i < sizeof(SnakePos) / sizeof(SnakePos[0]); i++)
            {
                if (x == SnakePos[i].x && y == SnakePos[i].y)
                {
                    i == 0 ? printf(" %c", c.SnakeHead) : printf(" %c", c.Snake);
                }
            }
            if (y == 0 || y == HEIGTH || x == 0 || x == WIDTH)
            {
                printf(" %c", c.Border);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
    drawScore();
    return 1;
}

int input(void)
{
    if (!kbhit())
        return 0;

    switch (getch())
    {
    case 'z':
        snakeDirection = North;
        break;
    case 's':
        snakeDirection = South;
        break;
    case 'q':
        snakeDirection = West;
        break;
    case 'd':
        snakeDirection = East;
        break;
    }
}
