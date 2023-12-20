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
                printw(" ");
            }
        }
        printw("\n");
    }

    for (int i = 0; i < width; i++)
    {
        printw("#");
    }
    printw("\n");
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
}
