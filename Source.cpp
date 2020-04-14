#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
#include "windows.h"

using namespace std;

enum eDir{STOP = 0,UP = 1,DOWN = 2};

class cEnemy
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cEnemy(int posX,int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	void Reset()
	{
		x = originalX; y = originalY;
		direction = STOP;
	}

	void ChangeDirection(eDir d)
	{
		direction = d;
	}

	void setX(int X)
	{
		x = X;
	}

	void setY(int Y)
	{
		y = Y;
	}

	inline int getX(){ return x; }
	inline int getY(){ return y; }
	inline eDir getDirection(){ return direction; }

	void Move()
	{
		switch (direction)
		{
		case STOP:
			break;

		case DOWN:
			y++;
			break;
		}
	}
};

class cWeapon
{
private:
	int x, y;
	int originalX, originalY;
	eDir direction;
public:
	cWeapon(int posX,int posY)
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
		direction = STOP;
	}

	void Reset()
	{
		x = originalX; y = originalY;
		direction = STOP;
	}

	void ChangeDirection(eDir d)
	{
		direction = d;
	}

	inline int getX(){ return x; }
	inline int getY(){ return y; }
	inline eDir getDirection(){ return direction; }
	
	void setX(int X)
	{
		x = X;
	}

	void setY(int Y)
	{
		y = Y;
	}

	void Move()
	{
		switch (direction)
		{
		case STOP:
			break;

		case UP:
			y--;
			break;
		}
	}

};

class cBattleShip
{
private:
	int x, y;
	int originalX, originalY;
public:
	cBattleShip()
	{
		x = y = 0;
	}

	cBattleShip(int posX, int posY) : cBattleShip()
	{
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}

	inline void Reset()
	{
		x = originalX;
		y = originalY;
	}

	inline int getX(){ return x; }
	inline int getY(){ return y; }

	inline void MoveRight(){ x++; }
	inline void MoveLeft(){ x--; }
};

class cGameManager
{
private:
	int width, height;
	int score;
	char right, left,fire;
	bool quit;
	cBattleShip* player;
	cEnemy* enemy;
	cWeapon* weapon;
public:
	cGameManager(int w,int h)
	{
		srand(time(NULL));
		quit = false;
		right = 'd'; left = 'a'; fire = 'f';
		score = 0;
		width = w;
		height = h;
		enemy = new cEnemy(w / 2,0);
		player = new cBattleShip(w / 2,h - 1);
		weapon = new cWeapon(player->getX() - 5,player->getY() - 1);
	}

	~cGameManager()
	{
		delete enemy, player, weapon;
	}

	void ScoreUp()
	{
		score++;
		enemy->Reset();
		weapon->Reset();
		player->Reset();
	}

	void Draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
		{
			cout << "\xB2";
		}
		cout << endl;

		for (int a = 0; a < height; a++)
		{
			for (int b = 0; b < width; b++)
			{

				int enemyX = enemy->getX();
				int enemyY = enemy->getY();
				int playerX = player->getX();
				int playerY = player->getY();
				int weaponX = weapon->getX();
				int weaponY = weapon->getY();

				if (b == 0)
					cout << "\xB2";

				if (enemyX == b && enemyY == a)
				{
					cout << "*";
				}
				else if (playerX - 4 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX - 3 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX - 2 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX - 1 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX + 1 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX + 2 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX + 3 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX + 4 == b && playerY == a)
				{
					cout << "\xDB";
				}
				else if (playerX + 5 == b && playerY == a)
				{
					cout << "\xDB";
				}
			
				
			
				


				else if (weaponX + 6 == b && weaponY == a)
					cout << "|";
				else
				{
					cout << " ";
				}


				if (b == width - 1)
					cout << "\xB2";
			}
			cout << endl;
		}

		for (int j = 0; j < width + 2; j++)
		{
			cout << "\xB2";
		}
		cout << endl;
		cout << "Player Score: " << score << endl;

	}

	void Input()
	{
		enemy->Move();
		weapon->Move();
		int enemyX = enemy->getX();
		int enemyY = enemy->getY();
		int playerX = player->getX();
		int playerY = player->getY();
		int weaponX = weapon->getX();
		int weaponY = weapon->getY();

		if (_kbhit())
		{
			char current = _getch();
			if (current == right)
			{
				if (playerX + 5 < width)
				{
					player->MoveRight();
					weapon->setX(weaponX + 1);
				}
			}
			if (current == left)
			{
				if (playerX - 4 > 0)
				{
					player->MoveLeft();
					weapon->setX(weaponX - 1);
				}
			}
			if (enemy->getDirection() == STOP)
				enemy->ChangeDirection(DOWN);
			if (current == 'q')
				quit = true;
			if (current == fire)
				weapon->ChangeDirection(UP);
		}
	}

	void Logic()
	{
		int enemyX = enemy->getX();
		int enemyY = enemy->getY();
		int playerX = player->getX();
		int playerY = player->getY();
		int weaponX = weapon->getX();
		int weaponY = weapon->getY();

		
		if ((enemyX - 4 == playerX || enemyX - 3 == playerX ||
			enemyX - 2 == playerX || enemyX - 1 == playerX ||
			enemyX == playerX) && (enemyY == playerY || enemyY - 1 == playerY
			))
		{
			score--;
			enemy->setX(width / 2);
			enemy->setY(0);
		}
		else if (
			(enemyX + 5 == playerX || enemyX + 4 == playerX ||
			enemyX + 3 == playerX || enemyX + 2 == playerX ||
			enemyX + 1 == playerX
			)&& (enemyY == playerY || enemyY - 1 == playerY
			))
		{
			score--;
			enemy->setX(width / 2);
			enemy->setY(0);
		}
		else if (enemyX == height && enemyY == width)
		{
			enemy->setX(width / 2);
			enemy->setY(0);
		}
		if (weaponX == enemyX && weaponY == enemyY)
		{
			score++;
			enemy->Reset();
			weapon->Reset();
		}
		else if (weaponX == height && weaponY == width)
		{
			weapon->Reset();
		}
		if (score < 0)
			quit = true;


	}

	void Run()
	{
		while (!quit)
		{
			Draw();
			Input();
			Logic();
			Sleep(100);
		}
	}
};

int main()
{
	cGameManager c(40,40);
	c.Run();
	return 0;
}