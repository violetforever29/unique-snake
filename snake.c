#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#include"time.h"
#include"sneak.h"
#pragma comment(lib,"winmm.lib")
#pragma warning(disable: 4129)
void game_main_body();
void HideCursor();
void Goto_Coord(int x, int y);
void Area_Show();
void introduction();
void Open_page();
void choose_model();
void self_defined();
void rand_sneak();
void draw_sneak();
void move();
void destroy_sneak();
void change_dir();
void pro_food();
void sneak_grow();
void count_point();
bool sneak_die();
void null_well();
void game_setting();
int main(void)
{
	int a = 1;
	system("mode con cols=115 lines=36");
	HideCursor();
	PlaySound(L"bgm.wav", NULL, SND_FILENAME | SND_ASYNC);
    Open_page();
	system("cls");
	choose_model();
	
	game_main_body();

	//system("pause");
	return 0;
}
//游戏运行主体
void game_main_body()
{
	system("cls");
	rand_sneak();

	while (1)
	{
		pro_food();

		game_setting();

		move();
		draw_sneak();

		Area_Show();

		change_dir();
		sneak_grow();
		if (false == sneak_die())
		{
			system("cls");
			printf("    \n\n\t\t\t\t\t     =====================\n\n\t\t\t\t\t           游戏结束 !!!\n\n\t\t\t\t\t  【=======================】\n\n\n\n\n");
			printf("\n\t\t\t\t\t     =====================\n\n\t\t\t\t\t        你的分数为 %d 分\n\n\t\t\t\t\t  【=======================】\n\n\n\n\n\n\n\n\n\n\n\n\n\n", score);
			PlaySound(L"die_sneak.wav", NULL, SND_FILENAME | SND_ASYNC);
			system("pause");
			if ('k' == _getch())
			{
				game_main_body();
				food = true;
			}
			else break;
		}

		count_point();
		Sleep(80);
	}
}





//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}
//光标坐标
void Goto_Coord(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}
//画地图
void Area_Show()
{
	//参数表示x,y的坐标
	int num;
	for (num = 0; num <= 60; num += 2)
	{
		Goto_Coord(num, 0);
		printf("■");
		Goto_Coord(num, 30);
		printf("■");
	}
	for (num = 0; num <= 30; num++)
	{
		Goto_Coord(0, num);
		printf("■");
		Goto_Coord(60, num);
		printf("■");
	}
}
void Open_page()
{
	printf("\n\n\n\n\t\t\t\t\t\t【 贪  吃  蛇 】\n\n\n\n\n\n\n");
	/*char open_input;*/
	
	int i, j;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 24; j++)
		{
			if (background[i][j] == 1)
				printf("■");
			else if (background[i][j] == 2)
				printf("★");
			else printf("  ");
		}
		printf("\n");
	}
	introduction();
	
	/*while (1)
	{
		open_input = _getch();
		if (' ' == open_input)
			break;
	}*/

}
void introduction()
{
	Goto_Coord(69, 12);
	printf("      游戏说明:\n\n\n\t\t\t\t\t\t\t\t\tWASD控制蛇的方向\n\n\t\t\t\t\t\t\t\t\t\  空格进入游戏\n\n\n\t\t\t\t\t\t\t\t\t\ P  暂停 / 开始\n\n\t\t\t\t\t\t\t\t\t\
 M  开 / 关音乐\n\n\t\t\t\t\t\t\t\t\t\ Y   显示说明");
	
	while (1)
	{
		if (GetAsyncKeyState(' '))
			break;
		Goto_Coord(73, 28);
		printf("-= 开始游戏 =-");
		if (GetAsyncKeyState(' '))
			break;
		Sleep(800);
		Goto_Coord(73, 28);
		printf("                           ");
		if (GetAsyncKeyState(' '))
			break;
		Sleep(800);		
	}
}

//选择模式
void choose_model()
{
	
	char a;
	Goto_Coord(47, 4);
	printf(" 请选择你的模式");

	Goto_Coord(50, 8);
	printf(" 经典模式");
	Goto_Coord(50, 11);
	printf(" 无尽模式");
	Goto_Coord(50, 14);
	printf("自定义模式");

	Goto_Coord(46, 8 + 3* model);
	printf("◆");
	while (1)
	{
		if (model == 0)
		{
			Goto_Coord(46, 24);
			printf("有墙壁，不能咬自己");
		}

		a = _getch();

		if ('s' == a || 'w' == a)
		{
			Goto_Coord(37, 24);
			printf("                                                  ");
		}
		if ('s' == a && model <=1)
		{
			Goto_Coord(46, 8 +3* model);
			printf("  ");
			model++;
			Goto_Coord(46, 8 + 3* model);
			printf("◆");	
		}
		else if ('w' == a && model >= 1)
		{
			Goto_Coord(46, 8 + 3* model);
			printf("  ");
			model--;
			Goto_Coord(46, 8 + 3* model);
			printf("◆");
		}
		if (model == 0)
		{
			Goto_Coord(46, 24);
			printf("有墙壁，不能咬自己 ");
		}
		if (model == 1)
		{
			Goto_Coord(37, 24 );
			printf("没有墙壁限制，可自由穿梭，永远不会死亡。");
		}
		if (model == 2)
		{
			Goto_Coord(44, 24);
			printf("自定义墙壁墙壁限制，死亡。");
		}


		if ('j' == a)
			break;

	}

}


//生成随机蛇
void rand_sneak()
{
	int x = 0, y = 0;
	srand((unsigned int)time(NULL));//种子
	x = rand() % 27+1;
	y = rand() % 27 + 1;
	//蛇头
	sneak_body[0][0] = 2 * x;
	sneak_body[0][1] = y;
	sneak_body[0][2] = to_west;

	sneak_body[1][0] = 2 * x + 2;
	sneak_body[1][1] = y;
	sneak_body[1][2] = to_west;

	sneak_body[2][0] = 2 * x + 4;
	sneak_body[2][1] = y;
	sneak_body[2][2] = to_west;
}
//画蛇
void draw_sneak()
{
	int i;
	for (i = 0; sneak_body[i][0] != 0; i++)
	{
		Goto_Coord(sneak_body[i][0], sneak_body[i][1]);
		printf("■");
	}
}
//蛇移动
void move()
{
	destroy_sneak();
	int i = sneak_length - 1 ;
	for (i = sneak_length - 1; i >= 1; i--)
	{
		if (sneak_body[i][0] == 0)
		{
			continue;
		}
		sneak_body[i][0] = sneak_body[i - 1][0];
		sneak_body[i][1] = sneak_body[i - 1][1];
		sneak_body[i][2] = sneak_body[i - 1][2];
	}
	sneak_body[0][2] = sneak_direction;
	if (to_west == sneak_body[0][2] || to_east == sneak_body[0][2])
	{
		sneak_body[0][0] += sneak_body[0][2];
	}
	else sneak_body[0][1] += sneak_body[0][2];

	if(model==1)
		null_well();

	draw_sneak();
}
//清除残留
void destroy_sneak()
{
	int i;
	for (i = 0; sneak_body[i][0] != 0; i++)
	{
		Goto_Coord(sneak_body[i][0], sneak_body[i][1]);
		printf("  ");
	}
}
//改变方向
void change_dir()
{
	if (GetAsyncKeyState('W') && (sneak_body[0][2] != to_north && sneak_body[0][2] != to_south))
	{
		sneak_direction = to_north;
	}
	else if (GetAsyncKeyState('A') && (sneak_body[0][2] != to_east && sneak_body[0][2] != to_west))
	{
		sneak_direction = to_west;
	}
	else if (GetAsyncKeyState('S') && (sneak_body[0][2] != to_north && sneak_body[0][2] != to_south))
	{
		sneak_direction = to_south;
	}
	else if (GetAsyncKeyState('D') && (sneak_body[0][2] != to_east && sneak_body[0][2] != to_west))
	{
		sneak_direction = to_east;
	}

}
//产生食物
void pro_food()
{
	int i;
	srand((unsigned int)time(NULL));
	//是否产生食物
	if (food == false)
	{
		return;
	}
	while (1)
	{
		bool ref = true;
		fx = rand() % 28 + 1;
		fy = rand() % 28 + 1;
		for (i = 0; sneak_body[i][0] != 0; i++)
		{
			if (sneak_body[i][0] == 2 * fx && sneak_body[i][1] == fy)
			{
				ref = false;
				break;
			}
		}
		if (ref == true)
			break;
	}
	Goto_Coord(2 * fx, fy);
	printf("★");
	food = false;
}
//蛇长长
void sneak_grow()
{
	if (sneak_body[0][0] == 2 * fx && sneak_body[0][1] == fy)
	{
		if (to_east == sneak_body[sneak_long][2])
		{
			sneak_body[sneak_long + 1][0] = sneak_body[sneak_long][0];
			sneak_body[sneak_long + 1][1] = sneak_body[sneak_long][0] - 2;
			sneak_body[sneak_long + 1][2] = sneak_body[sneak_long][0];
		}
		if (to_west == sneak_body[sneak_long][2])
		{
			sneak_body[sneak_long + 1][0] = sneak_body[sneak_long][0];
			sneak_body[sneak_long + 1][1] = sneak_body[sneak_long][0] + 2;
			sneak_body[sneak_long + 1][2] = sneak_body[sneak_long][0];
		}
		if (to_north == sneak_body[sneak_long][2])
		{
			sneak_body[sneak_long + 1][0] = sneak_body[sneak_long][0];
			sneak_body[sneak_long + 1][1] = sneak_body[sneak_long][0] + 1;
			sneak_body[sneak_long + 1][2] = sneak_body[sneak_long][0];
		}
		if (to_south == sneak_body[sneak_long][2])
		{
			sneak_body[sneak_long + 1][0] = sneak_body[sneak_long][0];
			sneak_body[sneak_long + 1][1] = sneak_body[sneak_long][0] - 1;
			sneak_body[sneak_long + 1][2] = sneak_body[sneak_long][0];
		}
		sneak_long++;
		food = true;
		score++;
	}
}
//计分
void count_point()
{
	COORD rd;
	rd.X = 26;
	rd.Y = 32;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("分数：  ");
	Goto_Coord(32, 32);
	printf("%d", score);
	Goto_Coord(0, 32);
}
//判断死亡
bool sneak_die()
{
	int i;
	bool bite_tail = false;
	bool knock_wall = sneak_body[0][0] == 0 || sneak_body[0][0] == 60 || sneak_body[0][1] == 0 || sneak_body[0][1] == 30;
	for (i = 4; i <200; i++)
	{
		if (sneak_body[0][0] == sneak_body[i][0] && sneak_body[0][1] == sneak_body[i][1])
		{
			bite_tail = true;;
			break;
		}
		else bite_tail = false;
	}

	if (model == 0 && (knock_wall==true || bite_tail == true))
		return false;
	else return true;
}
//穿墙、无边界
void null_well()
{
	if (sneak_body[0][0] == 0)
		sneak_body[0][0] = 58;
	if (sneak_body[0][0] == 60)
		sneak_body[0][0] = 2;
	if (sneak_body[0][1] == 0)
		sneak_body[0][1] = 29;
	if (sneak_body[0][1] == 30)
		sneak_body[0][1] = 1;
}
//暂停


void game_setting()
{
	//暂停
	while (GetAsyncKeyState('P'))
	{
		printf("暂停\n\n");
		system("pause");
		system("cls");
		Goto_Coord(2 * fx, fy);
		printf("★");
		if (GetAsyncKeyState('P'))
		{
			break;
		}
	}

	//游戏说明
	while (GetAsyncKeyState('Y'))
	{
		Goto_Coord(71, 5);
		printf("        游戏说明:\n\n\n\t\t\t\t\t\t\t\t\t    WASD控制蛇的方向\n\n\t\t\t\t\t\t\t\t\t\     P  暂停 / 开始\n\n\t\t\t\t\t\t\t\t\t\     M  开 / 关音乐\n\n\n\t\t\t\t\t\t\t\t       \t    ");
		system("pause");
		system("cls");
		Goto_Coord(2 * fx, fy);
		printf("★");
		if (GetAsyncKeyState('Y'))
			break;
	}

}

void self_defined()
{
	//......
}

