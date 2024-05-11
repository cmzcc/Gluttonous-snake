#pragma once
#include<iostream>
#include<graphics.h>
#include <random>
#include <conio.h>
#define nsnake 100
using namespace std;
random_device rd;
mt19937 gen(rd());
//定义随机数分布
uniform_int_distribution<> disx(1, 799); 
uniform_int_distribution<> disy(1, 599);

bool gameover = false;
const int width = 800;
const int height = 600;
int score;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;
class SNAKE
{
public:
	int size;
	int speed;
	POINT coor[nsnake];
    int fruitx = disx(gen);
    int fruity = disy(gen);
    int fruitr = 15;
    int r = 4;
	void SetUp()
	{
		size = 1;
		speed = 2*r;
		coor[0].x = width / 2;
		coor[0].y = height / 2;
        initgraph(width, height);
         
	}
	void Draw()
	{
     /*   IMAGE img_head;
        IMAGE img_increasescore;
        loadimage(&img_head, _T("img/head.jpg"),2*r,2*r,true);*/
		BeginBatchDraw();

        setbkcolor(RGB(45, 77, 169));
        setfillcolor(RGB(196, 75, 2));
        cleardevice();
        //putimage(coor[0].x-r, coor[0].y-r,&img_head);
        solidcircle(coor[0].x, coor[0].y, r);
        setfillcolor(RGB(148, 215, 26));
		for (int i = 1; i < size; i++)
		{
			solidcircle(coor[i].x, coor[i].y, r);
		}
        setfillcolor(RGB(18, 175, 96));
        Tip();
        solidcircle(fruitx,fruity,fruitr);
 /*       loadimage(&img_increasescore, _T("img/fruit.jpg"),2*fruitr,2*fruitr, true);
        putimage(fruitx - fruitr, fruity - fruitr, &img_increasescore);*/
		FlushBatchDraw();


		EndBatchDraw();
	}
    void getkey()
    {
        if (_kbhit()) // 检测是否有按键按下
        {
            switch (_getch()) // 获取按下的键值
            {
            case 'a':
                if (dir != RIGHT)
                {
                    dir = LEFT;
                }
                break;
            case 'd':
                if (dir != LEFT)
                {
                    dir = RIGHT;
                }
                break;
            case 'w':
                if (dir != DOWN)
                {
                    dir = UP;
                }
                break;
            case 's':
                if (dir != UP)
                {
                    dir = DOWN;
                }
                break;
            case 'x':
                gameover = true;
                break;
            }

        }
        cout << endl;
    
    }
	void Move()
	{
        int prevX = coor[1].x;
        int prevY = coor[1].y;
        int prev2X, prev2Y;
        coor[1].x = coor[0].x;
        coor[1].y = coor[0].y;
        for (int i = 2; i <size; i++)
        {
            prev2X = coor[i].x;
            prev2Y = coor[i].y;
            coor[i].x = prevX;
            coor[i].y = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }//将蛇头的位置继承给下一个蛇尾的位置，以此类推

        switch (dir)
        {
        case LEFT:
            coor[0].x-=speed;
            break;
        case RIGHT:
            coor[0].x+=speed;
            break;
        case UP:
            coor[0].y-=speed;
            break;
        case DOWN:
            coor[0].y+=speed;
            break;
        case 'x':
            gameover = true;
            break;
        default:
            break;
        }
        
	}
    void Logic()
    {
        
        if (coor[0].x >= width)
            coor[0].x = 0;
        else if (coor[0].x < 0)
            coor[0].x = width - 1;
        if (coor[0].y >= height)
            coor[0].y = 0;
        else if (coor[0].y < 0)
            coor[0].y = height - 1;

        for (int i = 1; i < size; i++)//如果蛇头的位置与尾巴的任意位置触碰，则gameover
            if ((abs(coor[0].x - coor[i].x) <= r) && (abs(coor[0].y - coor[i].y)<=r))
                gameover = true;
      
        if ((abs(coor[0].x - fruitx) <= fruitr)&&(abs(coor[0].y-fruity)<=fruitr))//吃到水果后尾巴长度＋1
        {
            score += 10;
            fruitx = disx(gen);
            fruity = disy(gen);
            size++;
        }
    }
    //打印提示信息
    void Tip()
    {
	static TCHAR str[64];
	_stprintf_s(str, _T("当前得分为:%d"), score);
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
    }
};
