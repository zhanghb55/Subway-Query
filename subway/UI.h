#pragma once

#include<Windows.h>
#include<iostream>
#include<string>
#include<conio.h>
#include<stdio.h>
#include<sstream>
#include<vector>
#include "Dijkstra.h"

#define  TITLE  "������·��ѯϵͳ(�뽫�ն������ʹ��)"
#define  TITLE  "������·��ѯϵͳ(�뽫�ն������ʹ��)"
using namespace std;
//ö��keyboard����ֵ
enum
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	ENTER = 13,
	ESC = 27,
};
//����ƶ�����x��y��λ��
void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

//��ӡ����߿�
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
//�˵���ӡ
void showmenu(HANDLE&hOut, int index, vector<string>menu)
{

	system("cls");
	border();
	gotoxy(45, 4);
	cout << "*                       ��ӭʹ�õ�����ѯϵͳ                       *" << endl;
	gotoxy(45, 6);
	cout << "*                    �����������ѡ��س���ȷ��                    *" << endl;
	gotoxy(45, 8);
	cout << "*                         ��Esc���˳�����                          *" << endl;
	for (int i = 0; i < menu.size(); i++)
	{
		//index��ʾ����ѡ����ǲ˵�����һ�Ĭ��Ϊ��һ��
		//�û������루���£�������index
		if (i == index)
		{
			//�û�����ѡ��Ĳ˵���Ŀ����ʾΪ��ɫ 
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | 0x8);
			if (i == 0)gotoxy(73, (i + 20));
			else if (i == 1)gotoxy(73, (i + 40));
			cout << menu[i];
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			//����˵���Ŀ��ʾΪ��ɫ
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (i == 0)gotoxy(73, (i + 20));
			else if (i == 1)gotoxy(73, (i + 40));
			cout << menu[i];
		}
	}
	gotoxy(1000, 100);
	//ˢ�±�׼��������� 
	fflush(stdout);
}
//�˵���ӡ
void showline(HANDLE hOut, int index, vector<string>line)
{
	system("cls");
	border();
	for (int i = 0; i < line.size(); i++)
	{
		//index��ʾ����ѡ����ǲ˵�����һ�Ĭ��Ϊ��һ��
		//�û������루���£�������index
		if (i == index)
		{
			//�û�����ѡ��Ĳ˵���Ŀ����ʾΪ��ɫ 
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | 0x8);
			gotoxy(73, (i + 7));
			cout << line[i];
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		else
		{
			//����˵���Ŀ��ʾΪ��ɫ
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		//	SetConsoleTextAttribute(hOut,BACKGROUND_RED |BACKGROUND_GREEN |BACKGROUND_BLUE |BACKGROUND_INTENSITY);
			gotoxy(73, (i + 7));
			cout << line[i];
		}
	}
	//ˢ�±�׼��������� 
	fflush(stdout);
}
//�������˵��û�keyboard�������index�ļӼ�
int  get_userinput(int* index,int size)
{
	int ch;
	ch = _getch();
	switch (ch)
	{
		//��������Ϊ���������index����1
	case UP:
		if (*index > 0)
			--(*index);
		break;
		//��������Ϊ���������index����1
	case DOWN:
		if (*index < size -1 )
			++(*index);
		break;
	case ENTER: return ENTER;
	case ESC: return ESC;
	}
	return 0;
}

//��ӡ����վ
void list_station_name(line stations) {
	//����ṹ��
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//��ȡ�������Ϊ��׼������ 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С   
	cci.dwSize = 1;
	//���ù�겻�ɼ�
	cci.bVisible = 0;
	//Ӧ�ù����Ϣ
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
//��ӡ������·
void showline(vector<string> all_line) {
	//����ṹ��
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//��ȡ�������Ϊ��׼������ 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С   
	cci.dwSize = 1;
	//���ù�겻�ɼ�
	cci.bVisible = 0;
	//Ӧ�ù����Ϣ
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
			//�������·���е�վ��
			list_station_name(lines[*p]);
		}
		else if (x == ESC)break;
	}
}

//��ӡ����վ
bool list_result(vector<station> result,string from,string to) {
	system("cls");
	//����ṹ��
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//��ȡ�������Ϊ��׼������ 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С   
	cci.dwSize = 1;
	//���ù�겻�ɼ�
	cci.bVisible = 0;
	//Ӧ�ù����Ϣ
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
//��ѯ����
void query() {
	//����ṹ��
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//��ȡ�������Ϊ��׼������ 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С   
	cci.dwSize = 1;
	//���ù�겻�ɼ�
	cci.bVisible = 0;
	//Ӧ�ù����Ϣ
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
	//����ṹ��
	CONSOLE_CURSOR_INFO cci;
	int ret;
	int index = 0;
	HANDLE hOut;
	SetConsoleTitleA(TITLE);
	//��ȡ�������Ϊ��׼������ 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С   
	cci.dwSize = 1;
	//���ù�겻�ɼ�
	cci.bVisible = 0;
	//Ӧ�ù����Ϣ
	SetConsoleCursorInfo(hOut, &cci);
	border();
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<string> menu;
	int new_index = 0;
	int* p = &new_index;
	menu.push_back("����������ѯ");
	menu.push_back("  ���е���");
	while (1) {
		showmenu(hOutput, *p, menu);
		int x = get_userinput(p,menu.size());
		if (x == ENTER) {
			//�û����� 
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
