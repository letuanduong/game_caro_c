#pragma once
#include <Windows.h>
#include <iostream>

class Cursor
{
	HANDLE handle;
public:
	static Cursor Dedault;
public:
	Cursor(HANDLE handle = 0) 
	{
		if (handle == 0)
			handle = GetStdHandle(STD_OUTPUT_HANDLE);
		this->handle = handle;
	}
	void Show()
	{
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo(handle, &info);
		info.bVisible = true;
		SetConsoleCursorInfo(handle, &info);
	}
	void Hide()
	{
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo(handle, &info);
		info.bVisible = false;
		SetConsoleCursorInfo(handle, &info);
	}
	void MoveTo(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(handle, coord);
	}
	void Put(char c)	{std::cout << c;	}
	void Put(char *s){std::cout << s;}
	void Put(int value){std::cout << char(value);}
};

