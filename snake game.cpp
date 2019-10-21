#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

using namespace std;

bool endgame = false;
const int width = 20, height = 20;//the frame of the game
int x = width / 2, y = height / 2;//the head of the snake
int frx = rand() % 20;//the fruit cordinations
int fry = rand() % 20;
enum direction {stop, rigt, lft, up, down};
direction dir;
int score = 0;
int snk_tail[399][2] = { 0 };
int tail_lnth = 0;

void draw()
{
	for (int i = 0; i < width+2; i++)
	{
		cout << "&";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "&";
			if (x == j && y == i)
				cout << "O";
			else if (frx == j && fry == i)
			{
				cout << "f";
			}
			else
			{
				bool prnt_spc = true;
				//print the tail or a space
				for (int k = 0; k < tail_lnth; k++)
					if (snk_tail[k][0] == j && snk_tail[k][1] == i)
					{
						cout << "o";
						prnt_spc = false;
					}
				if(prnt_spc)
					cout << " ";
			}
			if (j == width - 1)
				cout << "&";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
	{
		cout << "&";
	}
	cout << endl;
	cout << "Score: " << score;
}
void input()
{
	//getting directions
	if (_kbhit)
	{
		switch (_getch())
		{
			case 'x':
				dir = stop;
				break;
			case 'd':
				dir = rigt;
				break;
			case 'a':
				dir = lft;
				break;
			case 'w':
				dir = up;
				break;
			case 's':
				dir = down;
				break;
			default:
				break;
		}
	}
}
void logic()
{
	int prevX = x, prevY = y;

	move:
	switch (dir)
	{
		case stop:
			endgame = true;
			break;
		case up:
			y--;
			break;
		case down:
			y++;
			break;
		case rigt:
			x++;
			break;
		case lft:
			x--;
			break;
		default:
			break;
	}
	if (!_kbhit)
		goto move;
	//when the snake hits the borders terminate
	if (x < 0 || x >= width || y < 0 || y >= height)
		endgame = true;
	//if it eats a fruit
	if (x == frx && y == fry)
	{
		score += 10;
		
	frt_pos://to make sure the fruit doesn't land on the snake

		frx = rand() % 20;
		fry = rand() % 20;

		if (frx == x && fry == y)
			goto frt_pos;
		for (int i = 0; i < tail_lnth; i++)
		{
			if (frx == snk_tail[i][0] && fry == snk_tail[i][1])
				goto frt_pos;
		}

		tail_lnth++;
	}

	//this is concerning the tail of the snake
	for (int i = tail_lnth; i > 0; i--)
	{
		snk_tail[i][0] = snk_tail[i - 1][0];
		snk_tail[i][1] = snk_tail[i - 1][1];
	}
	snk_tail[0][0] = prevX;
	snk_tail[0][1] = prevY;
	//terminate the game if the snake bit itself
	for (int i = 0; i <= tail_lnth; i++)
	{
		if (snk_tail[i][0] == x && snk_tail[i][1] == y)
			endgame = true;
	}

}

int main()
{
	system("color 02");
	
	cout << "Enter keys W, S, D, A to move up, down, right, left respectively.\n\n";
	draw();
	Sleep(5000);
	
	while (!endgame)
	{
		system("cls");
		draw();
		input();
		logic();
	}
}
