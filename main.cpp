#include <iostream>
#include <ncurses.h>


void setup();
void draw();
void input();
void logic();

bool  gameOver;
const int height = 20;
const int width = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100], nTail;

enum Direction {STOP, UP, DOWN, RIGHT, LEFT};
Direction direction;


int main()
{
    initscr();
    noecho();
    nodelay(stdscr, true); // Make getch non-blocking

    setup();

    while (!gameOver)
    {
        clear(); // Clear the screen
        draw();
        input();
        logic();
    }

    endwin(); // End ncurses mode
    return 0;
}





void setup()
{
    gameOver = false;
    direction = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void draw()
{
    for (int i = 0; i < width; i++)
    {
        printw("#");
    }
    printw("\n");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width -1)
            {
                printw("#");
            }
            else if (i == y && j == x)
            {
                printw("O");
            }
            else if (i == fruitY && j == fruitX)
            {
                printw("F");
            }
            else
            {
                bool print = false;

                for (int k = 0; k < nTail; k++)
                {
                    if (i == tailY[k] && j == tailX[k])
                    {
                        printw("o");
                        print = true;
                    }
                }
                if (!print)
                {
                    printw(" ");
                }
            }
        }
        printw("\n");
    }

    for (int i = 0; i < width; i++)
    {
        printw("#");
    }
    printw("\n");

    std::cout << "Score: " << score;
}

void input()
{
    char ch = getch();
        std::cin >> ch; // Why does it work using this?!?!
        // Whitout this the variable y get the value -310531!!!
    switch (ch)
    {
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'a':
            direction = LEFT;
        default:
            break;
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        case LEFT:
            x--;
        default:
            break;
    }

    if (x < 0 || x > width || y < 0 || y > height)
    {
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
