#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <vector>
//control - a, s, d, w; x - game over
using namespace std;

bool printLow = true;
bool print;
bool gameOver, d;
const int width = 30;
const int height = 15;
int x, y, newX, newY, score;
int tailX[100], tailY[100];
int nTail;
int choise = 2;
char sign = '#';
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void printTail(int i, int j, bool &print)
{
	for (int k = 0; k < nTail; k++)
	{
		if (tailX[k] == j && tailY[k] == i)
		{
			print = true;
			cout << 'o';
		}
	}
}
void printLine()
{
	for (int i = 0; i < width + 1; i++)
		cout << sign;
	cout << endl;
}
class fruits
{
public:
	fruits()
	{
		nFruits++;
	}
	bool print_fruit(int i, int j)
	{
		if (i == fruitY && j == fruitX)
		{
			cout << 'F';
			return true;
		}
		return false;
	}
	void set_new_fruit(int x, int y)
	{
		if (x == fruitX && y == fruitY)
		{
			score += 10;
			fruitX = rand() % (width - 1);
			fruitY = rand() % (height - 1);
			if (fruitX == 0) fruitY++;
			if (fruitY == 0) fruitX++;
			nTail++;
			if (nTail % 10 == 0) printLow = true;
		}
	}
private:
	int nFruits;
	int fruitX = rand() % (width - 2);
	int fruitY = rand() % (height - 2);
};
class low
{
public:
	low()
	{
		nLow++;
	}
	bool print_low(int i, int j)
	{
		if (i == lowY && j == lowX && printLow)
		{
			cout << 'L';
			return true;
		}
		return false;
	}
	void print_new_low(int x, int y)
	{
		if ((x == lowX && y == lowY)&&(nTail >= 1))
		{
			lowX = rand() % (width - 1);
			lowY = rand() % (height - 1);
			if (lowX == 0) lowY++;
			if (lowY == 0) lowX++;
			nTail--;
			nLow++;
			printLow = false;
		}
	}
private:
	int nLow;
	int lowX = rand() % (width - 2);;
	int lowY = rand() % (height - 2);;
};
fruits a;
fruits b;
fruits c;
low q;

void Setup()
{
	srand(time(NULL));
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	score = 0;
}

void Draw()
{
	Sleep(100);
	system("cls");
	printLine();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1) cout << sign;
			if (i == y && j == x) cout << '0';
			else if (a.print_fruit(i, j));
			else if (b.print_fruit(i, j));
			else if (c.print_fruit(i, j));
			else if (q.print_low(i, j));
			else
			{
				bool print = false;
				printTail(i, j, print);
				if (!print) cout << ' ';
			}
		}
		cout << endl;
	}
	printLine();
	cout << "SCORE: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (dir != RIGHT || nTail == 0)dir = LEFT; break;
		case 'd':
			if (dir != LEFT || nTail == 0) dir = RIGHT; break;
		case 'w':
			if (dir != DOWN || nTail == 0) dir = UP; break;
		case 's':
			if (dir != UP || nTail == 0) dir = DOWN; break;
		case 'q':
			dir = STOP; break;
		case 'x':
			gameOver = true ; break;
		}
	}
}

void Logic()
{
	if (dir != STOP)
	{
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X;
		int prev2Y;
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
	}
	switch (dir)
	{
	case LEFT: x--; break;
	case RIGHT: x++; break;
	case UP: y--; break;
	case DOWN: y++; break;
	case STOP: break;
	}
	if (choise == 1)
	{
		if (x >= width - 1 || x < 0 || y > height || y < 0) gameOver = true;
	}
	if (choise == 2)
	{
		if (x >= width - 1) x = 0;
		else if (x < 0) x = width - 2;
		else if (y >= height) y = 0;
		else if (y < 0) y = height;
	}
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	a.set_new_fruit(x, y);
	b.set_new_fruit(x, y);
	c.set_new_fruit(x, y);
	q.print_new_low(x, y);
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	system("cls");
	cout << "GAME OVER, score: " << score << endl ;
	system("pause");
	return 0;
}