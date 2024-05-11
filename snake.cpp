#include"mordensnake.h"
int main()
{
	SNAKE snake;
	snake.SetUp();

	while (!gameover)
	{
		DWORD start_time = GetTickCount();

		snake.getkey();

		snake.Move();
		snake.Logic();
		snake.Draw();
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 500 / 60)
		{
			Sleep(500 / 60 - delta_time);
		}
	}

}
