#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>
using namespace std;

const int width = 20;
const int height = 20;

bool gameOver;
int fruitX;
int fruitY;
int x;
int y;
int score;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

int tailX[100], tailY[100];
int nTail;

void setup()
{
	gameOver = false;
	fruitX = rand() % width;
	fruitY = rand() & height;
	x = width / 2;
	y = height / 2;
	dir = STOP;
	int score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i <= width; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "#";
			}
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}

		}
		cout << endl;
	}

	for (int i = 0; i <= width; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case UP:
		y--;
		break;
	case LEFT:
		x--;
		break;
	case DOWN:
		y++;
		break;
	case RIGHT:
		x++;
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 5;
		fruitX = rand() % width;
		fruitY = rand() & height;
		nTail++;
	}


}

int main()
{
	setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(20);
	}
	cout << "\n GAME OVER \n";
	cout << "Final Score: " << score;

	return 0;
}