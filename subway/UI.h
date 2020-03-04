#pragma once

#include<Windows.h>
#include<iostream>
#include<string>
#include<conio.h>
#include<stdio.h>
#include<sstream>
#include<vector>
#include "Dijkstra.h"

#define  TITLE  "地铁线路查询系统(请将终端最大化再使用)"
#define  TITLE  "地铁线路查询系统(请将终端最大化再使用)"
using namespace std;
//枚举keyboard的数值
enum
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};
//光标移动到（x，y）位置
void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//打印程序边框
void border()
{
	system("cls");
	gotoxy(45, 3);
	cout << "********************************************************************" << endl;
	gotoxy(45, 50);
	cout << "********************************************************************" << endl;
	for (int i = 4; i < 50; i++)
	{
		gotoxy(45, i);
		cout << "*                                                                  *" << endl;
	}
}
//菜单打印
void showmenu(HANDLE&hOut, int index, vector<string>menu)
{

	system("cls");
	border();
	gotoxy(45, 4);
	cout << "*                       欢迎使用地铁查询系统                       *" << endl;
	gotoxy(45, 6);
	cout << "*                    按方向键进行选择回车键确认                    *" << endl;
	gotoxy(45, 8);
	cout << "*                         按Esc即退出程序                          *" << endl;
	for (int i = 0; i < menu.size(); i++)
	{
		//index表示现在选择的是菜单的哪一项，默认为第一项
		//用户的输入（上下）会增减index
		if (i == index)
		{
			//用户现在选择的菜单项目，显示为蓝色 
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | 0x8);
			if (i == 0)gotoxy(73, (i + 20));
			else if (i == 1)gotoxy(73, (i + 40));
			cout << menu[i];
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			//其余菜单项目显示为白色
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (i == 0)gotoxy(73, (i + 20));
			else if (i == 1)gotoxy(73, (i + 40));
			cout << menu[i];
		}
	}
	gotoxy(1000, 100);
	//刷新标准输出缓冲区 
	fflush(stdout);
}
//菜单打印
void showline(HANDLE hOut, int index, vector<string>line)
{
	system("cls");
	border();
	for (int i = 0; i < line.size(); i++)
	{
		//index表示现在选择的是菜单的哪一项，默认为第一项
		//用户的输入（上下）会增减index
		if (i == index)
		{
			//用户现在选择的菜单项目，显示为蓝色 
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | 0x8);
			gotoxy(73, (i + 7));
			cout << line[i];
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			//其余菜单项目显示为白色
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		//	SetConsoleTextAttribute(hOut,BACKGROUND_RED |BACKGROUND_GREEN |BACKGROUND_BLUE |BACKGROUND_INTENSITY);
			gotoxy(73, (i + 7));
			cout << line[i];
		}
	}
	//刷新标准输出缓冲区 
	fflush(stdout);
}
//根据主菜单用户keyboard输入进行index的加减
int  get_userinput(int* index,int size)
{
	int ch;
	ch = _getch();
	switch (ch)
	{
		//键盘输入为↑方向键，index减少1
	case UP:
		if (*index > 0)
			--(*index);
		break;
		//键盘输入为↓方向键，index增加1
	case DOWN:
		if (*index < size -1 )
			++(*index);
		break;
	case ENTER: return ENTER;
	case ESC: return ESC;
	}
	return 0;
}

//打印所有站
void list_station_name(line stations) {
	//定义结构体
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//获取句柄设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	//设置光标不可见
	cci.bVisible = 0;
	//应用光标信息
	SetConsoleCursorInfo(hOut, &cci);
	border();
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int new_index = 0;
	int* p = &new_index;
	vector<line> lines = get_line();
	while (1) {
		gotoxy(75, 4);
		cout << stations.line_name;
		int m = 0;
		for (int i = 0; i < stations.all_station.size(); i++) {
			if (i % 3 == 0) {
				gotoxy(68, 2* m + 8);
				m++;
			}
			cout << stations.all_station[i].station_name;
			if (i < stations.all_station.size() - 1) {
				cout << "->";
			}
		}
		gotoxy(40, 7);
		int x = get_userinput(p, 0);
		if (x == ESC)break;
	}
}
//打印所有线路
void showline(vector<string> all_line) {
	//定义结构体
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//获取句柄设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	//设置光标不可见
	cci.bVisible = 0;
	//应用光标信息
	SetConsoleCursorInfo(hOut, &cci);
	border();
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int new_index = 0;
	int* p = &new_index;
	vector<line> lines = get_line();
	while (1) {
		showline(hOutput, *p, all_line);
		int x = get_userinput(p,all_line.size());
		if (x == ENTER) {
			//输出该线路所有的站点
			list_station_name(lines[*p]);
		}
		else if (x == ESC)break;
	}
}

//打印所有站
bool list_result(vector<station> result,string from,string to) {
	system("cls");
	//定义结构体
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//获取句柄设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	//设置光标不可见
	cci.bVisible = 0;
	//应用光标信息
	SetConsoleCursorInfo(hOut, &cci);
	border();
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int new_index = 0;
	int* p = &new_index;
	if (result.size() == 0) {
		gotoxy(70, 20);
		cout << "The station is not found";
		gotoxy(45, 36);
		system("pause");
		return false;
	}
	while (1) {
		gotoxy(65, 4);
		cout << "From " << from << " to " << to << ":";
		int m = 0;
		int line_count = 0;
		gotoxy(53, 6);
		cout << "From ";
		cout << result[0].line_name;
		cout << ":" << endl;
		for (int i = 0; i < result.size(); i++) {
			if (line_count % 5 == 0) {
				gotoxy(53, 2 * m + 8);
				m++;
			}
			cout << result[i].station_name;
			if (i < result.size() - 1 && result[i].line_name != result[i + 1].line_name) {
				gotoxy(53, 2 * m + 8);
				cout << "Transfer " << result[i + 1].line_name << ":";
				gotoxy(53, 2 * m + 10);
				m++;
				line_count = 0;
				continue;
			}
			if (i < result.size() - 1) {
				cout << "->";
			}
			line_count++;
		}
		gotoxy(40, 7);
		int x = get_userinput(p, 0);
		if (x == ESC)break;
	}
	return true;
}
//查询界面
void query() {
	//定义结构体
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//获取句柄设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	//设置光标不可见
	cci.bVisible = 0;
	//应用光标信息
	SetConsoleCursorInfo(hOut, &cci);
	border();
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int new_index = 0;
	int* p = &new_index;
	while (1) {
		gotoxy(70, 10);
		cout << "From:";
		gotoxy(70, 20);
		cout << "To:" << endl;
		string from, to;
		gotoxy(75, 10);
		cin >> from;
		gotoxy(73, 20);
		cin >> to;
		vector<station> res = get_result(from, to);
		if (list_result(res, from, to) == false) {
			break;
		}
		int x = get_userinput(p, 0);
		if (x == ESC)break;
	}
}
void test1() {
	//定义结构体
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//获取句柄设置为标准输出句柄 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取光标信息
	GetConsoleCursorInfo(hOut, &cci);
	//设置光标大小   
	cci.dwSize = 1;
	//设置光标不可见
	cci.bVisible = 0;
	//应用光标信息
	SetConsoleCursorInfo(hOut, &cci);
	border();
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<string> menu;
	int new_index = 0;
	int* p = &new_index;
	menu.push_back("地铁线网查询");
	menu.push_back("  出行导航");
	while (1) {
		showmenu(hOutput, *p, menu);
		int x = get_userinput(p,menu.size());
		if (x == ENTER) {
			//用户界面 
			if (*p == 0) {
				vector<string> temp = get_line_name();
				showline(temp);

			}
			else if (*p == 1) {
				query();
			}
		}
		else if (x == ESC)break;
	}
		gotoxy(5, 100);
}
