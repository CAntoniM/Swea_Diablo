#pragma once
#include "Quick functions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include "Enemy.h"
#include "Enums.h"

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ENTER 13
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77

void Clear()
{
	system("cls");
}
void Pause()
{
	system("Pause>0");
}
void Sleep(int miliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	while (_kbhit())
	{
		_getch();
	}
}
void Print(std::string aString)
{
	std::cout << aString << std::endl;
}
void PrintInMenu(std::string aString)
{
	int row = 0;
	std::string printOutStringPart = aString;
	std::string tempString;

	ClearMenu();

	while (printOutStringPart.size() > static_cast<int>(MenuOptions::StatsSeperatorX) - 2)
	{
		if (aString.size() > static_cast<int>(MenuOptions::StatsSeperatorX) - 2)
		{
			std::string::size_type split = printOutStringPart.rfind(' ', static_cast<int>(MenuOptions::StatsSeperatorX) - 2);
			SetCursorPosition(static_cast<int>(MenuOptions::menyStartX), static_cast<int>(MenuOptions::menyStartY) + row);
			std::cout << printOutStringPart.substr(0, split) << std::endl;
			printOutStringPart.erase(0, split + 1);
			row++;
		}
	}
	
	SetCursorPosition(static_cast<int>(MenuOptions::menyStartX), static_cast<int>(MenuOptions::menyStartY) + row);
	std::cout << printOutStringPart << std::endl;
}


void ClearArea(int anX, int anY, int aXLength, int aYLength)
{
	for (int y = 0; y < aYLength; y++)
	{
		for (int x = 0; x < aXLength; x++)
		{
			SetCursorPosition(anX + x, anY + y);
			Print(" ");
		}
	}

}

void ClearGame()
{
	for (int y = 1; y < static_cast<int>(MenuOptions::ScreenSeperatorY); y++)
	{
		for (int x = 1; x < static_cast<int>(MenuOptions::FrameSizeEndX) - 1; x++)
		{
			SetCursorPosition(x, y);
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

void ClearMenu()
{
	for (int y = static_cast<int>(MenuOptions::ScreenSeperatorY) + 1; y < static_cast<int>(MenuOptions::FrameSizeEndY) - 1; y++)
	{
		for (int x = 1; x < static_cast<int>(MenuOptions::StatsSeperatorX) - 1; x++)
		{
			SetCursorPosition(x, y);
			std::cout << " ";
		}
	}
}



void SetColor(ColorInt aColor)
{
	switch (aColor)
	{
	case ColorInt::GreenColorText:
	{
		std::cout << "\x1B[32m";
		break;
	}
	case ColorInt::WhiteColorText:
	{
		std::cout << "\x1B[37m";
		break;
	}
	case ColorInt::RedColorText:
	{
		std::cout << "\x1B[31m";
		break;
	}
	case ColorInt::LightGrayColorText:
	{
		std::cout << "\x1B[90m";
		break;
	}
	default:
	{
		std::cout << "\x1B[37m";
		break;
	}
	}
}
void SetCursorPosition(int aX, int aY)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)aX, (SHORT)aY };
	SetConsoleCursorPosition(hConsole, coord);
}

int DamageAdjustment(int setDamage)
{
	 return static_cast<int>(setDamage * RandomFloatNumber(0.8, 1.2) + 0.5);
}

double RandomFloatNumber(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(min, max);  

	return distrib(gen);
}
int RandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

MenuOptions ButtonPress()
{
    int button = 0;
    while (true)
    {
        button = _getch();
        if (button == 0 || button == 224)
        {
            switch (_getch())
            {
            case KEY_ARROW_UP:
            {
                return MenuOptions::MenuListUp;
                break;
            }
            case KEY_ARROW_DOWN:
            {
                return MenuOptions::MenuListDown;
                break;
            }
            case KEY_ARROW_LEFT:
            {
                return MenuOptions::MenuListLeft;
                break;
            }
            case KEY_ARROW_RIGHT:
            {
                return MenuOptions::MenuListRight;
                break;
            }
            }
        }
        else
        {
            if (button == KEY_W)
            {
                return MenuOptions::MenuListUp;
            }
            else if (button == KEY_S)
            {
                return MenuOptions::MenuListDown;
            }
            else if (button == KEY_A)
            {
                return MenuOptions::MenuListLeft;
            }
            else if (button == KEY_D)
            {
                return MenuOptions::MenuListRight;
            }
            else if (button == KEY_ENTER)
            {
                return MenuOptions::MenuListOption;
            }
        }
    }
}

void FlipCursorVisibility(bool aSetCursor)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = aSetCursor;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}