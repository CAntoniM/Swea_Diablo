#include "UI.h"
#include "Quick functions.h"
#include <Windows.h>
#include "Enemy.h"
#include "Enums.h"


void UI::DrawFrame()
{
	SetCursorPosition(0, 0);
	for (int y = 0; y < MenuOptions::frameSizeEndY; y++)
	{
		for (int x = 0; x < MenuOptions::frameSizeEndX; x++)
		{
			if (y == MenuOptions::frameSizeStartY || y == MenuOptions::frameSizeEndY - 1 || y == MenuOptions::screenSeperatorY)
			{
				SetCursorPosition(x, y);
				std::cout << "-";
			}
			else if (x == MenuOptions::frameSizeStartX || x == MenuOptions::frameSizeEndX - 1)
			{
				SetCursorPosition(x, y);
				std::cout << "|";
			}
		}
	}
	std::cout << std::endl;
}


void UI::MenuControll(std::string aMenuList[], int aMenuSize, int aPlayerChoiseInMenu, int aStartingYPosision)
{
	for (int i = 0; i < aMenuSize; ++i)
	{
		if (i == aPlayerChoiseInMenu)
		{
			SetColor(ColorInt::GreenColorText);
			std::cout << "\t" << aMenuList[i] << "\t <---" << std::endl;
		}
		else
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			if (GetConsoleScreenBufferInfo(hConsole, &csbi))
			{
				COORD cursorPosition = csbi.dwCursorPosition;
				int x = cursorPosition.X + 1;
				int y = cursorPosition.Y;
				SetCursorPosition(x, y);
			}
			SetColor(ColorInt::WhiteColorText);
			std::cout << aMenuList[i] << std::endl;
		}
	}
	SetColor(ColorInt::WhiteColorText);
}

void UI::ShowEnemy(std::vector<Enemy>& aList)
{
	ClearGame();
	int ofSetX = 3;
	for (int i = 0; i < aList.size(); i++)
	{
		if (aList[i].GetIsAlive() == true)
		{
			aList[i].PrintEnemySprite(gameStartX + ofSetX, gameStartY + 2);
			ofSetX += aList[i].GetSpriteSizeX() + 10;
		}
		else
		{
			ofSetX += aList[i].GetSpriteSizeX() + 10;
		}

	}
}

int UI::ChoseEnemy(std::vector<Enemy>& aList)
{
	bool missingTarget = true;
	int playerChoise = 0;
	while (true)
	{
	
		int ofSetX = 3;
		for (int i = 0; i < aList.size(); i++)
		{
			if (i == playerChoise)
			{
				aList[i].ShowTarget(gameStartX + ofSetX, gameStartY + 2, true);
			
			}
			else
			{
				aList[i].ShowTarget(gameStartX + ofSetX, gameStartY + 2, false);
			}	
			ofSetX += aList[i].GetSpriteSizeX() + 10;
			
		}

		switch (ButtonPress())
		{
		case MenuOptions::MenuListLeft:
		{
			if (playerChoise > 0)
			{
				playerChoise--;
			}
			else
			{
				playerChoise = static_cast<int>(aList.size()) - 1;
			}
			break;
		}
		case MenuOptions::MenuListRight:
		{
			if (playerChoise < static_cast<int>(aList.size()) - 1)
			{
				playerChoise++;
			}
			else
			{
				playerChoise = 0;
			}
			break;
		}
		case MenuOptions::MenuListOption:
		{
			if (aList[playerChoise].GetIsAlive() == true)
			{
				return playerChoise;
			}
			else
			{
				if (missingTarget == true)
				{
					ClearMenu();
					PrintInMenu("There is no monster there, try again!");
					Sleep();
					missingTarget = false;
				}

			}
			break;
		}
		}
	}

}