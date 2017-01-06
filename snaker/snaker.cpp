#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

int x, y, fruitX, fruitY;
int score;
const int width = 20;
const int height = 20;
bool isEnd;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction direc;

int tailX[100], tailY[100];
int ntail;

void setup()
{
	isEnd = false;
	direc = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	//ntail = 1;
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			direc = UP;
			break;
		case 'a':
			direc = LEFT;
			break;
		case 's':
			direc = DOWN;
			break;
		case 'd':
			direc = RIGHT;
			break;
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; ++i)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (direc)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		isEnd = true;
	for (int i = 0; i < ntail; ++i)
	{
		if (tailX[i] == x && tailY[i] == y)
			isEnd = true;
	}
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		ntail ++ ;
	}
}

void draw()
{
	system("cls"); // clear the terminal
	for (int i = 0; i < width; ++i)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height - 1; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (j == 0 || j == width - 1)
				cout << "#";
			else if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; ++k)
				{	
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}				
				}
				if (!print)
					cout << " ";
				
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; ++i)
		cout << "#";

	cout << endl;
	cout << "Score:" << score << endl;
}

int main()
{
	setup();
	while (!isEnd)
	{
		draw();
		input();
		logic();
		Sleep(200);
	}
	return 0;
}
